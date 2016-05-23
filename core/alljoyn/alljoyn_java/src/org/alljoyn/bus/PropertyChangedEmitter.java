/*
 * Copyright AllSeen Alliance. All rights reserved.
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

package org.alljoyn.bus;

import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.HashMap;


import org.alljoyn.bus.annotation.BusAnnotation;
import org.alljoyn.bus.annotation.BusAnnotations;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.ifaces.Properties;

/**
 * A helper proxy used by BusObjects to send property change notifications.  A PropertyChangedlEmitter
 * instance can be used to send any signal from a given AllJoyn interface.
 */
public class PropertyChangedEmitter extends SignalEmitter {

    private Properties props;

    /**
     * Constructs a PropertyChangedEmitter.
     *
     * @param source the source object of any signals sent from this emitter
     * @param sessionId A unique SessionId for this AllJoyn session instance
     */
    public PropertyChangedEmitter(BusObject source, int sessionId) {
        super(source, null, sessionId, GlobalBroadcast.On);
        props = getInterface(Properties.class);
    }

    /**
     * Constructs a PropertyChangedEmitter used for broadcasting.
     *
     * @param source the source object of any signals sent from this emitter
     */
    public PropertyChangedEmitter(BusObject source) {
        this(source, BusAttachment.SESSION_ID_ANY);
    }

    /**
     * Sends the PropertyChanged signal.
     *
     * @param ifaceName name of the interface the property belongs to
     * @param propertyName name of the property that is changed
     * @param newValue Variant containing the new property value
     * @throws BusException indicating failure to send the PropertyChanged signal
     */
    public void PropertyChanged(String ifaceName, final String propertyName, final Variant newValue)
        throws BusException {
        Map<String, Variant> propsChanged = new HashMap<String, Variant>();
        String[] invalidatedProps;
        if (newValue == null) {
            props.PropertiesChanged(ifaceName, null, new String [] { propertyName });
        } else {
            props.PropertiesChanged(ifaceName, new HashMap<String, Variant>() {{ put(propertyName, newValue); }}, null);
        }
        props.PropertiesChanged(ifaceName, propsChanged, invalidatedProps);
    }

    /**
     * Sends the PropertiesChanged signal
     *
     * @param iface the BusInterface the property belongs to
     * @param properties list of properties that were changed
     * @throws BusException indicating failure to send the PropertiesChanged signal
     */
    public void PropertiesChanged(Class<?> iface, Set<String> properties)
        throws BusException {
        String ifaceName = InterfaceDescription.getName(iface);
        Map<String, Variant> changedProps = new HashMap<String, Variant>();
        List<String> invalidatedProps = new ArrayList<String>();

        for (String propName : properties) {
            Method m = null;
            try {
                // try to find the get method
                m = iface.getMethod("get" + propName);
            } catch (NoSuchMethodException ex) {
                throw new IllegalArgumentException("Not property with name " + propName + " found");
            }
            BusProperty busPropertyAnn = m.getAnnotation(BusProperty.class);
            if (busPropertyAnn != null) {
                // need to emit
                BusAnnotations bas = m.getAnnotation(BusAnnotations.class);
                if (bas != null) {
                    for (BusAnnotation ba : bas.value()) {
                        if (ba.name().equals("org.freedesktop.DBus.Property.EmitsChangedSignal")) {
                            if (ba.value().equals("true")) {
                                Object o;
                                try {
                                    o = m.invoke(source);
                                } catch (Exception ex) {
                                    throw new BusException("can't get value of property " + propName, ex);
                                }
                                Variant v;
                                if (busPropertyAnn.signature() != null && !busPropertyAnn.signature().isEmpty()) {
                                    v = new Variant(o, busPropertyAnn.signature());
                                } else {
                                    v = new Variant(o);
                                }
                                changedProps.put(propName, v);
                            } else if (ba.value().equals("invalidates")) {
                                invalidatedProps.add(propName);
                            }
                        }
                    }
                }
            }
        }

        props.PropertiesChanged(ifaceName, changedProps, invalidatedProps.toArray(new String[invalidatedProps.size()]));
    }
}
