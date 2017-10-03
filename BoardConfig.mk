# Copyright (C) 2014 The CyanogenMod Project
# Copyright (C) 2017 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# inherit from common tblte
-include device/samsung/tblte-common/BoardConfigCommon.mk

TARGET_OTA_ASSERT_DEVICE := tblte,tbltexx,tbltedt

# Camera
TARGET_FIXUP_PREVIEW := true 

# Kernel
BOARD_HAS_LARGE_FILESYSTEM := true
TARGET_USERIMAGES_USE_EXT4 := true
TARGET_USERIMAGES_USE_F2FS := true
TARGET_KERNEL_VARIANT_CONFIG := apq8084_sec_tblte_eur_defconfig
BOARD_BOOTIMAGE_PARTITION_SIZE := 17825792
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 199229440
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 3774873600 
BOARD_USERDATAIMAGE_PARTITION_SIZE := 27040657408
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := f2fs
BOARD_CACHEIMAGE_PARTITION_SIZE := 209715200

# Init
TARGET_INIT_VENDOR_LIB := libinit_tblte
TARGET_UNIFIED_DEVICE := true

# inherit from the proprietary version
-include vendor/samsung/tbltexx/BoardConfigVendor.mk