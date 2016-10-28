#include "Usuario.h"

t_usuario *aloca_usuarios(int numero_de_jogadores){
	t_usuario *vetor_de_usuarios = (t_usuario*) calloc(numero_de_jogadores, sizeof(t_usuario));
	if(vetor_de_usuarios == NULL){
		fprintf(stderr, "Allocation Error!\n");
		exit(-1);
	}
	return vetor_de_usuarios;
}

void inicia_jogadores(FILE *in, t_usuario *usuario){
	char *token = NULL;
	char *linha = (char*) calloc(BUFFER, sizeof(char));
	char *nome = NULL;
	
	usuario->seguidores = make_list();
	fgets(linha, BUFFER, in);
	if(linha == NULL){
		fscanf(stderr, "Reading Error!\n");
		exit(-1);
	}


	usuario->id = atoi(strtok(linha, ";"));
	nome = strtok(NULL, ";");

	usuario->nome = (char*) calloc(1, sizeof(char));
	if(usuario->nome == NULL){
		fscanf(stderr, "Reading Error!\n");
		exit(-1);
	}

	token = strtok(NULL, ";");
	while(token != NULL){
		add(usuario->seguidores, atoi(token));
		token = strtok(NULL, ";");
	}

	free(linha);
}