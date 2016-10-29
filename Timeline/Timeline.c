#include "Timeline.h"

/*
	This method receives an item and add on the list
*/
void add_begin(t_list *list, t_cell *new_cell){
	if(!is_empty(list)){
		new_cell->previous = NULL;   
		new_cell->next = list->first;   
		list->first->previous = new_cell;   
		list->first = new_cell;
		list->list_size++;
	}
	else{
		new_cell->previous = NULL;   
		new_cell->next = NULL; 
		list->first = new_cell;
		list->last = new_cell;
		list->list_size++;
	}
}

void add_end(t_list *list, t_cell *new_cell){
	if(!is_empty(list)){
		new_cell->previous = list->last;   
		new_cell->next = NULL;   
		list->last->next = new_cell;
		list->last = new_cell;
		list->list_size++;
	}
	else{
		new_cell->next = NULL;   
		new_cell->previous = NULL;
		list->first = new_cell;
		list->last = new_cell;
		list->list_size++;
	}
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

	if(list->list_size == 0)
		return 1;
	else
		return 0;
}

/*
	This function create a dynamic empty list and returns the address of it
*/
t_list *make_list(){
	t_list *list = (t_list*) calloc(1, sizeof(t_list));

	if(list == NULL){
		fprintf(stderr, "Alocation Error!\n");
		exit(-1);	
	}

	list->first = NULL;
	list->last = NULL;
	list->list_size = 0;

	return list;
}

/*
	This method removes the given item of the list
*/
t_cell* remove_item(t_list *list, int item){
	if(list == NULL || is_empty(list)){
		fprintf(stderr, "This List Doesn't Exist!\n");
		exit(-1);
	}

	//Walking cell
	t_cell *w_cell = list->first;
	while(w_cell != NULL){
		if(w_cell->message_id == item){
			if(w_cell == list->first){
				list->first = w_cell->next;
				list->first->previous = NULL;

				list->list_size--;
				return w_cell;
			}
			else if(w_cell == list->last){
				list->last = w_cell->previous;
				list->last->next = NULL;

				list->list_size--;
				return w_cell;
			}
			else{
				w_cell->previous->next = w_cell->next;
				w_cell->next->previous = w_cell->previous;
				
				w_cell->next = NULL;
				w_cell->previous = NULL;

				list->list_size--;
				return w_cell;
			}
		}
		else{
			w_cell = w_cell->next;
		}
	}
}

void set_first(t_list *list, int message_id){
	if((list == NULL) || (list->first == NULL)){
		fprintf(stderr, "This List Doesn't Exist!\n");
		exit(-1);
	}

	t_cell *aux = remove_item(list, message_id);
	add_begin(list, aux);

}

void show_list(t_list *list){
	if(list == NULL){
		fprintf(stderr, "This List Doesn't Exist!\n");
		exit(-1);
	}

	t_cell *aux = list->first;
	while(aux != NULL){
		printf("Item: [%d]->\t", aux->message_id);
		aux = aux->next;
	}
	printf("\n");
}
