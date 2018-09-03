/*
* 文件说明：无源蜂鸣器操作
*/
#ifndef BEEP_H
#define BEEP_H

#include "typedef.h"



void beepStartBuzz(uint16_t n, uint16_t t1, uint16_t t2);
void beepStopBuzz(void);
void beepTask(void);


#endif

