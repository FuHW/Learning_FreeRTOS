/*
 * @Author: yoyo
 * @Date: 2020-09-25 16:55:15
 * @LastEditTime: 2020-09-26 23:06:06
 * @LastEditors: yoyo
 * @Description: 
 * @FilePath: \SimulateFreeRTOS\User\main.c
 */
#include "FreeRTOS.h"
#include "list.h"

List_t        List_Test;

ListItem_t   List_Item1;
ListItem_t   List_Item2;
ListItem_t   List_Item3;

/**
 * @description: 
 * @param {type} 
 * @return {type} 
 */
int main(void)
{
    vListInitialise( &List_Test );

    vListInitialiseItem( &List_Item1 );
    List_Item1.xItemValue = 1;

    vListInitialiseItem( &List_Item2 );
    List_Item2.xItemValue = 2;

    vListInitialiseItem( &List_Item3 );
    List_Item3.xItemValue = 3;

    vListInsert( &List_Test, &List_Item2 );
    vListInsert( &List_Test, &List_Item1 );
    vListInsert( &List_Test, &List_Item3 );

    for(;;)
    {
        /* do nonthing */
    }
}
