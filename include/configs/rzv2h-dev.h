/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2022 Renesas Electronics Corporation
 */

#ifndef __RZV2H_DEV_H
#define __RZV2H_DEV_H

#include <asm/arch/rmobile.h>

#define CONFIG_REMAKE_ELF

#ifdef CONFIG_SPL
#define CONFIG_SPL_TARGET	"spl/u-boot-spl.scif"
#endif

/* boot option */

#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG

/* Generic Interrupt Controller Definitions */
/* RZ/V2H use GIC-v3 */
#define CONFIG_GICV3
#define GICD_BASE	0x14900000
#define GICR_BASE	0x14940000

/* console */
#define CONFIG_SYS_CBSIZE		2048
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE
#define CONFIG_SYS_MAXARGS		64
#define CONFIG_SYS_BAUDRATE_TABLE	{ 115200, 38400 }

/* PHY needs a longer autoneg timeout */
#define PHY_ANEG_TIMEOUT		20000

/* MEMORY */
#define CONFIG_SYS_INIT_SP_ADDR		CONFIG_SYS_TEXT_BASE

/* SDHI clock freq */
#define CONFIG_SH_SDHI_FREQ		133000000

#define DRAM_RSV_SIZE			0x08000000
#define CONFIG_SYS_SDRAM_BASE		(0x40000000 + DRAM_RSV_SIZE)
#define CONFIG_SYS_SDRAM_SIZE		(0x200000000u - DRAM_RSV_SIZE) //total 8GB
#define CONFIG_SYS_LOAD_ADDR		0x58000000
#define CONFIG_LOADADDR			CONFIG_SYS_LOAD_ADDR // Default load address for tfpt,bootp...
#define CONFIG_VERY_BIG_RAM
#define CONFIG_MAX_MEM_MAPPED		(0x80000000u - DRAM_RSV_SIZE)

#define CONFIG_SYS_MONITOR_BASE		0x00000000
#define CONFIG_SYS_MONITOR_LEN		(1 * 1024 * 1024)
#define CONFIG_SYS_MALLOC_LEN		(64 * 1024 * 1024)
#define CONFIG_SYS_BOOTM_LEN		(64 << 20)

/* The HF/QSPI layout permits up to 1 MiB large bootloader blob */
#define CONFIG_BOARD_SIZE_LIMIT		1048576

/* ENV setting */
#if defined(CONFIG_TARGET_RZV2H_DEV)
#define CONFIG_EXTRA_ENV_SETTINGS	\
	"usb_pgood_delay=2000\0"	\
	"bootm_size=0x10000000\0"	\
	"ipaddr=192.168.1.11\0" \
	"serverip=192.168.1.10\0" \
	"netmask=255.255.255.0\0" \
	"prodsdbootargs=setenv bootargs rw rootwait earlycon root=/dev/mmcblk2p2 \0" \
	"prodemmcbootargs=setenv bootargs rw rootwait earlycon root=/dev/mmcblk0p2 \0" \
	"bootimage=booti 0x48080000 - 0x48000000 \0" \
	"ocaaddr=0xC0000000 \0"     \
	"ocabin=OpenCV_Bin.bin \0"  \
	"codaddr=0xC7D00000 \0"     \
	"codbin=Codec_Bin.bin \0"   \
	"emmcload=ext4load mmc 0:2 ${ocaaddr} boot/${ocabin}; ext4load mmc 0:2 ${codaddr} boot/${codbin};ext4load mmc 0:2 0x48080000 boot/Image;ext4load mmc 0:2 0x48000000 boot/r9a09g057h4-dev.dtb;run prodemmcbootargs \0" \
	"sd2load=ext4load mmc 2:2 ${ocaaddr} boot/${ocabin}; ext4load mmc 2:2 ${codaddr} boot/${codbin}; ext4load mmc 2:2 0x48080000 boot/Image;ext4load mmc 2:2 0x48000000 boot/r9a09g057h4-dev.dtb;run prodsdbootargs \0" \
	"bootcmd_check=if mmc dev 2; then run sd2load; else run emmcload; fi \0"
