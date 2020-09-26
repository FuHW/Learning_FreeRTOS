/*
 * @Description: 
 * @Version: 2.0
 * @Autor: yoyo
 * @Date: 2020-09-25 22:29:24
 * @LastEditors: yoyo
 * @LastEditTime: 2020-09-26 23:08:45
 */
#include <stdlib.h>

#include "FreeRTOS.h"
#include "list.h"

void vListInitialise( List_t * const pxList )
{
    /* The list structure contains a list item which is used to mark the
     * end of the list.  To initialise the list the list end is inserted
     * as the only list entry. */
    pxList->pxIndex = ( ListItem_t * ) &( pxList->xListEnd );

    /* The list end value is the highest possible value in the list to
     * ensure it remains at the end of the list. */
    pxList->xListEnd.xItemValue = portMAX_DELAY;

    /* The list end next and previous pointers point to itself so we know
     * when the list is empty. */
    pxList->xListEnd.pxNext = ( ListItem_t * ) &( pxList->xListEnd );
    pxList->xListEnd.pxPrevious = ( ListItem_t * ) &( pxList->xListEnd );

    pxList->uxNumberOfItems = ( UBaseType_t ) 0U;
}

void vListInitialiseItem( ListItem_t * const  pxItem )
{
    /* Make sure the list item is not recorded as being on a list. */
    pxItem->pvContainer = NULL;
}

void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem )
{
    ListItem_t * const pxIndex = pxList->pxIndex;

    /* Insert a new list item into pxList, but rather than sort the list,
     * makes the new list item the last item to be removed by a call to
     * listGET_OWNER_OF_NEXT_ENTRY(). */
    pxNewListItem->pxNext = pxIndex;
    pxNewListItem->pxPrevious = pxIndex->pxPrevious;
    pxIndex->pxPrevious->pxNext = pxNewListItem;
    pxIndex->pxPrevious = pxNewListItem;

    /* Remember which list the item is in. */
    pxNewListItem->pvContainer = ( void * ) pxList;

    ( pxList->uxNumberOfItems )++;
}

void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem )
{
    ListItem_t *pxIterator;

    const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;

    if ( xValueOfInsertion == portMAX_DELAY )
    {
        pxIterator = pxList->xListEnd.pxPrevious;
    }
    else
    {
        for ( pxIterator = ( ListItem_t * ) &( pxList->xListEnd );
                pxIterator->pxNext->xItemValue <= xValueOfInsertion;
                pxIterator = pxIterator->pxNext )
        {
            /* There is nothing to do here, just iterating to the wanted
             * insertion position. */
        }
    }

    pxNewListItem->pxNext = pxIterator->pxNext;
    pxNewListItem->pxNext->pxPrevious = pxNewListItem;
    pxNewListItem->pxPrevious = pxIterator;
    pxIterator->pxNext = pxNewListItem;

    /* Remember which list the item is in.  This allows fast removal of the
     * item later. */
    pxNewListItem->pvContainer = ( void * ) pxList;
    
    ( pxList->uxNumberOfItems )++;
}

UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove )
{
    /* The list item knows which list it is in.  Obtain the list from the list
    * item. */
   List_t * const pxList = ( List_t * ) pxItemToRemove->pvContainer;

   pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
   pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;

   /* Make sure the index is left pointing to a valid item. */
   if ( pxList->pxIndex == pxItemToRemove )
   {
       pxList->pxIndex = pxItemToRemove->pxPrevious;
   }

   pxItemToRemove->pvContainer = NULL;

   ( pxList->uxNumberOfItems )--;

   return pxList->uxNumberOfItems;
}
