#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {Terminal, NonTerminal/*, Operation*/} AtomType;
typedef enum {IDNTER, ELTER, OPERATION} Code;

typedef struct nodeType{
    struct nodeType *left;
    struct nodeType *right;
    int action;
    AtomType aType;
    Code code;
    char name[15];
}nodeType;

char *nomfic = "gram";

void scan(){
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
			printf("%s\n",str);
			text[i] = malloc(sizeof(char)*33);
			strcpy(text[i], str);
		} 

	}
	fclose(stream);
}

int main(){
//TODO afficher text
	scan();
	return 0;
  
}
