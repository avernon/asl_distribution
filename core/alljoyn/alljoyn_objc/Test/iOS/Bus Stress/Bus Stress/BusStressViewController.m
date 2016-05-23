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

#import "BusStressViewController.h"
#import "BusStressManager.h"

@interface BusStressViewController () <BusStressManagerDelegate>

- (void)didCompleteIteration:(NSInteger)iterationNumber totalIterations:(NSInteger)totalInterations;

@end

@implementation BusStressViewController
@synthesize numberOfThreadsLabel = _numberOfThreadsLabel;
@synthesize numberOfIterationsLabel = _numberOfIterationsLabel;
@synthesize stopThreadsBeforeJoinSwitch = _stopThreadsBeforeJoinSwitch;
@synthesize deleteBusAttachmentsSwitch = _deleteBusAttachmentsSwitch;
@synthesize startButton = _startButton;
@synthesize iterationsCompletedLabel = _iterationsCompletedLabel;
@synthesize iterationsCompletedProgressView = _iterationsCompletedProgressView;
@synthesize numberOfIterationsSlider = _numberOfIterationsSlider;
@synthesize numberOfThreadsSlider = _numberOfThreadsSlider;
@synthesize operationModeSegmentedControl = _operationModeSegmentedControl;
@synthesize stopButton = _stopButton;
@synthesize stressTestActivityIndicatorView = _stressTestActivityIndicatorView;

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
 
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}

- (void)viewDidUnload
{
    [self setNumberOfIterationsLabel:nil];
    [self setNumberOfThreadsLabel:nil];
    [self setStopThreadsBeforeJoinSwitch:nil];
    [self setDeleteBusAttachmentsSwitch:nil];
    [self setStartButton:nil];
    [self setIterationsCompletedLabel:nil];
    [self setIterationsCompletedProgressView:nil];
    [self setNumberOfIterationsSlider:nil];
    [self setNumberOfThreadsSlider:nil];
    [self setOperationModeSegmentedControl:nil];
    [self setStopButton:nil];
    [self setStressTestActivityIndicatorView:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark - Table view data source

//- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
//{
//#warning Potentially incomplete method implementation.
//    // Return the number of sections.
//    return 0;
//}
//
//- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
//{
//#warning Incomplete method implementation.
//    // Return the number of rows in the section.
//    return 0;
//}
//
//- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
//{
//    static NSString *CellIdentifier = @"Cell";
//    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
//    
//    // Configure the cell...
//    
//    return cell;
//}

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
{
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Navigation logic may go here. Create and push another view controller.
    /*
     <#DetailViewController#> *detailViewController = [[<#DetailViewController#> alloc] initWithNibName:@"<#Nib name#>" bundle:nil];
     // ...
     // Pass the selected object to the new view controller.
     [self.navigationController pushViewController:detailViewController animated:YES];
     */
}

- (IBAction)didTouchStartButton:(id)sender
{
    [BusStressManager runStress:(NSInteger)self.numberOfIterationsSlider.value threadCount:(NSInteger)self.numberOfThreadsSlider.value deleteBusFlag:self.deleteBusAttachmentsSwitch.isOn stopThreadsFlag:self.stopThreadsBeforeJoinSwitch.isOn operationMode:self.operationModeSegmentedControl.selectedSegmentIndex delegate:self];
    self.startButton.hidden = YES;
    self.stopButton.hidden = NO;
    [self.stressTestActivityIndicatorView startAnimating];
}

- (IBAction)didTouchStopButton:(id)sender
{
    [BusStressManager stopStress];
    self.startButton.hidden = NO;
    self.stopButton.hidden = YES;
    [self.stressTestActivityIndicatorView stopAnimating];
}

- (IBAction)numberOfIterationsValueChanged:(id)sender
{
    self.numberOfIterationsLabel.text = [NSString stringWithFormat:@"%d", (NSInteger)self.numberOfIterationsSlider.value];
}

- (IBAction)numberOfThreadsValueChanged:(id)sender
{
    self.numberOfThreadsLabel.text = [NSString stringWithFormat:@"%d", (NSInteger)self.numberOfThreadsSlider.value];
}

- (AJNTransportMask)transportMask
{
    return kAJNTransportMaskAny;
}

- (void)didCompleteIteration:(NSInteger)iterationNumber totalIterations:(NSInteger)totalInterations
{
    dispatch_async(dispatch_get_main_queue(), ^{
        self.iterationsCompletedProgressView.progress = (float)iterationNumber / (float)totalInterations;
        self.iterationsCompletedLabel.text = [NSString stringWithFormat:@"%d", iterationNumber];
    });
}

@end
