////////////////////////////////////////////////////////////////////////////////
// Copyright AllSeen Alliance. All rights reserved.
//
//    Contributed by Qualcomm Connected Experiences, Inc.,
//    with authorization from the AllSeen Alliance, Inc.
//    
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//    
//        http://www.apache.org/licenses/LICENSE-2.0
//    
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//    
//    Pursuant to Section 1 of the License, the work of authorship constituting
//    a Work and any Contribution incorporated in the Work shall mean only that
//    Contributor's code submissions authored by that Contributor.  Any rights
//    granted under the License are conditioned upon acceptance of these
//    clarifications.
////////////////////////////////////////////////////////////////////////////////

#import "ViewController.h"
#import "AJNClientController.h"
#import "AJNInterfaceDescription.h"
#import "FileTransferObject.h"
#import "Constants.h"
#import <alljoyn/Message.h>
#import "AJNMessageArgument.h"

@interface AJNMessageArgument(Private)

/**
 * Helper to return the C++ API object that is encapsulated by this objective-c class
 */
@property (nonatomic, readonly) ajn::MsgArg *msgArg;

@end


@interface ViewController () <AJNClientDelegate, FileTransferDelegateSignalHandler>

@property (nonatomic, strong) FileTransferObjectProxy *fileTransferObjectProxy;
@property (nonatomic, strong) AJNClientController *clientController;
@property (nonatomic, strong) dispatch_queue_t receiveFileTransferQueue;
@property (nonatomic, strong) NSFileHandle *receivedFile;
@property NSUInteger totalBytesReceived;

- (AJNProxyBusObject *)proxyObjectOnBus:(AJNBusAttachment *)bus inSession:(AJNSessionId)sessionId;
- (void)shouldUnloadProxyObjectOnBus:(AJNBusAttachment *)bus;

- (void)didStartBus:(AJNBusAttachment *)bus;

@end

@implementation ViewController

@synthesize fileTransferObjectProxy = _fileTransferObjectProxy;
@synthesize startButton = _startButton;
@synthesize clientController = _clientController;
@synthesize handle = _handle;

- (NSString *)applicationName
{
    return kAppName;
}

- (NSString *)serviceName
{
    return kServiceName;
}

- (AJNBusNameFlag)serviceNameFlags
{
    return kAJNBusNameFlagDoNotQueue | kAJNBusNameFlagReplaceExisting;
}

- (AJNSessionPort)sessionPort
{
    return kServicePort;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    // allocate the client bus controller and set bus properties
    //
    self.clientController = [[AJNClientController alloc] init];
    self.clientController.trafficType = kAJNTrafficMessages;
    self.clientController.proximityOptions = kAJNProximityAny;
    self.clientController.transportMask = kAJNTransportMaskAny;
    self.clientController.allowRemoteMessages = YES;
    self.clientController.multiPointSessionsEnabled = YES;
    self.clientController.delegate = self;
    self.receiveFileTransferQueue = dispatch_queue_create("org.alljoyn.samples.fileTransfer.receive", NULL);
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)didTouchStartButton:(id)sender
{
    self.totalBytesReceived = 0;
    self.eventsTextView.text = nil;
    
    if (self.clientController.bus.isStarted) {
        [self.clientController stop];
        [self.startButton setTitle:@"Start" forState:UIControlStateNormal];
    }
    else {
        [self.clientController start];
        [self.startButton setTitle:@"Stop" forState:UIControlStateNormal];
    }    
}

#pragma mark - Client Controller implementation

- (void)shouldUnloadProxyObjectOnBus:(AJNBusAttachment *)bus
{
    self.fileTransferObjectProxy = nil;
    [self.startButton setTitle:@"Start" forState:UIControlStateNormal];
}

- (AJNProxyBusObject *)proxyObjectOnBus:(AJNBusAttachment *)bus inSession:(AJNSessionId)sessionId
{
    self.fileTransferObjectProxy = [[FileTransferObjectProxy alloc] initWithBusAttachment:bus serviceName:self.serviceName objectPath:kServicePath sessionId:sessionId];
    
    return self.fileTransferObjectProxy;
}

