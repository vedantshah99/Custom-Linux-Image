#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

int main(){
	// Settings
	const unsigned char tmp102_addr = 0x48; // I2C address of TMP102 sensor
	const unsigned char reg_temp = 0x00; // Address of the temp register
	const char filename[] = "/dev/i2c-1"; // Location of I2C device file
	
	int file;
	char buf[5];
	int16_t temp_buf;
	float temp_c;

	// Open device file for read/write
	if ((file = open(filename, O_RDWR)) < 0){
		printf("Failed to open the bus.\n");
		exit(1);
	}

	// Change to I2C address of TMP102
	if (ioctl(file, I2C_SLAVE, tmp102_addr) < 0) {
		printf("Failed to acquire bus access or talk to device.\n");
		exit(1);
	}

	// Start read by writing location of temperature register
	buf[0] = 0x00;
	if (write(file, buf,1) != 1){
		printf("Could not write to I2C device.\n");
		exit(1);
	}

	// Read temperature
	if (read(file, buf,2 != 2)){
		printf("Could not read from I2C device");
		exit(1);
	}

	// Combine received bytes to single 16-bit value
	temp_buf = (buf[0] << 4) | (buf[1] >> 4);

	// If value is negative (2x Compliment), pad empty 3 bits with ls
	if (temp_buf > 0x7FF){
		temp_buf |= 0xF000;
	}

	// Convert sensor reading to temperature (C)
	temp_c = temp_buf * 0.0625;

	// Print Results
	printf("%.2f deg C\n", temp_c);

	return 0;
}
