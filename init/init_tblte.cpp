/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "vendor_init.h"
#include <cutils/properties.h>
#include "log.h"
#include "util.h"
#include <sys/system_properties.h>

#define ISMATCH(a,b) (!strncmp(a,b,PROP_VALUE_MAX))

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void init_variant_properties() {
    char platform[PROP_VALUE_MAX];
    char bootloader[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char devicename[PROP_VALUE_MAX];
    int rc;

    rc = property_get("ro.board.platform", platform, NULL);
    if (!rc || !ISMATCH(platform, ANDROID_TARGET))
    return;

    property_get("ro.bootloader", bootloader, NULL);;

    if (strstr(bootloader, "N915FY")) {
        /* tbltexx These values are taken from tbltexx and edited for the 915FY FIXME */
        property_override("ro.build.fingerprint", "samsung/tbltebtu/tblte:6.0.1/MMB29M/N915FYXXS1DQH2:user/release-keys");
        property_override("ro.build.description", "tbltebtu-user 6.0.1 MMB29M N915FYXXS1DQH2 release-keys");
        property_override("ro.product.model", "SM-N915FY");
        property_override("ro.product.device", "tbltexx");
    } else if (strstr(bootloader, "N915G")) {
         /* tbltedt */
        property_override("ro.build.fingerprint", "samsung/tbltebtu/tblte:6.0.1/MMB29M/N915FYXXS1DQH2:user/release-keys");
        property_override("ro.build.description", "tbltebtu-user 6.0.1 MMB29M N915FYXXS1DQH2 release-keys");
        property_override("ro.product.model", "SM-N915G");
        property_override("ro.product.device", "tbltedt");
    } else {
        /* tblte */
        property_override("ro.build.fingerprint", "samsung/tbltebtu/tblte:6.0.1/MMB29M/N915FYXXS1DQH2:user/release-keys");
        property_override("ro.build.description", "tbltebtu-user 6.0.1 MMB29M N915FYXXS1DQH2 release-keys");
        property_override("ro.product.model", "SM-N915F");
        property_override("ro.product.device", "tblte");
    }

    property_get("ro.product.device", device, NULL);
    strlcpy(devicename, device, sizeof(devicename));
    ERROR("Found bootloader id %s setting build properties for %s device\n", bootloader, devicename);
}

void vendor_load_properties() {
    init_variant_properties();
}
