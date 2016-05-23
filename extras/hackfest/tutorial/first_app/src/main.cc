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

#include "MyAllJoynCode.h"
#include <qcc/StringUtil.h>

#include <signal.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>

using namespace qcc;
using namespace ajn;
using namespace std;

/*
 * get a line of input from the the file pointer (most likely stdin).
 * This will capture the the num-1 characters or till a newline character is
 * entered.
 *
 * @param[out] str a pointer to a character array that will hold the user input
 * @param[in]  num the size of the character array 'str'
 * @param[in]  fp  the file pointer the sting will be read from. (most likely stdin)
 *
 * @return returns the same string as 'str' if there has been a read error a null
 *                 pointer will be returned and 'str' will remain unchanged.
 */
char* get_line(char*str, size_t num, FILE*fp)
{
    char*p = fgets(str, num, fp);

    // fgets will capture the '\n' character if the string entered is shorter than
    // num. Remove the '\n' from the end of the line and replace it with nul '\0'.
    if (p != NULL) {
        size_t last = strlen(str) - 1;
        if (str[last] == '\n') {
            str[last] = '\0';
        }
    }
    return p;
}

static qcc::String NextToken(qcc::String& inStr)
{
    qcc::String ret;
    size_t off = inStr.find_first_of(' ');
    if (off == qcc::String::npos) {
        ret = inStr;
        inStr.clear();
    } else {
        ret = inStr.substr(0, off);
        inStr = Trim(inStr.substr(off));
    }
    return Trim(ret);
}

void printHelp() {
    printf("\n");
    printf("listapps                         - List the applications found through discovery\n");
    printf("join <name>                      - Connect to an application\n");
    printf("leave                            - Leave the current session\n");
    printf("listmembers <host|remote>        - Lists the users in the hosted session or current remote session\n");
    printf("tell <host|remote> <name> <msg>  - Executes a \"Tell\" BusMethod call on name sending msg\n");
    printf("share <host|remote> <msg>        - Emits a \"Share\" signal with msg on all users in a session\n");
    printf("broadcast <msg>                  - Emits a \"Broadcast\" signal (sessionless signal) with msg\n");
    printf("quit                             - Shutdown the application and exit\n");
    printf("\n");
} 


int main(int argc, char**argv, char**envArg)
{
    MyAllJoynCode* myAllJoynCode = new MyAllJoynCode();
    myAllJoynCode->initialize("test"); 
    const int bufSize = 1024;
    char buf[bufSize];

    SessionId joinedSessionId = 0;

    // An input loop, to allow for easy extension of the sample that takes in input
    while (get_line(buf, bufSize, stdin)) {
        qcc::String line(buf);
        qcc::String cmd = NextToken(line);
        if (cmd == "help" || cmd == "?") {
            printHelp();
        } else if (cmd == "listapps") {
            std::map<qcc::String, qcc::String> apps = myAllJoynCode->listNearby();
            std::map<qcc::String, qcc::String>::iterator it;
            for (it = apps.begin(); it != apps.end(); ++it) {             
                printf("%s @ %s\n", it->second.c_str(), it->first.c_str());
            }  
            printf("\n");
        } else if (cmd == "listmembers") {
            qcc::String which = NextToken(line);
            std::vector<qcc::String> members;
            if (which == "remote") {
                members = myAllJoynCode->listRemoteSessionMembers();
            } else { //hosted
                members = myAllJoynCode->listHostedSessionMembers();
            }
            for (int i = 0; i < members.size(); i++) {
                printf("In a session with %s @ %s\n", myAllJoynCode->getFriendlyName(members[i]).c_str(), members[i].c_str());
            }
        } else if (cmd == "join") {
            qcc::String name = NextToken(line);
            if (joinedSessionId != 0) {
                /* We are already in a session, so for this application we leave */
                myAllJoynCode->leaveSession(joinedSessionId);
            } 
            short sessionPort = myAllJoynCode->getSessionPort(name);
            joinedSessionId = myAllJoynCode->joinSession(name, sessionPort);
        } else if (cmd == "leave") {
            myAllJoynCode->leaveSession(joinedSessionId);
            joinedSessionId = 0;
        } else if (cmd == "tell") {
            qcc::String which = NextToken(line);
            qcc::String name = NextToken(line);
            qcc::String thought = Trim(line);
            ajn::SessionId sessionId;
            if (which == "host") {
                sessionId = myAllJoynCode->getHostSessionId();
            } else {
                sessionId = joinedSessionId;
            }
            //now lets call the Bus Method to "tell name a thought on a sessoinId"
            qcc::String response;
            QStatus status = myAllJoynCode->doTell(name, thought, sessionId, response); 
            if (status == ER_OK) {
                printf("%s replied with \"%s\"\n", name.c_str(), response.c_str());
            } else {
                printf("Error %d",status);
            }
        } else if (cmd == "share") {
            qcc::String which = NextToken(line);
            qcc::String thought = Trim(line);
            ajn::SessionId sessionId;
            if (which == "host") {
                sessionId = myAllJoynCode->getHostSessionId();
            } else {
                sessionId = joinedSessionId;
            }
            //now lets call the Bus Method to "share a thought on a sessoinId"
            myAllJoynCode->doShare(thought, sessionId);
        } else if (cmd == "broadcast") {
            qcc::String thought = Trim(line);
            //now lets call the Bus Method to "broadcast thought to anyone"
            myAllJoynCode->doBroadcast(thought);
        } else if (cmd == "quit") {
            delete myAllJoynCode;
            return 0;
        } else {
            printHelp();	
        }
    }

} /* main() */
