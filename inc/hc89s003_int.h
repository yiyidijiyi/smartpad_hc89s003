/*
* 文件说明：hc89s003f4中断系统
*/
#ifndef HC89S003_INT_H
#define HC89S003_INT_H

#define ENABLE_INTERRUPT()  do{IE |= 0x80;}while(0)
#define DIASBLE_INTERRUPT() do{IE &= 0x7f}while(0)
#define ENABLE_UART2_INT()  do{IE |= 0x40;}while(0)
#define DISABLE_UART2_INT() do{IE &= ~0x40;}while(0)
#define ENABLE_WDT_INT()  do{IE |= 0x20;}while(0)
#define DISABLE_WDT_INT() do{IE &= ~0x20;}while(0)
#define ENABLE_UART1_INT()  do{IE |= 0x10;}while(0)
#define DISABLE_UART1_INT() do{IE &= ~0x10;}while(0)
#define ENABLE_T1_INT()  do{IE |= 0x08;}while(0)
#define DISABLE_T1_INT() do{IE &= ~0x08;}while(0)
#define ENABLE_EX1_INT()  do{IE |= 0x04;}while(0)
#define DISABLE_EX1_INT() do{IE &= ~0x04;}while(0)
#define ENABLE_T0_INT()  do{IE |= 0x02;}while(0)
#define DISABLE_T0_INT() do{IE &= ~0x02;}while(0)
#define ENABLE_EX0_INT()  do{IE |= 0x01;}while(0)
#define DISABLE_EX0_INT() do{IE &= ~0x01;}while(0)

#define ENABLE_EX8_15_INT()  do{IE1 |= 0x80;}while(0)
#define DIASBLE_EX8_15_INT() do{IE1 &= 0x7f}while(0)
#define ENABLE_EX2_7_INT()  do{IE1 |= 0x40;}while(0)
#define DISABLE_EX2_7_INT() do{IE1 &= ~0x40;}while(0)
#define ENABLE_ADC_INT()  do{IE1 |= 0x20;}while(0)
#define DISABLE_ADC_INT() do{IE1 &= ~0x20;}while(0)
#define ENABLE_T5_INT()  do{IE1 |= 0x10;}while(0)
#define DISABLE_T5_INT() do{IE1 &= ~0x10;}while(0)
#define ENABLE_T4_INT()  do{IE1 |= 0x04;}while(0)
#define DISABLE_T4_INT() do{IE1 &= ~0x04;}while(0)
#define ENABLE_T3_INT()  do{IE1 |= 0x02;}while(0)
#define DISABLE_T3_INT() do{IE1 &= ~0x02;}while(0)
#define ENABLE_SPI_INT()  do{IE1 |= 0x01;}while(0)
#define DISABLE_SPI_INT() do{IE1 &= ~0x01;}while(0)

// 0为最低优先级，3为最高优先级
typedef enum{
    IntPriority0 = 0,
    Intpriority1,
    IntPriority2,
    IntPriority3,
    IntPriorityMax
}IntPriority_t;


#endif
