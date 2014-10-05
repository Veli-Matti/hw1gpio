#include <stdio.h>

/* Defines */
#define PERIPHERAL_BASE	0x20000000
#define GPIO_BASE (PERIPHERAL_BASE + 0x200000)
#define BLOCK_SIZE	(4*1024)

/* Data structures */
struct gpio_device {
	void *gpio_map;
	volatile unsigned int * gpio;
} my_gpio_dev;

typedef enum {
	gpio_direction_output	= 1,
	gpio_direction_input	= 2
} gpio_direction;

/* Function prototypes */
int local_init(void);
int initGPIO(const gpio_direction direction, const int pin);
int setGPIO(const int gpio, const int state);
void unmap_peripheral(struct gpio_device *p);
