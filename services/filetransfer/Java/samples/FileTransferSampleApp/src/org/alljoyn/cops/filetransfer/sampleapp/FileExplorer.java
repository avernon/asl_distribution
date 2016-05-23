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

package org.alljoyn.cops.filetransfer.sampleapp;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.view.ContextMenu;
import android.view.ContextMenu.ContextMenuInfo;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class FileExplorer extends Activity 
{
	private List<String> fileList = new ArrayList<String>();
	private ListView listView;
	private Intent selectedFileIntent;
	private File root;
	private File selected;

	/*
	 * Displays the file system to the user and returns the
	 * selected file to the calling activity using the putExtras()
	 * method 
	 */
	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.explorer);

		selectedFileIntent = new Intent();

		listView = (ListView) findViewById(R.id.listView);			
		listView.setOnItemClickListener(new OnItemClickListener() 
		{
			public void onItemClick(AdapterView<?> listView, View v, int position, long id) 
			{				
				selected = new File(fileList.get(position));				

				if(selected.isDirectory()) 
				{
					listDir();
				}
				else 
				{
					finishSelection();
				}				
			}
		});		
		registerForContextMenu(listView);

		root = new File(Environment.getExternalStorageDirectory().getAbsolutePath());	
		selected = root;
		listDir(); 
	}		

	private void finishSelection() 
	{
		selectedFileIntent.putExtra("file", selected);
		setResult(RESULT_OK, selectedFileIntent);
		finish();
	}

	private void listDir() 
	{
		File[] files = selected.listFiles();

		fileList.clear();
		for (File file : files) 
		{
			fileList.add(file.getPath()); 
		}

		ArrayAdapter<String> directoryList = new ArrayAdapter<String>(this, 
				android.R.layout.simple_list_item_1, fileList);
		listView.setAdapter(directoryList);
	} 

	@Override
	public void onCreateContextMenu(ContextMenu menu, View v, ContextMenuInfo menuInfo)
	{		   
		if (v.getId() == R.id.listView) 
		{
			menu.setHeaderTitle("Select Folder?");
			String[] menuItems = new String[] { "Yes", "No" }; 

			for (int i = 0; i < menuItems.length; i++) 
			{
				menu.add(Menu.NONE, i, i, menuItems[i]);
			}			   			   			   
		}
	}
	
	@Override
	public boolean onContextItemSelected(MenuItem item)	
	{
		String selectedString = item.getTitle().toString();		
		
		if (selectedString == "Yes")
		{
			AdapterView.AdapterContextMenuInfo info = (AdapterView.AdapterContextMenuInfo)item.getMenuInfo();			
			String path = fileList.get(info.position);
			selected = new File(path);
			
			finishSelection();		
		}		
		return true;				
	}
	
	@Override
    public void onBackPressed() 
    {
		if (!selected.getAbsolutePath().equals(root.getAbsolutePath()))
		{
			selected = selected.getParentFile();
			listDir();
			return;
		}
    	super.onBackPressed();
    }	
}
