#include <linux/module.h>
#include <linux/device.h>
#include "dev_desc.h"

extern struct bus_type bus_desc;


void drv_release(struct device * dev)
{
    printk("-------%s---------\n",__FUNCTION__);
}

struct dev_inf led_inf = {
    .reg_base = 0x11000c20,
    .pin_num = 0,
};

struct device dev_desc = {
    .init_name = "led_test",
    .bus = &bus_desc,
    .release = drv_release,
    .platform_data = &led_inf,
};

static int __init dev_init(void)
{
    int ret;
    printk("-------%s---------\n",__FUNCTION__);

    if ((ret = device_register(&dev_desc)) < 0){
        printk("dev register failed\n");
        return -1;
    }
    return 0;
}

static void __exit dev_exit(void)
{
    device_unregister(&dev_desc);
}

module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("bus mode");
MODULE_ALIAS("dev");
