# SPDX-License-Identifier: BSD-3-Clause

ifeq ($(CONFIG_SOC_AMD_MATISSE),y)

subdirs-y += ../../../cpu/amd/mtrr/
subdirs-y += ../../../cpu/x86/tsc
subdirs-y += ../../../cpu/x86/lapic
subdirs-y += ../../../cpu/x86/cache
subdirs-y += ../../../cpu/x86/mtrr
subdirs-y += ../../../cpu/x86/pae
subdirs-y += ../../../cpu/x86/smm
subdirs-$(CONFIG_VBOOT_STARTS_BEFORE_BOOTBLOCK) += psp_verstage

bootblock-y += bootblock/pre_c.S
bootblock-y += bootblock/bootblock.c
bootblock-y += aoac.c
bootblock-y += southbridge.c
bootblock-y += i2c.c
bootblock-y += uart.c
bootblock-$(CONFIG_MATISSE_CONSOLE_UART) += uart_console.c
bootblock-y += tsc_freq.c
bootblock-y += gpio.c
bootblock-y += smi_util.c
bootblock-y += config.c

romstage-y += i2c.c
romstage-y += romstage.c
romstage-y += gpio.c
romstage-y += pmutil.c
romstage-y += reset.c
romstage-y += memmap.c
romstage-y += uart.c
romstage-$(CONFIG_MATISSE_CONSOLE_UART) += uart_console.c
romstage-y += tsc_freq.c
romstage-y += aoac.c
romstage-y += southbridge.c
romstage-$(CONFIG_HAVE_SMI_HANDLER) += smi_util.c
romstage-y += psp.c
romstage-y += config.c
romstage-y += mrc_cache.c

verstage-y += i2c.c
verstage-y += pmutil.c
verstage-y += config.c
verstage-y += aoac.c
verstage_x86-y += gpio.c
verstage_x86-y += uart.c
verstage_x86-$(CONFIG_MATISSE_CONSOLE_UART) += uart_console.c
verstage_x86-y += tsc_freq.c
verstage_x86-y += reset.c

ramstage-y += i2c.c
ramstage-y += chip.c
ramstage-y += cpu.c
ramstage-y += data_fabric.c
ramstage-y += root_complex.c
ramstage-y += mca.c
ramstage-$(CONFIG_HAVE_ACPI_TABLES) += acpi.c
ramstage-$(CONFIG_HAVE_ACPI_TABLES) += agesa_acpi.c
ramstage-y += gpio.c
ramstage-y += aoac.c
ramstage-y += southbridge.c
ramstage-y += pmutil.c
ramstage-y += reset.c
ramstage-y += acp.c
ramstage-y += sata.c
ramstage-y += memmap.c
ramstage-$(CONFIG_HAVE_SMI_HANDLER) += smi.c
ramstage-$(CONFIG_HAVE_SMI_HANDLER) += smi_util.c
ramstage-y += uart.c
ramstage-$(CONFIG_MATISSE_CONSOLE_UART) += uart_console.c
ramstage-y += tsc_freq.c
ramstage-y += finalize.c
ramstage-y += psp.c
ramstage-y += fsp_params.c
ramstage-y += config.c
ramstage-y += update_microcode.c
ramstage-y += pcie_gpp.c
ramstage-y += xhci.c
ramstage-y += dmi.c

smm-y += smihandler.c
smm-y += smi_util.c
smm-y += tsc_freq.c
ifeq ($(CONFIG_DEBUG_SMI),y)
smm-y += uart.c
smm-$(CONFIG_MATISSE_CONSOLE_UART) += uart_console.c
endif
smm-y += gpio.c
smm-y += psp.c
smm-y += smu.c
smm-y += config.c

CPPFLAGS_common += -I$(src)/soc/amd/matisse
CPPFLAGS_common += -I$(src)/soc/amd/matisse/include
CPPFLAGS_common += -I$(src)/soc/amd/matisse/acpi
CPPFLAGS_common += -I$(src)/vendorcode/amd/fsp/matisse

