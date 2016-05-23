/*
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
 */
package org.allseen.lsf.sampleapp;

import android.util.Log;
import android.widget.TableLayout;
import android.widget.TableRow;

public class TableSorter {
    public static <T> void insertSortedTableRow(TableLayout table, TableRow tableRow, Comparable<T> tag) {
        int searchLow = 0;
        int searchHigh = table.getChildCount() - 1;

        while (searchLow <= searchHigh) {
            int searchNext = searchLow + ((searchHigh - searchLow) / 2);
            int comparison = compareTags(tag, (TableRow)table.getChildAt(searchNext));

            Log.v(SampleAppActivity.TAG, "insertSortedTableRow(): checking [" + searchLow + ", " + searchNext + ", " + searchHigh + "]");

            if (comparison < 0) {
                searchHigh = searchNext - 1;
            } else if (comparison > 0) {
                searchLow = searchNext + 1;
            } else {
                searchLow = searchHigh + 1;
            }
        }

        setTag(tableRow, tag);

        table.addView(tableRow, searchLow);
    }

    public static <T> void updateSortedTableRow(TableLayout table, TableRow tableRow, Comparable<T> tag) {
        if (!equalTags(tag, tableRow)) {
            table.removeView(tableRow);

            TableSorter.insertSortedTableRow(table, tableRow, tag);
        }
    }

    protected static <T> boolean equalTags(Comparable<T> tag, TableRow tableRow) {
        return compareTags(tag, tableRow) == 0;
    }

    @SuppressWarnings("unchecked")
    protected static <T> int compareTags(Comparable<T> tag, TableRow tableRow) {
        return tag.compareTo((T)tableRow.getTag(R.id.TAG_KEY_SORTABLE_NAME));
    }

    protected static <T> void setTag(TableRow tableRow, T tag) {
        tableRow.setTag(R.id.TAG_KEY_SORTABLE_NAME, tag);
    }
}
