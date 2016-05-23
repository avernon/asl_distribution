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

#import <Foundation/Foundation.h>

// constants
//
NSString * const kImplHeaderXSL = @"objcImplHeader.xsl";
NSString * const kImplSourceXSL = @"objcImplSource.xsl";
NSString * const kBaseHeaderXSL = @"objcBaseHeader.xsl";
NSString * const kBaseSourceXSL = @"objcBaseSource.xsl";

const NSInteger kExpectedArgumentCount = 2;

// print the expected arguments
//
void usage(void)
{
    NSLog(@"Usage: PeerGroupManagerCodeGenerator input_xml_file [output_file_name]");
    NSLog(@"Arguments:");
    NSLog(@"   input_xml_file        = The path to the input XML file containing the DBus-formatted object model.");
    NSLog(@"   output_file_name      = (Optional) The prefix and base file name used for the generated Objective-C files.");
    NSLog(@"");
    NSLog(@"The files containing the generated Objective-C source code will reside in the same directory as the specified input XML file.");
    NSLog(@"The xsl files used to generate the Objective-C source code should reside in the same directory as the AllJoynCodeGenerator executable.");
}


int main(int argc, const char * argv[])
{
    @autoreleasepool {
        
        //  Validate the there are the correct number of command line arguments.
        //  Remember that argv/argc includes the executable's path plus the
        //  arguments passed to it.
        //
        if (argc <= kExpectedArgumentCount) {
            
            // Print usage if not enough command line arguments.
            //
            usage();
            
            return 1;
        }
        
        //  Validate that the input file exists.
        //
        NSString *xmlFilePath = [NSString stringWithCString:argv[1] encoding:NSUTF8StringEncoding];
        if (![[NSFileManager defaultManager] fileExistsAtPath:xmlFilePath]) {
            NSLog(@"The input file specified does not exist %@", xmlFilePath);
            return 1;
        }
        
        // Validate that the base file name uses valid characters
        //
        NSString *baseFileName = [NSString stringWithCString:argv[2] encoding:NSUTF8StringEncoding];
        if (![[baseFileName stringByTrimmingCharactersInSet:[NSCharacterSet decimalDigitCharacterSet]] isEqualToString:baseFileName]
            && ![[baseFileName stringByTrimmingCharactersInSet:[NSCharacterSet letterCharacterSet]] isEqualToString:baseFileName]) {
            NSLog(@"The base file name should contain only letters or numbers.");
            return 1;
        }
        
        // Parse out the directory of the input file for use as the location of the output files
        //
        NSURL *fileUrl = [NSURL fileURLWithPath:xmlFilePath];
        NSURL *executableFileUrl = [NSURL fileURLWithPath:[NSString stringWithCString:argv[0] encoding:NSUTF8StringEncoding]];
        NSString *executableDirectory =  [[executableFileUrl URLByDeletingLastPathComponent] path];
        NSString *outputDirectory = [[fileUrl URLByDeletingLastPathComponent] path];
        NSError *error = nil;
        NSString *xslFileUrl = [NSString stringWithFormat:@"%@/%@", executableDirectory, kImplHeaderXSL];
        NSString *outputFilePath = [NSString stringWithFormat:@"%@/%@Impl.h", outputDirectory, baseFileName];
        NSString *outputFileName = [[NSURL fileURLWithPath:outputFilePath] lastPathComponent];

        // STEP ONE
        //
        // prepare to generate the Objective-C scaffold implementation header file
        //
        NSXMLDocument *xmlDocument = [[NSXMLDocument alloc] initWithContentsOfURL:fileUrl options:NSDataReadingMappedIfSafe error:&error];
        if (error) {
            NSLog(@"Error loading XML. %@",error);
            return 1;
        }
        
        NSData *generatedCodeData = [xmlDocument objectByApplyingXSLTAtURL:[NSURL fileURLWithPath:xslFileUrl] arguments:[NSDictionary dictionaryWithObjects:[NSArray arrayWithObject:[NSString stringWithFormat:@"\'%@\'", outputFileName]] forKeys:[NSArray arrayWithObject:@"fileName"]] error:&error];
        if (error) {
            NSLog(@"Error applying XSL. %@",error);
            return 1;
        }
        
        // write the Objective-C scaffold header file to disk
        //
        [generatedCodeData writeToURL:[NSURL fileURLWithPath:outputFilePath] atomically:YES];
        
        // STEP TWO
        //
        // prepare to generate the Objective-C++ scaffold implementation source file
        //
        xslFileUrl = [NSString stringWithFormat:@"%@/%@", executableDirectory, kImplSourceXSL];
        outputFilePath = [NSString stringWithFormat:@"%@/%@Impl.mm", outputDirectory, baseFileName];
        outputFileName = [[NSURL fileURLWithPath:outputFilePath] lastPathComponent];
        
        xmlDocument = [[NSXMLDocument alloc] initWithContentsOfURL:fileUrl options:NSDataReadingMappedIfSafe error:&error];
        if (error) {
            NSLog(@"Error loading XML. %@",error);
            return 1;
        }
        
        generatedCodeData = [xmlDocument objectByApplyingXSLTAtURL:[NSURL fileURLWithPath:xslFileUrl] arguments:[NSDictionary dictionaryWithObjects:[NSArray arrayWithObjects:[NSString stringWithFormat:@"\'%@\'",outputFileName], [NSString stringWithFormat:@"\'%@\'",baseFileName],nil] forKeys:[NSArray arrayWithObjects:@"fileName",@"baseFileName",nil]] error:&error];
        if (error) {
            NSLog(@"Error applying XSL. %@",error);
            return 1;
        }
        
        // write the source file to disk
        //
        [generatedCodeData writeToURL:[NSURL fileURLWithPath:outputFilePath] atomically:YES];
        
        // STEP THREE
        //
        // prepare to generate the Objective-C header file
        //
        xslFileUrl = [NSString stringWithFormat:@"%@/%@", executableDirectory, kBaseHeaderXSL];
        outputFilePath = [NSString stringWithFormat:@"%@/%@Base.h", outputDirectory, baseFileName];
        outputFileName = [[NSURL fileURLWithPath:outputFilePath] lastPathComponent];

        xmlDocument = [[NSXMLDocument alloc] initWithContentsOfURL:fileUrl options:NSDataReadingMappedIfSafe error:&error];
        if (error) {
            NSLog(@"Error loading XML. %@",error);
            return 1;
        }
        
        generatedCodeData = [xmlDocument objectByApplyingXSLTAtURL:[NSURL fileURLWithPath:xslFileUrl] arguments:[NSDictionary dictionaryWithObjects:[NSArray arrayWithObjects:[NSString stringWithFormat:@"\'%@\'",outputFileName], [NSString stringWithFormat:@"\'%@\'",baseFileName],nil] forKeys:[NSArray arrayWithObjects:@"fileName",@"baseFileName",nil]] error:&error];
        if (error) {
            NSLog(@"Error applying XSL. %@",error);
            return 1;
        }
        
        // write the category header file to disk
        //
        [generatedCodeData writeToURL:[NSURL fileURLWithPath:outputFilePath] atomically:YES];
        
        // STEP FOUR
        //
        // prepare to generate the Objective-C source file
        //
        xslFileUrl = [NSString stringWithFormat:@"%@/%@", executableDirectory, kBaseSourceXSL];
        outputFilePath = [NSString stringWithFormat:@"%@/%@Base.m", outputDirectory, baseFileName];
        outputFileName = [[NSURL fileURLWithPath:outputFilePath] lastPathComponent];
        
        xmlDocument = [[NSXMLDocument alloc] initWithContentsOfURL:fileUrl options:NSDataReadingMappedIfSafe error:&error];
        if (error) {
            NSLog(@"Error loading XML. %@",error);
            return 1;
        }
        
        generatedCodeData = [xmlDocument objectByApplyingXSLTAtURL:[NSURL fileURLWithPath:xslFileUrl] arguments:[NSDictionary dictionaryWithObjects:[NSArray arrayWithObjects:[NSString stringWithFormat:@"\'%@\'",outputFileName], [NSString stringWithFormat:@"\'%@\'",baseFileName],nil] forKeys:[NSArray arrayWithObjects:@"fileName",@"baseFileName",nil]] error:&error];
        if (error) {
            NSLog(@"Error applying XSL. %@",error);
            return 1;
        }
        
        // write the category source file to disk
        //
        [generatedCodeData writeToURL:[NSURL fileURLWithPath:outputFilePath] atomically:YES];
    }
    return 0;
}

