// Working example of 25 MHz SPI on Intel Edison using DMA
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/spi/spi.h>
#include <linux/interrupt.h>

#define BUF_SIZE 4096
#define BITS_PER_WORD 32

static volatile int tasklet_enabled = 0;
static struct spi_device* spi_dev = NULL;
static void* buffer;
static struct spi_message msg;
static struct spi_transfer xfer = {
    .bits_per_word = BITS_PER_WORD,
    .len = BUF_SIZE,
  };

static void spitx_tasklet(unsigned long);
DECLARE_TASKLET(spitx, spitx_tasklet, 0);

static void spi_async_callback(void* unused ) {
  tasklet_schedule(&spitx);
}

static void spitx_tasklet(unsigned long ignored) {
  int res;
  xfer.tx_buf = buffer;
  memset((char*)buffer, 0xA0, BUF_SIZE);
  spi_message_init(&msg);
  spi_message_add_tail(&xfer, &msg);
  msg.complete = spi_async_callback;
  res = spi_async(spi_dev, &msg);
    if (res)  {
      printk(KERN_ERR "spi_async_locked FAILED %d\n", res);
    }
}


static int test_spi_probe(struct spi_device *spi) {
  spi->max_speed_hz = 25000000;
  spi->bits_per_word = BITS_PER_WORD;
  spi_setup(spi);
  spi_dev = spi;
  printk(KERN_INFO "SPI probed, starting pump thread.\n");
  tasklet_enabled = 1;
  tasklet_schedule(&spitx);
  return 0;
}

static void terminate_tasklet() {
 if (!tasklet_enabled)
   return;
 tasklet_enabled = 0;
 tasklet_kill(&spitx);
}

static int test_spi_remove(struct spi_device *spi) {
  spi_dev = NULL;
  terminate_tasklet();
  return 0;
}

static const struct spi_device_id idtable[] = {
  {"ads7955", 0},
  {}
};

static struct spi_driver test_spi_driver = {
  .driver = {
    .name = "ads7955",
    .owner = THIS_MODULE,
  },
  .probe = test_spi_probe,
  .remove = test_spi_remove,
  .id_table = idtable,
};

static int __init test_spi_init(void)
{
    int res;
    buffer = kmalloc(BUF_SIZE, GFP_DMA | GFP_KERNEL);
    memset((char*)buffer, 0xA0, BUF_SIZE);
    res = spi_register_driver(&test_spi_driver);
    if (res)
      return res;
    printk(KERN_INFO "test spi intialized\n");
    return 0;
}

static void __exit test_spi_cleanup(void)
{
    terminate_tasklet();
    printk(KERN_INFO "Cleaning up module.\n");
    kfree(buffer);
    return spi_unregister_driver(&test_spi_driver);
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Primiano Tucci");
MODULE_DESCRIPTION("Test");

module_init(test_spi_init);
module_exit(test_spi_cleanup);