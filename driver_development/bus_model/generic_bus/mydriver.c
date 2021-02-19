#include <linux/module.h>
#include <linux/device.h>

extern struct bus_type bus_desc;

struct device_driver drv_desc={
    .name = "drv_test",
    .bus = &bus_desc,
};

static int __init drv_init(void)
{
    int ret;
    printk("-------%s---------\n"__FUNCTION__);

    if ((ret = driver_register(&drv_desc)) < 0){
        printk("drv register failed\n");
        return -1;
    }
    return 0;
}


static void __exit drv_exit(void)
{
    driver_unregister(&drv_desc);
}

module_init(drv_init);
module_init(drv_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRITPION("bus mode");
MODULE_ALIAS("drv");
