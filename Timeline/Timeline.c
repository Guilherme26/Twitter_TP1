#include "Timeline.h"

/*
	This method receives an item and add on the list
*/
void add_begin(t_timeline *list, t_msg *nova_msg){
	t_nodo *novo_nodo = (t_nodo*) calloc(1, sizeof(t_nodo));
	novo_nodo->msg = nova_msg;

	if(is_empty_timeline(list)){
		novo_nodo->previous = NULL;
		novo_nodo->next = NULL;
		list->first = novo_nodo;
		list->last = novo_nodo;
		list->list_size++;
		
		//Debugger
		printf("ADD_BEGIN = EMPTY\nEndereço: [%p]\t Id: [%d]\n", novo_nodo, novo_nodo->msg->message_id);

	}
	else{
		novo_nodo->previous = NULL;   
		novo_nodo->next = list->first;   
		list->first->previous = novo_nodo;   
		list->first = novo_nodo;
		list->list_size++;

		//Debugger
		printf("ADD_BEGIN = FILLED\nEndereço: [%p]\t Id: [%d]\n", novo_nodo, novo_nodo->msg->message_id);

	}
}

void add_end(t_timeline *list, t_msg *nova_msg){
	t_nodo *novo_nodo = (t_nodo*) calloc(1, sizeof(t_nodo));
	novo_nodo->msg = nova_msg;

	if(is_empty_timeline(list)){
		novo_nodo->next = NULL;   
		novo_nodo->previous = NULL;
		list->first = novo_nodo;
		list->last = novo_nodo;
		list->list_size++;
	}
	else{
		novo_nodo->previous = list->last;   
		novo_nodo->next = NULL;   
		list->last->next = novo_nodo;
		list->last = novo_nodo;
		list->list_size++;
	}
}

/*
	This method deletes all list and it's members. This method must be used on the end of program to avoid memory leak
*/
void delete_timeline(t_timeline *list){
	if(list == NULL){
		fprintf(stderr, "This List Doesn't Exist!\n");
		exit(-1);
	}

	if(list->first != NULL){
		t_nodo *aux = list->first->next;

		free(list->first);
		list->first = aux;

		delete_timeline(list);
	}
	else{
		free(list);
	}
}

/*
	This function checks if the list is empty, then returns 1 if yes and 0 if not
*/
int is_empty_timeline(t_timeline *list){
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
t_timeline *make_timeline(){
	t_timeline *list = (t_timeline*) calloc(1, sizeof(t_timeline));

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
void remove_msg(t_timeline *list, int item){
	if(list == NULL || is_empty_timeline(list)){
		fprintf(stderr, "This List Doesn't Exist!\n");
		exit(-1);
	}

	//Walking cell
	t_nodo *w_nodo = list->first;
	while(w_nodo != NULL){
		if(w_nodo->msg->message_id == item){
			if(w_nodo == list->first){
				list->first = w_nodo->next;
				list->first->previous = NULL;

				list->list_size--;
				free(w_nodo);
				return;
			}
			else if(w_nodo == list->last){
				list->last = w_nodo->previous;
				list->last->next = NULL;

				list->list_size--;
				free(w_nodo);
				return;			}
			else{
				w_nodo->previous->next = w_nodo->next;
				w_nodo->next->previous = w_nodo->previous;
				
				w_nodo->next = NULL;
				w_nodo->previous = NULL;

				list->list_size--;
				free(w_nodo);
				return;
			}
		}
		else{
			w_nodo = w_nodo->next;
		}
	}
}

t_msg* get_item(t_timeline *list, int item){
	if(list == NULL || is_empty_timeline(list)){
		fprintf(stderr, "This List Doesn't Exist!\n");
		exit(-1);
	}

	//Walking cell
	t_nodo *w_nodo = list->first;
	while(w_nodo != NULL){
		if(w_nodo->msg->message_id == item){
			if(w_nodo == list->first){
				list->first = w_nodo->next;
				w_nodo->next->previous = NULL;

				//Debugger
				printf("GET_ITEM = FIRST\nEndereço: [%p]\t Id: [%d]\n", w_nodo, w_nodo->msg->message_id);

				t_msg *tmp = w_nodo->msg;
				free(w_nodo);
				return tmp;
			}
			else if(w_nodo == list->last){
				list->last = w_nodo->previous;
				w_nodo->previous->next = NULL;

				//Debugger
				printf("GET_ITEM = LAST\nEndereço: [%p]\t Id: [%d]\n", w_nodo, w_nodo->msg->message_id);
				
				t_msg *tmp = w_nodo->msg;
				free(w_nodo);
				return tmp;
			}
			else{
				w_nodo->previous->next = w_nodo->next;
				w_nodo->next->previous = w_nodo->previous;
				
				w_nodo->next = NULL;
				w_nodo->previous = NULL;

				//Debbuger
				printf("GET_ITEM = MIDDLE\nEndereço: [%p]\t Id: [%d]\n", w_nodo, w_nodo->msg->message_id);

				t_msg *tmp = w_nodo->msg;
				free(w_nodo);
				return tmp;
			}
		}
		else{
			w_nodo = w_nodo->next;
		}
	}
}

void set_first(t_timeline *list, int message_id){
	if((list == NULL) || (list->first == NULL)){
		fprintf(stderr, "This List Doesn't Exist!\n");
		exit(-1);
	}


	t_msg *aux = get_item(list, message_id);
	//Debugger
	printf("SET_FIRST\nEndereço: [%p]\t Id: [%d]\n", aux, aux->message_id);

	if(aux != NULL)
		add_begin(list, aux);

}

void show_timeline(t_timeline *list){
	if(list == NULL){
		fprintf(stderr, "This List Doesn't Exist!\n");
		exit(-1);
	}

	t_nodo *aux = list->first;
	while(aux != NULL){
		printf("Item: [%d]->\t", aux->msg->message_id);
		aux = aux->next;
	}
	printf("\n");
}