MAINBOARD_BLOBS_DIR:=$(top)/3rdparty/blobs/mainboard/$(MAINBOARDDIR)

# ROMSIG Normally At ROMBASE + 0x20000
# Overridden by CONFIG_AMD_FWM_POSITION_INDEX
# +-----------+---------------+----------------+------------+
# |0x55AA55AA |               |                |            |
# +-----------+---------------+----------------+------------+
# |           |  PSPDIR ADDR  |  BIOSDIR ADDR  |
# +-----------+---------------+----------------+

MATISSE_FWM_POSITION=$(call int-add, \
	$(call int-subtract, 0xffffffff \
	$(call int-shift-left, \
	0x80000 $(CONFIG_AMD_FWM_POSITION_INDEX))) 0x20000 1)

#
# PSP Directory Table items
#
# Certain ordering requirements apply, however these are ensured by amdfwtool.
# For more information see "AMD Platform Security Processor BIOS Architecture
# Design Guide for AMD Family 17h Processors" (PID #55758, NDA only).
#

# type = 0x0
FIRMWARE_LOCATE=$(realpath $(dir $(call strip_quotes, $(CONFIG_AMD_PUBKEY_FILE))))

IMC_FW_FILE=$(FIRMWARE_LOCATE)/../imc.rom
FCH_FW_FILE=$(FIRMWARE_LOCATE)/PromontoryFW.bin
FCH_LP_FW_FILE=$(FIRMWARE_LOCATE)/LP_PromontoryFW.bin
EXTRA_FW_FILES=\
	0x3,$(FIRMWARE_LOCATE)/PspRecoveryBootLoader_mts.sbin \
	0x4,$(FIRMWARE_LOCATE)/../nvram.rom \
	0x8,$(FIRMWARE_LOCATE)/SmuFirmwareMts.cbin \
	0xA,$(FIRMWARE_LOCATE)/AblPubKey_mts.stkn \
	0xC,$(FIRMWARE_LOCATE)/dr_ftpm_prod_MTS.csbin \
	0x12,$(FIRMWARE_LOCATE)/SmuFirmware2Mts.cbin \
	0x21,$(FIRMWARE_LOCATE)/iKEK.enc.by.Matisse.rKEK \
	0x24,$(FIRMWARE_LOCATE)/RsmuSecPolicy_mts.sbin \
	0x28,$(FIRMWARE_LOCATE)/drv_sys_mts.sbin \
	0x2A,$(FIRMWARE_LOCATE)/Mp5Mts.cbin \
	0x30,$(FIRMWARE_LOCATE)/AgesaBootloader_U_prod_MTS.bin \
	0x42,$(FIRMWARE_LOCATE)/MtsPhyFw.sbin \
	0x43,$(FIRMWARE_LOCATE)/MtsPhyFwSb4kr.stkn \
	0x44,$(FIRMWARE_LOCATE)/Matisse_signed_USB_PHY_FW_20190711.sbin \
	0x4E,$(FIRMWARE_LOCATE)/Starship-PMU-FW-SB-Matisse-4KR.stkn

# type = 0x1
ifeq ($(CONFIG_PSP_BOOTLOADER_FILE),)
$(error CONFIG_PSP_BOOTLOADER_FILE was not defined)
endif
PSPBTLDR_FILE=$(realpath $(call strip_quotes, $(CONFIG_PSP_BOOTLOADER_FILE)))
$(info Adding PSP $(shell md5sum $(PSPBTLDR_FILE)))

ifeq ($(CONFIG_PSP_UNLOCK_SECURE_DEBUG),y)
# Enable secure debug unlock
EXTRA_FW_FILES+=0x9,$(FIRMWARE_LOCATE)/SecureDebug4KToken_mts.stkn
EXTRA_FW_FILES+=0x13,$(FIRMWARE_LOCATE)/SecureDebugUnlock_mts.sbin
PSP_SOFTFUSE_BITS += 0
PSP_TOKEN_UNLOCK="--token-unlock"
endif

ifeq ($(CONFIG_USE_PSPSCUREOS),y)
EXTRA_FW_FILES+=0x2,$(FIRMWARE_LOCATE)/psp_os_combined_mts.sbin
endif

