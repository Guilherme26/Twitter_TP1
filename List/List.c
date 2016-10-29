#include "List.h"

/*
	This method receives an seguidor and add on the list
*/
void add(t_list *list, int seguidor){
	if(list == NULL){
		fprintf(stderr, "This List Doesn't Exist!\n");
		exit(-1);
	}

	t_cell *cell = (t_cell*) calloc(1, sizeof(t_cell));
	if(cell == NULL){
		fprintf(stderr, "Alocation Error!\n");
		exit(-1);
	}

	cell->seguidor = seguidor;
	cell->next = NULL;

	list->last->next = cell;
	list->last = cell;
}

/*
	This method deletes all list and it's members. This method must be used on the end of program to avoid memory leak
*/
void delete_list(t_list *list){
	if(list == NULL){
		fprintf(stderr, "This List Doesn't Exist!\n");
		exit(-1);
	}

	if(list->first != NULL){
		t_cell *aux = list->first->next;
		free(list->first);
		list->first = aux;

		delete_list(list);
	}
	else{
		free(list);
	}
}

/*
	This function checks if the list is empty, then returns 1 if yes and 0 if not
*/
int is_empty(t_list *list){
	if(list == NULL){
		fprintf(stderr, "This List Doesn't Exist!\n");
		exit(-1);
	}

	if(list->first == list->last)
		return 1;
	else
		return 0;
}

/*
	This function create a dynamic empty list and returns the address of it
*/
t_list *make_list(){
	t_list *list = (t_list*) calloc(1, sizeof(t_list));
	t_cell *cell = (t_cell*) calloc(1, sizeof(t_cell));
	
	if(cell == NULL){
		fprintf(stderr, "Alocation Error!\n");
		exit(-1);
	}
	if(list == NULL){
		fprintf(stderr, "Alocation Error!\n");
		exit(-1);	
	}

	cell->next = NULL;

	list->first = cell;
	list->last = cell;

	return list;
}

/*
	This method removes the given seguidor of the list
*/
void remove_seguidor(t_cell *cell, int seguidor){
	if(cell == NULL){
		fprintf(stderr, "This List Doesn't Exist!\n");
		exit(-1);
	}

	if(cell->next->seguidor == seguidor){
		t_cell *aux = cell->next;
		cell->next = cell->next->next;
		
		free(aux);
	}
	else{
		remove_seguidor(cell->next, seguidor);
	}
}

void show_list(t_list *list){
	if(list == NULL){
		fprintf(stderr, "This List Doesn't Exist!\n");
		exit(-1);
	}

	t_cell *aux = list->first->next;
	while(aux != NULL){
		printf("seguidor: [%d]\t->\t", aux->seguidor);
		aux = aux->next;
	}
	printf("\n");
}
