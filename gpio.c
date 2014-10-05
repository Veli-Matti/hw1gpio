#include "gpio.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int local_init(void)
{
	// Init device struct
	// open emody driver 
	int fd = open("/dev/mem", (O_RDWR|O_SYNC));
	printf("%s called\n",__func__);
	
	if (fd < 0) {
		printf("Error: Unable to open '/dev/mem'\n");
		return -1;
	}
	
	my_gpio_dev.gpio_map = mmap(
		NULL,			// Any address in our space is ok
		BLOCK_SIZE,		// Map length
		PROT_READ|PROT_WRITE, //Enable reading & writing
		MAP_SHARED,		// Map can be shared with outhe processes
		fd,				// File to map
		GPIO_BASE		// Offset to starting point
	);
	
	close(fd);
	fd = -1;
	
	if (my_gpio_dev.gpio_map == MAP_FAILED) {
		printf("mmap error %d\n", (int) my_gpio_dev.gpio_map);
		return -1;
	}
	
	// Always use voletile pointer
	my_gpio_dev.gpio = (volatile unsigned *)my_gpio_dev.gpio_map;
	
	return 0;
}


int initGPIO(const gpio_direction direction, const int pin)
{
	int bank;
	int pinselect;
	volatile unsigned int * gpio;

	printf("%s called\n",__func__);
	
	// Get the right gpio control bank and pinselection
	bank = pin / 10;
	pinselect = (pin % 10)*3;
	printf("bank == %d, pinselect == %d\n", bank, pinselect);
	
	// Move the gpio pointer at the beginning of the right registry
	gpio = my_gpio_dev.gpio;
	gpio = gpio + bank;
	
	printf("gpio data (before) == '%d'\n", *gpio);
	
	// Setup the PIN
	// ... clear the old value (this inits a port as input also)
	*(gpio) &= ~(7 << pinselect); //0 == Input

	printf("gpio data (mid) == '%d'\n", *gpio);

	if (direction == gpio_direction_output) {
		*(gpio) |= (1 << pinselect); // 1 == Output
	}
	printf("gpio data (after) == '%d'\n", *gpio);

	return 0;
}

int setGPIO(const int gpio, const int state)
{
	volatile unsigned int * gpiomem;
	gpiomem = my_gpio_dev.gpio;
	int reg_pos = 7; // HIGH
	
	printf("%s called\n",__func__);
	
	if (state == 0) 
		reg_pos = 10; // LOW
	
	gpiomem = gpiomem + reg_pos;
	
	*(gpiomem) = 1 << gpio;

	return 0;
}

void unmap_peripheral(struct gpio_device *p)
{
    munmap(p->gpio_map, BLOCK_SIZE);
	p->gpio = NULL;
}

