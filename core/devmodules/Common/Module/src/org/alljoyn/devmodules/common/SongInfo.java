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
package org.alljoyn.devmodules.common;

import org.alljoyn.bus.annotation.Position;

public final class SongInfo {
	@Position(0)
	public String songPath;
	@Position(1)
	public String songName;
	@Position(2)
	public String artist;
	@Position(3)
	public String album;
	@Position(4)
	public String artPath;
	@Position(5)
	public int songId;
	@Position(6)
	public int albumId;
	@Position(7)
	public String fileName;
	@Position(8)
	public String busId;
	
	public SongInfo() {
		this.songId = -1;
		this.songPath = "ERROR";
		this.songName = "ERROR";
		this.artist = "ERROR";
		this.album = "ERROR";
		this.albumId = -1;
		this.artPath = "";
		this.busId = "ERROR";
		this.fileName = "ERROR";
	}
	
	public SongInfo(int songId, String songPath, String songName, String artist, String album, int albumId, String artPath, String fileName)
	{
		this.songId = songId;
		this.songPath = songPath;
		this.songName = songName;
		this.artist = artist;
		this.album = album;
		this.albumId = albumId;
		this.artPath = artPath;
		this.fileName = fileName;
		this.busId = "ERROR";
	}
	
	public String toString() {
		return "SongInfo: "
			+ songId + ", "
			+ songPath + ", "
			+ songName + ", "
			+ artist + ", "
			+ album + ", "
			+ albumId + ", "
			+ artPath + ", "
			+ fileName + ", "
			+ busId;
	}
}
