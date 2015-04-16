/*
 * -------------------------------------------------------------------
 * jogo_desenha.c
 * -------------------------------------------------------------------
 * implementação de desenho do solitaire em tela textual
 */

#include "jogo.h"
#include "tela.h"
#include <assert.h>

void jogo_desenha_linhas(jogo sol, posicao pos, char *l[])
{
    char *s;
    int i;
    
    i = 0;
    s = l[i];
    while (s != NULL) {
        tela_posiciona(jogo_tela(sol), pos);
        tela_escreve(jogo_tela(sol), s);
        pos.y++;
        i++;
        s = l[i];
    }
}

void jogo_desenha_espaco(jogo sol, posicao pos)
{
    
    char *linhas[] = {
        ". . . .",
        ".     .",
        ".     .",
        ". . . .",
        NULL
    };
    tela_muda_cor(jogo_tela(sol), azul);
    jogo_desenha_linhas(sol, pos, linhas);
}

void jogo_desenha_carta(jogo sol, posicao pos, carta c)
{
    char *linhas_a[] = {
        "+-----+",
        "|10 P |",
        "|     |",
        "+-----+",
        NULL
    };
    char *linhas_f[] = {
        "+-----+",
        "|X+X+X|",
        "|+X+X+|",
        "+-----+",
        NULL
    };
    if (carta_aberta(c)) {
        char l[8];
        naipe n;
        n = carta_naipe(c);
        if (n == OUROS || n == COPAS) {
            tela_muda_cor(jogo_tela(sol), vermelho);
        } else {
            tela_muda_cor(jogo_tela(sol), preto);
        }
        sprintf(l, "|%2s %s |", carta_valor_str(c), carta_naipe_str(c));
        linhas_a[1] = l;
        jogo_desenha_linhas(sol, pos, linhas_a);
    } else {
        tela_muda_cor(jogo_tela(sol), azul);
        jogo_desenha_linhas(sol, pos, linhas_f);
    }
}

void jogo_desenha_topo(jogo sol, posicao pos, pilha p)
{
    if (pilha_vazia(p)) {
        jogo_desenha_espaco(sol, pos);
    } else {
        carta c;
        c = pilha_remove_carta(p);
        jogo_desenha_carta(sol, pos, c);
        pilha_insere_carta(p, c);
    }
}

void jogo_desenha_pilha(jogo sol, posicao pos, pilha p)
{
    if (pilha_vazia(p)) {
        jogo_desenha_espaco(sol, pos);
    } else {
        pilha aux;
        carta c;
        aux = pilha_cria();
        while (!pilha_vazia(p)) {
            c = pilha_remove_carta(p);
            pilha_insere_carta(aux, c);
        }
        while (!pilha_vazia(aux)) {
            c = pilha_remove_carta(aux);
            jogo_desenha_carta(sol, pos, c);
            pos.y += 2;
            pilha_insere_carta(p, c);
        }
        pilha_destroi(aux);
    }
}

void jogo_desenha(jogo sol)
{
   
    
    int i;
    posicao posmonte = { 6, 5 };
    posicao posdescartes = { 6, 15 };
    posicao posases[] = { { 6, 30 }, { 6, 40 }, { 6, 50 }, { 6, 60 } };
    posicao pospilha[] = { { 11,  5 }, { 11, 15 }, { 11, 25 }, { 11, 35 },
                           { 11, 45 }, { 11, 55 }, { 11, 65 } };

    assert(jogo_valido(sol));
    
    tela_limpa(jogo_tela(sol));
    
    printw("Monte to Descartes press: SPACE \tTo quit press: ESC ");
    printw("\nDescartes to Pilhas press: 'd' + '1' || '2' || '3' || '4' || '5' || '6' || '7'");
    printw("\nDescartes to Ases press: 'd' + 'q' || 'w' || 'e' || 'r'");
    printw("\nPilha to Pilha press: select any pilha (1 on 7) and select destiny pilha (1 on 7) || to Ases (q on r)");
    printw("\nAses to Pilha press: select any Ases (q on r) and select destiny pilha (1 on 7)");
    
    jogo_desenha_topo(sol, posmonte, jogo_monte(sol));
    jogo_desenha_topo(sol, posdescartes, jogo_descartes(sol));
    for (i = 0; i < 4; i++) {
        jogo_desenha_topo(sol, posases[i], jogo_ases(sol, i));
    }
    for (i = 0; i < 7; i++) {
        jogo_desenha_pilha(sol, pospilha[i], jogo_pilha(sol, i));
    }
    
    tela_atualiza(jogo_tela(sol));
}