#
# BIOS Directory Table items - proper ordering is managed by amdfwtool
#

# type = 0x60
PSP_APCB_FILES=$(foreach f, $(APCB_SOURCES), $(obj)/APCB_$(f).bin)

# type = 0x61
PSP_APOB_BASE=$(CONFIG_PSP_APOB_DRAM_ADDRESS)

# type = 0x62
PSP_BIOSBIN_FILE=$(obj)/amd_biospsp.img
PSP_ELF_FILE=$(objcbfs)/bootblock.elf
# TODO(b/154957411): Refactor amdfwtool to extract the address and size from
# the elf file.
PSP_BIOSBIN_SIZE=$(CONFIG_C_ENV_BOOTBLOCK_SIZE)
# This address must match the BOOTBLOCK logic in arch/x86/memlayout.ld.
PSP_BIOSBIN_DEST=$(shell printf "0x%x" $(call int-subtract, $(call int-add, $(CONFIG_X86_RESET_VECTOR) 0x10) $(PSP_BIOSBIN_SIZE)))

# type = 0x63 - construct APOB NV base/size from flash map
# TODO(b/157068645): Add ability to fmaptool to extract offsets and sizes
# This code currently assumes the following FMAP structure. If
# the UNIFIED_MRC_CACHE region is present, it must have a 0 offset.
# FLASH@* {
#     BIOS@* {
#         RW_MRC_CACHE@* {
_FLASH_BASE=$(call int-subtract, 0x100000000 $(CONFIG_ROM_SIZE))
_GET_FLASH_BASE=grep "FLASH" | sed 's/.*FLASH@//' | sed 's/ .*//'
_GET_BIOS_REG_BASE=grep "BIOS" | sed 's/.*BIOS@//' | sed 's/ .*//'
_GET_APOBNV_BASE=grep "RW_MRC_CACHE" | sed 's/.*@//' | sed 's/ .*//'
_GET_APOBNV_SIZE=grep "RW_MRC_CACHE" | sed 's/.*@//' | sed 's/.* //'

# type2 = 0x64, 0x65
PSP_PMUI_FILE3=$(FIRMWARE_LOCATE)/Appb_MTS_1D_Ddr4_Udimm_Imem.csbin
PSP_PMUI_FILE4=$(FIRMWARE_LOCATE)/Appb_MTS_2D_Ddr4_Udimm_Imem.csbin
PSP_PMUD_FILE3=$(FIRMWARE_LOCATE)/Appb_MTS_1D_Ddr4_Udimm_Dmem.csbin
PSP_PMUD_FILE4=$(FIRMWARE_LOCATE)/Appb_MTS_2D_Ddr4_Udimm_Dmem.csbin

# type = 0x66
PSP_UCODE_FILE1=$(FIRMWARE_LOCATE)/UcodePatch_MTS_A0.bin
PSP_UCODE_FILE2=$(FIRMWARE_LOCATE)/UcodePatch_MTS_B0.bin

ifeq ($(CONFIG_VBOOT_STARTS_BEFORE_BOOTBLOCK),y)
# type = 0x6B - PSP Shared memory location
ifneq ($(CONFIG_PSP_SHAREDMEM_SIZE),0x0)
PSP_SHAREDMEM_SIZE=$(CONFIG_PSP_SHAREDMEM_SIZE)
_PSP_SHAREDMEM_BASE=$(shell grep _psp_sharedmem_dram $(obj)/cbfs/$(CONFIG_CBFS_PREFIX)/bootblock.map | cut -f1 -d' ')
PSP_SHAREDMEM_BASE=$(shell printf "0x%s" $(_PSP_SHAREDMEM_BASE))
endif

# type = 0x52 - PSP Bootloader Userspace Application (verstage)
PSP_VERSTAGE_FILE=$(obj)/psp_verstage.bin
endif # CONFIG_VBOOT_STARTS_BEFORE_BOOTBLOCK

