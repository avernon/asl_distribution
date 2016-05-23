/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

#import "LSFTableViewUtil.h"

@implementation LSFTableViewUtil

+(NSUInteger)findAlphaInsertIndexOf: (LSFSDKLightingItem *)item inItems: (NSArray*)items
{
    return [items indexOfObject: item inSortedRange: (NSRange){0, [items count]} options: (NSBinarySearchingFirstEqual | NSBinarySearchingInsertionIndex) usingComparator:
            ^NSComparisonResult(id a, id b) {
                NSString *first = [(LSFSDKLightingItem *)a name];
                NSString *second = [(LSFSDKLightingItem *)b name];

                NSComparisonResult result = [first localizedCaseInsensitiveCompare: second];
                if (result == NSOrderedSame)
                {
                    result = [((LSFSDKLightingItem *)a).theID localizedCaseInsensitiveCompare: ((LSFSDKLightingItem *)b).theID];
                }

                return result;
            }];
}

+(void)addObjectToTable: (UITableView *)tableView atIndex: (NSUInteger)insertIndex
{
    //NSLog(@"Add: Index = %u", insertIndex);
    NSArray *insertIndexPaths = [NSArray arrayWithObjects: [NSIndexPath indexPathForRow: insertIndex inSection:0], nil];

    [tableView beginUpdates];
    [tableView insertRowsAtIndexPaths: insertIndexPaths withRowAnimation: UITableViewRowAnimationFade];
    [tableView endUpdates];
}

+(void)moveObjectInTable: (UITableView *)tableView fromIndex: (NSUInteger)fromIndex toIndex: (NSUInteger)toIndex
{
    //NSLog(@"Move: FromIndex = %u; ToIndex = %u", fromIndex, toIndex);
    NSIndexPath *fromIndexPath = [NSIndexPath indexPathForRow: fromIndex inSection: 0];
    NSIndexPath *toIndexPath = [NSIndexPath indexPathForRow: toIndex inSection: 0];
    [tableView moveRowAtIndexPath: fromIndexPath toIndexPath: toIndexPath];

    [LSFTableViewUtil refreshRowInTable: tableView atIndex: toIndex];
}

+(void)refreshRowInTable: (UITableView *)tableView atIndex: (NSUInteger)index
{
    //NSLog(@"Refresh: Index = %u", index);
    NSArray *refreshIndexPaths = [NSArray arrayWithObjects: [NSIndexPath indexPathForRow: index inSection:0], nil];
    [tableView reloadRowsAtIndexPaths: refreshIndexPaths withRowAnimation: UITableViewRowAnimationNone];
}

+(void)deleteRowsInTable: (UITableView *)tableView atIndex: (NSArray *)cellIndexPaths
{
    [tableView deleteRowsAtIndexPaths: cellIndexPaths withRowAnimation: UITableViewRowAnimationFade];
}

@end
