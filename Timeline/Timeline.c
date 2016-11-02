#include "Timeline.h"

//Este método recebe um ponteiro para célula e a insere ao início uma determinada lista duplamente encadeada(TIMELINE)
void add_begin(t_timeline *list, t_msg *nova_msg){
	t_nodo *novo_nodo = (t_nodo*) calloc(1, sizeof(t_nodo));
	novo_nodo->msg = nova_msg;

	if(is_empty_timeline(list)){
		novo_nodo->previous = NULL;
		novo_nodo->next = NULL;
		list->first = novo_nodo;
		list->last = novo_nodo;
		list->list_size++;
	}
	else{
		novo_nodo->previous = NULL;
		novo_nodo->next = list->first;
		list->first->previous = novo_nodo;
		list->first = novo_nodo;
		list->list_size++;
	}
	list->first->saw = 0;
}

//Este método recebe um ponteiro para célula e a insere ao fim uma determinada lista duplamente encadeada(TIMELINE)
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

//Este método desaloca toda memória alocada dinamicamente para uma dada lista
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

//Função verifica se determinada lista esta vazia ou não, retornando 1(SIM) ou 0(NÃO)
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

//Esta função aloca dinamicamente um espaço de memória para uma lista duplamente encadeada que é usada para representação de uma timeline
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

//Este método recebe um determinado ID e remove a mensagem correpondente àquele identificador
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


//Esta função recebe um ID de uma mensagem qualquer e retorna, caso exista, o endereço na memória que corresponde à célula de mensagem
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

				t_msg *tmp = w_nodo->msg;
				free(w_nodo);
				return tmp;
			}
			else if(w_nodo == list->last){
				list->last = w_nodo->previous;
				w_nodo->previous->next = NULL;

				t_msg *tmp = w_nodo->msg;
				free(w_nodo);
				return tmp;
			}
			else{
				w_nodo->previous->next = w_nodo->next;
				w_nodo->next->previous = w_nodo->previous;

				w_nodo->next = NULL;
				w_nodo->previous = NULL;

				t_msg *tmp = w_nodo->msg;
				free(w_nodo);
				return tmp;
			}
		}
		else{
			w_nodo = w_nodo->next;
		}
	}

	return NULL;
}

//Este método recebe um ID qualquer de uma mensagem, e caso exista na timeline, a coloca na primeira posição da lista
void set_first(t_timeline *list, int message_id){
	if((list == NULL) || (list->first == NULL)){
		fprintf(stderr, "This List Doesn't Exist!\n");
		exit(-1);
	}

	t_msg *aux = get_item(list, message_id);

	if(aux != NULL){
		add_begin(list, aux);
	}

}

//Exibe todos os membros de uma lista duplamente encadeada qualquer
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