APOB_NV_SIZE=$(shell printf "0x%x" 	$(shell cat $(obj)/fmap.fmd | $(_GET_APOBNV_SIZE)))
APOB_NV_BASE=$(shell printf "0x%x" $(call int-add, \
			$(shell cat $(obj)/fmap.fmd | $(_GET_FLASH_BASE)) \
			$(shell cat $(obj)/fmap.fmd | $(_GET_BIOS_REG_BASE)) \
			$(shell cat $(obj)/fmap.fmd | $(_GET_APOBNV_BASE))))

# Helper function to return a value with given bit set
set-bit=$(call int-shift-left, 1 $(call _toint,$1))
PSP_SOFTFUSE=$(shell A=$(call int-add, \
		$(foreach bit,$(PSP_SOFTFUSE_BITS),$(call set-bit,$(bit)))); printf "0x%x" $$A)

#
# Build the arguments to amdfwtool (order is unimportant).  Missing file names
# result in empty OPT_ variables, i.e. the argument is not passed to amdfwtool.
#

add_opt_prefix=$(if $(call strip_quotes, $(1)), $(2) $(call strip_quotes, $(1)), )

OPT_AMD_PUBKEY_FILE=$(call add_opt_prefix, $(CONFIG_AMD_PUBKEY_FILE), --pubkey)
OPT_IMC_FW_FILE=$(call add_opt_prefix, $(IMC_FW_FILE), --imc)
OPT_FCH_FW_FILE=$(call add_opt_prefix, $(FCH_FW_FILE), --fch-fw)
OPT_FCH_LP_FW_FILE=$(call add_opt_prefix, $(FCH_LP_FW_FILE), --fch-lp-fw)

OPT_EXTRA_FW_FILES=$(foreach i, $(shell seq $(words $(EXTRA_FW_FILES))), \
	$(call add_opt_prefix, $(word $(i), $(EXTRA_FW_FILES)), --extra-fw))

OPT_PSPBTLDR_FILE=$(call add_opt_prefix, $(PSPBTLDR_FILE), --bootloader)
OPT_SMUFW1_SUB1_FILE=$(call add_opt_prefix, $(PSP_SMUFW1_SUB1_FILE), --subprogram 1 --smufirmware)
OPT_SMUFW1_SUB2_FILE=$(call add_opt_prefix, $(PSP_SMUFW1_SUB2_FILE), --subprogram 2 --smufirmware)
OPT_SMUFW2_SUB1_FILE=$(call add_opt_prefix, $(PSP_SMUFW2_SUB1_FILE), --subprogram 1 --smufirmware2)
OPT_SMUFW2_SUB2_FILE=$(call add_opt_prefix, $(PSP_SMUFW2_SUB2_FILE), --subprogram 2 --smufirmware2)
OPT_PSP_SEC_DBG_KEY_FILE=$(call add_opt_prefix, $(PSP_SEC_DBG_KEY_FILE), --securedebug)
OPT_TOKEN_UNLOCK=$(call add_opt_prefix, $(PSP_TOKEN_UNLOCK), "")
OPT_PSP_SOFTFUSE=$(call add_opt_prefix, $(PSP_SOFTFUSE), --soft-fuse)
OPT_PSPSCUREOS_FILE=$(call add_opt_prefix, $(PSPSCUREOS_FILE), --secureos)
OPT_SEC_DEBUG_FILE=$(call add_opt_prefix, $(PSP_SEC_DEBUG_FILE), --secdebug)
OPT_IKEK_FILE=$(call add_opt_prefix, $(PSP_IKEK_FILE), --ikek)
OPT_SECG1_FILE=$(call add_opt_prefix, $(PSP_SECG1_FILE), --subprog 1 --sec-gasket)
OPT_SECG2_FILE=$(call add_opt_prefix, $(PSP_SECG2_FILE), --subprog 2 --sec-gasket)
OPT_MP2FW1_FILE=$(call add_opt_prefix, $(PSP_MP2FW1_FILE), --subprog 1 --mp2-fw)
OPT_MP2FW2_FILE=$(call add_opt_prefix, $(PSP_MP2FW2_FILE), --subprog 2 --mp2-fw)
OPT_DRIVERS_FILE=$(call add_opt_prefix, $(PSP_DRIVERS_FILE), --drv-entry-pts)
OPT_PSP_S0I3_FILE=$(call add_opt_prefix, $(PSP_S0I3_FILE), --s0i3drv)
OPT_ABL0_FILE=$(call add_opt_prefix,  $(PSP_ABL0_FILE), --abl-image)
OPT_ABL1_FILE=$(call add_opt_prefix,  $(PSP_ABL1_FILE), --abl-image)
OPT_ABL2_FILE=$(call add_opt_prefix,  $(PSP_ABL2_FILE), --abl-image)
OPT_ABL3_FILE=$(call add_opt_prefix,  $(PSP_ABL3_FILE), --abl-image)
OPT_ABL4_FILE=$(call add_opt_prefix,  $(PSP_ABL4_FILE), --abl-image)
OPT_ABL5_FILE=$(call add_opt_prefix,  $(PSP_ABL5_FILE), --abl-image)
OPT_ABL6_FILE=$(call add_opt_prefix,  $(PSP_ABL6_FILE), --abl-image)
OPT_ABL7_FILE=$(call add_opt_prefix,  $(PSP_ABL7_FILE), --abl-image)
OPT_PSP_UCODE_FILE1=$(call add_opt_prefix,  $(PSP_UCODE_FILE1), --instance 0 --ucode)
OPT_PSP_UCODE_FILE2=$(call add_opt_prefix,  $(PSP_UCODE_FILE2), --instance 1 --ucode)
OPT_PSP_UCODE_FILE3=$(call add_opt_prefix,  $(PSP_UCODE_FILE3), --instance 2 --ucode)
OPT_WHITELIST_FILE=$(call add_opt_prefix, $(PSP_WHITELIST_FILE), --whitelist)
OPT_VERSTAGE_FILE=$(call add_opt_prefix, $(PSP_VERSTAGE_FILE), --verstage)

