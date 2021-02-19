#include <linux/module.h>
#include <linux/device.h>

struct bus_type bus_desc = {
    .name = "bus_test",
};
EXPORT_SYMBOL(bus_desc);

static int __init bus_init(void)
{
    int ret;
    printk("-------%s---------\n"__FUNCTION__);

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
module_init(bus_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRITPION("bus mode");
MODULE_ALIAS("bus");
