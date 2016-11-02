#include "List.h"

//Este método faz com que um novo seguidor seja adicionado ao fim de uma lista encadeada
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

//Este método realiza a desalocação de toda memória dinamicamente alocada para a lista
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

//Esta função confere se uma lista encadeada está vazia e retorna 1(SIM) ou 0(NÃO);
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

/*Essa função aloca dinamicamente uma lista encadeada e retorna o endereço na memória que foi alocado, a primeira célula
é reservada para a célula cabeça deste contexto*/
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

//Dado um certo ID, o método remove um seguidor de determinada lista
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

//Mostra quais são os membros integrantes da lista encadeada
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
