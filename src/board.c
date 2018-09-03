/*
* 文件说明：
*/

#include "board.h"
#include "ht1621.h"
#include "led.h"

#define MAX_PTR	((uint8_t)12)
static uint8_t ptr = 0;
static AdcChannel_t ch = BatteryVoltage;
static XDATA uint16_t adcResultBuffer[MAX_PTR] = {0};
static XDATA uint8_t batteryVoltageLv = IconBatLv3;	// 4.0V
static XDATA int16_t temperature = 0;	// 0℃
static TemperatureParam_t param = {2643, 3878};

/*
* 输入：
* 输出：
* 功能：初始化看门狗模块
*/
void initWdt(void)
{
    // 复位周期为3秒 (255 + 1) * 512 / 44000 = 2.9789
    WDTConfig(WDT_DIV_512, 255);
}

/*
* 输入：
* 输出：
* 功能：根据项目电路板，初始化MCU引脚
*/
void initGpio(void)
{  
    // 按键K1-P2.7
    gpioConfig(GPIO_P2, GPIO_PIN_7, Input_PullUp_NonSchmitt);
	
	// 液晶背光P1.1
	gpioConfig(GPIO_P1, GPIO_PIN_1, Output_PP);
	P1_1 = 1;
}

/*
* 输入：
* 输出：
* 功能：ADC模块初始化
*/
void initAdc(void)
{
    // P0.2-温度检测AD，P0.1电池电压检测AD
	gpioConfig(GPIO_P0, GPIO_PIN_1 | GPIO_PIN_2, Analog);
    
	// 2.7V内部参考电压，500k转换时钟
	adcConfig();
	XCH_SEL((uint8_t)BatteryVoltage);
	delay_us(10);
	START_CONVERT();
	
}

/*
* 输入：
* 输出：
* 功能：定时器初始化
*/
void initTimer(void)
{
	timer3Config();
}

/*
* 输入：
* 输出：
* 功能：RGB LED控制初始化
*/
void initLEDControl(void)
{
    // PWM_LEDR-PWM0-P0.6，PWM_LEDG-PWM1-P0.7，PWM_LEDB-PWM2-P2.0
	gpioConfig(GPIO_P0, GPIO_PIN_6 , Output_PP);
    gpioConfig(GPIO_P0, GPIO_PIN_7 , Output_PP);
	GPIO_PIN_MAP(PWM0_MAP, GPIO_P0, 6);
    GPIO_PIN_MAP(PWM1_MAP, GPIO_P0, 7);
    gpioConfig(GPIO_P2, GPIO_PIN_0, Output_PP);
    GPIO_PIN_MAP(PWM2_MAP, GPIO_P2, 0);
    
    // 时钟4M， 周期1k，周期值为4000 - 1
    led.ccp = 3999; 
    
	pwm0Config();
	pwm1Config();
	pwm2Config();	
    
    setRGB(0, 0, 255, BRIGHTNESS);
    led.color = Blue;
}

/*
* 输入：
* 输出：
* 功能：pwm输出初始化
*/
void initBeepControl(void)
{
    // PWM_BEEP-PWM3-P0.0
    gpioConfig(GPIO_P0, GPIO_PIN_0, Output_PP);
    GPIO_PIN_MAP(PWM3_MAP, GPIO_P0, 0);
	P0_0 = 0;
    
    pwm3Config();
}

/*
* 输入：
* 输出：
* 功能：uart输出初始化
*/
void initUart(void)
{
    // uart_tx-P2.2 uart_rx-P2.1
	gpioConfig(GPIO_P2, GPIO_PIN_2, Output_PP);
	gpioConfig(GPIO_P2, GPIO_PIN_1, Input_PullUp_NonSchmitt);
	GPIO_PIN_MAP(TXD_MAP, GPIO_P2, 2);
	GPIO_PIN_MAP(RXD_MAP, GPIO_P2, 1);
    
	uart1Config();
}

/*
* 输入：
* 输出：
* 功能：lcd驱动初始化
*/
void initLcdDriver(void)
{
    // LCD_CS-P0.5, LCD_W-P0.4, LCD_IO-0.3
    gpioConfig(GPIO_P0, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, Output_PP);
    
    fm1906Config();
    //ht1621_init();
}

/*
* 输入：
* 输出：
* 功能：lcd驱动初始化
*/
void initTemperatureMeasure(void)
{
    readTempeartureParam(&param);
}

