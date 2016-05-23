/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
 *
 *    Contributed by Qualcomm Connected Experiences, Inc.,
 *    with authorization from the AllSeen Alliance, Inc.
 *    
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *    
 *        http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *    
 *    Pursuant to Section 1 of the License, the work of authorship constituting
 *    a Work and any Contribution incorporated in the Work shall mean only that
 *    Contributor's code submissions authored by that Contributor.  Any rights
 *    granted under the License are conditioned upon acceptance of these
 *    clarifications.
 ******************************************************************************/

#import "LSFWifiMonitor.h"
#import "LSFConstants.h"
#import "LSFAllJoynManager.h"
#import "LSFDispatchQueue.h"

#import <arpa/inet.h>
#import <ifaddrs.h>
#import <netdb.h>
#import <sys/socket.h>
#import <CoreFoundation/CoreFoundation.h>

@interface LSFWifiMonitor()

@property (nonatomic, strong) NSString *lastKnownSSID;

-(void)startController;
-(void)stopController;

@end

/*
 * Static functions to serve as reachability callback and print flags
 */
static void NetworkStatusCallback(SCNetworkReachabilityRef target, SCNetworkReachabilityFlags flags, void* info)
{
    NSLog(@"LSFWifiMonitor - NetworkStatusCallback() executing");
    [[LSFWifiMonitor getWifiMonitor] checkCurrentStatus];
}

@implementation LSFWifiMonitor
{
	SCNetworkReachabilityRef _nrr;
}

@synthesize isWifiConnected = _isWifiConnected;
@synthesize lastKnownSSID = _lastKnownSSID;

+(id)getWifiMonitor
{
    static LSFWifiMonitor *wifiMonitor = nil;
    static dispatch_once_t onceToken;

    dispatch_once(&onceToken, ^{
        wifiMonitor = [[self alloc] init];
    });

    return wifiMonitor;
}

-(id)init
{
    self = [super init];

    if (self)
    {
        self.lastKnownSSID = @"";

        struct sockaddr_in localWifiAddress;
        bzero(&localWifiAddress, sizeof(localWifiAddress));
        localWifiAddress.sin_len = sizeof(localWifiAddress);
        localWifiAddress.sin_family = AF_INET;
        localWifiAddress.sin_addr.s_addr = htonl(IN_LINKLOCALNETNUM);

        _nrr = SCNetworkReachabilityCreateWithAddress(kCFAllocatorDefault, (const struct sockaddr *)&localWifiAddress);

        if ([self currentNetworkStatus] == NotReachable)
        {
            NSLog(@"Wifi Disconnected at startup");
            self.isWifiConnected = NO;
            self.lastKnownSSID = @"";
        }
        else
        {
            NSLog(@"Wifi Connected at startup. Last Known SSID = %@", [[LSFConstants getConstants] currentWifiSSID]);
            self.isWifiConnected = YES;
            self.lastKnownSSID = [[LSFConstants getConstants] currentWifiSSID];

            [self startController];
        }

        BOOL monitorStartSuccess = [self startMonitoringWifi];
        NSLog(@"Starting to monitor wifi return %@", monitorStartSuccess ? @"success" : @"fail");
    }

    return self;
}

-(void)dealloc
{
    [self stopMonitoringWifi];

	if (_nrr != NULL)
	{
		CFRelease(_nrr);
	}
}

-(BOOL)startMonitoringWifi
{
    BOOL successful = NO;
	SCNetworkReachabilityContext context = {0, (__bridge void *)(self), NULL, NULL, NULL};

	if (SCNetworkReachabilitySetCallback(_nrr, NetworkStatusCallback, &context))
	{
		if (SCNetworkReachabilityScheduleWithRunLoop(_nrr, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode))
		{
			successful = YES;
		}
	}

	return successful;
}

-(void)stopMonitoringWifi
{
    if (_nrr != NULL)
	{
		SCNetworkReachabilityUnscheduleFromRunLoop(_nrr, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
	}
}

-(void)checkCurrentStatus
{
    NetworkConnectionStatus ncs = [self currentNetworkStatus];

    if (ncs == NotReachable && self.isWifiConnected)
    {
        NSLog(@"Wifi Disconnected");
        self.isWifiConnected = NO;
        self.lastKnownSSID = @"";
        [self stopController];

        [[NSNotificationCenter defaultCenter] postNotificationName: @"WifiNotification" object: self];
    }
    else
    {
        NSLog(@"Wifi Connected. Last Known SSID = %@. Current SSID = %@", self.lastKnownSSID, [[LSFConstants getConstants] currentWifiSSID]);

        if ([[LSFConstants getConstants] currentWifiSSID] == nil)
        {
            NSLog(@"Current Wi-Fi SSID is nil just calling stop");
            [self stopController];
        }
        else
        {
            if (![self.lastKnownSSID isEqualToString: [[LSFConstants getConstants] currentWifiSSID]])
            {
                NSLog(@"SSID has changed. Resetting Controller.");
                //[self stopController];
                [self startController];
            }
        }

        self.isWifiConnected = YES;
        self.lastKnownSSID = [[LSFConstants getConstants] currentWifiSSID];

        [[NSNotificationCenter defaultCenter] postNotificationName: @"WifiNotification" object: self];
    }
}

-(NetworkConnectionStatus)currentNetworkStatus
{
    NetworkConnectionStatus ncs = NotReachable;
    SCNetworkReachabilityFlags flags;

    if (SCNetworkReachabilityGetFlags(_nrr, &flags))
    {
        if ((flags & kSCNetworkReachabilityFlagsReachable) && (flags & kSCNetworkReachabilityFlagsIsDirect))
        {
            ncs = ReachableViaWiFi;
        }
    }

    return ncs;
}

/*
 * Private Functions
 */
-(void)startController
{
    LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];

    ControllerClientStatus status = [ajManager.lsfControllerClient start];

    if (status == CONTROLLER_CLIENT_ERR_RETRY)
    {
        NSLog(@"Controller Client start return retry. Retrying 5 seconds later");
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5 * NSEC_PER_SEC)), ([LSFDispatchQueue getDispatchQueue]).queue, ^{
            [self startController];
        });
    }
    else if (status == CONTROLLER_CLIENT_OK)
    {
        [ajManager.aboutManager registerAnnouncementHandler];
        NSLog(@"Controller Client started successfully");
    }
}

-(void)stopController
{
    LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
    [ajManager.aboutManager unregisterAnnouncementHandler];

    ControllerClientStatus status = [ajManager.lsfControllerClient stop];

    if (status == CONTROLLER_CLIENT_OK)
    {
        NSLog(@"Controller Client stop returned ok");
    }
    else
    {
        NSLog(@"Controller Client stop returned some type of error");
    }
}

@end
