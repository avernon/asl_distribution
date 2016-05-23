/**
 * @file
 */
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

#include "ajs.h"
#include "ajs_io.h"

static const AJS_IO_Info info[] = {
    { AJS_IO_FUNCTION_UART_TX,                                 0, "TX",  "",  "Serial RX"  },
    { AJS_IO_FUNCTION_UART_RX,                                 1, "RX",  "",  "Serial TX"  },
    { AJS_IO_FUNCTION_DIGITAL_IO | AJS_IO_FUNCTION_I2C_SDA,                       2, "D2",  "",  "SDA/Digital Pin 2"  },
    { AJS_IO_FUNCTION_DIGITAL_IO | AJS_IO_FUNCTION_I2C_SCL | AJS_IO_FUNCTION_PWM, 3, "D3",  "",  "SCL/Digital Pin 3"  },
    { AJS_IO_FUNCTION_DIGITAL_IO,                              4, "D4",  "",  "Digital Pin 4"  },
    { AJS_IO_FUNCTION_DIGITAL_IO | AJS_IO_FUNCTION_PWM,        5, "D5",  "",  "Digital Pin 5"  },
    { AJS_IO_FUNCTION_DIGITAL_IO | AJS_IO_FUNCTION_PWM,        6, "D6",  "",  "Digital Pin 6"  },
    { 0,                                                       7, "N/A", "",  "Not available"  },
    { AJS_IO_FUNCTION_DIGITAL_IO,                              8, "D8",  "",  "Digital Pin 8"  },
    { AJS_IO_FUNCTION_DIGITAL_IO | AJS_IO_FUNCTION_PWM,        9, "D9",  "",  "Digital Pin 9"  },
    { AJS_IO_FUNCTION_DIGITAL_IO | AJS_IO_FUNCTION_PWM,       10, "D10", "",  "Digital Pin 10" },
    { AJS_IO_FUNCTION_DIGITAL_IO | AJS_IO_FUNCTION_PWM,       11, "D11", "",  "0igital Pin 11" },
    { AJS_IO_FUNCTION_DIGITAL_IO,                             12, "D12", "",  "Digital Pin 12" },
    { AJS_IO_FUNCTION_DIGITAL_IO,                             13, "D13", "",  "Digital Pin 13" },

    { AJS_IO_FUNCTION_ANALOG_IN, 0xA0, "A0",  "",  "Analog Input Pin 0"   },
    { AJS_IO_FUNCTION_ANALOG_IN, 0xA1, "A1",  "",  "Analog Input Pin 1"   },
    { AJS_IO_FUNCTION_ANALOG_IN, 0xA2, "A2",  "",  "Analog Input Pin 2"   },
    { AJS_IO_FUNCTION_ANALOG_IN, 0xA3, "A3",  "",  "Analog Input Pin 3"   },
    { AJS_IO_FUNCTION_ANALOG_IN, 0xA4, "A4",  "",  "Analog Input Pin 4"   },
    { AJS_IO_FUNCTION_ANALOG_IN, 0xA5, "A5",  "",  "Analog Input Pin 5"   }
};

uint16_t AJS_TargetIO_GetNumPins()
{
    return ArraySize(info);
}

const AJS_IO_Info* AJS_TargetIO_GetInfo(uint16_t pin)
{
    if (pin < ArraySize(info)) {
        return &info[pin];
    } else {
        return NULL;
    }
}
