/*
 * This file is part of the coreboot project.
 *
 * Copyright 2020 The coreboot project Authors.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <commonlib/helpers.h>

/* Pad configuration in ramstage */
/* Leave eSPI pins untouched from default settings */
static const struct pad_config gpio_table[] = {
	/* A0 thru A6 come configured out of reset, do not touch */
	/* A0  : ESPI_IO0 ==> ESPI_IO_0 */
	/* A1  : ESPI_IO1 ==> ESPI_IO_1 */
	/* A2  : ESPI_IO2 ==> ESPI_IO_2 */
	/* A3  : ESPI_IO3 ==> ESPI_IO_3 */
	/* A4  : ESPI_CS# ==> ESPI_CS_L */
	/* A5  : ESPI_CLK ==> ESPI_CLK */
	/* A6  : ESPI_RESET# ==> NC(TP764) */
	/* A7  : I2S2_SCLK ==> EN_PP3300_TRACKPAD */
	PAD_CFG_GPO(GPP_A7, 1, DEEP),
	/* A8  : I2S2_SFRM ==> EN_PP3300_TOUCHSCREEN */
	PAD_CFG_GPO(GPP_A8, 1, DEEP),
	/* A9  : I2S2_TXD ==> EC_IN_RW_OD */
	PAD_CFG_GPI(GPP_A9, NONE, DEEP),
	/* A10 : I2S2_RXD ==> EN_SPKR_PA */
	PAD_CFG_GPO(GPP_A10, 1, DEEP),
	/* A11 : PMC_I2C_SDA ==> SSD_PERST_L */
	PAD_CFG_GPO(GPP_A11, 1, DEEP),
	/* A12 : SATAXPCIE1 ==> M2_SSD_PEDET */
	PAD_CFG_NF(GPP_A12, NONE, DEEP, NF1),
	/* A13 : PMC_I2C_SCL ==> BT_DISABLE_L */
	PAD_CFG_GPO(GPP_A13, 1, DEEP),
	/* A14 : USB_OC1# ==> USB_A0_OC_ODL */
	PAD_CFG_NF(GPP_A14, NONE, DEEP, NF1),
	/* A15 : USB_OC2# ==> USB_A1_OC_ODL */
	PAD_CFG_NF(GPP_A15, NONE, DEEP, NF1),
	/* A16 : USB_OC3# ==> USB_C0_OC_ODL */
	PAD_CFG_NF(GPP_A16, NONE, DEEP, NF1),
	/* A17 : DDSP_HPDC ==> MEM_CH_SEL */
	PAD_CFG_GPI(GPP_A17, NONE, DEEP),
	/* A18 : DDSP_HPDB ==> HDMI_HPD */
	PAD_CFG_NF(GPP_A18, NONE, DEEP, NF1),
	/* A19 : DDSP_HPD1 ==> USB_C0_DP_HPD */
	PAD_CFG_NF(GPP_A19, NONE, DEEP, NF1),
	/* A20 : DDSP_HPD2 ==> USB_C1_DP_HPD */
	PAD_CFG_NF(GPP_A20, NONE, DEEP, NF1),
	/* A21 : DDPC_CTRCLK ==> EN_FP_PWR */
	PAD_CFG_GPO(GPP_A21, 1, DEEP),
	/* A22 : DDPC_CTRLDATA ==> EN_HDMI_PWR */
	PAD_CFG_GPO(GPP_A22, 1, DEEP),
	/* A23 : I2S1_SCLK ==> I2S1_SPKR_SCLK */
	PAD_CFG_NF(GPP_A23, NONE, DEEP, NF1),

	/* B0  : CORE_VID0 */
	PAD_CFG_NF(GPP_B0, NONE, DEEP, NF1),
	/* B1  : CORE_VID1 */
	PAD_CFG_NF(GPP_B1, NONE, DEEP, NF1),
	/* B2  : VRALERT# ==> VRALERT_L */
	PAD_CFG_NF(GPP_B2, NONE, DEEP, NF1),
	/* B3  : CPU_GP2 ==> PEN_DET_ODL */
	PAD_CFG_GPI(GPP_B3, NONE, DEEP),
	/* B4  : CPU_GP3 ==> NC */
	PAD_NC(GPP_B4, NONE),
	/* B5  : ISH_I2C0_CVF_SDA */
	PAD_CFG_NF(GPP_B5, NONE, DEEP, NF1),
	/* B6  : ISH_I2C0_CVF_SCL */
	PAD_CFG_NF(GPP_B6, NONE, DEEP, NF1),
	/* B7  : ISH_12C1_SDA ==> ISH_I2C0_SENSOR_SDA */
	PAD_CFG_NF(GPP_B7, NONE, DEEP, NF1),
	/* B8  : ISH_I2C1_SCL ==> ISH_I2C0_SENSOR_SCL */
	PAD_CFG_NF(GPP_B8, NONE, DEEP, NF1),
	/* B9  : I2C5_SDA ==> PCH_I2C5_TRACKPAD_SDA */
	PAD_CFG_NF(GPP_B9, NONE, DEEP, NF1),
	/* B10 : I2C5_SCL ==> PCH_I2C5_TRACKPAD_SCL */
	PAD_CFG_NF(GPP_B10, NONE, DEEP, NF1),
	/* B11 : PMCALERT# ==> PCH_WP_OD */
	PAD_CFG_GPI_GPIO_DRIVER(GPP_B11, NONE, DEEP),
	/* B12 : SLP_S0# ==> SLP_S0_L */
	PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1),
	/* B13 : PLTRST# ==> PLT_RST_L */
	PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1),
	/* B14 : SPKR ==> GPP_B14_STRAP */
	PAD_NC(GPP_B14, NONE),
	/* B15 : GSPI0_CS0# ==> PCH_GSPI0_H1_TPM_CS_L */
	PAD_CFG_NF(GPP_B15, NONE, DEEP, NF1),
	/* B16 : GSPI0_CLK ==> PCH_GSPI0_H1_TPM_CLK */
	PAD_CFG_NF(GPP_B16, NONE, DEEP, NF1),
	/* B17 : GSPI0_MISO ==> PCH_GSPIO_H1_TPM_MISO */
	PAD_CFG_NF(GPP_B17, NONE, DEEP, NF1),
	/* B18 : GSPI0_MOSI ==> PCH_GSPI0_H1_TPM_MOSI_STRAP */
	PAD_CFG_NF(GPP_B18, NONE, DEEP, NF1),
	/* B19 : GSPI1_CS0# ==> PCH_GSPI1_FPMCU_CS_L */
	PAD_CFG_NF(GPP_B19, NONE, DEEP, NF1),
	/* B20 : GSPI1_CLK ==> PCH_GSPI1_FPMCU_CLK */
	PAD_CFG_NF(GPP_B20, NONE, DEEP, NF1),
	/* B21 : GSPI1_MISO ==> PCH_GSPI1_FPMCU_MISO */
	PAD_CFG_NF(GPP_B21, NONE, DEEP, NF1),
	/* B22 : GSPI1_MOSI ==> PCH_GSPI1_GPMCU_MOSI */
	PAD_CFG_NF(GPP_B22, NONE, DEEP, NF1),
	/* B23 : SML1ALERT# ==> GPP_B23_STRAP # */
	PAD_NC(GPP_B23, NONE),

	/* C0  : SMBCLK ==> EN_PP3300_WLAN */
	PAD_CFG_GPO(GPP_C0, 1, DEEP),
	/* C1  : SMBDATA ==> NOT USED */
	PAD_NC(GPP_C1, NONE),
	/* C2  : SMBALERT# ==> GPP_C2_STRAP */
	PAD_NC(GPP_C2, NONE),
	/* C3  : SML0CLK ==> USB4_SMB_SCL */
	PAD_CFG_NF(GPP_C3, NONE, DEEP, NF1),
	/* C4  : SML0DATA ==> USB4_SMB_SDA */
	PAD_CFG_NF(GPP_C4, NONE, DEEP, NF1),
	/* C5  : SML0ALERT# ==> USB_SMB_INT_L_BOOT_STRAP0 */
	PAD_NC(GPP_C5, NONE),
	/* C6  : SML1CLK ==> EC_PCH_INT_ODL */
	PAD_CFG_GPI_APIC(GPP_C6, NONE, PLTRST, LEVEL, INVERT),
	/* C7  : SML1DATA ==> EN_USI_CHARGE */
	PAD_CFG_GPO(GPP_C7, 1, DEEP),
	/* C8  : UART0_RXD ==> UART_PCH_RX_DEBUG_TX */
	PAD_CFG_NF(GPP_C8, NONE, DEEP, NF1),
	/* C9  : UART0_TXD ==> UART_PCH_TX_DEBUG_RX */
	PAD_CFG_NF(GPP_C9, NONE, DEEP, NF1),
	/* C10 : UART0_RTS# ==> USI_RST_L */
	PAD_CFG_GPO(GPP_C10, 1, DEEP),
	/* C11 : UART0_CTS# ==> CVF_LPSS_INT_L */
	PAD_CFG_GPI(GPP_C11, NONE, DEEP),
	/* C12 : UART1_RXD ==> MEM_STRAP_0 */
	PAD_CFG_GPI(GPP_C12, NONE, DEEP),
	/* C13 : UART1_TXD ==> EN_PP5000_TRACKPAD */
	PAD_CFG_GPO(GPP_C13, 1, DEEP),
	/* C14 : UART1_RTS# ==> MEM_STRAP_2 */
	PAD_CFG_GPI(GPP_C14, NONE, DEEP),
	/* C15 : UART1_CTS# ==> MEM_STRAP_1 */
	PAD_CFG_GPI(GPP_C15, NONE, DEEP),
	/* C16 : I2C0_SDA ==> PCH_I2C0_1V8_AUDIO_SDA */
	PAD_CFG_NF(GPP_C16, NONE, DEEP, NF1),
	/* C17 : I2C0_SCL ==> PCH_I2C0_1V8_AUDIO_SCL */
	PAD_CFG_NF(GPP_C17, NONE, DEEP, NF1),
	/* C18 : I2C1_SDA ==> PCH_I2C1_TOUCH_USI_SDA */
	PAD_CFG_NF(GPP_C18, NONE, DEEP, NF1),
	/* C19 : I2C1_SCL ==> PCH_I2C1_TOUCH_USI_SCL */
	PAD_CFG_NF(GPP_C19, NONE, DEEP, NF1),
	/* C20 : UART2_RXD ==> FPMCU_INT_L */
	/* APIC interrupt conflict, so used GPI_INT; see b/147500717 */
	PAD_CFG_GPI_INT(GPP_C20, NONE, PLTRST, LEVEL),
	/* C21 : UART2_TXD ==> H1_PCH_INT_ODL */
	PAD_CFG_GPI_APIC(GPP_C21, NONE, PLTRST, LEVEL, INVERT),
	/* C22 : UART2_RTS# ==> PCH_FPMCU_BOOT0 */
	PAD_CFG_GPO(GPP_C22, 0, DEEP),
	/* C23 : UART2_CTS# ==> FPMCU_RST_ODL */
	PAD_CFG_GPO(GPP_C23, 1, DEEP),

	/* D0  : ISH_GP0 ==> ISH_IMU_INT_L */
	PAD_NC(GPP_D0, NONE),
	/* D1  : ISH_GP1 ==> ISH_ACCEL_INT_L */
	PAD_CFG_GPI(GPP_D1, NONE, DEEP),
	/* D2  : ISH_GP2 ==> ISH_LID_OPEN */
	PAD_CFG_GPI(GPP_D2, NONE, DEEP),
	/* D3  : ISH_GP3 ==> ISH_ALS_RGB_INT_L */
	PAD_CFG_GPI(GPP_D3, NONE, DEEP),
	/* D4  : IMGCLKOUT0 ==> FCAM_RST_L */
	PAD_CFG_GPO(GPP_D4, 0, PLTRST),
	/* D5  : SRCCLKREQ0$ ==> SSD_CLKREQ_ODL */
	PAD_CFG_NF(GPP_D5, NONE, DEEP, NF1),
	/* D6  : SRCCLKREQ1# ==> WLAN_CLKREQ_ODL */
	PAD_CFG_NF(GPP_D6, NONE, DEEP, NF1),
	/* D7  : SRCCLKREQ2# ==> WWAN_CLKREQ_ODL */
	PAD_CFG_NF(GPP_D7, NONE, DEEP, NF1),
	/* D8  : SRCCLKREQ3# ==> SD_CLKREQ_ODL */
	PAD_CFG_NF(GPP_D8, NONE, DEEP, NF1),
	/* D9  : ISH_SPI_CS# ==> PCH_GSPI2_CVF_CS_L */
	PAD_CFG_NF(GPP_D9, NONE, DEEP, NF7),
	/* D10 : ISH_SPI_CLK ==> PCH_GSPI2_CVF_CLK_STRAP */
	PAD_CFG_NF(GPP_D10, NONE, DEEP, NF7),
	/* D11 : ISH_SPI_MISO ==> PCH_GSPI2_CVF_MISO */
	PAD_CFG_NF(GPP_D11, NONE, DEEP, NF7),
	/* D12 : ISH_SPI_MOSI ==> PCH_GSPI2_CVF_MISO_STRAP */
	PAD_CFG_NF(GPP_D12, DN_20K, DEEP, NF7),
	/* D13 : ISH_UART0_RXD ==> UART_ISH_RX_DEBUG_TX */
	PAD_CFG_NF(GPP_D13, NONE, DEEP, NF1),
	/* D14 : ISH_UART0_TXD ==> UART_ISH_TX_DEBUG_RX */
	PAD_CFG_NF(GPP_D14, NONE, DEEP, NF1),
	/* D15 : ISH_UART0_RTS# ==> MEM_STRAP_3 */
	PAD_CFG_GPI(GPP_D15, NONE, DEEP),
	/* D16 : ISH_UART0_CTS# ==> EN_PP3300_SD */
	PAD_CFG_GPO(GPP_D16, 1, DEEP),
	/* D17 : ISH_GP4 ==> EN_FCAM_PWR */
	PAD_CFG_GPO(GPP_D17, 1, DEEP),
	/* D18 : ISH_GP5 ==> FCAM_SNRPWR_EN */
	PAD_CFG_GPO(GPP_D18, 1, DEEP),
	/* D19 : I2S_MCLK1 ==> I2S_MCLK1 */
	PAD_CFG_NF(GPP_D19, NONE, DEEP, NF1),

	/* E0  : SATAXPCIE0 ==> USB_A1_RT_RST_ODL */
	PAD_CFG_GPO(GPP_E0, 1, DEEP),
	/* E1  : SPI1_IO2 ==> PEN_DET_ODL */
	PAD_CFG_GPI_SCI_LOW(GPP_E1, NONE, DEEP, EDGE_SINGLE),
	/* E2  : SPI1_IO3 ==> WLAN_PCIE_WAKE_ODL */
	PAD_CFG_GPI(GPP_E2, NONE, DEEP),
	/* E3  : CPU_GP0 ==> USI_REPORT_EN */
	PAD_CFG_GPO(GPP_E3, 1, DEEP),
	/* E4  : SATA_DEVSLP0 ==> M2_SSD_PE_WAKE_ODL */
	PAD_NC(GPP_E4, NONE),
	/* E5  : SATA_DEVSLP1 ==> M2_SSD_DEVSLP_OD */
	PAD_CFG_NF(GPP_E5, NONE, DEEP, NF1),
	/* E6  : THC0_SPI1_RST# ==> GPPE6_STRAP */
	PAD_NC(GPP_E6, NONE),
	/* E7  : CPU_GP1 ==> USI_INT */
	PAD_CFG_GPI(GPP_E7, NONE, DEEP),
	/* E8  : SPI1_CS1# ==> SLP_S0IX */
	PAD_CFG_GPO(GPP_E8, 0, DEEP),
	/* E9  : USB2_OC0# ==> USB_C1_OC_ODL */
	PAD_CFG_NF(GPP_E9, NONE, DEEP, NF1),
	/* E10 : SPI1_CS# ==> USB_C0_AUXP_DC */
	PAD_CFG_GPO(GPP_E10, 0, DEEP),
	/* E11 : SPI1_CLK ==> SD_PE_WAKE_ODL */
	PAD_CFG_GPI(GPP_E11, NONE, DEEP),
	/* E12 : SPI1_MISO_IO1 ==> NOT USED */
	PAD_NC(GPP_E12, NONE),
	/* E13 : SPI1_MOSI_IO0 ==> USB_C0_AUXN_DC */
	PAD_CFG_GPO(GPP_E13, 0, DEEP),
	/* E14 : DDPC_HPDA ==> SOC_EDP_HPD */
	PAD_CFG_NF(GPP_E14, NONE, DEEP, NF1),
	/* E15 : ISH_GP6 ==> TRACKPAD_INT_ODL */
	PAD_CFG_GPI_APIC(GPP_E15, NONE, PLTRST, LEVEL, INVERT),
	/* E16 : ISH_GP7 ==> WWAN_SIM1_DET_OD */
	PAD_CFG_GPI(GPP_E16, NONE, DEEP),
	/* E17 : THC0_SPI1_INT# ==> WWAN_PERST_L */
	PAD_CFG_GPO(GPP_E17, 1, DEEP),
	/* E18 : DDP1_CTRLCLK ==> USB_C0_LSX_SOC_TX */
	PAD_CFG_NF(GPP_E18, NONE, DEEP, NF4),
	/* E19 : DDP1_CTRLDATA ==> USB0_C0_LSX_SOC_RX_STRAP */
	PAD_CFG_NF(GPP_E19, NONE, DEEP, NF4),
	/* E20 : DDP2_CTRLCLK ==> USB_C1_LSX_SOC_TX */
	PAD_CFG_NF(GPP_E20, NONE, DEEP, NF4),
	/* E21 : DDP2_CTRLDATA ==> USB_C1_LSX_SOC_RX_STRAP */
	PAD_CFG_NF(GPP_E21, NONE, DEEP, NF4),
	/* E22 : DDPA_CTRLCLK ==> USB_C1_AUXP_DC: Retimer FW drives this pin */
	PAD_NC(GPP_E22, NONE),
	/* E23 : DDPA_CTRLDATA ==> USB_C1_AUXN_DC: Retimer FW drives this pin */
	PAD_NC(GPP_E23, NONE),

	/* F0  : CNV_BRI_DT ==> CNV_BRI_DT_STRAP */
	PAD_CFG_NF(GPP_F0, NONE, DEEP, NF1),
	/* F1  : CNV_BRI_RSP ==> NCV_BRI_RSP */
	PAD_CFG_NF(GPP_F1, UP_20K, DEEP, NF1),
	/* F2  : I2S2_TXD ==> CNV_RGI_DT_STRAP */
	PAD_CFG_NF(GPP_F2, NONE, DEEP, NF1),
	/* F3  : I2S2_RXD ==> CNV_RGI_RSP */
	PAD_CFG_NF(GPP_F3, UP_20K, DEEP, NF1),
	/* F4  : CNV_RF_RESET# ==> CNV_RF_RST_L */
	PAD_CFG_NF(GPP_F4, NONE, DEEP, NF1),
	/* F5  : MODEM_CLKREQ ==> CNV_CLKREQ0 */
	PAD_CFG_NF(GPP_F5, NONE, DEEP, NF3),
	/* F6  : CNV_PA_BLANKING ==> WWAN_WLAN_COEX3 */
	PAD_CFG_NF(GPP_F6, NONE, DEEP, NF1),
	/* F7  : GPPF7_STRAP */
	PAD_NC(GPP_F7, NONE),
	/* F8  : I2S_MCLK2_INOUT ==> HP_INT_L */
	PAD_CFG_GPI_APIC(GPP_F8, UP_20K, DEEP, EDGE_BOTH, INVERT),
	/* F9  : Reserved ==> NC */
	PAD_NC(GPP_F9, NONE),
	/* F10 : GPPF10_STRAP */
	PAD_NC(GPP_F10, DN_20K),
	/* F11 : THC1_SPI2_CLK ==> EN_PP3300_WWAN */
	PAD_CFG_GPO(GPP_F11, 1, DEEP),
	/* F12 : GSXDOUT ==> WWAN_RST_ODL */
	PAD_CFG_GPO(GPP_F12, 1, DEEP),
	/* F13 : GSXDOUT ==> WiFi_DISABLE_L */
	PAD_CFG_GPO(GPP_F13, 1, DEEP),
	/* F14 : GSXDIN ==> SAR0_INT_L */
	PAD_CFG_GPI_SCI_LOW(GPP_F14, NONE, PLTRST, EDGE_SINGLE),
	/* F15 : GSXSRESET# ==> RCAM_RST_L */
	PAD_CFG_GPO(GPP_F15, 1, DEEP),
	/* F16 : GSXCLK ==> WWAN_DPR_SAR_ODL */
	PAD_CFG_GPO(GPP_F16, 1, DEEP),
	/* F17 : WWAN_RF_DISABLE_ODL */
	PAD_CFG_GPO(GPP_F17, 1, DEEP),
	/* F18 : THC1_SPI2_INT# ==> WWAN_PCIE_WAKE_ODL */
	PAD_CFG_GPI_SCI_LOW(GPP_F18, NONE, DEEP, EDGE_SINGLE),
	/* F19 : SRCCLKREQ6# ==> WLAN_INT_L */
	PAD_CFG_GPI_SCI_LOW(GPP_F19, NONE, DEEP, EDGE_SINGLE),
	/* F20 : EXT_PWR_GATE# ==> EXT_PWR_GATE_L */
	PAD_CFG_NF(GPP_F20, NONE, DEEP, NF1),
	/* F21 : EXT_PWR_GATE2# ==> EXT_PWR_GATE2_L */
	PAD_CFG_NF(GPP_F21, NONE, DEEP, NF1),
	/* F22 : VNN_CTRL */
	PAD_CFG_NF(GPP_F22, NONE, DEEP, NF1),
	/* F23 : V1P05_CTRL */
	PAD_CFG_NF(GPP_F23, NONE, DEEP, NF1),

	/* H0  : GPPH0_BOOT_STRAP1 */
	PAD_NC(GPP_H0, NONE),
	/* H1  : GPPH1_BOOT_STRAP2 */
	PAD_NC(GPP_H1, NONE),
	/* H2  : GPPH2_BOOT_STRAP3 */
	PAD_NC(GPP_H2, NONE),
	/* H3  : SX_EXIT_HOLDOFF# ==> SD_PERST_L */
	PAD_CFG_GPO(GPP_H3, 1, DEEP),
	/* H4  : I2C2_SDA ==> PCH_I2C2_MISC_SDA */
	PAD_CFG_NF(GPP_H4, NONE, DEEP, NF1),
	/* H5  : I2C2_SCL ==> PCH_I2C2_MISC_SCL */
	PAD_CFG_NF(GPP_H5, NONE, DEEP, NF1),
	/* H6  : I2C3_SDA ==> PCH_I2C3_CAM_SDA */
	PAD_CFG_NF(GPP_H6, NONE, DEEP, NF1),
	/* H7  : I2C3_SCL ==> PCH_I2C3_CAM_SCL */
	PAD_CFG_NF(GPP_H7, NONE, DEEP, NF1),
	/* H8  : I2C4_SDA ==> WWAN_WLAN_COEX1 */
	PAD_CFG_NF(GPP_H8, NONE, DEEP, NF2),
	/* H9  : I2C4_SCL ==> WWAN_WLAN_COEX2 */
	PAD_CFG_NF(GPP_H9, NONE, DEEP, NF2),
	/* H10 : SRCCLKREQ4# ==> USB_C1_RT_FORCE_PWR */
	PAD_CFG_GPO(GPP_H10, 1, DEEP),
	/* H11 : SRCCLKREQ5# ==> WLAN_PERST_L */
	PAD_CFG_GPO(GPP_H11, 1, DEEP),
	/* H12 : M2_SKT2_CFG0 ==> WWAN_CONFIG0 */
	PAD_CFG_GPI(GPP_H12, NONE, DEEP),
	/* H13 : M2_SKT2_CFG1 # ==> WWAN_CONFIG1 */
	PAD_CFG_GPI(GPP_H13, NONE, DEEP),
	/* H14 : M2_SKT2_CFG2 # ==> RCAM_SNRPWR_EN */
	PAD_CFG_GPO(GPP_H14, 1, DEEP),
	/* H15 : M2_SKT2_CFG3 # ==> WWAN_CONFIG3 */
	PAD_CFG_GPI(GPP_H15, NONE, DEEP),
	/* H16 : DDPB_CTRLCLK ==> DDPB_HDMI_CTRLCLK */
	PAD_CFG_NF(GPP_H16, NONE, DEEP, NF1),
	/* H17 : DDPB_CTRLDATA ==> DDPB_HDMI_CTRLDATA */
	PAD_CFG_NF(GPP_H17, NONE, DEEP, NF1),
	/* H18 : CPU_C10_GATE# ==> CPU_C10_GATE_L */
	PAD_CFG_NF(GPP_H18, NONE, DEEP, NF1),
	/* H19 : TIME_SYNC0 ==> USER_PRES_FP_ODL */
	PAD_CFG_GPI(GPP_H19, NONE, DEEP),
	/* H20 : IMGCLKOUT1 ==> EN_MIPI_RCAM_PWR */
	PAD_CFG_GPO(GPP_H20, 1, DEEP),
	/* H21 : IMGCLKOUT2 ==> CAM_MCLK1 */
	PAD_CFG_NF(GPP_H21, NONE, DEEP, NF1),
	/* H22 : IMGCLKOUT3 ==> CAM_MCLK0 */
	PAD_CFG_NF(GPP_H22, NONE, DEEP, NF1),
	/* H23 : IMGCLKOUT4 ==> WWAN_ESIM_SEL_ODL */
	PAD_CFG_GPO(GPP_H23, 1, DEEP),

	/* R0 : HDA_BCLK ==> I2S0_HP_SCLK */
	PAD_CFG_NF(GPP_R0, NONE, DEEP, NF2),
	/* R1 : HDA_SYNC ==> I2S0_HP_SFRM */
	PAD_CFG_NF(GPP_R1, NONE, DEEP, NF2),
	/* R2 : HDA_SDO ==> I2S0_PCH_TX_HP_RX_STRAP */
	PAD_CFG_NF(GPP_R2, DN_20K, DEEP, NF2),
	/* R3 : HDA_SDIO ==> I2S0_PCH_RX_HP_TX */
	PAD_CFG_NF(GPP_R3, NONE, DEEP, NF2),
	/* R4 : HDA_RST# ==> HDA_RST_L */
	PAD_CFG_NF(GPP_R4, NONE, DEEP, NF1),
	/* R5 : HDA_SDI1 ==> I2S1_PCH_RX_SPKR_TX */
	PAD_CFG_NF(GPP_R5, NONE, DEEP, NF2),
	/* R6 : I2S1_TXD ==> I2S1_PCH_RX_SPKR_RX */
	PAD_CFG_NF(GPP_R6, NONE, DEEP, NF2),
	/* R7 : I2S1_SFRM ==> I2S1_SPKR_SFRM */
	PAD_CFG_NF(GPP_R7, NONE, DEEP, NF2),

	/* S0 : SNDW0_CLK ==> SNDW0_HP_CLK */
	PAD_CFG_NF(GPP_S0, NONE, DEEP, NF1),
	/* S1 : SNDW0_DATA ==> SNDW0_HP_DATA */
	PAD_CFG_NF(GPP_S1, NONE, DEEP, NF1),
	/* S2 : SNDW1_CLK ==> SNDW1_SPKR_CLK */
	PAD_CFG_NF(GPP_S2, NONE, DEEP, NF1),
	/* S3 : SNDW1_DATA ==> SNDW1_SPKR_DATA */
	PAD_CFG_NF(GPP_S3, NONE, DEEP, NF1),
	/* S4 : SNDW2_CLK ==> DMIC_CLK1 */
	PAD_CFG_NF(GPP_S4, NONE, DEEP, NF2),
	/* S5 : SNDW2_DATA ==> DMIC_DATA1 */
	PAD_CFG_NF(GPP_S5, NONE, DEEP, NF2),
	/* S6 : SNDW3_CLK ==> DMIC_CLK0 */
	PAD_CFG_NF(GPP_S6, NONE, DEEP, NF2),
	/* S7 : SNDW3_DATA ==> DMIC_DATA0 */
	PAD_CFG_NF(GPP_S7, NONE, DEEP, NF2),

	/* GPD0: BATLOW# ==> BATLOW_L */
	PAD_CFG_NF(GPD0, NONE, DEEP, NF1),
	/* GPD1: ACPRESENT ==> PCH_ACPRESENT */
	PAD_CFG_NF(GPD1, NONE, DEEP, NF1),
	/* GPD2: LAN_WAKE# ==> EC_PCH_WAKE_ODL */
	PAD_CFG_NF(GPD2, NONE, DEEP, NF1),
	/* GPD3: PWRBTN# ==> EC_PCH_PWR_BTN_ODL */
	PAD_CFG_NF(GPD3, NONE, DEEP, NF1),
	/* GPD4: SLP_S3# ==> SLP_S3_L */
	PAD_CFG_NF(GPD4, NONE, DEEP, NF1),
	/* GPD5: SLP_S4# ==> SLP_S4_L */
	PAD_CFG_NF(GPD5, NONE, DEEP, NF1),
	/* GPD6: SLP_A# ==> SLP_A_L */
	PAD_CFG_NF(GPD6, NONE, DEEP, NF1),
	/* GPD7: GPD7_STRAP */
	PAD_CFG_GPI(GPD7, DN_20K, DEEP),
	/* GPD8: SUSCLK ==> PCH_SUSCLK */
	PAD_CFG_NF(GPD8, NONE, DEEP, NF1),
	/* GPD9: SLP_WLAN# ==> SLP_WLAN_L */
	PAD_CFG_NF(GPD9, NONE, DEEP, NF1),
	/* GPD10: SLP_S5# ==> SLP_S5_L */
	PAD_CFG_NF(GPD10, NONE, DEEP, NF1),
	/* GPD11: LANPHYC ==> NC */
};

