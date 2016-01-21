#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {Terminal, NonTerminal, Operation} AtomType;
typedef struct nodeType{
    struct nodeType *left;
    struct nodeType *right;
    int action;
    AtomType aType;
    char name[];
}nodeType;

nodeType *A[5];

nodeType *genConc(nodeType *p1, nodeType *p2){
	nodeType *node;
	node->left = p1;
	node->right = p2;
	strcpy(node->name, "conc");
	return (node);
}

nodeType *genUnion(nodeType *p1, nodeType *p2){
	nodeType *node;
	node->left = p1;
	node->right = p2;
	strcpy(node->name, "union");
	return (node);
}

nodeType *genStar(nodeType *p1){
	nodeType *node;
	node->left = p1;
	node->right = NULL;
	strcpy(node->name, "star");
	return (node);
}

nodeType *genUn(nodeType *p1){
	nodeType *node;
	node->left = p1;
	node->right = NULL;
	strcpy(node->name, "un");
	return (node);
}

nodeType *genAtom(char code[], int action, AtomType atomeT){//TODO
	nodeType *node;
	node->right = NULL; 
	node->aType = atomeT;
	if(atomeT == NonTerminal){
		switch (code[1] ){
			case 'S':
				node->left = A[0];
			break;
			case 'N':
				node->left = A[1];
			break;
			case 'E':
				node->left = A[2];
			break;
			case 'T':
				node->left = A[3];
			break;
			case 'F':
				node->left = A[4];
			break;
			default:
				printf("erreur type de nonTerminal");
			break;
		}
	}else{
		node->left = NULL;
	}
	
	strcpy(node->name, code);
	return (node);
}

void genForet(){

}

void ImprimArbreRec(nodeType *p1, int prof){
  ++prof;
  char nodeName[10];
  strcpy(nodeName,p1->name);
  int i;
  for(i=1; i=prof; ++i){
    printf("---");
  }
  printf(">%s\n", nodeName);
  if (nodeName == "conc"){
     //printf(">conc\n");
     ImprimArbreRec(p1->left, prof);
     ImprimArbreRec(p1->right, prof);
  }else if (nodeName == "union"){
    //printf(">union\n");
    ImprimArbreRec(p1->left, prof);
    ImprimArbreRec(p1->right, prof);
  }else if (nodeName == "star"){
    // printf(">star\n");
    ImprimArbreRec(p1->left, prof);
  }else if (nodeName == "un"){
     //printf(">un\n");
     ImprimArbreRec(p1->left, prof);
  }else { //atome
     //TODO
     
     
  }
}/*
void ImprimArbre(nodeType * p1){
  ImprimArbreRec(p1, 1);
}*/

int main(){

	return 0;
}
