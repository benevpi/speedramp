/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#define VREG_VSEL VREG_VOLTAGE_1_30
#include "hardware/vreg.h"

#define LOOPS 1000100

int time(int (*func)(), char name[]) {
	int start;
	int end;
	float millis;
	int y;
	
	
	start = time_us_32();
	y = func();
	end = time_us_32();
	
	millis = (end - start) / 1000;
	
	printf(name);
	printf(" completed in %0.3f milliseconds\n", millis);
	printf(" --- %d\n", y); // print so this isn't optimised away by the compiler
	
	return end-start;
	
}

int int_sum() {
	int y = 0;
	for(int z=0; z < LOOPS; z++) {
		y = y+z;
		if(y>1000000) { y=1;}
	}
	return y;// print so the loop isn't optimised away
}

int int_mult() {
	int y=1;
	for(int x=0; x < LOOPS; x++) {
		y = y*2+x;
		if(y>1000000) { y=1;}
	}
	return y;
}

int gpio_flicker() {
	for(int x=0; x < LOOPS; x++) {
		gpio_put(25, 1);
		gpio_put(25, 0);
	}
	
	return 1;
}

int float_sum() {
	float z=0;
	  for(long w=0;w<LOOPS;w++) {
		z = z+1;
	  }
	return (int)z;
}

int float_mult() {
	float z = 1.0;
	float a = 1.1;
	  for(long w=0;w<LOOPS;w++) {
		z = z*a;
		if (z > 1000) { z = a; }
	  }
	  return (int)z;
}

int float_divide() {
	  float z=1;
	  float a = 1.1;

	  for(long w=1;w<LOOPS;w++) {
		z = w/a + z;
		if (z > 1000) { z=a;}
	  }
	return (int)z;
}

int array_test() {
	int arraya[500];
	int arrayb[500];

	 for(int j =0; j<100;j++) {
		  for(int i=0; i<500;i++) {
			arraya[i]=i;
		  }
		  
		  for(int i=0; i<500;i++) {
			arrayb[i]=arraya[i] + arraya[500-i] + arraya[(i*123)%500] + arraya[(i+42)%500] + arraya[(i*23)%500];
		  }
	 }
	return arrayb[100] + arraya[100];
}



int main() {

	vreg_set_voltage(VREG_VSEL);
	sleep_ms(10);
	int start = 0;
	int end = 0;
	int loops = 1000100;
	int y = 0;
	float y_float = 0;
	
	uint32_t vco = 600000000;
	uint32_t crystal_freq = 12000000;
	
	float procspeed = 120;
	
	volatile float z;
	volatile float a = 1.1;
	
	int div1 = 5;
	int div2 = 1;
	
	int step = 6;
	

	
	//attempt_sys_clock(procspeed * 1000);
	sleep_ms(10);
	
	setup_default_uart();
	
	gpio_init(25);
    gpio_dir(25, GPIO_OUT);
	
	printf("Pico Speed test\n");
	printf("let's see how fast your pico can go ...");
	
    
    while (true) {
        printf("Hello, world!\n");
		
		
		time(int_sum, "Int Sum: ");
		time(int_mult, "Int Multiply: ");
		time(gpio_flicker, "GPIO Flicker: ");
		time(float_sum, "Float Sum: ");
		time(float_mult, "Float Multiply: ");
		time(float_divide, "Floar Divide: ");
		time(array_test, "Array jiggery pokery: ");

		 
		 vco = vco+(step*crystal_freq); //increase at multiples of the crystal oscillator?
		 
		 procspeed = (vco/(div1*div2))/1000000;
		 
		 printf("trying vco speed: %d\n", vco);
		 printf("********************\n");
		 printf("trying procspeed = %0.1f MHz\n", procspeed);
		 printf("********************\n");
		 
		 set_sys_clock(vco,div1,div2);
		 sleep_ms(100);
		 setup_default_uart();
		 sleep_ms(100);
		
    }	
    return 0;
}
