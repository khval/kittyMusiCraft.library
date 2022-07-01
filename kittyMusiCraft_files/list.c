
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#ifdef __amigaos4__
#include <proto/exec.h>
#include <proto/retroMode.h>
#endif

#include "context.h"

void list_allocate(struct list *list,int new_allocated)
{
	if (new_allocated > list -> used)
	{
		struct item **items = (struct item **) malloc( sizeof(struct item *)  * new_allocated );
		if (items)
		{
			if (list -> items)
			{
				memcpy(items, list -> items, sizeof(struct item *) * list -> used );
				free(list -> items);
			}
			list -> items = items;
			list -> allocated = new_allocated;
		}
	}
}

void list_push_back(struct list *list,struct item *item)
{
	if ((list -> used +1) > list -> allocated)
	{
		int new_allocated = list -> allocated +10;
		list_allocate( list, new_allocated );
	}

	list -> items[ list -> used ] = item;
	list -> used ++;	
}

struct item *list_find(struct list *list,int id)
{
	int i;
	struct item **items = list -> items;
	if (items == NULL) return NULL;
	for (i=0;i<list -> used;i++)
	{
		if (items[i]->id == id) return items[i];
	}
	return NULL;
}

void list_free(struct list *list, void (*dispose) (void *ptr) )
{
	int i;
	struct item **items = list -> items;

	if (items)
	{
		for (i=0;i<list -> used;i++)
		{
			dispose( items[i] );
			items[ i] = NULL;
		}
		free( items );
		list -> items = NULL;
	}
}

void list_dump(struct list *list)
{
	struct item **items = list -> items;
	int i;

	for (i=0;i<list -> used;i++)
	{
		if (items[i])
		{
			printf("idx: %d, id: %d, %08x\n",i,items[i]->id, (int) items[i]);
		}
		else
		{
			printf("idx: %d, id: -1, NULL\n", -1);
		}
	}
}

void list_erase(struct list *list,int id, void (*dispose) (void *ptr))
{
	int i;
	struct item **items = list -> items;

	printf("before:\n");
	list_dump(list);


	for (i=0;i<list -> used;i++)
	{
		if (items[i]->id == id) 
		{
			dispose(items[i]);
			i++;
			for ( ; i < list -> used;i++)
			{
				items[i-1] = items[i];
			}				
			list -> used--;
			items[ list -> used ] = NULL;
			break;
		}
	}

	printf("after:\n");
	list_dump(list);
}

