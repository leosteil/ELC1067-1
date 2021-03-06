#ifndef _JOGO_H_
#define _JOGO_H_
/*
 * jogo.h
 * TAD que implementa o jogo de cartas "solitaire".
 *
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014, 2015 João V. Lima, UFSM
 *               2005       Benhur Stein, UFSM
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "carta.h"
#include "pilha.h"
#include "tela.h"

typedef struct {
    int magico;
    pilha monte;        // monte de cartas de onde se pode comprar
    pilha descartes;    // cartas ja abertas do monte; a de cima pode ser usada
    pilha ases[4];      // as 4 pilhas de cartas da saída
    pilha pilhas[7];    // as 7 pilhas principais do jogo
    tela tela;          // a tela onde sao desenhadas as cartas
}jogo_t;
typedef jogo_t *jogo;

/* Funções de Criação do jogo */
jogo jogo_cria(void);

void jogo_destroi(jogo);

bool jogo_valido(jogo sol);

/* acessores */
tela jogo_tela(jogo sol);

pilha jogo_monte(jogo sol);

pilha jogo_descartes(jogo sol);

pilha jogo_ases(jogo sol, int i);

pilha jogo_pilha(jogo sol, int i);

/* desenha a mesa do jogo */
void jogo_desenha(jogo);

/* funções para mover de uma pilha para outra */
void desvira_carta(jogo solit, pilha p);

void monte_to_descartes(jogo sol);

void descartes_to_monte(jogo sol);

void descartes_to_pilha(jogo solit, int nPilha);

void descartes_to_pilhaAses(jogo solit, int nPilhaAS, carta ct);

void pilha_to_pilha(jogo solit, int nPilha1, int nPilha2);

void pilha_to_pilhaAses(jogo solit,int nPilha1,int nPilhaAS ,carta ct);

void pilhaAses_to_pilha(jogo solit,int nPilhaAS, int pilha, carta ct);

void select_pilhas(jogo solit,int nPilha1,char tecla);

void select_pilhas_descartes(jogo solit,char tecla);

#endif

