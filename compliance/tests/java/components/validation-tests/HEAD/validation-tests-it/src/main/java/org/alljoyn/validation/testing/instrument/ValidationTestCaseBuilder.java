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
package org.alljoyn.validation.testing.instrument;

import java.lang.reflect.Method;
import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import junit.framework.TestCase;

import org.alljoyn.validation.framework.ValidationBaseTestCase;
import org.alljoyn.validation.framework.ValidationTestCase;
import org.alljoyn.validation.framework.annotation.Disabled;
import org.alljoyn.validation.framework.annotation.ValidationTest;
import org.alljoyn.validation.testing.utils.ValidationTestComparator;

public class ValidationTestCaseBuilder
{
    private String className;
    private Class<? extends TestCase> clazz;
    private String methodName;
    private Method method;
    private String testName;

    public static class BaseFailureTestCase extends ValidationBaseTestCase
    {
        private String testDesc;

        public BaseFailureTestCase(String testDesc)
        {
            this.testDesc = testDesc;
            setName("testMethod");
        }

        public void testMethod()
        {

        }

        @Override
        public String toString()
        {
            return testDesc;
        }
    }

    public static class FailureTestCase extends BaseFailureTestCase
    {
        private String message;

        public FailureTestCase(String testDesc, String message)
        {
            super(testDesc);
            this.message = message;
        }

        @Override
        protected void runTest() throws Throwable
        {
            fail(message);
        }
    }

    public static class ErrorTestCase extends BaseFailureTestCase
    {
        private Throwable throwable;

        public ErrorTestCase(String testDesc, Throwable throwable)
        {
            super(testDesc);
            this.throwable = throwable;
        }

        @Override
        protected void runTest() throws Throwable
        {
            throw throwable;
        }
    }

    public static ValidationTestCaseBuilder allTestCasesFromClass(String className)
    {
        ValidationTestCaseBuilder builder = new ValidationTestCaseBuilder();
        builder.className = className;
        return builder;
    }

    public static ValidationTestCaseBuilder allTestCasesFromClass(Class<? extends TestCase> clazz)
    {
        ValidationTestCaseBuilder builder = new ValidationTestCaseBuilder();
        builder.clazz = clazz;
        return builder;
    }

    public static ValidationTestCaseBuilder testCaseByMethodName(String className, String methodName)
    {
        ValidationTestCaseBuilder builder = new ValidationTestCaseBuilder();
        builder.className = className;
        builder.methodName = methodName;
        return builder;
    }

    public static ValidationTestCaseBuilder testCaseByMethodName(Class<? extends TestCase> clazz, String methodName)
    {
        ValidationTestCaseBuilder builder = new ValidationTestCaseBuilder();
        builder.clazz = clazz;
        builder.methodName = methodName;
        return builder;
    }

    public static ValidationTestCaseBuilder testCaseByMethod(Class<? extends TestCase> clazz, Method method)
    {
        ValidationTestCaseBuilder builder = new ValidationTestCaseBuilder();
        builder.clazz = clazz;
        builder.method = method;
        return builder;
    }

    public static ValidationTestCaseBuilder testCaseByTestName(String className, String testName)
    {
        ValidationTestCaseBuilder builder = new ValidationTestCaseBuilder();
        builder.className = className;
        builder.testName = testName;
        return builder;
    }

    public static ValidationTestCaseBuilder testCaseByTestName(Class<? extends TestCase> clazz, String testName)
    {
        ValidationTestCaseBuilder builder = new ValidationTestCaseBuilder();
        builder.clazz = clazz;
        builder.testName = testName;
        return builder;
    }

    public List<TestCase> build()
    {
        List<TestCase> testCases = null;
        try
        {
            populateValues();

            if (clazz == null)
            {
                lookupClassForClassName();
            }

            checkThatClassIsAValidationTestCase(clazz);

            if (testName != null)
            {
                lookupTestCaseMethodFromTestName();
            }
            else if ((method == null) && (methodName != null))
            {
                lookupTestCaseMethodFromMethodName();
            }

            if (method == null)
            {
                testCases = getAllTestCasesFromClass();
            }
            else
            {
                testCases = getListWithSingleTestCase(getSingleTestCaseInstance(clazz, method));
            }

        }
        catch (FailTestCaseException e)
        {
            testCases = getListWithSingleTestCase(new FailureTestCase(getTestDescription(), e.getMessage()));
        }
        catch (ErrorTestCaseException e)
        {
            testCases = getListWithSingleTestCase(new ErrorTestCase(getTestDescription(), e.getCause()));
        }
        return testCases;
    }

    private String getTestDescription()
    {
        String testDesc = null;

        String methodDesc = null;
        if (testName != null)
        {
            methodDesc = testName;
        }
        else
        {
            methodDesc = methodName;
        }

        if (methodDesc == null)
        {
            testDesc = className;
        }
        else
        {
            testDesc = methodDesc + "(" + className + ")";
        }
        return testDesc;
    }

    private List<TestCase> getListWithSingleTestCase(TestCase testCase)
    {
        List<TestCase> testCases = new ArrayList<TestCase>();
        testCases.add(testCase);
        return testCases;
    }

    protected void populateValues()
    {
        if (clazz != null)
        {
            className = clazz.getName();
        }
        if (method != null)
        {
            methodName = method.getName();
        }
    }