/*
* 输入：
* 输出：
* 功能：去掉最大值和最小值滤波
*/
static uint16_t filterMaxMin(void)
{
	uint16_t max = 0;
	uint16_t min = 0xfff;
	uint16_t sum = 0;
	int i = 0;
	
	for(i = 0; i < MAX_PTR; i++)
	{
		sum += adcResultBuffer[i];
		if(max < adcResultBuffer[i])
		{
			max = adcResultBuffer[i];
		}
		
		if(min > adcResultBuffer[i])
		{
			min = adcResultBuffer[i];
		}
	}
	
	sum -= (min + max);
	
	return sum;
}


/*
* 输入：
* 输出：
* 功能：计算的电池电压
*/
static void calcBatteryVoltage(void)
{
	uint16_t sum = filterMaxMin();
	
	// batteryVoltage = (sum / 4095) * 2 * 2;
	sum >>= 10;
	
	if(sum >= 42)
	{
		batteryVoltageLv = IconBatLv3;
	}
	else if(sum >= 39)
	{
		batteryVoltageLv = IconBatLv2;
	}
	else if(sum >= 34)
	{
		batteryVoltageLv = IconBatLv1;
	}
	else
	{
		batteryVoltageLv = IconBatLv0;
	}
}

/*
* 输入：
* 输出：
* 功能：返回电池电压等级
*/
uint8_t getBatteryVoltageLv(void)
{
	return batteryVoltageLv;
}

/*
* 输入：
* 输出：
* 功能：返回温度值
*/
int16_t getTemperature(void)
{
	return temperature;
}

/*
* 输入：
* 输出：
* 功能：计算的温度值
*/
static void calcTemperature(void)
{
	int32_t sum = filterMaxMin();
    
    // 12位AD，参考电压2V，实际电压值*10 = sum / 4095 * 2
    sum *= 100;
    sum >>= 11;
    
    sum = sum * param.k;
    sum = sum - (int32_t)100 * param.b;
    
    temperature = sum / 1000;
}

/*
* 输入：
* 输出：
* 功能：切换ADC转换通道通道
*/
void switchAdcChannel(void)
{	
	if(ptr >= MAX_PTR)
	{
		if(ch == BatteryVoltage)
		{
			calcBatteryVoltage();
			ch = Temperature;
			XCH_SEL((uint8_t)Temperature);			
		}
		else
		{
			calcTemperature();
			ch = BatteryVoltage;
			XCH_SEL((uint8_t)BatteryVoltage);			
		}
			
		ptr = 0;
		delay_us(10);
	}
	
	START_CONVERT();
}

/*
* 输入：
* 输出：
* 功能：ADC模块初始化
*/
void adcIsr() interrupt ADC_VECTOR
{	
	ADCC0 &= ~0x20;		//清除ADC中断标志位
	adcResultBuffer[ptr++] = ADCR;
}


/*
 参数：
 返回：
 功能：打开自锁开关
*/	
void powerOn(void)
{
    // P1.0设置为推挽输出
	gpioConfig(GPIO_P1, GPIO_PIN_0, Output_PP);
    P1_0 = 1;
}

/*
 参数：
 返回：
 功能：关闭自锁开关
*/	
void powerOff(void)
{
	P1_0 = 0;
	
	while(1)
	{}
}


/*
 参数：r-红色分量，g-绿色分量，b-蓝色分量，brightness-亮度百分比(0-100)
 返回：
 功能：设置RGB灯的颜色
*/	
void setRGB(uint8_t r, uint8_t g, uint8_t b, uint16_t brightness)
{
    // 设置新的颜色，中断中不再进行呼吸效果变化
    led.colorChanged = 0;
   
    
    if(brightness > 1000)
    {
        brightness = 1000;
    }
    
    led.red = (uint16_t)r * brightness / 255;
    led.green = (uint16_t)g * brightness / 255;
    led.blue = (uint16_t)b * brightness / 255;
    led.redStep = led.red / STEPS;
    led.greenStep = led.green / STEPS;
    led.blueStep = led.blue / STEPS;
    
    setPwm2Duty(led.red);     
    setPwm0Duty(led.green);     
    setPwm1Duty(led.blue);  
    
    led.currentRed = led.red;
    led.currentGreen = led.green;
    led.currentBlue = led.blue;
    
    // 中断中开始呼吸效果变化
    led.colorChanged = 2;
}




// end of file

