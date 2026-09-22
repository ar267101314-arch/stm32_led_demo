#include "stm32f10x.h"

/* ????? */
#define LED_RED_PIN     0       /* PA0 ?? */
#define LED_BLUE_PIN    1       /* PB1 ?? */
#define LED_BOARD_PIN   13      /* PC13 ??? */
#define LED_GREEN_PIN   14      /* PC14 ?? */

/* LED?? */
#define LED_RED         0
#define LED_BLUE        1
#define LED_BOARD       2
#define LED_GREEN       3


void Delay_ms(uint32_t ms)
{
    SysTick->LOAD = 72000 - 1;
    SysTick->VAL  = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_ENABLE_Msk;
    while (ms--)
    {
        while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
            ;
    }
    SysTick->CTRL = 0;
}


void LED_Init(void)
{
    /* ??GPIOA GPIOB GPIOC?? */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN |
                    RCC_APB2ENR_IOPBEN |
                    RCC_APB2ENR_IOPCEN;

    /* PA0 ????50M */
    GPIOA->CRL &= ~0x0F;
    GPIOA->CRL |=  0x03;

    /* PB1 ????50M,??4? */
    GPIOB->CRL &= ~(0x0F << 4);
    GPIOB->CRL |=  (0x03 << 4);

    /* PC13 ????50M (?? 20) */
    GPIOC->CRH &= ~(0x0F << 20);
    GPIOC->CRH |=  (0x03 << 20);

    /* PC14 ????50M (?? 24) */
    GPIOC->CRH &= ~(0x0F << 24);
    GPIOC->CRH |=  (0x03 << 24);

    /* ??????????(??) */
    GPIOA->ODR |= (1U << LED_RED_PIN);
    GPIOB->ODR |= (1U << LED_BLUE_PIN);
    GPIOC->ODR |= (1U << LED_BOARD_PIN);
    GPIOC->ODR |= (1U << LED_GREEN_PIN);
}


void LED_On(uint8_t led)
{
    //?????(BSRR?1?????)
    GPIOA->BSRR  = (1U << LED_RED_PIN);
    GPIOB->BSRR  = (1U << LED_BLUE_PIN);
    GPIOC->BSRR  = (1U << LED_BOARD_PIN);
    GPIOC->BSRR  = (1U << LED_GREEN_PIN);

    switch (led)
    {
        case LED_RED:
            GPIOA->BRR = (1U << LED_RED_PIN);
            break;
        case LED_BLUE:
            GPIOB->BRR = (1U << LED_BLUE_PIN);
            break;
        case LED_BOARD:
            GPIOC->BRR = (1U << LED_BOARD_PIN);
            break;
        case LED_GREEN:
            GPIOC->BRR = (1U << LED_GREEN_PIN);
            break;
        default:
            break;
    }
}


int main(void)
{
    LED_Init();
    while(1)
    {
        LED_On(LED_RED);     //PA0
        Delay_ms(1000);

        LED_On(LED_BLUE);    //PB1
        Delay_ms(1000);

        LED_On(LED_BOARD);   //PC13
        Delay_ms(1000);

        LED_On(LED_GREEN);   //PC14
        Delay_ms(1000);
    }
}
