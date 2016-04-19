/*
 * trabalhoSO.c
 * 
 * Copyright 2016 RAFAEL SOUZA MORAIS DOS SANTOS <rafaelmorais@s147pc132>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <string.h>

void lerArquivo();

int main(int argc, char **argv)
{	
	int i = argc;
	printf("%d\n", argc);
	for(i = 0; i < argc; i++)
		printf("%s\n", argv[i]);
	char prefix[] = "prefix-";
	for(i = 1; i<argc; i++)
		fork()
	strcat(prefix, "poema.txt");
	lerArquivo("poema.txt",prefix);
	return 0;
	
}

void lerArquivo(char urlOrig[], char urlDest[])
{
	char ch;
	FILE *arqOrig, *arqDest;
	arqOrig = fopen(urlOrig, "r");
	if(arqOrig == NULL)
		printf("Erro ao abrir o arquivo '%s'.\n", urlOrig);
	else{
		arqDest = fopen(urlDest, "w");
		if(arqDest == NULL)
			printf("Erro ao criar o arquivo '%s'.\n", urlDest);
		else
			while((ch = fgetc(arqOrig)) != EOF)
				fputc(ch, arqDest);
	}
	fclose(arqDest);
	fclose(arqOrig);
	
	
}
