@rem ******************************************************************************
@rem * Copyright AllSeen Alliance. All rights reserved.
@rem *
@rem *    Contributed by Qualcomm Connected Experiences, Inc.,
@rem *    with authorization from the AllSeen Alliance, Inc.
@rem *    
@rem *    Licensed under the Apache License, Version 2.0 (the "License");
@rem *    you may not use this file except in compliance with the License.
@rem *    You may obtain a copy of the License at
@rem *    
@rem *        http://www.apache.org/licenses/LICENSE-2.0
@rem *    
@rem *    Unless required by applicable law or agreed to in writing, software
@rem *    distributed under the License is distributed on an "AS IS" BASIS,
@rem *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
@rem *    See the License for the specific language governing permissions and
@rem *    limitations under the License.
@rem *    
@rem *    Pursuant to Section 1 of the License, the work of authorship constituting
@rem *    a Work and any Contribution incorporated in the Work shall mean only that
@rem *    Contributor's code submissions authored by that Contributor.  Any rights
@rem *    granted under the License are conditioned upon acceptance of these
@rem *    clarifications.
@rem ******************************************************************************/
@%SystemRoot%\syswow64\WindowsPowershell\v1.0\powershell -c (New-Object Media.SoundPlayer '%1').PlaySync();
