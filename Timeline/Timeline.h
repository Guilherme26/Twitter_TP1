#include <stdio.h>
#include <stdlib.h>

#define MESSAGE_SIZE 140


typedef struct{
	int message_id;
	int num_likes;
	int moment;
	int owner;
	char message[MESSAGE_SIZE];
}t_msg;

typedef struct nodo{
	struct nodo *previous;
	t_msg *msg;
	int saw;
	struct nodo *next;
}t_nodo;

typedef struct{
	t_nodo *first;
	t_nodo *last;
	int list_size;
}t_timeline;


void add_begin(t_timeline *list, t_msg *new_cell);

void add_end(t_timeline *list, t_msg *new_cell);

void delete_timeline(t_timeline *list);

int is_empty_timeline(t_timeline *list);

t_timeline *make_timeline();

void remove_msg(t_timeline *list, int item);

t_msg* get_item(t_timeline *list, int item);

void set_first(t_timeline *list, int message_id);

void show_timeline(t_timeline *list);
