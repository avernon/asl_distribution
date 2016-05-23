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
package org.alljoyn.whiteboard.activity;

import java.util.ArrayList;

public class DrawingLines {

	public static final float CANVAS_FLOAT_WIDTH = 1.0f;	
	public static final float CANVAS_FLOAT_HEIGHT = 1.0f;	
	public static final float REVIEW_SCALE = 0.25f;	
	public static final int PART_COUNT = 4;

	private ArrayList <ArrayList <Point> > mListOfLines;

	transient private int scaleWidth = 320;
	transient private int displayYOffset = 0;

	public DrawingLines() {
		ArrayList <Point> initCurve = new ArrayList<Point>();
		mListOfLines = new ArrayList<ArrayList <Point> >();
		mListOfLines.add(initCurve);
	}

	public ArrayList<ArrayList <Point> > getDraw(){ 
		return mListOfLines;
	}

	public void setDisplaySize(int x, int y){
		displayYOffset = (int) ((y - (scaleWidth * CANVAS_FLOAT_HEIGHT)) / 2);
	}

	public int getCanvasHeight(){		
		return (int) (scaleWidth  * CANVAS_FLOAT_HEIGHT);
	}

	public void addCurvePoint(int x, int y){
		Point p = new Point();
		p.set(x, y);
		if(mListOfLines.size() <= 0){
			ArrayList <Point> initCurve = new ArrayList<Point>();
			mListOfLines.add(initCurve);
		}
		mListOfLines.get(mListOfLines.size()-1).add(p);
	}

	public void addCurvePoint(Point p){
		mListOfLines.get(mListOfLines.size()-1).add(p);
	}

	public void createNewCurve(){
		ArrayList <Point> initCurve = new ArrayList<Point>();
		mListOfLines.add(initCurve);
	}

	public void addCurve(ArrayList<Point> ap){
		mListOfLines.add(ap);
	}

	public void removeLastCurve(){
		if(mListOfLines.size() > 0){
			mListOfLines.remove(mListOfLines.size() - 1);
		}
	}

	public class Point{
		/**
		 * 
		 */
		private float x;
		private float y;

		public Point(){

		}

		public void set(int x, int y){
			this.x  = x / (scaleWidth *  CANVAS_FLOAT_WIDTH) ;
			this.y =  (y - displayYOffset) / (scaleWidth * CANVAS_FLOAT_HEIGHT);
		}
		public int rx(int layer){
			int offset = (int)((1.0f - 1.0f*REVIEW_SCALE) / 2.0f * scaleWidth * CANVAS_FLOAT_WIDTH);
			return (int) ((x) * scaleWidth * CANVAS_FLOAT_WIDTH * REVIEW_SCALE) + offset;
		}

		public int ry(int layer){
			int offset = (int)((1.0f - 4.0f*REVIEW_SCALE + (2.0f*displayYOffset/scaleWidth) ) / 2.0f * scaleWidth * CANVAS_FLOAT_HEIGHT);
			return (int) ((y + layer) * scaleWidth * CANVAS_FLOAT_HEIGHT * REVIEW_SCALE) + offset ;
		}
		public int x(){
			return (int) (x * scaleWidth * CANVAS_FLOAT_WIDTH);
		}

		public int y(){
			return (int) (y * scaleWidth * CANVAS_FLOAT_HEIGHT) + displayYOffset;
		}
		public int topPartY(){
			return (int) ((y - 1)  * scaleWidth * CANVAS_FLOAT_HEIGHT) + displayYOffset;
		}
		public float rawX(){
			return x;
		}

		public float rawY(){
			return y ;
		}
	}

	public void setScaleWidth(int w) {
		scaleWidth = w;
	};

	public void clear()
	{
		mListOfLines = new ArrayList<ArrayList <Point> >();
	}
}
