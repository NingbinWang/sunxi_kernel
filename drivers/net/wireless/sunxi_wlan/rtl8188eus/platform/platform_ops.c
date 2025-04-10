/******************************************************************************
 *
 * Copyright(c) 2013 - 2017 Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 *****************************************************************************/
#ifndef CONFIG_PLATFORM_OPS
/*
 * Return:
 *	0:	power on successfully
 *	others: power on failed
 */
#include <linux/version.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/of_fdt.h>
#include <linux/gpio.h>
#include <hal_data.h>

/*
*如果需要支持power pin控制，需要知道接USB口相关的port的pin脚，并在设备树中
usbtowifi {
	compatible = "hatbsp,rtl8188eus";
	power_pin = <P_GPIO(10)>;
};

*
*/

int platform_wifi_power_on(void)
{
	int ret = 0;
	unsigned int power_pin;
	void *node = NULL;
	printk("platform_wifi_power_on start \n");
	node = of_find_node_by_path("/usbtowifi");
	if(!node){
	  RTW_ERR("[%s]no find usbtowifi\n", __func__);
	  return 0;
	}
	if(!of_device_is_compatible(node,"hatbsp,rtl8188eus")){
		RTW_ERR("can't find node match\n");
		return 0;
	}
	ret = of_property_read_u32(node, "power_pin",&power_pin);
    if(ret < 0){
      RTW_ERR("%s wifi_power_on fail\n", __func__);
	  return 0;
   }
	ret =  gpio_direction_output(power_pin,1);
	if (ret < 0){
		RTW_ERR(" %s *** Failed to set power_pin %d OUTPUTPUT ERROR ***\n", __func__,power_pin);
		return ret;
	}
	printk("platform_wifi_power_on ok \n");
	return ret;
}

void platform_wifi_power_off(void)
{
    int ret = 0;
	unsigned int power_pin;
	void *node = NULL;
	node = of_find_node_by_path("/usbtowifi");
	if(!node){
	  RTW_ERR("[%s]no find usbtowifi\n", __func__);
	  return;
	}
	if(!of_device_is_compatible(node,"hatbsp,rtl8188eus")){
		RTW_ERR("can't find node match\n");
		return ;
	}
	ret = of_property_read_u32(node, "power_pin",&power_pin);
    if(ret < 0){
      RTW_ERR("[%s] wifi_power_on fail\n", __func__);
	  return ;
   }
	ret =  gpio_direction_output(power_pin,0);
	if (ret < 0){
		RTW_ERR(" %s *** Failed to set power_pin %d OUTPUTPUT ERROR ***\n", __func__,power_pin);
		return;
	}
	gpio_set_value(power_pin,1);

}
#endif /* !CONFIG_PLATFORM_OPS */
