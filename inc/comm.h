/*
* 文件说明：通信与数据存储
*/
#ifndef COMM_H
#define COMM_H
#include "typedef.h"

#define WRTIE_PARAMETERS   ((uint8_t)0x01)
#define READ_PARAMETERS    ((uint8_t)0x02)
#define WRITE_RGB          ((uint8_t)0x03)
#define READ_WARNING_NUM   ((uint8_t)0x04)

typedef struct{
	uint16_t k;
	uint16_t b;
}TemperatureParam_t;

void commTask(void);
void readTempeartureParam(TemperatureParam_t *param);


#endif
