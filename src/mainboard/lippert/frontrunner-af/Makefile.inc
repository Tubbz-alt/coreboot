# SPDX-License-Identifier: GPL-2.0-only

ifeq ($(CONFIG_AHCI_BIOS),y)
stripped_ahcibios_id = $(call strip_quotes,$(CONFIG_AHCI_BIOS_ID))
cbfs-files-$(CONFIG_AHCI_BIOS) += pci$(stripped_ahcibios_id).rom
pci$(stripped_ahcibios_id).rom-file := $(call strip_quotes,$(CONFIG_AHCI_BIOS_FILE))
pci$(stripped_ahcibios_id).rom-type := optionrom
endif

bootblock-y += bootblock.c

romstage-y += buildOpts.c
romstage-y += BiosCallOuts.c
romstage-y += OemCustomize.c

ramstage-y += buildOpts.c
ramstage-y += BiosCallOuts.c
ramstage-y += OemCustomize.c

# Minimal SEMA watchdog support
romstage-y += sema.c
ramstage-y += sema.c
