#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
//#include "dev_desc.h"

#define GPX1CON  0x11000c20
#define GPX1SIZE 16

#define GPX3CON  0x114001e0
#define GPX3SIZE 16

struct resource pdev_res[] = {
    {
        .start = GPX1CON,
        .end = GPX1CON + GPX1SIZE -1,
        .flags = IORESOURCE_MEM,
    },
    {
        .start = GPX3CON,
        .end = GPX3CON + GPX3SIZE -1,
        .flags = IORESOURCE_MEM,
    },
    {
        .start = 0,
        .end = 0,
        .flags = IORESOURCE_IRQ,
    },
    {
        .start = 4,
        .end = 4,
        .flags = IORESOURCE_IRQ,
    },
};
void platform_dev_release(struct device * dev)
{
    printk("-------%s---------\n",__FUNCTION__);

}

struct platform_device pdev_desc = {
    .name = "led2",
    .num_resources = ARRAY_SIZE(pdev_res), 
    .resource = pdev_res,
    .dev = {
        .release = platform_dev_release,
    }
};

static int __init platform_dev_init(void)
{
    printk("-------%s---------\n",__FUNCTION__);
    
    if(platform_device_register(&pdev_desc) < 0 )
        printk("register failed\n");

    return 0;
}

static void __exit platform_dev_exit(void)
{
    printk("-------%s---------\n",__FUNCTION__);
    platform_device_unregister(&pdev_desc);
}

module_init(platform_dev_init);
module_exit(platform_dev_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("platform bus");
MODULE_ALIAS("platform_dev");
