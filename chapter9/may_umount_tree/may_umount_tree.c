/********************************************************************************
* File Name:	may_umount_tree.c
* Description:	第9章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/fs.h> 
#include <linux/fs_struct.h> 
#include <linux/path.h> 
#include <linux/sched.h> 
#include <linux/fdtable.h> 
#include <linux/mount.h> 
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");


static struct seq_file seq= 
{ 
	.size = 1, 
};

{
	struct vfsmount *mnt; 
	mnt = current->fs->pwd.mnt; 
  	int data4 = may_umount_tree(mnt); 
	printk("<0>After \"may_umount_tree\", the returned value is :%d\n",data4); 
 

	return 0;
}

void may_umount_tree_exit(void)
{
        printk("<0>Goodbye  may_umount_tree_test\n");
}



module_init(may_umount_tree_init);
module_exit(may_umount_tree_exit);
