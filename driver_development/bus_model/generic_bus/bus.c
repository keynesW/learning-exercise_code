#include <linux/module.h>
#include <linux/device.h>
#include "dev_desc.h"

int drv_dev_match(struct device * dev, \
    struct device_driver *drv)
{
    if(!strcmp(dev->kobj.name,drv->name)){
        printk(" match ok\n");
        return 1;
    }else{
        printk(" match failed\n");
    }
    return 0;
}

struct bus_type bus_desc = {
    .name = "bus_test",
    .match = drv_dev_match,
};
EXPORT_SYMBOL(bus_desc);

static int __init bus_init(void)
{
    int ret;
    printk("-------%s---------\n",__FUNCTION__);

    if( (ret = bus_register(&bus_desc)) < 0 ){
        printk("bus register failed\n");
        return -1;
    }
    return 0;
}

static void __exit bus_exit(void)
{
    bus_unregister(&bus_desc);
}

module_init(bus_init);
module_exit(bus_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("bus mode");
MODULE_ALIAS("bus");
