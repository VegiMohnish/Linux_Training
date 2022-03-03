#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/slab.h>
#include<linux/string.h>
#include<linux/init.h>


static struct example_struct {
	unsigned int id;
	char example_string[10];
	struct example_struct *next;
}	*example_struct_pointer;

static struct example_struct *top = NULL;
static struct kmem_cache *example_cachep;
static unsigned int i;

static void example_constructor(void *argument)
{
	static unsigned int id;
	static char test_string[] = "Stack";
	struct example_struct *example = (struct example_struct *)argument;
	example->id = id;
	strcpy(example->example_string,test_string);
	//example->next = top;
	//top = example;
	id++;
}

struct example_struct* push(void)
{
	struct example_struct* example = kmem_cache_alloc(example_cachep,GFP_KERNEL);
	if(example) {
		// Add to the stack here
		example->next = top;
		top = example;
	}
	return example;
}

void pop(void)
{
	// Take the first element.
	struct example_struct *example = top;
	// Remove the element from the stack
	top = example->next;
	// In given example re-initialization actions before freeing the element are not needed.
	kmem_cache_free(example_cachep, example);
}

void print_example_struct(struct example_struct *example)
{
	pr_notice("Struct id: %u\n",example->id);
	//pr_notice("String field content: %s\n",example->example_string);
	printk(KERN_ALERT "example_struct_pointer: %p\n",example_struct_pointer);
	//printk(KERN_ALERT "top: %p\n",top);
	printk(KERN_ALERT "i: %d\n",i);
	i++;
}

static int __init slabmod_init(void)
{
	example_cachep = kmem_cache_create("example cache", sizeof(struct example_struct),0, SLAB_HWCACHE_ALIGN|SLAB_POISON|SLAB_RED_ZONE, example_constructor);
	if(IS_ERR(example_cachep)) {
		pr_alert("Error creating cache: %ld\n",PTR_ERR(example_cachep));
		return -ENOMEM;
	}

	for(i=1 ; i<6 ; i++) {
		printk(KERN_ALERT "i: %d\n",i);
		example_struct_pointer = push();
		if(IS_ERR(example_struct_pointer)) {
			pr_alert("Error allocating from cache: %ld\n", PTR_ERR(example_struct_pointer));
			kmem_cache_destroy(example_cachep);
		return -ENOMEM;
		}
	}
	return 0;
}

static void __exit slabmod_exit(void)
{
	struct example_struct *tmp = example_struct_pointer;
	i = 1;
	if(example_cachep) {
		while(example_struct_pointer != NULL) {
			pop();
			print_example_struct(example_struct_pointer);
			printk(KERN_ALERT "tmp: %p\n",tmp);
			printk(KERN_ALERT "next: %p / %p\n\n",top->next,*(top->next));
		}
		printk(KERN_ALERT "tmp: %p\n",tmp);
		printk(KERN_ALERT "next: %p\n\n",top->next);
		printk(KERN_ALERT "example_struct_pointer: %p\n",example_struct_pointer);
		kmem_cache_destroy(example_cachep);
	}
}

module_init(slabmod_init);
module_exit(slabmod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vegi Mohnish");
MODULE_DESCRIPTION("A module demonstrating use of the slab allocator.");

