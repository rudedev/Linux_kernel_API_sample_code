/********************************************************************************
* File Name:	__wake_up.c
* Description:	第4章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
/*Í·ÎÄŒþÒýÓÃ*/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/wait.h>
#include <linux/list.h>
MODULE_LICENSE("GPL");

/*È«ŸÖ±äÁ¿¶šÒå*/
static wait_queue_head_t head; //µÈŽý¶ÓÁÐÍ·ÔªËØ

/*×Óœø³ÌŽŠÀíº¯Êý¶šÒå*/
int my_function(void * argc)
{
       printk("<0>in the kernel thread function!\n");	
	printk("<0>the current pid is:%d\n",current->pid);   //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>the state of the real_parent is :%ld\n",current->real_parent->state); //ÏÔÊŸžžœø³ÌµÄ×ŽÌ¬
	__wake_up(&head,TASK_ALL,0,NULL); //µ÷ÓÃº¯Êý»œÐÑµÈŽý¶ÓÁÐÖÐµÄœø³Ì
	printk("<0>the state of the real_parent after __wake_up is :%ld\n",current->real_parent->state); //ÏÔÊŸº¯Êýµ÷ÓÃÖ®ºóµÄžžœø³ÌµÄ×ŽÌ¬
	printk("<0>out the kernel thread function\n");
	return 0;
}

/*Ä£¿éŒÓÔØº¯Êý¶šÒå*/
static int __init __wake_up_init(void)
{
	int result=0;    //ŸÖ²¿±äÁ¿¶šÒå
	long left_time=0;
	wait_queue_t data;
	printk("<0>into __wake_up_init.\n");
	result=kernel_thread(my_function,NULL,CLONE_KERNEL);  //ŽŽœšÐÂœø³Ì
       init_waitqueue_head(&head); //³õÊŒ»¯µÈŽý¶ÓÁÐÍ·ÔªËØ
	init_waitqueue_entry(&data,current); //ÓÃµ±Ç°œø³Ì³õÊŒ»¯µÈŽý¶ÓÁÐÖÐµÄÒ»žöÔªËØ
	add_wait_queue(&head,&data); //œ«µÈŽý¶ÓÁÐÔªËØŒÓÈëµÈŽý¶ÓÁÐÖÐ
	left_time=sleep_on_timeout(&head,100);	//Ê¹µÈŽý¶ÓÁÐœø³Ì²»¿ÉÖÐ¶ÏµÄµÈŽý×ŽÌ¬
	printk("<0>the return result of the sleep_on_timeout is:%ld\n",left_time); //ÏÔÊŸº¯Êýsleep_on_timeout( )µÄ·µ»Øœá¹û
	printk("<0>the result of the kernel_thread is :%d\n",result); //ÏÔÊŸº¯Êýkernel_thread( )µÄ·µ»Øœá¹û
	printk("<0>the current pid is:%d\n",current->pid);  //ÏÔÊŸµ±Ç°œø³ÌµÄPIDÖµ
	printk("<0>out __wake_up_init.\n");
	return 0;
}

/*Ä£¿éÐ¶ÔØº¯Êý¶šÒå*/
static void __exit __wake_up_exit(void)
{	
        printk("<0>Goodbye __wake_up\n");	
}

/*Ä£¿éŒÓÔØŒ°Ð¶ÔØº¯Êýµ÷ÓÃ*/
module_init(__wake_up_init);
module_exit(__wake_up_exit);