#elif defined(CONFIG_TARGET_RZV2H_EVK_ALPHA)
#define CONFIG_EXTRA_ENV_SETTINGS	\
	"usb_pgood_delay=2000\0"	\
	"bootm_size=0x10000000\0"	\
	"ipaddr=192.168.1.11\0" \
	"serverip=192.168.1.10\0" \
	"netmask=255.255.255.0\0" \
	"prodsdbootargs=setenv bootargs rw rootwait earlycon root=/dev/mmcblk1p2 \0" \
	"prodemmcbootargs=setenv bootargs rw rootwait earlycon root=/dev/mmcblk0p2 \0" \
	"set_pmic=i2c dev 8; i2c mw 0x6a 0x22 0x0f; i2c mw 0x6a 0x24 0x00; i2c md 0x6a 0x00 0x30; i2c mw 0x12 0x8D 0x02; i2c md 0x12 0x20 0x80 \0" \
	"bootimage=run set_pmic; booti 0x48080000 - 0x48000000 \0" \
	"ocaaddr=0xC0000000 \0"     \
	"ocabin=OpenCV_Bin.bin \0"  \
	"codaddr=0xC7D00000 \0"     \
	"codbin=Codec_Bin.bin \0"   \
	"emmcload=ext4load mmc 0:2 ${ocaaddr} boot/${ocabin}; ext4load mmc 0:2 ${codaddr} boot/${codbin};ext4load mmc 0:2 0x48080000 boot/Image;ext4load mmc 0:2 0x48000000 boot/r9a09g057h4-evk-alpha.dtb;run prodemmcbootargs \0" \
	"sd1load=ext4load mmc 1:2 ${ocaaddr} boot/${ocabin}; ext4load mmc 1:2 ${codaddr} boot/${codbin}; ext4load mmc 1:2 0x48080000 boot/Image;ext4load mmc 1:2 0x48000000 boot/r9a09g057h4-evk-alpha.dtb;run prodsdbootargs \0" \
	"bootcmd_check=if mmc dev 1; then run sd1load; else run emmcload; fi \0"
#else
#define CONFIG_EXTRA_ENV_SETTINGS       \
	"usb_pgood_delay=2000\0"        \
	"bootm_size=0x10000000\0"       \
	"ipaddr=192.168.1.11\0" \
	"serverip=192.168.1.10\0" \
	"netmask=255.255.255.0\0" \
	"boot_fdt_overlay=no\0"	\
	"fdt_file=kakip-es1\0"	\
	"fdt_overlay_files=kakip-es1-spi0\0"	\
	"fdt_addr=0x48000000\0"	\
	"fdt_ovaddr=0x87fc0000\0"	\
	"fdt_load=load mmc 0:2 ${fdt_addr} boot/${fdt_file}.dtb \0"	\
	"apply_fdt_overlay=run fdt_load; "	\
		"fdt addr ${fdt_addr}; "	\
		"fdt resize 0x2000; "	\
		"for overlay_file in ${fdt_overlay_files}; do "	\
			"load mmc 0:2 ${fdt_ovaddr} boot/${overlay_file}.dtbo; "	\
			"fdt apply ${fdt_ovaddr}; "	\
		"done\0"	\
	"prodsd0bootargs=setenv bootargs rw rootwait earlycon root=/dev/mmcblk0p2 \0" \
	"prodsd1bootargs=setenv bootargs rw rootwait earlycon root=/dev/mmcblk1p2 \0" \
	"bootimage=booti 0x48080000 - 0x48000000 \0" \
	"ocaaddr=0xC0000000 \0"     \
	"ocabin=OpenCV_Bin.bin \0"  \
	"codaddr=0xC7D00000 \0"     \
	"codbin=Codec_Bin.bin \0"   \
	"sd0load=ext4load mmc 0:2 ${ocaaddr} boot/${ocabin}; ext4load mmc 0:2 ${codaddr} boot/${codbin}; ext4load mmc 0:2 0x48080000 boot/Image;ext4load mmc 0:2 0x48000000 boot/kakip-es1.dtb;run prodsd0bootargs; " \
		"if test ${boot_fdt_overlay} = yes; then "	\
			"run apply_fdt_overlay; "	\
		"fi;"	\
		"saveenv;\0"	\
	"sd1load=ext4load mmc 1:2 ${ocaaddr} boot/${ocabin}; ext4load mmc 1:2 ${codaddr} boot/${codbin}; ext4load mmc 1:2 0x48080000 boot/Image;ext4load mmc 1:2 0x48000000 boot/kakip-es1.dtb;run prodsd1bootargs \0" \
	"bootcmd_check=if mmc dev 1; then run sd1load; else run sd0load; fi \0"
#endif

#define CONFIG_BOOTCOMMAND	"run bootcmd_check;run bootimage"

/* For board */
/* Ethernet RAVB */
#define CONFIG_BITBANGMII_MULTI
/* add initialize process. */
#define CONFIG_MISC_INIT_R

#endif /* __RZV2H_DEV_H */