OPT_PSP_APCB_FILES=$(foreach i, $(shell seq $(words $(PSP_APCB_FILES))), \
	$(call add_opt_prefix, $(word $(i), $(PSP_APCB_FILES)), \
	--instance $(shell printf "%x" $$(($(i)-1))) --apcb ))

OPT_APOB_ADDR=$(call add_opt_prefix, $(PSP_APOB_BASE), --apob-base)
OPT_PSP_BIOSBIN_FILE=$(call add_opt_prefix, $(PSP_BIOSBIN_FILE), --bios-bin)
OPT_PSP_BIOSBIN_DEST=$(call add_opt_prefix, $(PSP_BIOSBIN_DEST), --bios-bin-dest)
OPT_PSP_BIOSBIN_SIZE=$(call add_opt_prefix, $(PSP_BIOSBIN_SIZE), --bios-uncomp-size)
OPT_PSP_PMUI_FILE1=$(call add_opt_prefix, $(PSP_PMUI_FILE1), --subprogram 0 --instance 1 --pmu-inst)
OPT_PSP_PMUI_FILE2=$(call add_opt_prefix, $(PSP_PMUI_FILE2), --subprogram 0 --instance 4 --pmu-inst)
OPT_PSP_PMUI_FILE3=$(call add_opt_prefix, $(PSP_PMUI_FILE3), --subprogram 1 --instance 1 --pmu-inst)
OPT_PSP_PMUI_FILE4=$(call add_opt_prefix, $(PSP_PMUI_FILE4), --subprogram 1 --instance 4 --pmu-inst)
OPT_PSP_PMUD_FILE1=$(call add_opt_prefix, $(PSP_PMUD_FILE1), --subprogram 0 --instance 1 --pmu-data)
OPT_PSP_PMUD_FILE2=$(call add_opt_prefix, $(PSP_PMUD_FILE2), --subprogram 0 --instance 4 --pmu-data)
OPT_PSP_PMUD_FILE3=$(call add_opt_prefix, $(PSP_PMUD_FILE3), --subprogram 1 --instance 1 --pmu-data)
OPT_PSP_PMUD_FILE4=$(call add_opt_prefix, $(PSP_PMUD_FILE4), --subprogram 1 --instance 4 --pmu-data)
OPT_MP2CFG_FILE=$(call add_opt_prefix, $(PSP_MP2CFG_FILE), --mp2-config)
OPT_PSP_SHAREDMEM_BASE=$(call add_opt_prefix, $(PSP_SHAREDMEM_BASE), --sharedmem)
OPT_PSP_SHAREDMEM_SIZE=$(call add_opt_prefix, $(PSP_SHAREDMEM_SIZE), --sharedmem-size)
OPT_APOB_NV_SIZE=$(call add_opt_prefix, $(APOB_NV_SIZE), --apob-nv-size)
OPT_APOB_NV_BASE=$(call add_opt_prefix, $(APOB_NV_BASE), --apob-nv-base)

