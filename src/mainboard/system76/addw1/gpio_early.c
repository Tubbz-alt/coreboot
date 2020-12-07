/* SPDX-License-Identifier: GPL-2.0-only */

#include <mainboard/gpio.h>
#include <soc/gpio.h>

static const struct pad_config early_gpio_table[] = {
	PAD_CFG_TERM_GPO(GPP_F22, 0, NONE, DEEP), // DGPU_RST_N
	PAD_CFG_TERM_GPO(GPP_F23, 0, NONE, DEEP), // DGPU_PWR_EN
};

void mainboard_configure_early_gpios(void)
{
	gpio_configure_pads(early_gpio_table, ARRAY_SIZE(early_gpio_table));
}
