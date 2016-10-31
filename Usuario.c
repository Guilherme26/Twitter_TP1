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

void curtir_mensagem(t_usuario *vetor_de_usuarios, int numero_de_usuarios, int id_usuario, int id_mensagem, int instante){

	int i;
	for(i=0; i < numero_de_usuarios; i++){
		if(vetor_de_usuarios[i].id == id_usuario){
			set_first(vetor_de_usuarios[i].timeline, id_mensagem);
			vetor_de_usuarios[i].timeline->first->msg->num_likes++;
			
			vetor_de_usuarios[i].timeline->first->msg->moment = instante;
		}
		else{
			t_nodo *post = vetor_de_usuarios[i].timeline->first;

			while(post != NULL){
				if(post->msg->message_id == id_mensagem){
					set_first(vetor_de_usuarios[i].timeline, id_mensagem);

					break;
				}
				else{
					post = post->next;
				}
			}
		}
	}

}

void exibir_timeline(FILE *out, t_usuario usuario){
	fprintf(out, "%d %s\n", usuario.id, usuario.nome);

	t_nodo *w_nodo = usuario.timeline->first;
	while(w_nodo != NULL){
		fprintf(out, "%d %d %s", w_nodo->msg->message_id, w_nodo->msg->num_likes, w_nodo->msg->message);
		w_nodo = w_nodo->next;
	}
}

void exe(FILE *in, FILE *out, t_usuario *vetor_de_usuarios, int numero_de_usuarios){
	char linha[BUFFER];

	while( fgets(linha, BUFFER, in) ){
		int instante = -1, acao_usuario = -1;
			
		instante = atoi(strtok(linha, ";"));
		acao_usuario = atoi(strtok(NULL, ";"));

		switch(acao_usuario){
			case 1:{
				int id_usuario = -1, id_mensagem = -1;
				char mensagem[MESSAGE_SIZE];

				id_usuario = atoi(strtok(NULL, ";"));
				id_mensagem = atoi(strtok(NULL, ";"));
				strcpy(mensagem, strtok(NULL, ";"));

				postar_mensagem(vetor_de_usuarios, numero_de_usuarios, id_usuario, id_mensagem, mensagem, instante);

				break;
			}
			case 2:{
				int id_usuario1 = -1, id_usuario2 = -1;

				id_usuario1 = atoi(strtok(NULL, ";"));
				id_usuario2 = atoi(strtok(NULL, ";"));

				iniciar_amizade(vetor_de_usuarios, numero_de_usuarios, id_usuario1, id_usuario2);

				break;
			}
			case 3:{
				int id_usuario1 = -1, id_usuario2 = -1;

				id_usuario1 = atoi(strtok(NULL, ";"));
				id_usuario2 = atoi(strtok(NULL, ";"));

				cancelar_amizade(vetor_de_usuarios, numero_de_usuarios, id_usuario1, id_usuario2);

				break;
			}
			case 4:{
				int id_usuario = -1, id_mensagem = -1;

				id_usuario = atoi(strtok(NULL, ";"));
				id_mensagem = atoi(strtok(NULL, ";"));

				curtir_mensagem(vetor_de_usuarios, numero_de_usuarios, id_usuario, id_mensagem, instante);

				break;
			}
			case 5:{
				int id_usuario = -1;
			
				id_usuario = atoi(strtok(NULL, ";"));

				int i;
				for(i = 0; i < numero_de_usuarios; i++){
					if(vetor_de_usuarios[i].id == id_usuario){
						exibir_timeline(out, vetor_de_usuarios[i]);
						break;
					}
				}


				break;
			}
		}
	}
}