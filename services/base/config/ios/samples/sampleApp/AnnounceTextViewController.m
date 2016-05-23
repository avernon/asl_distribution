/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

#import "AnnounceTextViewController.h"
#import "alljoyn/about/AJNAboutDataConverter.h"

@interface AnnounceTextViewController ()
@property (weak, nonatomic) IBOutlet UITextView *announceInformation;

@end

@implementation AnnounceTextViewController

- (NSString *)objectDescriptionsToString:(NSMutableDictionary *)qnsObjectDesc
{
	NSMutableString *qnsObjectDescContent = [[NSMutableString alloc] init];
    
	for (NSString *key in qnsObjectDesc.allKeys) {
		//  iterate over the NSMutableDictionary
		//  path: <key>
		[qnsObjectDescContent appendString:[NSString stringWithFormat:@"path: %@ \n", key]];
		[qnsObjectDescContent appendString:[NSString stringWithFormat:@"interfaces: "]];
		//  interfaces: <NSMutableArray of NSString with ' ' between each element>
		for (NSString *intrf in qnsObjectDesc[key]) {
			//  get NSString from the received object(NSMutableArray)
			[qnsObjectDescContent appendString:[NSString stringWithFormat:@"%@ ", intrf]];
		}
		[qnsObjectDescContent appendString:[NSString stringWithFormat:@"\n\n"]];
	}
    
	return (qnsObjectDescContent);
} //  parseObjectDescriptions

- (void)viewDidLoad
{
	[super viewDidLoad];
    
	//  retrive AJNAnnouncement by the  announcementButtonCurrentTitle unique name
	NSString *txt = [[NSString alloc] init];
    
	//  set title
	NSString *title = [self.ajnAnnouncement busName];
    
	txt = [txt stringByAppendingFormat:@"%@\n%@\n", title, [@"" stringByPaddingToLength :[title length] + 10 withString : @"-" startingAtIndex : 0]];
    
	//  set body
	txt = [txt stringByAppendingFormat:@"BusName: %@\n", [self.ajnAnnouncement busName]];
    
	txt = [txt stringByAppendingFormat:@"Port: %hu\n", [self.ajnAnnouncement port]];
    
    txt = [txt stringByAppendingFormat:@"Version: %u\n", [self.ajnAnnouncement version]];
    
	txt = [txt stringByAppendingString:@"\n\n"];
    
	//  set AboutMap info
	txt = [txt stringByAppendingFormat:@"About map:\n"];
    
	txt = [txt stringByAppendingString:[AJNAboutDataConverter aboutDataDictionaryToString:([self.ajnAnnouncement aboutData])]];
    
	txt = [txt stringByAppendingString:@"\n\n"];
    
	//  set ObjectDesc info
	txt = [txt stringByAppendingFormat:@"Bus Object Description:\n"];
    
	txt = [txt stringByAppendingString:[self objectDescriptionsToString:[self.ajnAnnouncement objectDescriptions]]];
    
	self.announceInformation.text = txt;
}


@end
