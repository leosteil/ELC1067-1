#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void le_alunos(int* matriculas, char nomes[][50], int *n){
	int mat;
	char c;
	char nome[50];
	int i,linha = 0;
	FILE*f = fopen("alunos.txt","r");
	if(f == NULL){
	        printf("Não foi possível abrir o arquivo ou o mesmo se encontra vazio\n");
	}else{ 
	while(feof(f) == 0 ){
		if(fscanf(f,"%d",&mat) < 0)//testar se o arquivo terminou 		
			break;//retorna o valor de EOF = -1 se o aquivo acabou
		i=0;
		c=fgetc(f);
		while(c != '\n'){//busca nome até acabar a linha no alunos.txt
			nome[i] = c;
			i++;
			c=fgetc(f);			
		}
		        nome[i]='\0';//delimita o final de cada linha
		        matriculas[linha]= mat;//armazena todas as matriculas no vetor
			strcpy(nomes[linha],nome);
			linha++;			
	}
	        *n = linha;//quantas linhas a busca deve percorrer
	        fclose(f);
        }
}

void le_notas(int* matriculas){
        float n1,n2,media;
        FILE *f = fopen("notas.txt","r");
	if(f == NULL){
	        printf("Não foi possível abrir o arquivo ou o mesmo se encontra vazio\n");
	}else{
	        while(feof(f)){}  
                
}

void busca(int* n, char nomes[][50], char* p, int* matriculas){
  int i=0;
  
        for(i=0;i<*n;i++){ 
             if(strstr(nomes[i],p) != NULL){
               printf("%d %s\n",matriculas[i],nomes[i]);  
        }  
    }     
} 


int main(int argc, char**argv){
	char nome[50];
	char* p = nome;
	if(argc > 1){
		p = argv[1];
}
	
	int matriculas[50];
	char nomes[50][50];
	int n;
	float notas[50][50];
	
	le_alunos(matriculas,nomes,&n);
	busca(&n,nomes,p,matriculas); 

	return 0;

}
