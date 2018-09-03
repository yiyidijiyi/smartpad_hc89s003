#ifndef TYPE_DEF_H
#define TYPE_DEF_H


typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned long uint32_t;
typedef signed long int32_t;

#ifdef MCU_HC89S_CORE
#define XDATA xdata
#define IDATA idata
#else
#define XDATA
#define IDATA
#endif

#define BIT0    ((uint8_t)0x01)
#define BIT1    ((uint8_t)0x02)
#define BIT2    ((uint8_t)0x04)
#define BIT3    ((uint8_t)0x08)
#define BIT4    ((uint8_t)0x10)
#define BIT5    ((uint8_t)0x20)
#define BIT6    ((uint8_t)0x40)
#define BIT7    ((uint8_t)0x80)

typedef enum{
    False = 0,
    True = !False
}Bool_t;

typedef enum{
    Reset = 0,
    Set = !Reset
}FlagStatus_t;

typedef enum{
    Disable = 0,
    Enable = !Disable
}FunctionState_t;

typedef enum{
    Error = 0,
    Sucess = !Error
}ErrorStatus_t;


#endif
