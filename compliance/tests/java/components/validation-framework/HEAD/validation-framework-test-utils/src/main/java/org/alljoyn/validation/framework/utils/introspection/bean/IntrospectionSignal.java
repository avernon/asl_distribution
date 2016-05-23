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

import java.util.ArrayList;
import java.util.List;

public class IntrospectionSignal extends IntrospectionBaseTag implements Comparable<IntrospectionSignal>
{
    private List<IntrospectionArg> args = new ArrayList<IntrospectionArg>();

    public List<IntrospectionArg> getArgs()
    {
        return args;
    }

    public void setArgs(List<IntrospectionArg> args)
    {
        this.args = args;
    }

    @Override
    public int compareTo(IntrospectionSignal introspectionSignal)
    {
        return getName().compareTo(introspectionSignal.getName());
    }

    @Override
    public int hashCode()
    {
        final int prime = 31;
        int result = super.hashCode();
        result = prime * result + ((args == null) ? 0 : args.hashCode());

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
        if (!(obj instanceof IntrospectionSignal))
        {
            return false;
        }
        IntrospectionSignal other = (IntrospectionSignal) obj;
        if (args == null)
        {
            if (other.args != null)
            {
                return false;
            }
        }
        else if (!args.equals(other.args))
        {
            return false;
        }

        return true;
    }

    @Override
    public String toString()
    {
        StringBuilder builder = new StringBuilder();
        builder.append("Signal [name=");
        builder.append(getName());
        builder.append(", args=");
        builder.append(args);
        builder.append("]");

        return builder.toString();
    }
}