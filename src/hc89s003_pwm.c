/*
* 文件说明：hc89s003f4 12位pwm模块，包括pwm0，1,2及互补的3路输出
*/
#include "HC89S003F4.h"
#include "hc89s003_pwm.h"
#include "hc89s003_gpio.h"
#include "led.h"



/*
* 输入：d-pwm占空比
* 输出：
* 功能：设置pwm1模块的占空比
*/
void setPwm0Duty(uint16_t p)
{
    uint16_t tmp;
    
    if(p > 1000)
    {
        p = 1000;
    }
    
    tmp = (uint32_t)led.ccp * p / 1000;
    
    PWM0DH = (uint8_t)(tmp >> 8) & 0x0f;
    PWM0DL = (uint8_t)tmp;
}

/*
* 输入：d-pwm占空比
* 输出：
* 功能：设置pwm1模块的占空比
*/
void setPwm1Duty(uint16_t p)
{
    uint16_t tmp;
    
    if(p > 1000)
    {
        p = 1000;
    }
    
    tmp = (uint32_t)led.ccp * p / 1000;
    
    PWM1DH = (uint8_t)(tmp >> 8) & 0x0f;
    PWM1DL = (uint8_t)tmp;
}

/*
* 输入：d-pwm占空比
* 输出：
* 功能：设置pwm2模块的占空比
*/
void setPwm2Duty(uint16_t p)
{
    uint16_t tmp;
    
    if(p > 1000)
    {
        p = 1000;
    }
    tmp = (uint32_t)led.ccp * p / 1000;
    
    PWM2DH = (uint8_t)(tmp >> 8) & 0x0f;
    PWM2DL = (uint8_t)tmp;
}

/*
* 输入：
* 输出：
* 功能：pwm0模块配置
*/
void pwm0Config(void)
{
    DISABLE_PWM(PWM0EN);
    
    PWM0C = PWM_OUT_LL | PWM_CLK_FOSC_1;
    PWM0EN |= PWM_OUT_EN;
    
    // 时钟4M， 周期1k，周期值为4000 - 1
    PWM0PH = 0x0F;
    PWM0PL = 0x9f;
    
    setPwm0Duty(50);
    
    ENABLE_PWM(PWM0EN);
}

/*
* 输入：
* 输出：
* 功能：pwm1模块配置
*/
void pwm1Config(void)
{
    DISABLE_PWM(PWM1EN);
    
    PWM1C = PWM_OUT_LL | PWM_CLK_FOSC_1;
    PWM1EN |= PWM_OUT_EN;
    
    // 时钟4M， 周期1k，周期值为4000 - 1
    PWM1PH = 0x0F;
    PWM1PL = 0x9f;
    
    setPwm1Duty(50);
    
    ENABLE_PWM(PWM1EN);
}

/*
* 输入：
* 输出：
* 功能：pwm2模块配置
*/
void pwm2Config(void)
{
    DISABLE_PWM(PWM2EN);
    
    PWM2C = PWM_OUT_LL | PWM_CLK_FOSC_1;
    PWM2EN |= PWM_OUT_EN;
    
    // 时钟4M， 周期1k，周期值为4000 - 1
    PWM2PH = 0x0F;
    PWM2PL = 0x9f;
    
    setPwm2Duty(50);
    
    ENABLE_PWM(PWM2EN);
}

/*
* 输入：
* 输出：
* 功能：pwm3模块配置
*/
void pwm3Config(void)
{
    //DISABLE_PWM3();
    
    PWM3C = PWM3_OUT_EN | PWM3_OUT_H | PWM3_CLK_FOSC_16;
    
    // 时钟4M / 16 = 250K， 周期 1/2.8K， 周期值 = 250 / 2.8 = 89
    PWM3P = 89;
    // 50%占空比
    PWM3D = 44;
}



// end of file
