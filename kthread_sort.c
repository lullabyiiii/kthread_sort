#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/kthread.h>

static struct task_struct *thread_st;

int list[] = {4,2,7,34,13,56,8,43,90,21,23,1,5,78,9};
int input[15];
int output[15];
int num_samples = 15;

void sorter(int list[])
{
	int i;
	int temp;
	//int begin = p->from_index;
	//int end = p->to_index;
	int swapped = 1;
	int j = 0;
	while(swapped == 1)
	{	
		swapped = 0;
		j++;
		for (i = 0; i < num_samples+1; i++)
		{
			if (list[i] > list[i+1])
			{
				temp = list[i];
				list[i] = list[i+1];
				list[i+1] = temp;
				swapped = 1;
				
			}
		
		}	

	
	}
	
}


static struct task_struct *thread_st;
//function executed by kernel thread
static int sort_fn(void *Ptr)
{
	//parameters* data = Ptr;
	
	int i;

	printk(KERN_INFO "Original List: \n");
	for (i = 0; i < num_samples; i++)
	{
		printk(KERN_CONT"%d ", list[i]);
	}

	//int n = sizeof(list)/sizeof(list[0]);

	sorter(list);

	printk(KERN_INFO"Sorted list: \n");
	for (i = 0; i < num_samples+2; i++)
	{
		printk(KERN_CONT"%d ", list[i]);
	}
	
	//while(!kthread_should_stop())
	//{
	//	printk(KERN_INFO "Thread running\n");
	//	ssleep(5);
	//}
	//printk(KERN_INFO "Thread stopping\n");
	do_exit(0);
	return 0;
}
//module initialization

static int __init init_thread(void)
{
	int i;

	printk(KERN_INFO "creating thread\n");
	//creating the kernel thread with name"mythread"
	thread_st = kthread_run(sort_fn, NULL, "mythread");
	
	if(thread_st)
	
		printk(KERN_INFO "Thread created succesully\n");

	else
		printk(KERN_ERR "Thrad creating failed \n");
	

	return 0;
}
//moudle exit
static void __exit cleanup_thread(void)
{
	printk(KERN_INFO "cleaning up\n");
	//if (thread_st)
	//{
		//kthread_stop(thread_st);
		//printk(KERN_INFO "Thread stopped\n");
	//}
}


module_init( init_thread);
module_exit( cleanup_thread);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SALLY");
MODULE_DESCRIPTION("KTHRAD PRACTICE");
