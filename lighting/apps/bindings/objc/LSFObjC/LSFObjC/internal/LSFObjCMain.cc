/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#include "controller.h"

#define QCC_MODULE "MAIN"

// if we're tracking the child process, we need to pass signals to it
static pid_t g_child_process = 0;
volatile sig_atomic_t g_running = true;
volatile sig_atomic_t isRunning = false;
lsf::controllerservice::LSFAboutDataStore* luminaireDS = NULL;
lsf::controllerservice::ControllerServiceManager* controllerSvcManagerPtrForLuminaire = NULL;

static void SigIntHandler(int sig)
{
    g_running = false;
    if (g_child_process) {
        kill(g_child_process, SIGINT);
    }
}

static void SigTermHandler(int sig)
{
    g_running = false;
    if (g_child_process) {
        kill(g_child_process, SIGTERM);
    }
}

static std::string factoryConfigFile = "OEMConfig.ini";
static std::string configFile = "Config.ini";
static std::string lampGroupFile = "LampGroups.lsf";
static std::string presetFile = "Presets.lsf";
static std::string transitionEffectFile = "TransitionEffects.lsf";
static std::string pulseEffectFile = "PulseEffects.lsf";
static std::string sceneElementFile = "SceneElements.lsf";
static std::string sceneFile = "Scenes.lsf";
static std::string sceneWithSceneElementFile = "SceneWithSceneElements.lsf";
static std::string masterSceneFile = "MasterScenes.lsf";
static std::string storeFile = "LightingControllerService";
static std::string factoryConfigFilePath = factoryConfigFile;
static std::string configFilePath = configFile;
static std::string lampGroupFilePath = lampGroupFile;
static std::string presetFilePath = presetFile;
static std::string transitionEffectFilePath = transitionEffectFile;
static std::string pulseEffectFilePath = pulseEffectFile;
static std::string sceneElementFilePath = sceneElementFile;
static std::string sceneFilePath = sceneFile;
static std::string sceneWithSceneElementFilePath = sceneWithSceneElementFile;
static std::string masterSceneFilePath = masterSceneFile;
static std::string storeFilePath = storeFile;
static std::string storeLocation;
static bool runForeground = false;
static bool disableBackgroundLogging = true;

static void usage(int argc, char** argv)
{
    printf("Usage: %s -h ? -k <absolute_directory_path> -f\n\n", argv[0]);
    printf("Options:\n");
    printf("   -h                    = Print this help message\n");
    printf("   -?                    = Print this help message\n");
    printf("   -f                    = Run the Controller Service as a foreground process\n");
    printf("   -k <absolute_directory_path>   = The absolute path to a directory required to store the AllJoyn KeyStore, Persistent Store and read/write the Config FilePaths\n\n");
    printf("   -v                    = Print the version number and exit\n");
    printf("   -l                    = Enable background logging\n");
    printf("Default:\n");
    printf("    %s\n", argv[0]);
}

static void parseCommandLine(int argc, char** argv)
{
    /* Parse command line args */
    for (int i = 1; i < argc; ++i) {
        if (0 == strcmp("-h", argv[i]) || 0 == strcmp("-?", argv[i])) {
            usage(argc, argv);
            exit(0);
        } else if (0 == strcmp("-v", argv[i])) {
            printf("Version: %u\n", CONTROLLER_SERVICE_VERSION);
            exit(0);
        } else if (0 == strcmp("-k", argv[i])) {
            ++i;
            if (i == argc) {
                printf("option %s requires a parameter\n", argv[i - 1]);
                usage(argc, argv);
                exit(1);
            } else {
                storeLocation = argv[i];
                char* dirPath = getenv("HOME");
                if (dirPath == NULL) {
                    dirPath = const_cast<char*>("/");
                }
                static std::string absDirPath = std::string(dirPath) + "/" + storeLocation + "/";
                factoryConfigFilePath = absDirPath + factoryConfigFile;
                configFilePath = absDirPath + configFile;
                lampGroupFilePath = absDirPath + lampGroupFile;
                presetFilePath = absDirPath + presetFile;
                transitionEffectFilePath = absDirPath + transitionEffectFile;
                pulseEffectFilePath = absDirPath + pulseEffectFile;
                sceneElementFilePath = absDirPath + sceneElementFile;
                sceneFilePath = absDirPath + sceneFile;
                sceneWithSceneElementFilePath = absDirPath + sceneWithSceneElementFile;
                masterSceneFilePath = absDirPath + masterSceneFile;
                storeFilePath = storeLocation + "/" + storeFile;
            }
        } else if (0 == strcmp("-f", argv[i])) {
            runForeground = true;
        } else if (0 == strcmp("-l", argv[i])) {
            disableBackgroundLogging = false;
        } else {
            printf("Unknown option %s\n", argv[i]);
            usage(argc, argv);
            exit(-1);
        }
    }
}

void lsf_Sleep(uint32_t msec)
{
    usleep(1000 * msec);
}

