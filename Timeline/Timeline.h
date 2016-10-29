#include <stdio.h>
#include <stdlib.h>

#define MESSAGE_SIZE 140

typedef struct cell{
	int message_id;
	int num_likes;
	int message[MESSAGE_SIZE];
	int moment;
	struct cell *next;
	struct cell *previous;
}t_cell;

typedef struct{
	t_cell *first;
	t_cell *last;
	int list_size;
}t_list;

void add_begin(t_list *list, t_cell *new_cell);

void add_end(t_list *list, t_cell *new_cell);

void delete_list(t_list *list);

int is_empty(t_list *list);

t_list *make_list();

t_cell* remove_item(t_list *list, int item);

void set_first(t_list *list, int message_id);

void show_list(t_list *list);
