#include <string.h>
#include "List/List.h"
#include "Timeline/Timeline.h"

#define BUFFER 255

typedef struct {
	int id;
	char *nome;
	t_list *seguidores;
	t_timeline *timeline;
} t_usuario;

t_usuario *aloca_usuarios(int numero_de_jogadores);

void cancelar_amizade(t_usuario *vetor_de_usuarios, int numero_de_usuarios, int id_usuario1, int id_usuario2);

void inicia_usuarios(FILE *in, t_usuario *usuario);

void iniciar_amizade(t_usuario *vetor_de_usuarios, int numero_de_usuarios, int id_usuario1, int id_usuario2);

void ver_amigos(t_usuario usuario);

//------------------------------------------------------------------------------------------------------------------------------------
void postar_mensagem(t_timeline *principal, t_usuario *vetor_de_usuarios, int numero_de_usuarios, int id_usuario, int id_mensagem, char *mensagem, int instante);

void curtir_mensagem(t_timeline *principal, t_usuario *vetor_de_usuarios, int numero_de_usuarios, int id_usuario, int id_mensagem, int instante);

void exibir_timeline(FILE *out, t_usuario usuario);

void exe(FILE *in, FILE *out, t_timeline *principal, t_usuario *vetor_de_usuarios, int numero_de_usuarios);
