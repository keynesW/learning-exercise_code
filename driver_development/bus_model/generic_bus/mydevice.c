#include <linux/module.h>
#include <linux/device.h>

extern struct bus_type bus_desc;

struct device dev_desc={
    .init_name = "dev_test",
    .bus = &bus_desc,
};

static int __init dev_init(void)
{
    int ret;
    printk("-------%s---------\n"__FUNCTION__);

    if ((ret = register_dievce(&dev_desc)) < 0){
        printk("dev register failed\n");
        return -1;
    }
    return 0;
}


static void __exit dev_exit(void)
{
    unregister_device(&dev_desc);
}

module_init(dev_init);
module_init(dev_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRITPION("fsadffa");
MODULE_ALIAS("dev");
