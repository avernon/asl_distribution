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

package org.alljoyn.gatewaycontroller.adapters;

import java.util.Arrays;
import java.util.Collection;
import java.util.List;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ArrayAdapter;

/**
 * All the adapter classes may extend this class
 */
public abstract class VisualArrayAdapter extends ArrayAdapter<VisualItem> {

    /**
     * The context of the activity running the adapter
     */
    protected final Context context;

    /**
     * The resource id of the viewed item
     */
    protected final int viewItemResId;

    /**
     * The list of the {@link VisualItem}s managed by the adapter
     */
    protected final List<VisualItem> itemsList;

    /**
     * Inflater to get {@link View} of the rendered row
     */
    protected final LayoutInflater inflater;

    /**
     * Constructor
     * 
     * @param context
     *            The context of the activity running the adapter
     * @param viewItemResId
     *            The resource id of the viewed item
     * @param itemsList
     *            The list of the {@link VisualItem}s managed by the adapter
     * @throws IllegalArgumentException
     *             if the received itemsList or context are undefined
     */
    public VisualArrayAdapter(Context context, int viewItemResId, List<VisualItem> itemsList) {

        super(context, viewItemResId, itemsList);

        if (context == null) {
            throw new IllegalArgumentException("context is undefined");
        }

        if (itemsList == null) {
            throw new IllegalArgumentException("itemsList is undefined");
        }

        this.context       = context;
        this.viewItemResId = viewItemResId;
        this.itemsList     = itemsList;
        inflater           = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
    }

    /**
     * @see android.widget.ArrayAdapter#add(java.lang.Object)
     */
    @Override
    public void add(VisualItem object) {
        itemsList.add(object);
    }

    /**
     * @see android.widget.ArrayAdapter#addAll(java.util.Collection)
     */
    @Override
    public void addAll(Collection<? extends VisualItem> collection) {
        itemsList.addAll(collection);
    }

    /**
     * @see android.widget.ArrayAdapter#addAll(java.lang.Object[])
     */
    @Override
    public void addAll(VisualItem... items) {
        itemsList.addAll(Arrays.asList(items));
    }

    /**
     * @see android.widget.ArrayAdapter#clear()
     */
    @Override
    public void clear() {
        itemsList.clear();
    }

    /**
     * @see android.widget.ArrayAdapter#getCount()
     */
    @Override
    public int getCount() {
        return itemsList.size();
    }

    /**
     * @see android.widget.ArrayAdapter#getItem(int)
     */
    @Override
    public VisualItem getItem(int position) {

        if (position < 0 || position >= getCount()) {
            return null;
        }

        return itemsList.get(position);
    }

    /**
     * @see android.widget.ArrayAdapter#getItemId(int)
     */
    @Override
    public long getItemId(int position) {

        return position;
    }

    /**
     * If the item is not found "-1" is returned
     * 
     * @see android.widget.ArrayAdapter#getPosition(java.lang.Object)
     */
    @Override
    public int getPosition(VisualItem item) {

        int retVal = -1;

        for (int i = 0; i < getCount(); ++i) {

            VisualItem listItem = itemsList.get(i);

            if (listItem.equals(item)) {
                retVal = i;
                break;
            }
        }

        return retVal;
    }

    /**
     * @see android.widget.ArrayAdapter#insert(java.lang.Object, int)
     * @see List#add(int, Object)
     */
    @Override
    public void insert(VisualItem object, int index) {

        if (index < 0 || index > getCount()) {
            return;
        }

        itemsList.add(index, object);
    }

    /**
     * @return List of the visual items
     */
    public List<VisualItem> getItemsList() {

        return itemsList;
    }
}
