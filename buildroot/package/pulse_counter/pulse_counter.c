#include <generated/autoconf.h>
#include <linux/init.h>
#include <linux/module.h>

#include <linux/device.h>
#include <linux/err.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>
#include <linux/timekeeping.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("whitfijs");


#define PULSE_COUNTER_GPIO                  6
#define PULSE_COUNTER_GPIO_DESC             "Pulse Interrupt Pin"
#define PULSE_COUNTER_GPIO_DEVICE_DESC      "Pulse counter"

#define PULSE_COUNTER_LED_GPIO              18
#define PULSE_COUNTER_LED_GPIO_DESC         "Pulse counter led indicator pin"

#define PULSE_SPACING_NUM_SAMPLES           4

static __u16 pulse_counter_gpio_irq_num 	= 0;
static __u32 pulse_count_total				= 0;
static __u64 pulse_spacing[PULSE_SPACING_NUM_SAMPLES];
static __u64 pulse_spacing_index            = 0;
static __u64 pulse_spacing_avg              = 0;

static irqreturn_t pulse_irq_handler(__u32 irq, void * dev_id, struct pt_regs * regs){
	static ktime_t last;
	ktime_t now;
	static int lastInterrupt = 0;
    static __u8 on = 0;
	
	
    on = !on;
    gpio_set_value(PULSE_COUNTER_LED_GPIO, on);

    if (lastInterrupt == 0) {
		last = ktime_get();
        lastInterrupt = jiffies;
    } else {
		now = ktime_get();
        __u64 now_usec = ktime_to_ns(now);
		__u64 last_usec = ktime_to_ns(last);
        pulse_spacing[pulse_spacing_index++] = (now_usec - last_usec);
        pulse_spacing_index = pulse_spacing_index & (PULSE_SPACING_NUM_SAMPLES - 1);
        last = now;

        if (pulse_spacing_index == 0) {
            __u64 avg = 0;
	        for (int i = 0; i < PULSE_SPACING_NUM_SAMPLES; i++) {
	            avg += pulse_spacing[i];
	        }
	        pulse_spacing_avg = avg / PULSE_SPACING_NUM_SAMPLES;
        }
    }
    pulse_count_total++;

    return IRQ_HANDLED;
}

static ssize_t set_pulse_count_callback(struct device* dev,struct device_attribute* attr, const char * buf, size_t count){
	long int count_value = 0;
	if (kstrtol(buf, 10, &count_value) < 0)
		return -EINVAL;

	pulse_count_total = count_value;
	return count;
}

static ssize_t show_pulse_count_callback(struct device *d, struct device_attribute * attr, char * buf){
	__u32 pulse_count = pulse_count_total;
	printk(KERN_INFO "In attr1_show function\n");
	printk(KERN_INFO "%u\n", pulse_count);
	return sprintf(buf, "%u\n", pulse_count);
}



static ssize_t set_pulse_spacing_avg_callback(struct device* dev,struct device_attribute* attr, const char * buf, size_t count){
	long int spacing = 0;
	if (kstrtol(buf, 10, &spacing) < 0)
		return -EINVAL;

	pulse_spacing_avg = spacing;
	return count;
}

static ssize_t show_pulse_spacing_avg_callback(struct device *d, struct device_attribute * attr, char * buf){
	__u32 pulse_spacing = pulse_spacing_avg;
	printk(KERN_INFO "Show Pulse Spacing Avg:\n");
	printk(KERN_INFO "%u\n", pulse_spacing);
	return sprintf(buf, "%u\n", pulse_spacing);
}

static DEVICE_ATTR(pulse_count, 00664, show_pulse_count_callback, set_pulse_count_callback);
static DEVICE_ATTR(pulse_spacing_avg, 00664, show_pulse_spacing_avg_callback, set_pulse_spacing_avg_callback);

static struct class *s_pDeviceClass;
static struct device *s_pDeviceObject;
//static struct device *s_pPulseSpacingDeviceObject;

static int __init pulseCounterModule_init(void){
	int result;
	
	if (gpio_request(PULSE_COUNTER_LED_GPIO, "LED Pin")) {
	  printk("GPIO request faiure: %s\n", "LED Pin");
	  return -EINVAL;
	}
	gpio_direction_output(PULSE_COUNTER_LED_GPIO, 1);
    
    // create class in /sys/class
	s_pDeviceClass = class_create(THIS_MODULE, "volvo_dash");
	BUG_ON(IS_ERR(s_pDeviceClass));
    
    // create pulse_count attribute
	s_pDeviceObject = device_create(s_pDeviceClass, NULL, 0, NULL, "pulse_counter");
	BUG_ON(IS_ERR(s_pDeviceObject));

	result = device_create_file(s_pDeviceObject, &dev_attr_pulse_count);
    
    // create pulse spacing object
	//s_pPulseSpacingDeviceObject = device_create(s_pDeviceClass, NULL, 0, NULL, "pulse_spacing_avg");
	//BUG_ON(IS_ERR(s_pPulseSpacingDeviceObject));

	result = device_create_file(s_pDeviceObject, &dev_attr_pulse_spacing_avg);

   if (gpio_request(PULSE_COUNTER_GPIO, PULSE_COUNTER_GPIO_DESC)) {
      printk("GPIO request faiure: %s\n", PULSE_COUNTER_GPIO_DESC);
      return -EINVAL;
   }
   
 
   if ( (pulse_counter_gpio_irq_num = gpio_to_irq(PULSE_COUNTER_GPIO)) < 0 ) {
      printk("GPIO to IRQ mapping faiure %s\n", PULSE_COUNTER_GPIO_DESC);
      return -EINVAL;
   }
 
   printk(KERN_NOTICE "Mapped int %d\n", pulse_counter_gpio_irq_num);
 
   if (request_irq(pulse_counter_gpio_irq_num,
                   (irq_handler_t ) pulse_irq_handler,
                   IRQF_TRIGGER_FALLING,
                   PULSE_COUNTER_GPIO_DESC,
                   PULSE_COUNTER_GPIO_DEVICE_DESC)) {
      printk("Irq Request failure\n");
      return -EINVAL;
   }


	return 0;
}

static void __exit pulseCounterModule_exit(void)
{
	device_remove_file(s_pDeviceObject, &dev_attr_pulse_count);
	device_destroy(s_pDeviceClass, 0);
	class_destroy(s_pDeviceClass);

	/*Free LED GPIO*/
	gpio_free(PULSE_COUNTER_LED_GPIO);

	/*Free pulse counter interrupt and GPIO*/
	free_irq(pulse_counter_gpio_irq_num, PULSE_COUNTER_GPIO_DEVICE_DESC);
	gpio_free(PULSE_COUNTER_GPIO);
}

module_init(pulseCounterModule_init);
module_exit(pulseCounterModule_exit);
