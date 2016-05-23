/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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

#import "FTMFileDescriptor.h"

@implementation FTMFileDescriptor

@synthesize owner = _owner;
@synthesize sharedPath = _sharedPath;
@synthesize relativePath = _relativePath;
@synthesize filename = _filename;
@synthesize fileID = _fileID;
@synthesize size = _size;

- (id)init
{
	return [self initWithFileDescriptor: nil];	
}

- (id)initWithFileDescriptor: (FTMFileDescriptor *)fileDescriptor
{
	self = [super init];
	
	if (self && fileDescriptor) {
		self.owner = fileDescriptor.owner;
		self.sharedPath = fileDescriptor.sharedPath;
		self.relativePath = fileDescriptor.relativePath;
		self.filename = fileDescriptor.filename;
		self.fileID = fileDescriptor.fileID;
		self.size = fileDescriptor.size;
	}
	
	return self;
}

- (BOOL)isEqual: (id)other
{
	if (other == nil) {
		return NO;
	}

	if (other == self) {
		return YES;
	}
	
	if (![other isKindOfClass: [self class]]) {
		return NO;
	}
	
	return [self isEqualToFileDescriptor: other];
}

- (BOOL)isEqualToFileDescriptor: (FTMFileDescriptor *)that
{
	return
		[self.owner isEqual: that.owner] &&
		[self.sharedPath isEqual: that.sharedPath] &&
		[self.relativePath isEqual: that.relativePath] &&
		[self.fileID isEqual: that.fileID] &&
		self.size == that.size;
}

- (NSUInteger)hash
{
	const int prime = 31;
	int result = 1;
	
	result = (prime * result) + (self.owner ? [self.owner hash] : 0);
	result = (prime * result) + (self.sharedPath ? [self.sharedPath hash] : 0);
	result = (prime * result) + (self.relativePath ? [self.relativePath hash] : 0);
	result = (prime * result) + (self.filename ? [self.filename hash] : 0);
	result = (prime * result) + (self.fileID ? [self.fileID hash] : 0);
	result = (prime * result) + self.size;
	
	return result;	
}

@end