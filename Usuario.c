#include "Usuario.h"

t_usuario *aloca_usuarios(int numero_de_usuarios){
	t_usuario *vetor_de_usuarios = (t_usuario*) calloc(numero_de_usuarios, sizeof(t_usuario));
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

	int tam_nome = strlen(nome);
	usuario->nome = (char*) calloc(tam_nome+1, sizeof(char));
	if(usuario->nome == NULL){
		fscanf(stderr, "Reading Error!\n");
		exit(-1);
	}
	strcpy(usuario->nome, nome);
	token = strtok(NULL, ";");
	while(token != NULL){
		add(usuario->seguidores, atoi(token));
		token = strtok(NULL, ";");
	}

	free(linha);
}

//------------------------------------------------------------------------------------------------------------------------------------
void iniciar_amizade(t_usuario *vetor_de_usuarios, int numero_de_usuarios, int id_usuario1, int id_usuario2){
	int i;
	for(i=0; i< numero_de_usuarios; i++){
		if(vetor_de_usuarios[i].id == id_usuario1){
			add(vetor_de_usuarios[i].seguidores, id_usuario2);
		}
		else if(vetor_de_usuarios[i].id == id_usuario2){
			add(vetor_de_usuarios[i].seguidores, id_usuario1);
		}
	}
}

void cancelar_amizade(t_usuario *vetor_de_usuarios, int numero_de_usuarios, int id_usuario1, int id_usuario2){
	int i;
	for(i=0; i< numero_de_usuarios; i++){
		if(vetor_de_usuarios[i].id == id_usuario1){
			remove_item(vetor_de_usuarios[i].seguidores->first, id_usuario2);
		}
		else if(vetor_de_usuarios[i].id == id_usuario2){
			remove_item(vetor_de_usuarios[i].seguidores->first, id_usuario1);
		}
	}
}

void ver_amigos(t_usuario usuario){
	show_list(usuario.seguidores);
}