/* Early pad configuration in bootblock */
static const struct pad_config early_gpio_table[] = {
	/* A12 : SATAXPCIE1 ==> M2_SSD_PEDET */
	PAD_CFG_NF(GPP_A12, NONE, DEEP, NF1),

	/* A17 : DDSP_HPDC ==> MEM_CH_SEL */
	PAD_CFG_GPI(GPP_A17, NONE, DEEP),

	/* B11 : PMCALERT# ==> PCH_WP_OD */
	PAD_CFG_GPI_GPIO_DRIVER(GPP_B11, NONE, DEEP),

	/* B15 : GSPI0_CS0# ==> PCH_GSPI0_H1_TPM_CS_L */
	PAD_CFG_NF(GPP_B15, NONE, DEEP, NF1),

	/* B16 : GSPI0_CLK ==> PCH_GSPI0_H1_TPM_CLK */
	PAD_CFG_NF(GPP_B16, NONE, DEEP, NF1),

	/* B17 : GSPI0_MISO ==> PCH_GSPIO_H1_TPM_MISO */
	PAD_CFG_NF(GPP_B17, NONE, DEEP, NF1),

	/* B18 : GSPI0_MOSI ==> PCH_GSPI0_H1_TPM_MOSI_STRAP */
	PAD_CFG_NF(GPP_B18, NONE, DEEP, NF1),

	/* C0  : SMBCLK ==> EN_PP3300_WLAN */
	PAD_CFG_GPO(GPP_C0, 1, DEEP),

	/* C21 : UART2_TXD ==> H1_PCH_INT_ODL */
	PAD_CFG_GPI_APIC(GPP_C21, NONE, PLTRST, LEVEL, INVERT),

	/* C22 : UART2_RTS# ==> PCH_FPMCU_BOOT0 */
	PAD_CFG_GPO(GPP_C22, 0, DEEP),

	/* E12 : SPI1_MISO_IO1 ==> EN_PP3300_SSD */
	PAD_CFG_GPO(GPP_E12, 1, DEEP),

	/* H11 : SRCCLKREQ5# ==> WLAN_PERST_L */
	PAD_CFG_GPO(GPP_H11, 1, DEEP),
};

const struct pad_config *__weak variant_base_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(gpio_table);
	return gpio_table;
}

const struct pad_config *__weak variant_override_gpio_table(size_t *num)
{
	*num = 0;
	return NULL;
}

const struct pad_config *__weak variant_early_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(early_gpio_table);
	return early_gpio_table;
}

static const struct cros_gpio cros_gpios[] = {
	CROS_GPIO_REC_AL(CROS_GPIO_VIRTUAL, CROS_GPIO_COMM1_NAME),
	CROS_GPIO_WP_AH(GPIO_PCH_WP, CROS_GPIO_COMM1_NAME),
};

const struct cros_gpio *__weak variant_cros_gpios(size_t *num)
{
	*num = ARRAY_SIZE(cros_gpios);
	return cros_gpios;
}
