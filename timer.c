#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>

static int timer_period_ms = 1000;
module_param(timer_period_ms, int, 0755);

static struct timer_list timer;

void timer_handler (unsigned long data)
{
 	printk(KERN_NOTICE "This message is displayed every %d ms\n", timer_period_ms);
	mod_timer(&timer, jiffies + msecs_to_jiffies(timer_period_ms));
}

static int __init timer_init (void)
{
	int ret;
	printk(KERN_NOTICE "Module loaded\n");
	setup_timer(&timer, timer_handler, 0);
	ret = mod_timer(&timer, jiffies + msecs_to_jiffies(timer_period_ms));
	if (ret)
		printk(KERN_ALERT "ERROR in mod_timer\n");
	return 0;
}

static void __exit timer_exit (void)
{
	int ret = del_timer(&timer);
	if (ret)
		printk(KERN_ALERT "ERROR timer is still in use\n");
	printk(KERN_NOTICE "Module unloaded\n");
}

module_init(timer_init);
module_exit(timer_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Artyom Asadchy");