AMDFW_COMMON_ARGS=$(OPT_AMD_PUBKEY_FILE) \
		$(OPT_IMC_FW_FILE) \
		$(OPT_FCH_FW_FILE) \
		$(OPT_FCH_LP_FW_FILE) \
		$(OPT_EXTRA_FW_FILES) \
		$(OPT_PSPBTLDR_FILE) \
		$(OPT_PSPSCUREOS_FILE) \
		$(OPT_PSP_SEC_DBG_KEY_FILE) \
		$(OPT_SMUFW1_SUB2_FILE) \
		$(OPT_SMUFW2_SUB2_FILE) \
		$(OPT_SMUFW1_SUB1_FILE) \
		$(OPT_SMUFW2_SUB1_FILE) \
		$(OPT_PSP_APCB_FILES) \
		$(OPT_APOB_ADDR) \
		$(OPT_APOB_NV_SIZE) \
		$(OPT_APOB_NV_BASE) \
		$(OPT_PSP_BIOSBIN_FILE) \
		$(OPT_PSP_BIOSBIN_DEST) \
		$(OPT_PSP_BIOSBIN_SIZE) \
		$(OPT_PSP_SOFTFUSE) \
		$(OPT_PSP_PMUI_FILE1) \
		$(OPT_PSP_PMUI_FILE2) \
		$(OPT_PSP_PMUI_FILE3) \
		$(OPT_PSP_PMUI_FILE4) \
		$(OPT_PSP_PMUD_FILE1) \
		$(OPT_PSP_PMUD_FILE2) \
		$(OPT_PSP_PMUD_FILE3) \
		$(OPT_PSP_PMUD_FILE4) \
		$(OPT_MP2CFG_FILE) \
		$(OPT_ABL0_FILE) \
		$(OPT_ABL1_FILE) \
		$(OPT_ABL2_FILE) \
		$(OPT_ABL3_FILE) \
		$(OPT_ABL4_FILE) \
		$(OPT_ABL5_FILE) \
		$(OPT_ABL6_FILE) \
		$(OPT_ABL7_FILE) \
		$(OPT_PSP_UCODE_FILE1) \
		$(OPT_PSP_UCODE_FILE2) \
		$(OPT_PSP_UCODE_FILE3) \
		$(OPT_WHITELIST_FILE) \
		$(OPT_SECG1_FILE) \
		$(OPT_SECG2_FILE) \
		$(OPT_MP2FW1_FILE) \
		$(OPT_MP2FW2_FILE) \
		$(OPT_DRIVERS_FILE) \
		$(OPT_PSP_S0I3_FILE) \
		$(OPT_IKEK_FILE) \
		$(OPT_SEC_DEBUG_FILE) \
		$(OPT_VERSTAGE_FILE) \
		$(OPT_PSP_SHAREDMEM_BASE) \
		$(OPT_PSP_SHAREDMEM_SIZE) \
		--combo-capable \
		--multilevel \
		$(OPT_TOKEN_UNLOCK) \
		--flashsize $(CONFIG_ROM_SIZE)

