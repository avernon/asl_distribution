/******************************************************************************
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
 ******************************************************************************/

#include <SceneManager.h>
#include <ControllerClient.h>

#include <qcc/Debug.h>

#include <utility>

#define QCC_MODULE "LAMP_GROUP_MANAGER"

using namespace lsf;
using namespace ajn;

SceneManager::SceneManager(ControllerClient& controllerClient, SceneManagerCallback& callback) :
    Manager(controllerClient),
    callback(callback)
{
    controllerClient.sceneManagerPtr = this;
}

ControllerClientStatus SceneManager::GetAllSceneIDs(void)
{
    QCC_DbgPrintf(("%s", __func__));
    return controllerClient.MethodCallAsyncForReplyWithResponseCodeAndListOfIDs(
               ControllerServiceSceneInterfaceName,
               "GetAllSceneIDs");
}

ControllerClientStatus SceneManager::GetSceneName(const LSFString& sceneID, const LSFString& language)
{
    QCC_DbgPrintf(("%s: sceneID=%s", __func__, sceneID.c_str()));
    MsgArg args[2];
    args[0].Set("s", sceneID.c_str());
    args[1].Set("s", language.c_str());
    return controllerClient.MethodCallAsyncForReplyWithResponseCodeIDLanguageAndName(
               ControllerServiceSceneInterfaceName,
               "GetSceneName",
               args,
               2);
}

ControllerClientStatus SceneManager::SetSceneName(const LSFString& sceneID, const LSFString& sceneName, const LSFString& language)
{
    QCC_DbgPrintf(("%s: sceneID=%s sceneName=%s language=%s", __func__, sceneID.c_str(), sceneName.c_str(), language.c_str()));

    MsgArg args[3];
    args[0].Set("s", sceneID.c_str());
    args[1].Set("s", sceneName.c_str());
    args[2].Set("s", language.c_str());

    return controllerClient.MethodCallAsyncForReplyWithResponseCodeIDAndName(
               ControllerServiceSceneInterfaceName,
               "SetSceneName",
               args,
               3);
}

ControllerClientStatus SceneManager::CreateScene(const Scene& scene, const LSFString& sceneName, const LSFString& language)
{
    QCC_DbgPrintf(("%s", __func__));
    MsgArg args[6];
    scene.Get(&args[0], &args[1], &args[2], &args[3]);
    args[4].Set("s", sceneName.c_str());
    args[5].Set("s", language.c_str());

    return controllerClient.MethodCallAsyncForReplyWithResponseCodeAndID(
               ControllerServiceSceneInterfaceName,
               "CreateScene",
               args,
               6);
}

ControllerClientStatus SceneManager::CreateSceneWithTracking(uint32_t& trackingID, const Scene& scene, const LSFString& sceneName, const LSFString& language)
{
    QCC_DbgPrintf(("%s", __func__));
    MsgArg args[6];
    scene.Get(&args[0], &args[1], &args[2], &args[3]);
    args[4].Set("s", sceneName.c_str());
    args[5].Set("s", language.c_str());

    return controllerClient.MethodCallAsyncForReplyWithResponseCodeIDAndTrackingID(
               trackingID,
               ControllerServiceSceneInterfaceName,
               "CreateScene",
               args,
               6);
}

ControllerClientStatus SceneManager::CreateSceneWithSceneElements(uint32_t& trackingID, const SceneWithSceneElements& sceneWithSceneElements, const LSFString& sceneName, const LSFString& language)
{
    QCC_DbgPrintf(("%s", __func__));

    MsgArg args[3];
    sceneWithSceneElements.Get(&args[0]);
    args[1].Set("s", sceneName.c_str());
    args[2].Set("s", language.c_str());

    return controllerClient.MethodCallAsyncForReplyWithResponseCodeIDAndTrackingID(
               trackingID,
               ControllerServiceSceneWithSceneElementsInterfaceName,
               "CreateSceneWithSceneElements",
               args,
               3);
}

ControllerClientStatus SceneManager::UpdateScene(const LSFString& sceneID, const Scene& scene)
{
    QCC_DbgPrintf(("%s: sceneID=%s", __func__, sceneID.c_str()));
    MsgArg args[5];
    args[0].Set("s", sceneID.c_str());
    scene.Get(&args[1], &args[2], &args[3], &args[4]);

    return controllerClient.MethodCallAsyncForReplyWithResponseCodeAndID(
               ControllerServiceSceneInterfaceName,
               "UpdateScene",
               args,
               5);
}

