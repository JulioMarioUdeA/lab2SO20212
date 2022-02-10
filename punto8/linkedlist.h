#ifndef __LINKEDLIST_H_
#define __LINKEDLIST_H_

typedef struct __node_t node_t;
typedef struct __list_t list_t;

struct __node_t
{
	int data;
	node_t *next;
};

struct __list_t
{
	node_t *head;
};

void list_init(list_t *l);
int list_nondup_end_insert(list_t *list, int ele);
int get_index(list_t *list, int ele);
int get_size(list_t *l);
void display(list_t *l);
#endif
