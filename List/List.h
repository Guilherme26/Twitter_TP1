#include <stdio.h>
#include <stdlib.h>

typedef struct cell{
	int item;
	struct cell *next;
}t_cell;

typedef struct{
	t_cell *first;
	t_cell *last;
}t_list;

void add(t_list *list, int item);

void delete_list(t_list *list);

int is_empty(t_list *list);

t_list *make_list();

void remove_item(t_cell *cell, int item);

void show_list(t_list *list);
