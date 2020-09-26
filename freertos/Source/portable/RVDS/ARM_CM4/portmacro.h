/*
 * @Description: 
 * @Version: 2.0
 * @Autor: yoyo
 * @Date: 2020-09-25 22:30:09
 * @LastEditors: yoyo
 * @LastEditTime: 2020-09-26 23:08:52
 */
#ifndef PORTMACRO_H
#define PORTMACRO_H

#include <stdint.h>
#include <stddef.h>


#define portCHAR            char
#define portFLOAT           float
#define portDOUBLE          double
#define portLONG            long
#define portSHORT           short
#define portSTACK_TYPE      uint32_t
#define portBASE_TYPE       long

typedef portSTACK_TYPE stackType_t;
typedef long BaseType_t;
typedef unsigned long UBaseType_t;

#if ( configUSE_16_BIT_TICKS == 1 )
typedef uint16_t TickType_t;
#define portMAX_DELAY       ( TickType_t ) 0xffff
#else
typedef uint32_t TickType_t;
#define portMAX_DELAY       ( TickType_t ) 0xffffffffUL
#endif

#endif /* PORTMACRO_H */
