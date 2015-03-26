/*
 * vetor.c
 * TAD que implementa um vetor dinamico.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vetor.h"
#include "carta.h"
#include "memo.h"

struct vetor {
	carta* baralho;   /* baralho - vetor de cartas */
	int n;		/* número de cartas */
};

vetor_t* vetor_cria(void)
{
	struct vetor *vet = (struct vetor*)memo_aloca(sizeof(struct vetor));
	vet->n = 0;
	int i;
	vet->baralho = (carta*) memo_aloca(50*sizeof(carta));
	for(i=0; i< 50;i++){
	  vet->baralho[i] = NULL;
	}	
	return vet;
}

void vetor_destroi(vetor_t* vet)
{
	memo_libera(vet->baralho);
	memo_libera(vet);	
}

int vetor_numelem(vetor_t *vet)
{
	/* TODO aqui */
	return vet->n;
}

void vetor_insere_carta(vetor_t *vet, int indice, carta c)
{
	/* TODO aqui */
	vet->n++;
}

carta vetor_remove_carta(vetor_t *vet, int indice)
{
	/* TODO aqui */
	vet->n--;
	return NULL;
}

carta vetor_acessa_carta(vetor_t *vet, int indice)
{
	/* TODO aqui */
	return NULL;
}

bool vetor_valido(vetor_t *vet)
{
	/* TODO aqui */
	return false;
}
