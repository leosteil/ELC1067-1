#include<stdio.h>

main(){
	FILE *f;
	int matricula;
	char nome[100];

	printf("digite matricula: ");
	scanf("%d",&matricula);
	printf("\nNome: ");
	scanf("%s",nome);

	f = fopen("saida.txt","w");
	fprintf(f, "%d %s\n", matricula,nome);
	fclose(f);

}
