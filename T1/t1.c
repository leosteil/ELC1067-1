#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void le_alunos(int* matriculas, char** nomes, int *n){
	int mat;
	char c;
	char nome[50];
	int i,linha = 0;
	FILE*f = fopen("alunos.txt","R");
	while(feof(f) != 0 ){
		if(fscanf(f,"%d",&mat) == 0)//testar se o arquivo terminou		
			break;
		i=0;
		c=fgetc(f);
		while(c != '\n'){
			nome[i] = '\0';
			matriculas[linha]=mat;
			strcopy(nomes[linha],nome);
			linha++		
		}
	*n = linha;
	fclose(f);			
	}
}


int main(int argc, char**argv){
	char* nome;
	if(argc > 1){
		nome = argv[1];
}
	printf("%s\n",nome);
	int matricula[50];
	char nomes[50][50];
	int n;
	le_alunos(matriculas,nomes,&n); 

	return 0;

}
