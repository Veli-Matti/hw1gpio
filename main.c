#include "gpio.h"
#include <unistd.h>

int main(int argc, char **argv)
{
	printf("myGPIP main called!\n");
	int err = local_init();
	
	if (!err) {
	
		// init GPIO 17 as output
		initGPIO(gpio_direction_output, 17);
	
		// ...and start toggling
		while(1) {
			setGPIO(17, 1);
			sleep(1);
		
			setGPIO(17, 0);
			sleep(1);
		}
	}
	
	return 0;
}

