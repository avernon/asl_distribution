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

public class IntrospectionProperty extends IntrospectionBaseTag implements Comparable<IntrospectionProperty>
{
    private String type;
    private String access;

    public String getType()
    {
        return type;
    }

    public void setType(String type)
    {
        this.type = type;
    }

    public String getAccess()
    {
        return access;
    }

    public void setAccess(String access)
    {
        this.access = access;
    }

    @Override
    public int compareTo(IntrospectionProperty introspectionProperty)
    {
        return getName().compareTo(introspectionProperty.getName());
    }

    @Override
    public int hashCode()
    {
        final int prime = 31;
        int result = super.hashCode();
        result = prime * result + ((access == null) ? 0 : access.hashCode());
        result = prime * result + ((type == null) ? 0 : type.hashCode());

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
        if (!(obj instanceof IntrospectionProperty))
        {
            return false;
        }
        IntrospectionProperty other = (IntrospectionProperty) obj;
        if (access == null)
        {
            if (other.access != null)
            {
                return false;
            }
        }
        else if (!access.equals(other.access))
        {
            return false;
        }
        if (type == null)
        {
            if (other.type != null)
            {
                return false;
            }
        }
        else if (!type.equals(other.type))
        {
            return false;
        }

        return true;
    }

    @Override
    public String toString()
    {
        StringBuilder builder = new StringBuilder();
        builder.append("Property [name=");
        builder.append(getName());
        builder.append(", type=");
        builder.append(type);
        builder.append(", access=");
        builder.append(access);
        builder.append("]");

        return builder.toString();
    }
}