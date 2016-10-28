#include <stdio.h>
#include <stdlib.h>
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
