#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mempool.h>
#include<linux/slab.h>
#include<linux/string.h>
#include<linux/init.h>

static int	__init my_module_init(void);
static void	__exit my_module_exit(void);

mempool_t *mempool;
static int __init my_module_init(void)
{
	// cache pointer
	struct kmem_cache *kmem_cache;
	void *p0 , *p1;
	// creation of slab cache
	kmem_cache = kmem_cache_create("my_mempool" ,100 , 0 ,SLAB_PANIC ,NULL);
	// create a memory poll, 4 - min number of allocated objects 
	mempool = mempool_create(4 , mempool_alloc_slab , mempool_free_slab , kmem_cache);
	p0 = mempool_alloc(mempool, SLAB_PANIC);
	p1 = mempool_alloc(mempool , SLAB_PANIC);
	strcpy(p0 , "Vegi Mohnish");
	strcpy(p1 , "Ignitarium");
	mempool_free( p0 , mempool);
	printk("%s",p0);
	printk("%s",p1);
	return 0;
}

static void __exit my_module_exit(void)
{	
	mempool_destroy(mempool);
	printk("module removed....\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vegi Mohnish");
MODULE_DESCRIPTION("mempool implementation");
