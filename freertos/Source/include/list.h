/*
 * @Description: 
 * @Version: 2.0
 * @Autor: yoyo
 * @Date: 2020-09-25 22:29:11
 * @LastEditors: yoyo
 * @LastEditTime: 2020-09-26 23:13:55
 */
#ifndef LIST_H
#define LIST_H

struct xLIST_ITEM
{
    TickType_t xItemValue;          /*< The value being listed.  In most cases this is used to sort the list in descending order. */
    struct xLIST_ITEM * pxNext;     /*< Pointer to the next ListItem_t in the list. */
    struct xLIST_ITEM * pxPrevious; /*< Pointer to the previous ListItem_t in the list. */
    void * pvOwner;                 /*< Pointer to the object (normally a TCB) that contains the list item.  There is therefore a two way link between the object containing the list item and the list item itself. */
    void * pvContainer;             /*< Pointer to the list in which this list item is placed (if any). */
};

typedef struct xLIST_ITEM ListItem_t;

struct xMINI_LIST_ITEM
{
    TickType_t xItemValue;
    struct xLIST_ITEM * pxNext;
    struct xLIST_ITEM * pxPrevious;
};

typedef struct xMINI_LIST_ITEM MiniListItem_t;

typedef struct xLIST
{
    UBaseType_t uxNumberOfItems;
    ListItem_t * pxIndex;           /*< Used to walk through the list.  Points to the last item returned by a call to listGET_OWNER_OF_NEXT_ENTRY (). */
    MiniListItem_t xListEnd;         /*< List item that contains the maximum possible item value meaning it is always at the end of the list and is therefore used as a marker. */
} List_t;

/*
 * Access macro to set the owner of a list item.  The owner of a list item
 * is the object (usually a TCB) that contains the list item.
 */
#define listSET_LIST_ITEM_OWNER( pxListItem, pxOwner )\
        ( ( pxListItem )->pvOwner = ( void * ) ( pxOwner ) )

#define listGET_LIST_ITEM_OWNER( pxListItem )\
        ( ( pxListItem )->pvOwener )

#define listSET_LIST_ITEM_VALUE( pxListItem, xValue )\
        ( ( pxListItem )->xItemValue = ( xValue ))

#define listGET_LIST_ITEM_VALUE( pxListItem )\
        ( ( pxListItem )->xItemValue )

#define listGET_ITEM_VALUE_OF_HEAD_ENTRY( pxList )\
        ( ( ( pxList )->xListEnd ).pxNext->xItemValue )

#define listGET_HEAD_ENTRY( pxList )\
        ( ( ( pxList )->xListEnd ).pxNext )

#define listGET_NEXT( pxListItem )\
        ( ( pxListItem )->pxNext )

#define listGET_END_MARKER( pxList )\
        ( ( ListItem_t const * ) ( &( ( pxList )->xListEnd ) ) )

#define listLIST_IS_EMPTY(pxList)\
        ( ( BaseType_t ) ( ( pxList )->uxNumberOfItems == ( UBaseType_t )0 ) )

#define listCURRENT_LIST_LENGTH( pxList )\
        ( ( pxList )->uxNumberOfItems )

#define listGET_OWNER_OF_NEXT_ENTRY( pxTCB, pxList )                                            \
{                                                                                               \
    List_t * const pxConstList = ( pxList );                                                    \
    /* Increment the index to the next item and return the item, ensuring */                    \
    /* we don't return the marker used at the end of the list.  */                              \
    ( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;                                \
    if( ( void * ) ( pxConstList )->pxIndex == ( void * ) &( ( pxConstList )->xListEnd ) )      \
    {                                                                                           \
        ( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;                            \
    }                                                                                           \
    ( pxTCB ) = ( pxConstList )->pxIndex->pvOwner;                                              \
}


void vListInitialise( List_t * const pxList );
void vListInitialiseItem( ListItem_t * const  pxItem );
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem );
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem );
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove );

#endif /* LIST_H */
