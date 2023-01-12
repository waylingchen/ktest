#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

/* For modinfo */
MODULE_AUTHOR(" ");
MODULE_DESCRIPTION("Example Linux Module");
MODULE_VERSION("1.0");

/* Necessary */
MODULE_LICENSE("GPL");

/* Specify a parameter and default value */
static char *name = "Yocto";

/* Char pointer, world readable */
module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "dmesg parameter");

int init_tasks(void)
{
    struct task_struct *task = current; 
    printk(KERN_NOTICE "current process: %s, PID: %d", task->comm, task->pid);
    do
    {
        task = task->parent;
        printk(KERN_NOTICE "Parent process: %s, PID: %d", task->comm, task->pid);
    } while (task->pid != 0);
    return 0;
}


void exit_tasks(void)
{
    printk(KERN_NOTICE "Exiting module");
}


module_init(init_tasks);
module_exit(exit_tasks);