ControllerClientStatus SceneManager::UpdateSceneWithSceneElements(const LSFString& sceneID, const SceneWithSceneElements& sceneWithSceneElements)
{
    QCC_DbgPrintf(("%s: sceneID=%s", __func__, sceneID.c_str()));
    MsgArg args[2];
    args[0].Set("s", sceneID.c_str());
    sceneWithSceneElements.Get(&args[1]);

    return controllerClient.MethodCallAsyncForReplyWithResponseCodeAndID(
               ControllerServiceSceneWithSceneElementsInterfaceName,
               "UpdateSceneWithSceneElements",
               args,
               2);
}

ControllerClientStatus SceneManager::GetScene(const LSFString& sceneID)
{
    QCC_DbgPrintf(("%s: sceneID=%s", __func__, sceneID.c_str()));
    MsgArg arg;
    arg.Set("s", sceneID.c_str());

    return controllerClient.MethodCallAsync(
               ControllerServiceSceneInterfaceName,
               "GetScene",
               this,
               &SceneManager::GetSceneReply,
               &arg,
               1);
}

ControllerClientStatus SceneManager::GetSceneWithSceneElements(const LSFString& sceneID)
{
    QCC_DbgPrintf(("%s: sceneID=%s", __func__, sceneID.c_str()));
    MsgArg arg;
    arg.Set("s", sceneID.c_str());

    return controllerClient.MethodCallAsync(
               ControllerServiceSceneWithSceneElementsInterfaceName,
               "GetSceneWithSceneElements",
               this,
               &SceneManager::GetSceneWithSceneElementsReply,
               &arg,
               1);
}

ControllerClientStatus SceneManager::ApplyScene(const LSFString& sceneID)
{
    QCC_DbgPrintf(("%s: sceneID=%s", __func__, sceneID.c_str()));
    MsgArg arg;
    arg.Set("s", sceneID.c_str());

    return controllerClient.MethodCallAsyncForReplyWithResponseCodeAndID(
               ControllerServiceSceneInterfaceName,
               "ApplyScene",
               &arg,
               1);
}

void SceneManager::GetSceneReply(Message& message)
{
    QCC_DbgPrintf(("%s", __func__));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerClient.CheckNumArgsInMessage(numArgs, 6) != LSF_OK) {
        return;
    }

    LSFResponseCode responseCode = static_cast<LSFResponseCode>(args[0].v_uint32);
    LSFString sceneID = static_cast<LSFString>(args[1].v_string.str);
    Scene scene(args[2], args[3], args[4], args[5]);

    callback.GetSceneReplyCB(responseCode, sceneID, scene);
}

void SceneManager::GetSceneWithSceneElementsReply(Message& message)
{
    QCC_DbgPrintf(("%s", __func__));
    size_t numArgs;
    const MsgArg* args;
    message->GetArgs(numArgs, args);

    if (controllerClient.CheckNumArgsInMessage(numArgs, 3) != LSF_OK) {
        return;
    }

    LSFResponseCode responseCode = static_cast<LSFResponseCode>(args[0].v_uint32);
    LSFString sceneID = static_cast<LSFString>(args[1].v_string.str);
    SceneWithSceneElements sceneWithSceneElements(args[2]);

    callback.GetSceneWithSceneElementsReplyCB(responseCode, sceneID, sceneWithSceneElements);
}

ControllerClientStatus SceneManager::DeleteScene(const LSFString& sceneID)
{
    QCC_DbgPrintf(("%s: sceneID=%s", __func__, sceneID.c_str()));
    MsgArg arg;
    arg.Set("s", sceneID.c_str());

    return controllerClient.MethodCallAsyncForReplyWithResponseCodeAndID(
               ControllerServiceSceneInterfaceName,
               "DeleteScene",
               &arg,
               1);
}

ControllerClientStatus SceneManager::GetSceneDataSet(const LSFString& sceneID, const LSFString& language)
{
    ControllerClientStatus status = CONTROLLER_CLIENT_OK;

    status = GetScene(sceneID);

    if (CONTROLLER_CLIENT_OK == status) {
        status = GetSceneName(sceneID, language);
    }

    return status;
}

ControllerClientStatus SceneManager::GetSceneWithSceneElementsDataSet(const LSFString& sceneID, const LSFString& language)
{
    ControllerClientStatus status = CONTROLLER_CLIENT_OK;

    status = GetSceneWithSceneElements(sceneID);

    if (CONTROLLER_CLIENT_OK == status) {
        status = GetSceneName(sceneID, language);
    }

    return status;
}
