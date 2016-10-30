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
	usuario->timeline = make_timeline();
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

//-------------------------------------------------Funções obrigatórias---------------------------------------------------------------
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
			remove_seguidor(vetor_de_usuarios[i].seguidores->first, id_usuario2);
		}
		else if(vetor_de_usuarios[i].id == id_usuario2){
			remove_seguidor(vetor_de_usuarios[i].seguidores->first, id_usuario1);
		}
	}
}

void ver_amigos(t_usuario usuario){
	show_list(usuario.seguidores);
}

//---------------------------------------------------Funções sobre mensagens----------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------

void postar_mensagem(t_usuario *vetor_de_usuarios, int numero_de_usuarios, int id_usuario, int id_mensagem, char *mensagem, int instante){
	t_msg *nova_msg = (t_msg*) calloc(1, sizeof(t_msg));
	if(nova_msg == NULL){
		fprintf(stderr, "Allocation Error!\n");
		exit(-1);
	}	

	nova_msg->message_id = id_mensagem;
	strcpy(nova_msg->message, mensagem);
	nova_msg->moment = instante;
	nova_msg->num_likes = 0;

	int i;
	for (i=0; i < numero_de_usuarios; i++){
		if(id_usuario == vetor_de_usuarios[i].id){
			add_begin(vetor_de_usuarios[i].timeline, nova_msg);
		}
		else{
			//Walking Followers
			t_cell *w_seguidores = vetor_de_usuarios[i].seguidores->first;
			while(w_seguidores != NULL){
				if(w_seguidores->seguidor == id_usuario){
					add_begin(vetor_de_usuarios[i].timeline, nova_msg);
					break;
				}
				else{
					w_seguidores = w_seguidores->next;
				}
			}
		}
	}

}

void curtir_mensagem(t_usuario *vetor_de_usuarios, int numero_de_usuarios, int id_usuario, int id_mensagem){

	int i;
	for(i=0; i < numero_de_usuarios; i++){
		if(vetor_de_usuarios[i].id == id_usuario){
			show_timeline(vetor_de_usuarios[i].timeline);
			set_first(vetor_de_usuarios[i].timeline, id_mensagem);
			vetor_de_usuarios[i].timeline->first->msg->num_likes++;
			printf("Index: [%d]\n", i);
			
		}
		else{
			printf("Index: [%d]\n", i);
			t_cell *seguidores = vetor_de_usuarios[i].seguidores->first;

			while(seguidores != NULL){
				if(seguidores->seguidor == id_usuario){

					show_timeline(vetor_de_usuarios[i].timeline);
					set_first(vetor_de_usuarios[i].timeline, id_mensagem);
					vetor_de_usuarios[i].timeline->first->msg->num_likes++;
					break;
				}
				else{
					seguidores = seguidores->next;
				}
			}
		}
	}

}

// void exibir_timeline(){


// }
