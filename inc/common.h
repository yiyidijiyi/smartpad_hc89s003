/*
 最后修改：2018-05-05 by syf
 功能描述：
*/
#ifndef COMMON_H
#define COMMON_H


#define TICKS_PER_SECOND	(20)
#define ELAPSED_TIME_100_MS ((uint16_t)(2))
#define ELAPSED_TIME_200_MS	((uint16_t)(4))
#define ELAPSED_TIME_300_MS	((uint16_t)(6))
#define ELAPSED_TIME_500_MS	((uint16_t)(10))
#define ELAPSED_TIME_700_MS	((uint16_t)(14))
#define ELAPSED_TIME_1_SECOND	((uint16_t)(20))
#define ELAPSED_TIME_2_SECOND	((uint16_t)(40))
#define ELAPSED_TIME_3_SECOND	((uint16_t)(60))
#define ELAPSED_TIME_5_SECOND	((uint16_t)(100))
#define ELAPSED_TIME_1_MINUTE	((uint16_t)(1200))

// 电池电压等级分类，参考电压为3.6V，adc为10位精度
#define BATTERY_VOLTAGE_LV3	(853)	// 3.0V以上为满格，3.0 * 1024 / 3.6 = 853.3
#define BATTERY_VOLTAGE_LV2	(796)	// 2.8V以上为2格， 2.8 * 1024 / 3.6 = 796.4
#define BATTERY_VOLTAGE_LV1	(739)	// 2.6V以上为1格， 2.6 * 1024 / 3.6 = 739.5
#define BATTERY_VOLTAGE_LV0	(682)	// 2.4V以上为0格， 2.4 * 1024 / 3.6 = 682.2

// 报警温度 实际值×10，保留一位小数
#define WARNING_TEMPERATURE	((int16_t)3000)
#define MIN_TEMPERATURE     ((int16_t)500)
#define GREEN_TEMPERATURE   ((int16_t)1800)
#define YELLOW_TEMPERATURE  ((int16_t)2600)
#define RED_TEMPERATURE     ((int16_t)3000)

// AD通道
#define AD_channel_Vbat 0
#define AD_channel_Cold 2
#define AD_channel_Thermo  3



#endif	// COMMON_H
