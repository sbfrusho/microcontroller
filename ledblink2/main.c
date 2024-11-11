#define RCC_APB2ENR *((volatile unsigned long *)0x40021018)// rcc_baseVal + rcc_apb2enr_offset = 0x40021000 + 0x18
#define GPIOC_CRH *((volatile unsigned long *)0x40011004)//gpioc_baseVal + gpioc_crh_offset = 0x4001100 + 0x04
#define GPIOC_ODR *((volatile unsigned long *)0x4001100C)//gpioc_baseVal + gpioc_odr_offset = 0x4001100 + 0x0c
#define SysTick_CTRL *((volatile unsigned long *)0xE000E010)
#define RCC_CFGR *((volatile unsigned long *)0x40021004)
#define SysTick_LOAD *((volatile unsigned long *)0xE000E014)
#define SysTick_VAL *((volatile unsigned long *)0xE000E018)
// Simple delay function
void delay2(int time) {
    for(int i = 0; i < time * 1000; i++) {}  
}

void sistyk_init(){
	SysTick_CTRL = 0; //clears the control register.
	
	SysTick_CTRL |= 5; //This enables the SysTick timer and sets the clock source to the processor clock (HCLK).
}

void systemClockInit(){
	
	RCC_CFGR &= ~(0x3);
	
	while(RCC_CFGR & (3<<2) != (0<<2));
	
}

void delaymills(){
	SysTick_LOAD = 8000 - 1;
	SysTick_VAL = 0;
	while((SysTick_CTRL & 0x10000) == 0);
}

void delay(int time){
	int i;
	for(i = 0 ; i < time ; i++){
		delaymills();
	}
}

int main() {
    // Enable GPIOC Clock (bit 4 in APB2ENR)
    RCC_APB2ENR |= 0x10;
    
    GPIOC_CRH &= 0X0FFFFF;
    GPIOC_CRH |= 0x300000;
	
		sistyk_init();
	
		systemClockInit();
	
		while(1){
			GPIOC_ODR ^= 0x2000;
			delay(1000);
		}

    /*while(1) {
        GPIOC_ODR ^= 0x2000;
				//delay(10);
        
        GPIOC_ODR &= 0;
        delay(100000);
    }*/
}