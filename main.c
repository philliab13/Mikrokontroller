// #include <stdint.h>

// #define GPIO ((NRF_GPIO_REGS*)0x50000000)

// typedef struct {
// 	volatile uint32_t RESERVED0[321];
// 	volatile uint32_t OUT;
// 	volatile uint32_t OUTSET;
// 	volatile uint32_t OUTCLR;
// 	volatile uint32_t IN;
// 	volatile uint32_t DIR;
// 	volatile uint32_t DIRSET;
// 	volatile uint32_t DIRCLR;
// 	volatile uint32_t RESERVED1[118];
// 	volatile uint32_t PIN_CNF[32];
// } NRF_GPIO_REGS;

// int main(){
// 	// Configure LED Matrix
// 	for(int i = 0; i <= 3; i++){
// 		GPIO->DIRSET = (1 << i);
// 		GPIO->OUTCLR = (1 << i);
// 	}

	
// 	// Configure buttons
// 	GPIO->PIN_CNF[13] = 0;
// 	GPIO->PIN_CNF[14] = 0;
	

// 	int sleep = 0;
// 	while(1){

// 		/* Check if button 1 is pressed;
// 		 * turn on LED matrix if it is. */
// 		GPIO->PIN_CNF[18]=1;
// 		GPIO->OUTCLR |= (1>>18);
		

// 		/* Check if button 2 is pressed;
// 		 * turn off LED matrix if it is. */

// 		sleep = 10000;
// 		while(--sleep); // Delay
// 	}
// 	return 0;
// }

#include <stdint.h>
#include <stdbool.h>



#define GPIO0 ((NRF_GPIO_REGS0*)0x50000000)


typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t RESERVED1[118];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS0;


void led_init(){
	  GPIO0->PIN_CNF[17]=1;
	  GPIO0->PIN_CNF[18] = 1;
	  GPIO0->PIN_CNF[19]=1;
	  GPIO0->PIN_CNF[20]=1;

};

void btn_init(){
	GPIO0->PIN_CNF[13]=(3<<2);
	GPIO0->PIN_CNF[14]=(3<<2);
	GPIO0->PIN_CNF[15]=(3<<2);
	GPIO0->PIN_CNF[16]=(3<<2);

}
int isBtnPressed(int placement) {
	return (!(GPIO0->IN & (1 << placement)));
}

void led_off(int placement){
	GPIO0->OUTSET |= (1<<placement);
};

void led_on(int placement){
	GPIO0->OUTCLR |= (1<<placement);
};


int main(){

	led_init();
	btn_init();
	int sleep = 0;
	for(int i=17; i<21;i++){
			led_off(i);
		}
	while(1){
		

		if (isBtnPressed(13))
		{
			led_on(17);
		}
	if (isBtnPressed(14))
		{
			led_off(18);
			led_off(17);
			led_off(19);
			led_off(20);
		}
		

		
		
		// led_on(18);
		sleep = 10000;
		while(--sleep);
		// led_off(18);
		// sleep = 1000000;
		// while(--sleep);
	}
	return 0;
}