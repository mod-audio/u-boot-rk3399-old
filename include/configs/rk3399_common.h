/*
 * (C) Copyright 2016 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __CONFIG_RK3399_COMMON_H
#define __CONFIG_RK3399_COMMON_H

#include "rockchip-common.h"

#define CONFIG_SYS_MALLOC_LEN		(192 << 20)
#define CONFIG_SYS_CBSIZE		1024
#define CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_SPL_FRAMEWORK
#if defined(CONFIG_SPL_SPI_SUPPORT)
#define CONFIG_SPL_SPI_LOAD
#endif

#define CONFIG_SYS_TEXT_BASE		0x00200000
#define CONFIG_SYS_INIT_SP_ADDR		0x00400000
#define CONFIG_SYS_LOAD_ADDR		0x00800800
#define CONFIG_SPL_STACK		0x00400000
#define CONFIG_SPL_TEXT_BASE		0x00000000
#define CONFIG_SPL_MAX_SIZE             0x100000
#define CONFIG_SPL_BSS_START_ADDR	0x00400000
#define CONFIG_SPL_BSS_MAX_SIZE         0x2000
#define CONFIG_SYS_BOOTM_LEN	(64 << 20)	/* 64M */
#define CONFIG_SUPPORT_EMMC_RPMB

#define GICD_BASE			0xFEE00000
#define GICR_BASE			0xFEF00000
#define GICC_BASE			0xFFF00000

#define CONFIG_ROCKUSB_G_DNL_PID	0x330C

/* MMC/SD IP block */
#define CONFIG_BOUNCE_BUFFER
#define CONFIG_ROCKCHIP_SDHCI_MAX_FREQ	200000000

#define CONFIG_SUPPORT_VFAT
#define CONFIG_FS_EXT4

#define CONFIG_USB_FUNCTION_MASS_STORAGE

/* RAW SD card / eMMC locations. */
#define CONFIG_SYS_SPI_U_BOOT_OFFS	(128 << 10)

/* FAT sd card locations. */
#define CONFIG_SYS_MMCSD_FS_BOOT_PARTITION	1
#define CONFIG_SYS_SDRAM_BASE		0
#define SDRAM_MAX_SIZE			0xf8000000

#define CONFIG_SF_DEFAULT_SPEED 20000000

#ifndef CONFIG_SPL_BUILD

#define ENV_MEM_LAYOUT_SETTINGS \
	"scriptaddr=0x00500000\0" \
	"pxefile_addr_r=0x00600000\0" \
	"fdt_addr_r=0x08300000\0" \
	"kernel_addr_r=0x00280000\0" \
	"ramdisk_addr_r=0x0a200000\0"

#include <config_distro_bootcmd.h>
#define CONFIG_EXTRA_ENV_SETTINGS \
	ENV_MEM_LAYOUT_SETTINGS \
	"partitions=" PARTS_DEFAULT \
	ROCKCHIP_DEVICE_SETTINGS \
	RKIMG_DET_BOOTDEV \
	BOOTENV

#endif

#define CONFIG_PREBOOT

/* enable usb config for usb ether */

/* rockchip ohci host driver */
#define CONFIG_USB_OHCI_NEW
#define CONFIG_SYS_USB_OHCI_MAX_ROOT_PORTS	1

#undef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS \
	"devtype=mmc\0" \
	"devnum=0\0" \
	"scriptaddr=0x00500000\0" \
	"fdt_addr_r=0x08300000\0" \
	"kernel_addr_r=0x00280000\0" \
	"bootdelay=1\0" \
	"bootcmd=run boot_main; run boot_restore; rockusb 0 mmc 0\0" \
	"console=ttyFIQ0,1500000n8\0" \
	"loglevel=8\0" \
	"bootenv=/uEnv-rk3399.txt\0" \
	"kernel=/Image-rk3399\0" \
	"fdtbin=/modduox-rk3399.dtb\0" \
	"boot_image=booti ${kernel_addr_r} - ${fdt_addr_r}\0" \
	"setbootargs=setenv bootargs console=${console} init=/sbin/init root=${root} loglevel=${loglevel} ${extraargs}\0" \
	"main_bootargs=setenv root \"/dev/mmcblk1p4\"\0" \
	"main_loadbootenv=ext4load mmc 0:4 ${scriptaddr} /boot${bootenv}; env import ${scriptaddr} ${filesize}\0" \
	"main_script=ext4load mmc 0:4 ${fdt_addr_r} /boot${fdtbin}\0" \
	"main_kernel=ext4load mmc 0:4 ${kernel_addr_r} /boot${kernel}\0" \
	"boot_main=run main_bootargs main_loadbootenv main_script main_kernel setbootargs boot_image\0" \
	"restore_bootargs=setenv root \"\"\0" \
	"restore_loadbootenv=fatload mmc 0:3 ${scriptaddr} ${bootenv}; env import ${scriptaddr} ${filesize}\0" \
	"restore_script=fatload mmc 0:3 ${fdt_addr_r} ${fdtbin}\0" \
	"restore_kernel=fatload mmc 0:3 ${kernel_addr_r} ${kernel}\0" \
	"boot_restore=run restore_bootargs restore_loadbootenv restore_script restore_kernel setbootargs boot_image\0" \
	"loadbootenv=echo\0"

#endif