# Copy prebuild APCBs if they exist
$(obj)/APCB_%.bin: $(MAINBOARD_BLOBS_DIR)/APCB_%.bin
	cp $< $@

# APCB binary with magic numbers to be replaced by apcb_edit tool
APCB_MAGIC_BLOB:=$(FIRMWARE_LOCATE)/APCB_magic.bin

$(obj)/APCB_empty.bin: $(APCB_MAGIC_BLOB) $(APCB_EDIT_TOOL)
	$(APCB_EDIT_TOOL) \
	$(APCB_MAGIC_BLOB) \
	$@ \
	--board_id_gpio0 $(APCB_BOARD_ID_GPIO0) \
	--board_id_gpio1 $(APCB_BOARD_ID_GPIO1) \
	--board_id_gpio2 $(APCB_BOARD_ID_GPIO2) \
	--board_id_gpio3 $(APCB_BOARD_ID_GPIO3)

$(obj)/APCB_%_x1.bin:	$$(SPD_SOURCES_DIR)/%.spd.hex \
			$(APCB_EDIT_TOOL) \
			$(APCB_MAGIC_BLOB)
	$(APCB_EDIT_TOOL) \
	$(APCB_MAGIC_BLOB) \
	$@ \
	--hex \
	--spd_0_0 $< \
	--board_id_gpio0 $(APCB_BOARD_ID_GPIO0) \
	--board_id_gpio1 $(APCB_BOARD_ID_GPIO1) \
	--board_id_gpio2 $(APCB_BOARD_ID_GPIO2) \
	--board_id_gpio3 $(APCB_BOARD_ID_GPIO3)

$(obj)/APCB_%_x2.bin:	$$(SPD_SOURCES_DIR)/%.spd.hex \
			$(APCB_EDIT_TOOL) \
			$(APCB_MAGIC_BLOB)
	$(APCB_EDIT_TOOL) \
	$(APCB_MAGIC_BLOB) \
	$@ \
	--hex \
	--spd_0_0 $< \
	--spd_1_0 $< \
	--board_id_gpio0 $(APCB_BOARD_ID_GPIO0) \
	--board_id_gpio1 $(APCB_BOARD_ID_GPIO1) \
	--board_id_gpio2 $(APCB_BOARD_ID_GPIO2) \
	--board_id_gpio3 $(APCB_BOARD_ID_GPIO3)

$(obj)/amdfw.rom:	$(call strip_quotes, $(CONFIG_AMD_PUBKEY_FILE)) \
			$(call strip_quotes, $(IMC_FW_FILE)) \
			$(call strip_quotes, $(FCH_FW_FILE)) \
			$(call strip_quotes, $(FCH_FW_LP_FILE)) \
			$(call strip_quotes, $(PSPBTLDR_FILE)) \
			$(call strip_quotes, $(PSPSCUREOS_FILE)) \
			$(call strip_quotes, $(PSP_SEC_DBG_KEY_FILE)) \
			$(call strip_quotes, $(PSP_BIOSBIN_FILE)) \
			$(call strip_quotes, $(PSP_PMUI_FILE1)) \
			$(call strip_quotes, $(PSP_PMUI_FILE2)) \
			$(call strip_quotes, $(PSP_PMUI_FILE3)) \
			$(call strip_quotes, $(PSP_PMUI_FILE4)) \
			$(call strip_quotes, $(PSP_PMUD_FILE1)) \
			$(call strip_quotes, $(PSP_PMUD_FILE2)) \
			$(call strip_quotes, $(PSP_PMUD_FILE3)) \
			$(call strip_quotes, $(PSP_PMUD_FILE4)) \
			$(call strip_quotes, $(PSP_MP2CFG_FILE)) \
			$(call strip_quotes, $(PSP_SMUFW1_SUB1_FILE)) \
			$(call strip_quotes, $(PSP_SMUFW1_SUB2_FILE)) \
			$(call strip_quotes, $(PSP_SMUFW2_SUB1_FILE)) \
			$(call strip_quotes, $(PSP_SMUFW2_SUB2_FILE)) \
			$(call strip_quotes, $(PSP_ABL0_FILE)) \
			$(call strip_quotes, $(PSP_ABL1_FILE)) \
			$(call strip_quotes, $(PSP_ABL2_FILE)) \
			$(call strip_quotes, $(PSP_ABL3_FILE)) \
			$(call strip_quotes, $(PSP_ABL4_FILE)) \
			$(call strip_quotes, $(PSP_ABL5_FILE)) \
			$(call strip_quotes, $(PSP_ABL6_FILE)) \
			$(call strip_quotes, $(PSP_ABL7_FILE)) \
			$(call strip_quotes, $(PSP_WHITELIST_FILE)) \
			$(call strip_quotes, $(PSP_SECG1_FILE)) \
			$(call strip_quotes, $(PSP_SECG2_FILE)) \
			$(call_strip_quotes, $(PSP_DRIVERS_FILE)) \
			$(call_strip_quotes, $(PSP_S0I3_FILE)) \
			$(call_strip_quotes, $(PSP_IKEK_FILE)) \
			$(call_strip_quotes, $(PSP_SEC_DEBUG_FILE)) \
			$(PSP_VERSTAGE_FILE) \
			$$(PSP_APCB_FILES) \
			$(AMDFWTOOL) \
			$(obj)/fmap.fmd
	rm -f $@
	@printf "    AMDFWTOOL  $(subst $(obj)/,,$(@))\n"
	$(AMDFWTOOL) \
		$(AMDFW_COMMON_ARGS) \
		--location $(shell printf "%#x" $(MATISSE_FWM_POSITION)) \
		--output $@

