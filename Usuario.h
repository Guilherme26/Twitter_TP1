#include <string.h>
#include "List/List.h"

#define BUFFER 255

typedef struct {
	int id;
	char *nome;
	t_list *seguidores;
} t_usuario;

t_usuario *aloca_usuarios(int numero_de_jogadores);

void inicia_jogadores(FILE *in, t_usuario *usuario);

void iniciar_amizade(t_usuario *vetor_de_usuarios, int numero_de_usuarios, int id_usuario1, int id_usuario2);

void ver_amigos(t_usuario usuario);
