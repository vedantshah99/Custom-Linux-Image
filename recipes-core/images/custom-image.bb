SUMMARY = "My custom Linux image."

IMAGE_INSTALL = "packagegroup-core-boot ${CORE_IMAGE_EXTRA_INSTALL}"

IMAGE_LINGUAS = " "

LICENSE = "MIT"

inherit core-image
inherit extrausers

# set rootfs to 200 MiB by default
IMAGE_OVERHEAD_FACTOR ?= "1.0"
IMAGE_ROOTFS_SIZE ?= "204800"

#Change root password
EXTRA_USERS_PARAMS = "\
usermod -P 'toor' root \
"


# Include our custom application
IMAGE_INSTALL += "gettemp"

# Add kernel module for USB Wifi Driver
IMAGE += "kernel-module-r8188eu \
	linux-firmware-rtl8188 \
	dhcp-client \
	iw \
	wpa-supplicant \
	wireless-regdb-status"

# Autoload Wifi dirver on boot
KERNEL_MODULE_AUTOLOAD += "r8188eu"
