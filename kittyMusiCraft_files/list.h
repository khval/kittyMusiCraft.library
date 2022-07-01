
// Copyright 2020, LiveForIt-Software / Kjetil Hvalstrand, software licence MIT


void list_allocate(struct list *list,int n);
// if [n] size is less then used items, then list_allocate can't reallocate size.


void list_push_back(struct list *list,struct item *item);
// push item to the end of the list.


struct item *list_find(struct list *list,int id);
// Find ID in a list, and returns a item address.


void list_erase(struct list *list,int id, void (*dispose) (void *ptr));
// erase a item in list, dispose is called on the item.


void list_free(struct list *list, void (*dispose) (void *ptr));
// free all items in a list, does not free list struct



