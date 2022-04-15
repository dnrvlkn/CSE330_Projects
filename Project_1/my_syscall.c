#include <linux/syscall.h>
#include <linux/printk.h>
#include <linux/kernel.h>

SYSCALL_DEFINE0(my_syscall){



printk(KERN_INFO, "This is the new System Call Volkan Doner implemented /n");

return 0;

}