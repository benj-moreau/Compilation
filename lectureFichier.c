#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *nomfic = "gram";

char ** lectureFichier(){
	FILE *stream;
	char str[32];
	char **text;
	text = malloc(256*sizeof(str));
	
	stream = fopen(nomfic, "r");
	if(stream == NULL)
	{
		printf("Le fichier n'existe pas");
	}
	else
	{
		int i = 0;
		while (fscanf(stream,"%s",str)!= EOF){
			text[i] = malloc(sizeof(char)*33);
			strcpy(text[i], str);
			i++;
		}

	}
	fclose(stream);
	return text;
}
