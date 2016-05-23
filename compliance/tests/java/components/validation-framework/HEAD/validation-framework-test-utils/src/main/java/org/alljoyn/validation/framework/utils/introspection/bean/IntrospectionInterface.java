/*******************************************************************************
 *  Copyright AllSeen Alliance. All rights reserved.
 *
 *     Contributed by Qualcomm Connected Experiences, Inc.,
 *     with authorization from the AllSeen Alliance, Inc.
 *     
 *     Licensed under the Apache License, Version 2.0 (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *     
 *         http://www.apache.org/licenses/LICENSE-2.0
 *     
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 *     
 *     Pursuant to Section 1 of the License, the work of authorship constituting
 *     a Work and any Contribution incorporated in the Work shall mean only that
 *     Contributor's code submissions authored by that Contributor.  Any rights
 *     granted under the License are conditioned upon acceptance of these
 *     clarifications.
 *******************************************************************************/
package org.alljoyn.validation.framework.utils.introspection.bean;

import java.util.Set;
import java.util.TreeSet;

public class IntrospectionInterface extends IntrospectionBaseTag
{
    private Set<IntrospectionMethod> methods = new TreeSet<IntrospectionMethod>();
    private Set<IntrospectionProperty> properties = new TreeSet<IntrospectionProperty>();
    private Set<IntrospectionSignal> signals = new TreeSet<IntrospectionSignal>();
    private Set<IntrospectionAnnotation> annotations = new TreeSet<IntrospectionAnnotation>();

    public Set<IntrospectionMethod> getMethods()
    {
        return methods;
    }

    public Set<IntrospectionProperty> getProperties()
    {
        return properties;
    }

    public Set<IntrospectionSignal> getSignals()
    {
        return signals;
    }

    public Set<IntrospectionAnnotation> getAnnotations()
    {
        return annotations;
    }

    @Override
    public int hashCode()
    {
        final int prime = 31;
        int result = super.hashCode();
        result = prime * result + ((methods == null) ? 0 : methods.hashCode());
        result = prime * result + ((properties == null) ? 0 : properties.hashCode());
        result = prime * result + ((signals == null) ? 0 : signals.hashCode());
        result = prime * result + ((annotations == null) ? 0 : annotations.hashCode());

        return result;
    }

    @Override
    public boolean equals(Object obj)
    {
        if (this == obj)
        {
            return true;
        }
        if (!super.equals(obj))
        {
            return false;
        }
        if (!(obj instanceof IntrospectionInterface))
        {
            return false;
        }
        IntrospectionInterface other = (IntrospectionInterface) obj;
        if (methods == null)
        {
            if (other.methods != null)
            {
                return false;
            }
        }
        else if (!methods.equals(other.methods))
        {
            return false;
        }
        if (properties == null)
        {
            if (other.properties != null)
            {
                return false;
            }
        }
        else if (!properties.equals(other.properties))
        {
            return false;
        }
        if (signals == null)
        {
            if (other.signals != null)
            {
                return false;
            }
        }
        else if (!signals.equals(other.signals))
        {
            return false;
        }
        if (annotations == null)
        {
            if (other.annotations != null)
            {
                return false;
            }
        }
        else if (!annotations.equals(other.annotations))
        {
            return false;
        }

        return true;
    }
}