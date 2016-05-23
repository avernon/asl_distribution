# Copyright AllSeen Alliance. All rights reserved.
#
#    Contributed by Qualcomm Connected Experiences, Inc.,
#    with authorization from the AllSeen Alliance, Inc.
#    
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#    
#        http://www.apache.org/licenses/LICENSE-2.0
#    
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#    
#    Pursuant to Section 1 of the License, the work of authorship constituting
#    a Work and any Contribution incorporated in the Work shall mean only that
#    Contributor's code submissions authored by that Contributor.  Any rights
#    granted under the License are conditioned upon acceptance of these
#    clarifications.

# returns current working directory
TOP := $(dir $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))

ALLJOYN_DIST := ../..
# for use by AllJoyn developers. Code built from alljoyn_core
#ALLJOYN_DIST := ../../build/linux/x86/debug/dist
#ALLJOYN_DIST := ../../build/linux/x86/release/dist
#ALLJOYN_DIST := ../../build/linux/x86_64/debug/dist
#ALLJOYN_DIST := ../../build/linux/x86_64/release/dist
# for use by AllJoyn developers. Code built from master
#ALLJOYN_DIST := ../../../build/linux/x86/debug/dist
#ALLJOYN_DIST := ../../../build/linux/x86/release/dist
#ALLJOYN_DIST := ../../../build/linux/x86_64/debug/dist
#ALLJOYN_DIST := ../../../build/linux/x86_64/release/dist

OBJ_DIR := obj

BIN_DIR := bin

ALLJOYN_LIB := $(ALLJOYN_DIST)/lib/liballjoyn.a

CXXFLAGS = -Wall -pipe -std=c++98 -fno-rtti -fno-exceptions -Wno-long-long -Wno-deprecated -g -DQCC_OS_LINUX -DQCC_OS_GROUP_POSIX -DQCC_CPU_X86

LIBS = -lstdc++ -lcrypto -lpthread -lrt

.PHONY: default clean

default: all

all: mqtt_client mqtt_service

mqtt_client: mqtt_client.o $(ALLJOYN_LIB)
	mkdir -p $(BIN_DIR)
	$(CXX) -o $(BIN_DIR)/$@ $(OBJ_DIR)/mqtt_client.o $(TOP)$(ALLJOYN_LIB) $(LIBS)

mqtt_client.o: bamqttsic_client.cc $(ALLJOYN_LIB)
	mkdir -p $(OBJ_DIR)
	$(CXX) -c $(CXXFLAGS) -I$(ALLJOYN_DIST)/inc -o $(OBJ_DIR)/$@ mqtt_client.cc

mqtt_service: mqtt_service.o $(ALLJOYN_LIB)
	$(CXX) -o $(BIN_DIR)/$@ $(OBJ_DIR)/mqtt_service.o $(TOP)$(ALLJOYN_LIB) $(LIBS)

mqtt_service.o: mqtt_service.cc $(ALLJOYN_LIB)
	$(CXX) -c $(CXXFLAGS) -I$(ALLJOYN_DIST)/inc -o $(OBJ_DIR)/$@ mqtt_service.cc

clean: clean_mqtt_client clean_mqtt_service
	rmdir $(OBJ_DIR)
	rmdir $(BIN_DIR)

clean_mqtt_client:
	rm -f $(OBJ_DIR)/mqtt_client.o $(BIN_DIR)/mqtt_client

clean_mqtt_service:
	rm -f $(OBJ_DIR)/mqtt_service.o $(BIN_DIR)/mqtt_service

clean_nameChange_client:
	rm -f $(OBJ_DIR)/nameChange_client.o $(BIN_DIR)/nameChange_client

clean_signal_service:
	rm -f $(OBJ_DIR)/signal_service.o $(BIN_DIR)/signal_service

clean_signalConsumer_client:
	rm -f $(OBJ_DIR)/signalConsumer_client.o $(BIN_DIR)/signalConsumer_client
