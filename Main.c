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

		fscanf(in, "%d", &numero_de_usuarios);
		fseek(in, 2, SEEK_CUR);
		vetor_de_usuarios = aloca_usuarios(numero_de_usuarios);

		for(i = 0; i < numero_de_usuarios; i++){
			inicia_jogadores(in, &vetor_de_usuarios[i]);
		}

		// //Debugger
		// for(i = 0; i < numero_de_usuarios; i++){
		// 	printf("ID: [%d]\nNome: [%s]\n", vetor_de_usuarios[i].id, vetor_de_usuarios[i].nome);
		// }

//--------------------------------------------------------------------------------------------------------------------------------------------


		iniciar_amizade(vetor_de_usuarios, numero_de_usuarios, 300, 400);
		cancelar_amizade(vetor_de_usuarios, numero_de_usuarios, 300, 400);


//--------------------------------------------------------------------------------------------------------------------------------------------


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
		}
		free(vetor_de_usuarios);

	}while(fopen(in_file_name, "r"));

	return 0;
}