void RunService(bool listenToInterrupts)
{
    QCC_DbgTrace(("%s", __func__));
    if (!storeLocation.empty()) {
        chdir(storeLocation.c_str());
    }

    if (listenToInterrupts) {
        signal(SIGINT, SigIntHandler);
        signal(SIGTERM, SigTermHandler);
    }

    const char* res = getControllerDefaultDeviceId(); //The device id is computed by the objective-c part
    QCC_DbgTrace(("%s deviceId: %s", __func__, res));
    printf("Device ID returned from iOS App level %s\n", res);
    luminaireDS = new lsf::controllerservice::LSFAboutDataStore(factoryConfigFilePath.c_str(), configFilePath.c_str(), res);

    if (luminaireDS == NULL) {
        QCC_LogError(ER_OUT_OF_MEMORY, ("%s: Failed to allocate memory for LSFAboutDataStore", __func__));
        printf("Failed to allocate memory for LSFAboutDataStore\n");
        exit(-1);
    }

    lsf::controllerservice::ControllerServiceManager* controllerSvcManagerPtr = InitializeControllerServiceManager(factoryConfigFilePath, configFilePath, lampGroupFilePath, presetFilePath, transitionEffectFilePath, pulseEffectFilePath, sceneElementFilePath, sceneFilePath, sceneWithSceneElementFilePath, masterSceneFilePath);

    if (controllerSvcManagerPtr == NULL) {
        QCC_LogError(ER_OUT_OF_MEMORY, ("%s: Failed to start the Controller Service Manager", __func__));
        printf("Failed to start the Controller Service Manager\n");
        exit(-1);
    }

    luminaireDS->SetControllerServicePtr(controllerSvcManagerPtr->GetControllerServicePtr());

    QStatus status = controllerSvcManagerPtr->Start(storeLocation.empty() ? NULL : storeFilePath.c_str());
    controllerSvcManagerPtrForLuminaire = controllerSvcManagerPtr;
    isRunning = true;

    if (status == ER_OK) {
        while (g_running && controllerSvcManagerPtr->IsRunning()) {
            lsf_Sleep(OEM_CS_TIMEOUT_MS_CONNECTED_TO_ROUTING_NODE);
        }
    }

    QCC_LogError(ER_FAIL, ("%s: Failed to talk to bus", __func__));

    if (controllerSvcManagerPtr) {
        controllerSvcManagerPtr->Stop();
        controllerSvcManagerPtr->Join();
        delete luminaireDS;
        luminaireDS = NULL;
        controllerSvcManagerPtrForLuminaire = NULL;
        delete controllerSvcManagerPtr;
        controllerSvcManagerPtr = NULL;
        QCC_DbgPrintf(("%s: After delete controllerSvcManagerPtr", __func__));
    }

    isRunning = false;
}


void RunAndMonitor()
{
    // we are a background process!
    if (disableBackgroundLogging) {
        fclose(stdin);
        fclose(stdout);
        fclose(stderr);
    }

    signal(SIGINT, SigIntHandler);
    signal(SIGTERM, SigTermHandler);

    while (g_running) {
        pid_t pid = fork();

        if (pid == -1) {
            // failed to fork!
            exit(-1);
        } else if (pid == 0) {
            QCC_DbgPrintf(("%s: Starting Child", __func__));
            RunService(false);
            break;
        } else {
            g_child_process = pid;
            int status = 0;
            QCC_DbgPrintf(("%s: Child PID %d", __func__, pid));
            // wait for exit
            wait(&status);
            QCC_DbgPrintf(("%s: Exited child PID %d", __func__, pid));
            lsf_Sleep(1000);
        }
    }
}

void ControllerServiceStop()
{
    SigIntHandler(SIGINT);

    while (isRunning) {
        lsf_Sleep(1000);
    }
}

int runMain(int argc, char** argv)
{
    AJInitializer ajInitializer;
    if (ajInitializer.Initialize() != ER_OK) {
        return -1;
    }

    QCC_DbgTrace(("%s", __func__));

    parseCommandLine(argc, argv);

    if (runForeground) {
        QCC_DbgPrintf(("%s: Running in foreground", __func__));
        RunService(true);
    } else {
        QCC_DbgPrintf(("%s: Running in background", __func__));
        QCC_LogError(ER_OK, ("%s: You are running Controller Service in the default background mode. To debug, start Controller Service with the -f option", __func__));
        pid_t pid = fork();

        if (pid == -1) {
            return -1;
        } else if (pid == 0) {
            QCC_DbgPrintf(("%s: Starting Monitor", __func__));
            RunAndMonitor();
            return 0;
        } else {
            // Unneeded parent process, just exit.
            QCC_DbgPrintf(("%s: Monitor PID %d", __func__, pid));
            QCC_DbgPrintf(("%s: Exiting Main", __func__));
            return 0;
        }
    }
    
    return 0;
}
