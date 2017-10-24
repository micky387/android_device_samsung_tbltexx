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

#include <fcntl.h>
#include "log.h"
#include <stdlib.h>
#include <unistd.h>
#include "util.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sysinfo.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include <android-base/file.h>
#include <android-base/properties.h>
#include <android-base/strings.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using android::base::ReadFileToString;
using android::base::Trim;

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

    std::string platform = GetProperty("ro.board.platform", "");
    if (platform != ANDROID_TARGET)
        return;

    std::string bootloader = GetProperty("ro.bootloader", "");

    if (bootloader.find("N915FY") == 0) {
        /* tbltexx These values are taken from tbltexx and edited for the 915FY FIXME */
        property_override("ro.build.fingerprint", "samsung/tbltebtu/tblte:6.0.1/MMB29M/N915FYXXS1DQH2:user/release-keys");
        property_override("ro.build.description", "tbltebtu-user 6.0.1 MMB29M N915FYXXS1DQH2 release-keys");
        property_override("ro.product.model", "SM-N915FY");
        property_override("ro.product.device", "tbltexx");
    } else if (bootloader.find("N915G") == 0) {
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

    std::string device = GetProperty("ro.product.device", "");
    LOG(INFO) << "Found bootloader id " << bootloader.c_str() << " setting build properties for " << device.c_str() << " device\n";
}

void vendor_load_properties() {
    init_variant_properties();
}
