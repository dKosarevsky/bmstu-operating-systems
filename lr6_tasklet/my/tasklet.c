#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/random.h>

void my_tasklet_function( void  )
{
  printk( "my_tasklet_function: %d\n", get_random_int() % 90 + 10);
  return;
}

void my_hi_tasklet_function( void )
{
  printk( "my_hi_tasklet_function: %d\n", get_random_int() % 900 + 100);
  return;
}

DECLARE_TASKLET( my_tasklet1, my_tasklet_function, NULL );
DECLARE_TASKLET( my_tasklet2, my_tasklet_function, NULL );
DECLARE_TASKLET( my_tasklet3, my_tasklet_function, NULL );
DECLARE_TASKLET( my_tasklet4, my_tasklet_function, NULL );
DECLARE_TASKLET( my_hi_tasklet1, my_hi_tasklet_function, NULL );

int init_m( void )
{
  printk( "\n\ninit_module\n" );

  tasklet_schedule( &my_tasklet1 );
  tasklet_schedule( &my_tasklet2 );
  tasklet_hi_schedule( &my_hi_tasklet1);
  tasklet_schedule( &my_tasklet3 );
  tasklet_schedule( &my_tasklet4 );

  return 0;
}

void exit_m( void )
{
  printk( "\nexit_module\n\n\n" );
  tasklet_kill( &my_tasklet1 );
  tasklet_kill( &my_tasklet2 );
  tasklet_kill( &my_hi_tasklet1);
  tasklet_kill( &my_tasklet3 );
  tasklet_kill( &my_tasklet4 );
  return;
}

module_init(init_m);
module_exit(exit_m);

MODULE_LICENSE("GPL"); 