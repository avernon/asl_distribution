/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

package org.alljoyn.ioe.notificationviewer;

import java.util.List;
import java.util.Map;
import java.util.Set;

import org.alljoyn.about.AboutKeys;
import org.alljoyn.services.common.PropertyStore;
import org.alljoyn.services.common.PropertyStoreException;

import android.content.SharedPreferences;

public class  PropertyStoreImpl implements PropertyStore{
	
	  public static class Property
    {	    		
    	private  String m_language=null;
    	private final boolean m_isWritable;
    	private final boolean m_isAnnounced;
    	private final boolean m_isPublic;
    	private final String m_name;
    	private Object m_object=null;
      // public.write.announce
    	
    	
    	public Property(String m_name,Object value, boolean isPublic,boolean isWritable,boolean isAnnounced)
    	{
    		super();
    		this.m_isWritable = isWritable;
    		this.m_isAnnounced = isAnnounced;
    		this.m_isPublic = isPublic;
    		this.m_name = m_name;
    		this.m_object=value;
    	}
    	
    	public boolean isWritable()
    	{
    		return m_isWritable;
    	}
    	public boolean isAnnounced()
    	{
    		return m_isAnnounced;
    	}
    	public boolean isPublic()
    	{
    		return m_isPublic;
    	}
    	public String getName()
    	{
    		return m_name;
    	}
    	
    	public String getLangauge()
    	{
    		return m_language;
    	}	    	
    	public void setLanguage(String language ) { this.m_language = language; }	 
    	
    	public Object getObject() {
    		return m_object;
    	}
    }

	  
	private Map<String,List<Property>> m_internalMap=null;
	private SharedPreferences sharedPrefs;
	
	public PropertyStoreImpl(Map<String,List<Property>>   dataMap, SharedPreferences sharedPrefs){
		m_internalMap=dataMap;
		this.sharedPrefs = sharedPrefs;
	}
	
	@Override
    public void readAll(String languageTag, Filter filter, Map<String, Object> dataMap) throws PropertyStoreException{
		if (filter==Filter.ANNOUNCE)
		{	    		
			
			if (m_internalMap!=null)
			{		    			
				  List<Property> langauge=m_internalMap.get(AboutKeys.ABOUT_DEFAULT_LANGUAGE);
				  if (langauge!=null)
				  {
					  languageTag=(String)langauge.get(0).getObject();
				  }else{
					  throw new PropertyStoreException(PropertyStoreException.UNSUPPORTED_LANGUAGE);
				  }
				  	    				
				  Set<Map.Entry<String, List<Property>>> entries = m_internalMap.entrySet();	    				
				  for(Map.Entry<String, List<Property>> entry : entries) {
					  	String key = entry.getKey();
					  	List<Property> properyList = entry.getValue();
					  	for (int i=0;i<properyList.size();i++)
					  	{
					  		Property property=properyList.get(i);
					  		if (!property.isAnnounced())
					  			continue;
					  		 if (!(property.getLangauge()==null|| property.getLangauge().compareTo(languageTag) == 0))
				                continue;
					  		dataMap.put(key, property.getObject());	    					  		
					  	}	    					  	
			      }	    					    				
			}else 
				throw new  PropertyStoreException(PropertyStoreException.UNSUPPORTED_KEY); 
			
			
		}
		else if (filter==Filter.READ)
		{	    			
			if (languageTag!=null && languageTag.length()>1)
			{
  			 List<Property> supportedLanguages=m_internalMap.get(AboutKeys.ABOUT_SUPPORTED_LANGUAGES);		    			
  			 if (supportedLanguages==null)
  					throw new  PropertyStoreException(PropertyStoreException.UNSUPPORTED_KEY); 
  			if (!( supportedLanguages.get(0).getObject() instanceof Set<?>)){	    						
					throw new  PropertyStoreException(PropertyStoreException.UNSUPPORTED_LANGUAGE);
				}else{
					@SuppressWarnings("unchecked")
					Set<String> languages=(Set<String>)supportedLanguages.get(0).getObject();
					if (!languages.contains(languageTag)){
						throw new  PropertyStoreException(PropertyStoreException.UNSUPPORTED_LANGUAGE);
					}								
				}
			}else{
				
				 List<Property> langauge=m_internalMap.get(AboutKeys.ABOUT_DEFAULT_LANGUAGE);
				  if (langauge!=null)
				  {
					  languageTag=(String)langauge.get(0).getObject();
				  }else{
					  throw new PropertyStoreException(PropertyStoreException.UNSUPPORTED_LANGUAGE);
				  }
			}	    			 	    			
		  Set<Map.Entry<String, List<Property>>> entries = m_internalMap.entrySet();    				
		  for(Map.Entry<String, List<Property>> entry : entries) {
			  	String key = entry.getKey();
			  	List<Property> properyList = entry.getValue();
			  	for (int i=0;i<properyList.size();i++)
			  	{
			  		Property property=properyList.get(i);
			  		if (!property.isPublic())
			  			continue;
			  		 if (!(property.getLangauge()==null|| property.getLangauge().compareTo(languageTag) == 0))
		                continue;
			  		dataMap.put(key, property.getObject());	    					  		
			  	}	    					  	
	      }
			
		}//end of read.
        else if (filter == Filter.WRITE) {
            Set<Map.Entry<String, List<Property>>> entries = m_internalMap.entrySet();                      
            for(Map.Entry<String, List<Property>> entry : entries) {
                  String key = entry.getKey();
                  List<Property> properyList = entry.getValue();
                  for (int i=0;i<properyList.size();i++)
                  {
                      Property property=properyList.get(i);
//                      if (!(property.getLangauge()==null|| property.getLangauge().compareTo(languageTag) == 0))
//                          continue;
                      if (property.isWritable()) {
                          dataMap.put(key, property.getObject());                                 
                      }
                  }                               
            }     
        }//end of write
		else throw new PropertyStoreException(PropertyStoreException.ILLEGAL_ACCESS);
		
		
	}
	
	@Override
    public void update(String key, String languageTag, Object newValue) throws PropertyStoreException{
//	      languageTag = checkLanguage(languageTag);
	        if (!m_internalMap.containsKey(key))
	        {
	        throw new PropertyStoreException(PropertyStoreException.INVALID_VALUE);
	        }
	        
	        m_internalMap.get(key).get(0).m_object = newValue;
	        
            //TODO: Refactor this later?
	        if (null != key && key.equals(AboutKeys.ABOUT_DEVICE_NAME)) {
	            SharedPreferences.Editor editor = sharedPrefs.edit();
	            editor.putString(Constants.SHARED_PREFS_KEY_DEVICE_NAME, newValue.toString());
	            editor.apply();
	        }
	}

	@Override
    public void reset(String key, String languageTag) throws PropertyStoreException{
		
	}
	
	@Override
    public void resetAll() throws PropertyStoreException{
		
	}
	
}