    private void lookupTestCaseMethodFromTestName() throws FailTestCaseException
    {
        for (Method classMethod : clazz.getMethods())
        {
            ValidationTest validationTest = classMethod.getAnnotation(ValidationTest.class);
            if ((validationTest != null) && testName.equals(validationTest.name()))
            {
                method = classMethod;
                break;
            }
        }
        if (method == null)
        {
            throw new FailTestCaseException(String.format("No test case annotated as '%s' found in %s", testName, className));
        }
    }

    private void lookupTestCaseMethodFromMethodName() throws ErrorTestCaseException
    {
        Exception exception = null;
        try
        {
            method = clazz.getMethod(methodName);
        }
        catch (SecurityException e)
        {
            exception = e;
        }
        catch (NoSuchMethodException e)
        {
            exception = e;
        }
        if (exception != null)
        {
            throw new ErrorTestCaseException(exception);
        }
    }

    private static class FailTestCaseException extends Exception
    {
        private static final long serialVersionUID = 1L;

        FailTestCaseException(String message)
        {
            super(message);
        }
    }

    private static class ErrorTestCaseException extends Exception
    {
        private static final long serialVersionUID = 1L;

        ErrorTestCaseException(Exception e)
        {
            super(e);
        }
    }

    private void lookupClassForClassName() throws FailTestCaseException, ErrorTestCaseException
    {
        Class<?> retrievedClass = getClassForName(className);
        checkThatClassIsATestCase(retrievedClass);
        clazz = castToTestCase(retrievedClass);
    }

    private static Class<?> getClassForName(String className) throws ErrorTestCaseException
    {
        Class<?> retrievedClass = null;
        try
        {
            retrievedClass = Class.forName(className);
        }
        catch (ClassNotFoundException e)
        {
            throw new ErrorTestCaseException(e);
        }
        return retrievedClass;
    }

    private static void checkThatClassIsATestCase(Class<?> clazzToCheck) throws FailTestCaseException
    {
        if (!TestCase.class.isAssignableFrom(clazzToCheck))
        {
            throw new FailTestCaseException(String.format("Test case must extend from %s", TestCase.class.getName()));
        }
    }

    private static void checkThatClassIsAValidationTestCase(Class<? extends TestCase> clazzToCheck) throws FailTestCaseException
    {
        if (!ValidationTestCase.class.isAssignableFrom(clazzToCheck))
        {
            throw new FailTestCaseException(String.format("Test case must implement %s", ValidationTestCase.class.getName()));
        }
    }

    @SuppressWarnings("unchecked")
    private static Class<? extends TestCase> castToTestCase(Class<?> clazz)
    {
        return (Class<? extends TestCase>) clazz;
    }

    private List<TestCase> getAllTestCasesFromClass() throws FailTestCaseException, ErrorTestCaseException
    {
        List<TestCase> testCases = new ArrayList<TestCase>();

        List<Method> methods = getTestCaseMethodsFromClass(clazz);
        if (methods.size() > 0)
        {
            Collections.sort(methods, ValidationTestComparator.getInstance());
            for (Method method : methods)
            {
                testCases.add(getSingleTestCaseInstance(clazz, method));
            }
        }
        else
        {
            String className = clazz.getName();
            testCases.add(new FailureTestCase(className, String.format("No test cases annotated with ValidationTest in %s", className)));
        }
        return testCases;
    }

    private static List<Method> getTestCaseMethodsFromClass(Class<? extends TestCase> clazz)
    {
        List<Method> methods = new ArrayList<Method>();
        for (Method method : clazz.getMethods())
        {
            if (isTestCase(method) && isEnabled(method))
            {
                methods.add(method);
            }
        }
        return methods;
    }

    private static boolean isEnabled(Method method)
    {
        Disabled disabled = method.getAnnotation(Disabled.class);
        return (disabled == null);
    }

    private static boolean isTestCase(Method method)
    {
        ValidationTest validationTest = method.getAnnotation(ValidationTest.class);
        return (method.getName().startsWith("test") && (validationTest != null));
    }

    private TestCase getSingleTestCaseInstance(Class<? extends TestCase> testCaseClass, Method testCaseMethod) throws FailTestCaseException, ErrorTestCaseException
    {
        ValidationTest validationTest = testCaseMethod.getAnnotation(ValidationTest.class);
        Disabled disabled = testCaseMethod.getAnnotation(Disabled.class);

        if (!testCaseMethod.getName().startsWith("test"))
        {
            throw new FailTestCaseException(formatMessage("The test case method name {1} in {0} does not start with 'test'", testCaseClass, testCaseMethod));
        }
        else if (validationTest == null)
        {
            throw new FailTestCaseException(formatMessage("The test case method name {1} in {0} is not annotated with ValidationTest", testCaseClass, testCaseMethod));
        }
        else if (disabled != null)
        {
            throw new FailTestCaseException(formatMessage("The test case method name {1} in {0} is annotated with Disabled", testCaseClass, testCaseMethod));
        }

        return instantiateTestCase(testCaseClass, testCaseMethod);
    }

    private String formatMessage(String formatString, Class<? extends TestCase> testCaseClass, Method testCaseMethod)
    {
        String methodName = method.getName();
        String className = clazz.getName();
        return MessageFormat.format(formatString, className, methodName);
    }

    private TestCase instantiateTestCase(Class<? extends TestCase> testCaseClass, Method testCaseMethod) throws ErrorTestCaseException
    {
        TestCase testCase = null;
        try
        {
            testCase = testCaseClass.newInstance();
            testCase.setName(testCaseMethod.getName());
        }
        catch (Exception exception)
        {
            throw new ErrorTestCaseException(exception);
        }
        return testCase;
    }

}
