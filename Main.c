#include "Usuario.h"

int main(){
	int file_index = 1;
	char in_file_name[30];
	char out_file_name[30];

	sprintf(in_file_name, "entrada0%d.txt", file_index);
	sprintf(out_file_name, "log.entrada0%d.txt", file_index);

	do{

		FILE *in = fopen(in_file_name, "r");
		FILE *out = fopen(out_file_name, "w");
		t_usuario *vetor_de_usuarios = NULL;
		int numero_de_usuarios = 0, i = 0;
		t_timeline *principal = make_timeline();

		fscanf(in, "%d", &numero_de_usuarios);
		fseek(in, 2, SEEK_CUR);
		vetor_de_usuarios = aloca_usuarios(numero_de_usuarios);

		for(i = 0; i < numero_de_usuarios; i++){
			inicia_usuarios(in, &vetor_de_usuarios[i]);
		}

		//Essa função analisa quais são as próximas ações à serem executadas
		exe(in, out, principal, vetor_de_usuarios, numero_de_usuarios);


		//Fecha o fluxo de entrada e saída de dados
		fclose(in);
		fclose(out);

		file_index++;
		sprintf(in_file_name, "entrada0%d.txt", file_index);
		sprintf(out_file_name, "log.entrada0%d.txt", file_index);

		//Libera as memórias alocadas dinamicamente
		for(i=0; i< numero_de_usuarios; i++){
			delete_list(vetor_de_usuarios[i].seguidores);
			free(vetor_de_usuarios[i].nome);
			delete_timeline(vetor_de_usuarios[i].timeline);
		}
		t_nodo *w_nodo = principal->first;
		while(w_nodo != NULL){
			free(w_nodo->msg);
			w_nodo = w_nodo->next;
		}
		delete_timeline(principal);
		free(vetor_de_usuarios);

		FILE *teste = fopen(in_file_name, "r");
		if(teste == NULL){
			return 0;
		}
		fclose(teste);

	}while(1);

	return 0;
}