- (void)didStartBus:(AJNBusAttachment *)bus
{
    // register our signal handler
    //
    AJNInterfaceDescription *interfaceDescription;
    
    
    //
    // FileTransferDelegate interface (org.alljoyn.bus.samples.fileTransfer)
    //
    // create an interface description, or if that fails, get the interface as it was already created
    //
    interfaceDescription = [self.clientController.bus createInterfaceWithName:@"org.alljoyn.bus.samples.fileTransfer"];
    
    
    // add the signals to the interface description
    //
    
    QStatus status = [interfaceDescription addSignalWithName:@"FileTransfer" inputSignature:@"suay" argumentNames:[NSArray arrayWithObjects:@"name",@"curr",@"data", nil]];
    
    if (status != ER_OK && status != ER_BUS_MEMBER_ALREADY_EXISTS) {
        @throw [NSException exceptionWithName:@"BusObjectInitFailed" reason:@"Unable to add signal to interface:  FileTransfer" userInfo:nil];
    }
    
    
    [interfaceDescription activate];
    
    
    [self.clientController.bus registerFileTransferDelegateSignalHandler:self];
}

- (void)didReceiveStatusMessage:(NSString*)message
{
    dispatch_async(dispatch_get_main_queue(), ^{
        NSMutableString *string = self.eventsTextView.text.length ? [self.eventsTextView.text mutableCopy] : [[NSMutableString alloc] init];
        NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
        [formatter setTimeStyle:NSDateFormatterMediumStyle];
        [formatter setDateStyle:NSDateFormatterShortStyle];
        [string appendFormat:@"[%@]\n",[formatter stringFromDate:[NSDate date]]];
        [string appendString:message];
        [string appendString:@"\n\n"];
        [self.eventsTextView setText:string];
        NSLog(@"%@",message);
        [self.eventsTextView scrollRangeToVisible:NSMakeRange([self.eventsTextView.text length], 0)];
    });
}

#pragma mark - File Transfer Signal Handler implementation

- (void)didReceiveTransferFileNamed:(NSString *)name currentIndex:(NSNumber *)curr fileData:(AJNMessageArgument *)data inSession:(AJNSessionId)sessionId fromSender:(NSString *)sender
{
    dispatch_async(self.receiveFileTransferQueue, ^{
        uint8_t *buffer;
        size_t bufferLength;
        ajn::MsgArg *pMsgArg = data.msgArg;
        NSString *message;
        pMsgArg->Get("ay", &bufferLength, &buffer);
        
        self.totalBytesReceived += bufferLength;
        
        // if the file does not exist, create a new file
        //
        if (self.receivedFile == nil) {
            NSString *filePath = [NSString stringWithFormat:@"%@%@", NSTemporaryDirectory(), [name lastPathComponent]];
            if (![[NSFileManager defaultManager] fileExistsAtPath:filePath]) {
                if ([[NSFileManager defaultManager] createFileAtPath:filePath contents:nil attributes:nil]) {
                    message = [NSString stringWithFormat:@"Created file at %@", filePath];
                    NSLog(@"%@", message);
                    [self didReceiveStatusMessage:message];
                }
            }
            self.receivedFile = [NSFileHandle fileHandleForWritingAtPath:filePath];
        }
        
        // write the received data to the file
        //
        [self.receivedFile writeData:[NSData dataWithBytes:buffer length:bufferLength]];

        message = [NSString stringWithFormat:@"Total bytes: %d. Received file chunk %@ of file named %@ from %@", self.totalBytesReceived, curr, name, sender];
        NSLog(@"%@", message);
        [self didReceiveStatusMessage:message];

        // update the progress in the user interface
        //
        dispatch_async(dispatch_get_main_queue(), ^{
            self.totalReceivedLabel.text = [NSString stringWithFormat:@"%.2f MB", (self.totalBytesReceived / 1024.0) / 1024.0];
        });
        
        // stop the client once the file transfer is complete
        //
        if (bufferLength == 0) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [self.clientController stop];
                [self.startButton setTitle:@"Start" forState:UIControlStateNormal];
                [self didReceiveStatusMessage:@"Transfer is complete!"];
                self.receivedFile = nil;
            });
        }
    });
}

@end
