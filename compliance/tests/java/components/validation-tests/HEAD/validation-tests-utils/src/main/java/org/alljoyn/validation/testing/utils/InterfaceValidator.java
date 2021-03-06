/*******************************************************************************
 *  Copyright (c) 2013 - 2014, AllSeen Alliance. All rights reserved.
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
package org.alljoyn.validation.testing.utils;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.alljoyn.validation.framework.ValidationTestContext;
import org.alljoyn.validation.framework.utils.introspection.IntrospectionXmlParser;
import org.alljoyn.validation.framework.utils.introspection.bean.InterfaceDetail;
import org.alljoyn.validation.framework.utils.introspection.bean.IntrospectionAnnotation;
import org.alljoyn.validation.framework.utils.introspection.bean.IntrospectionInterface;
import org.alljoyn.validation.framework.utils.introspection.bean.IntrospectionMethod;
import org.alljoyn.validation.framework.utils.introspection.bean.IntrospectionNode;
import org.alljoyn.validation.framework.utils.introspection.bean.IntrospectionProperty;
import org.alljoyn.validation.framework.utils.introspection.bean.IntrospectionSignal;
import org.alljoyn.validation.testing.utils.log.Logger;
import org.alljoyn.validation.testing.utils.log.LoggerFactory;

public class InterfaceValidator
{
    private List<IntrospectionNode> introspectionNodesLoadedFromXmlFiles = new ArrayList<IntrospectionNode>();
    private IntrospectionXmlParser introspectionXmlParser;
    private ValidationTestContext validationTestContext;
    private static final String TAG = "InterfaceValidator";
    private static final Logger logger = LoggerFactory.getLogger(TAG);

    public InterfaceValidator(ValidationTestContext validationTestContext)
    {
        this.validationTestContext = validationTestContext;
    }

    public ValidationResult validate(InterfaceDetail interfaceDetail)
    {
        StringBuilder failureReasonBuilder = new StringBuilder();
        boolean valid = true;

        for (IntrospectionInterface standardizedIntrospectionInterface : interfaceDetail.getIntrospectionInterfaces())
        {
            ValidationResult validationResult = validateInterface(standardizedIntrospectionInterface, interfaceDetail.getPath());

            if (!validationResult.isValid())
            {
                valid = false;
                appendToFailureReason(failureReasonBuilder, validationResult.getFailureReason());
            }
        }

        return new ValidationResult(valid, failureReasonBuilder.toString());
    }

    public ValidationResult validate(List<InterfaceDetail> interfaceDetailList)
    {
        StringBuilder failureReasonBuilder = new StringBuilder();
        boolean valid = true;

        for (InterfaceDetail interfaceDetail : interfaceDetailList)
        {
            ValidationResult validationResult = validate(interfaceDetail);

            if (!validationResult.isValid())
            {
                valid = false;
                appendToFailureReason(failureReasonBuilder, validationResult.getFailureReason());
            }
        }

        return new ValidationResult(valid, failureReasonBuilder.toString());
    }

    List<String> getXmlFilesToBeLoaded()
    {
        return Arrays.asList(IntrospectionXmlFile.About.getValue(), IntrospectionXmlFile.Introspectable.getValue(), IntrospectionXmlFile.Action.getValue(),
                IntrospectionXmlFile.Audio.getValue(), IntrospectionXmlFile.Config.getValue(), IntrospectionXmlFile.Container.getValue(),
                IntrospectionXmlFile.ControlPanel.getValue(), IntrospectionXmlFile.DeviceIcon.getValue(), IntrospectionXmlFile.Dialog.getValue(),
                IntrospectionXmlFile.HTTPControl.getValue(), IntrospectionXmlFile.LabelProperty.getValue(), IntrospectionXmlFile.ListProperty.getValue(),
                IntrospectionXmlFile.Notification.getValue(), IntrospectionXmlFile.NotificationAction.getValue(), IntrospectionXmlFile.Onboarding.getValue(),
                IntrospectionXmlFile.Peer.getValue(), IntrospectionXmlFile.Property.getValue(), IntrospectionXmlFile.Clock.getValue(),
                IntrospectionXmlFile.TimeAuthority.getValue(), IntrospectionXmlFile.Alarm.getValue(), IntrospectionXmlFile.AlarmFactory.getValue(),
                IntrospectionXmlFile.Timer.getValue(), IntrospectionXmlFile.TimerFactory.getValue(), IntrospectionXmlFile.GWAgentCtrlAcl.getValue(),
                IntrospectionXmlFile.GWAgentCtrlAclMgmt.getValue(), IntrospectionXmlFile.GWAgentCtrlApp.getValue(), IntrospectionXmlFile.GWAgentCtrlAppMgmt.getValue(),
                IntrospectionXmlFile.GWAgentConnectorApp.getValue());
    }

    private ValidationResult validateInterface(IntrospectionInterface standardizedIntrospectionInterface, String path)
    {
        ValidationResult validationResult = null;
        InterfaceDetail interfaceDetail = getInterfaceDetail(getIntrospectionNodesLoadedFromXmlFiles(), standardizedIntrospectionInterface.getName());

        if (interfaceDetail == null)
        {
            logger.warn(String.format("Interface definition does not exist for: %s", standardizedIntrospectionInterface.getName()));
            validationResult = new ValidationResult(true, null);
        }
        else
        {
            validationResult = compare(interfaceDetail, standardizedIntrospectionInterface, path);
        }

        return validationResult;
    }

    private ValidationResult compare(InterfaceDetail interfaceDetail, IntrospectionInterface standardizedIntrospectionInterface, String path)
    {
        boolean valid = true;
        StringBuilder failureReasonBuilder = new StringBuilder();
        IntrospectionInterface expectedIntrospectionInterface = interfaceDetail.getIntrospectionInterfaces().get(0);

        if (interfaceDetail.getPath() != null && !interfaceDetail.getPath().equals(path))
        {
            valid = false;
            appendToFailureReason(failureReasonBuilder, " - Interface ");
            appendToFailureReason(failureReasonBuilder, standardizedIntrospectionInterface.getName());
            appendToFailureReason(failureReasonBuilder, " found at invalid path ");
            appendToFailureReason(failureReasonBuilder, path);
        }

        ValidationResult methodValidationResult = new SetValidator<IntrospectionMethod>().validate(expectedIntrospectionInterface.getMethods(),
                standardizedIntrospectionInterface.getMethods());
        ValidationResult propertyValidationResult = new SetValidator<IntrospectionProperty>().validate(expectedIntrospectionInterface.getProperties(),
                standardizedIntrospectionInterface.getProperties());
        ValidationResult signalValidationResult = new SetValidator<IntrospectionSignal>().validate(expectedIntrospectionInterface.getSignals(),
                standardizedIntrospectionInterface.getSignals());
        ValidationResult annotationValidationResult = new SetValidator<IntrospectionAnnotation>().validate(expectedIntrospectionInterface.getAnnotations(),
                standardizedIntrospectionInterface.getAnnotations());

        if (!methodValidationResult.isValid() || !propertyValidationResult.isValid() || !signalValidationResult.isValid() || !annotationValidationResult.isValid())
        {
            valid = false;

            if (isVersionPropertyMissing(expectedIntrospectionInterface, propertyValidationResult))
            {
                logger.warn(String.format("Ignoring interface property match comparison: %s", propertyValidationResult.getFailureReason()));
                validationTestContext.addNote(String.format("Interface definition does not match for %s - %s", standardizedIntrospectionInterface.getName(),
                        propertyValidationResult.getFailureReason()));
                valid = true;
            }
            if (isUndefinedMethodPresentForConfigInterface(expectedIntrospectionInterface, methodValidationResult))
            {
                logger.warn(String.format("Ignoring interface method match comparison: %s", methodValidationResult.getFailureReason()));
                validationTestContext.addNote(String.format("Interface definition does not match for %s - %s", standardizedIntrospectionInterface.getName(),
                        methodValidationResult.getFailureReason()));
                valid = true;
            }
            if (isAnnotationMissingForPeerAuthenticationInterface(expectedIntrospectionInterface, annotationValidationResult))
            {
                logger.warn(String.format("Ignoring interface annotation match comparison: %s", annotationValidationResult.getFailureReason()));
                valid = true;
            }
            if (!valid)
            {
                appendToFailureReason(failureReasonBuilder, methodValidationResult.getFailureReason());
                appendToFailureReason(failureReasonBuilder, propertyValidationResult.getFailureReason());
                appendToFailureReason(failureReasonBuilder, signalValidationResult.getFailureReason());
                appendToFailureReason(failureReasonBuilder, annotationValidationResult.getFailureReason());
                appendToFailureReason(failureReasonBuilder, " ----------- ");
            }
        }

        if (!valid)
        {
            failureReasonBuilder.insert(0, "Interface definition does not match for " + standardizedIntrospectionInterface.getName());
        }

        return new ValidationResult(valid, failureReasonBuilder.toString());
    }

    private boolean isVersionPropertyMissing(IntrospectionInterface expectedIntrospectionInterface, ValidationResult propertyValidationResult)
    {
        return !propertyValidationResult.isValid()
                && (expectedIntrospectionInterface.getName().equals("org.alljoyn.Config") || expectedIntrospectionInterface.getName().equals("org.alljoyn.Notification"))
                && propertyValidationResult.getFailureReason().equals(" - Missing Property [name=Version, type=q, access=read]");
    }

    private boolean isUndefinedMethodPresentForConfigInterface(IntrospectionInterface expectedIntrospectionInterface, ValidationResult methodValidationResult)
    {
        return !methodValidationResult.isValid() && expectedIntrospectionInterface.getName().equals("org.alljoyn.Config")
                && methodValidationResult.getFailureReason().equals(" - Undefined Method [name=getVersion, args=[[type=q]], annotations=[]]");
    }

    private boolean isAnnotationMissingForPeerAuthenticationInterface(IntrospectionInterface expectedIntrospectionInterface, ValidationResult annotationValidationResult)
    {
        return !annotationValidationResult.isValid() && expectedIntrospectionInterface.getName().equals("org.alljoyn.Bus.Peer.Authentication")
                && annotationValidationResult.getFailureReason().contains("Missing Annotation") && !annotationValidationResult.getFailureReason().contains("Undefined Annotation");
    }

    private List<IntrospectionNode> getIntrospectionNodesLoadedFromXmlFiles()
    {
        if (introspectionNodesLoadedFromXmlFiles.isEmpty())
        {
            introspectionXmlParser = new IntrospectionXmlParser();
            buildIntrospectionNodesFromXmlFiles();
        }

        return introspectionNodesLoadedFromXmlFiles;
    }

    private void buildIntrospectionNodesFromXmlFiles()
    {
        for (String xmlFileToBeLoaded : getXmlFilesToBeLoaded())
        {
            InputStream inputStream = getClass().getClassLoader().getResourceAsStream(xmlFileToBeLoaded);

            try
            {
                introspectionNodesLoadedFromXmlFiles.add(introspectionXmlParser.parseXML(inputStream));
            }
            catch (Exception exception)
            {
                logger.error("While loading xml " + xmlFileToBeLoaded + " exception caught: " + exception);
            }
        }
    }

    private InterfaceDetail getInterfaceDetail(List<IntrospectionNode> introspectionNodes, String introspectionInterfaceName)
    {
        for (IntrospectionNode introspectionNode : introspectionNodes)
        {
            for (IntrospectionInterface introspectionInterface : introspectionNode.getInterfaces())
            {
                if (introspectionInterfaceName.equals(introspectionInterface.getName()))
                {
                    List<IntrospectionInterface> interfaces = new ArrayList<IntrospectionInterface>();
                    interfaces.add(introspectionInterface);

                    return new InterfaceDetail(introspectionNode.getName(), interfaces);
                }
            }
        }

        return null;
    }

    private void appendToFailureReason(StringBuilder failureReasonBuilder, String reason)
    {
        if (!reason.trim().isEmpty())
        {
            failureReasonBuilder.append(reason);
        }
    }
}