$(PSP_BIOSBIN_FILE): $(PSP_ELF_FILE) $(AMDCOMPRESS)
	rm -f $@
	@printf "    AMDCOMPRS  $(subst $(obj)/,,$(@))\n"
	$(AMDCOMPRESS) --infile $(PSP_ELF_FILE) --outfile $@ --compress \
		--maxsize $(PSP_BIOSBIN_SIZE)

$(obj)/amdfw_a.rom: $(obj)/amdfw.rom
	rm -f $@
	@printf "    AMDFWTOOL  $(subst $(obj)/,,$(@))\n"
	$(AMDFWTOOL) \
		$(AMDFW_COMMON_ARGS) \
		--location $(shell printf "%#x" $(CONFIG_MATISSE_FW_A_POSITION)) \
		--anywhere \
		--output $@

$(obj)/amdfw_b.rom: $(obj)/amdfw.rom
	rm -f $@
	@printf "    AMDFWTOOL  $(subst $(obj)/,,$(@))\n"
	$(AMDFWTOOL) \
		$(AMDFW_COMMON_ARGS) \
		--location $(shell printf "%#x" $(CONFIG_MATISSE_FW_B_POSITION)) \
		--anywhere \
		--output $@

cbfs-files-y += apu/amdfw
apu/amdfw-file := $(obj)/amdfw.rom
apu/amdfw-position := $(MATISSE_FWM_POSITION)
apu/amdfw-type := raw

ifeq ($(CONFIG_VBOOT_SLOTS_RW_AB)$(CONFIG_VBOOT_STARTS_BEFORE_BOOTBLOCK),yy)
cbfs-files-y += apu/amdfw_a
apu/amdfw_a-file := $(obj)/amdfw_a.rom
apu/amdfw_a-position := $(call strip_quotes, $(CONFIG_MATISSE_FW_A_POSITION))
apu/amdfw_a-type := raw

cbfs-files-y += apu/amdfw_b
apu/amdfw_b-file := $(obj)/amdfw_b.rom
apu/amdfw_b-position := $(call strip_quotes, $(CONFIG_MATISSE_FW_B_POSITION))
apu/amdfw_b-type := raw
endif

$(call strip_quotes,$(CONFIG_FSP_M_CBFS))-options := -b $(CONFIG_FSP_M_ADDR)

cpu_microcode_bins += $(wildcard $(FIRMWARE_LOCATE)/UcodePatch_*.bin)

endif # ($(CONFIG_SOC_AMD_MATISSE),y)