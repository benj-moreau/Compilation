#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {Terminal, NonTerminal, Operation} AtomType;

typedef struct nodeType{
    struct nodeType *left;
    struct nodeType *right;
    int action;
    AtomType aType;
    char name[15];
}nodeType;

nodeType** A;
 
nodeType *genConc(nodeType *p1, nodeType *p2){
	nodeType *node;
	node = malloc(sizeof(nodeType));
	node->left = p1;
	node->right = p2;
	strcpy(node->name, "conc");
	return (node);
}

nodeType *genUnion(nodeType *p1, nodeType *p2){
	nodeType *node;
	node = malloc(sizeof(nodeType));
	node->left = p1;
	node->right = p2;
	strcpy(node->name, "union");
	return (node);
}

nodeType *genStar(nodeType *p1){
	nodeType *node;
	node = malloc(sizeof(nodeType));
	node->left = p1;
	node->right = NULL;
	strcpy(node->name, "star");
	return (node);
}

nodeType *genUn(nodeType *p1){
	nodeType *node;
	node = malloc(sizeof(nodeType));
	node->left = p1;
	node->right = NULL;
	strcpy(node->name, "un");
	return (node);
}

nodeType *genAtom(char code[], int action, AtomType atomeT){//TODO
	nodeType *node;

	node = malloc(sizeof(nodeType));
	node->right = NULL; 
	node->aType = atomeT;
	if(atomeT == NonTerminal){
		/*switch (code[0]){
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
		}*/
	}else{
		node->left = NULL;
	}
	strcpy(node->name, code);
	return (node);
}

nodeType** genForet(){
	A =(nodeType**) malloc(5*sizeof(nodeType*));
  //S
	A[0] = genConc(
 				  genStar(
 						genConc(
 								genConc(
 										genConc(
 												genAtom("N",0,NonTerminal),
 												genAtom("FLECHE",0,Terminal)
 												),
 										genAtom("E",0,NonTerminal)),
 								genAtom("VIRGULE",0,Terminal))),
 				genAtom("POINTVIRGULE",0,Terminal));
  //N
  A[1] = 	genAtom("IDNTER", 0, Terminal);
  
  //E
  A[2] =	genConc(
			      genAtom("T", 0, NonTerminal),
				    genStar(
					    genConc(
						    genAtom("+", 0, Terminal),
						    genAtom("T", 0, NonTerminal)
					    )
				    )
		    );

  //T
  A[3] =	genConc(
			      genAtom("F", 0, NonTerminal),
			      genStar(
				      genConc(
					      genAtom(".", 0, Terminal),
					      genAtom("F", 0, NonTerminal)
				      )
			      )
		      );
		
  A[4] = genUnion(
		      genUnion(
		        genUnion(
				      genUnion(
				        genAtom("IDNTER", 0, Terminal),
				        genAtom("ELTER", 0, Terminal)
			        ),
					    genConc(
						    genAtom("(", 0, Terminal),
						    genConc(
							    genAtom("E", 0, NonTerminal),
							    genAtom(")", 0, Terminal)
						    )
					    )
					  ),
					  genConc(
						  genAtom("[", 0, Terminal),
						  genConc(
							  genAtom("E", 0, NonTerminal),
							  genAtom("]", 0, Terminal)
						  )
					  )
				  ),
			    genConc(
					  genAtom("(/", 0, Terminal),
					  genConc(
						  genAtom("E", 0, NonTerminal),
						  genAtom("/)", 0, Terminal)
					  )
				  )
				
			    );
  return A;									
}
 
void ImprimArbreRec(nodeType *p1, int prof){
  ++prof;
  char nodeName[15];
  nodeName[0]='0';
  strcpy(nodeName,p1->name);
  //printf("p1 name     %s  -   node name     %s\n",p1->name,nodeName);
  int i;
  for(i=1; i<prof; i++){
    printf("---");
  }
  //printf(">%s\n", nodeName);
  if (strcmp(nodeName,"conc")==0){
     printf(">conc\n");
     ImprimArbreRec(p1->left, prof);
     //printf("**okG**\n");
     ImprimArbreRec(p1->right, prof);
    // printf("**okD**\n");
 
  }else if (strcmp(nodeName,"union")==0){
  printf(">union\n");
    ImprimArbreRec(p1->left, prof);
    //printf("**okG**\n");
    ImprimArbreRec(p1->right, prof);
    //printf("**okD**\n");
  }else if (strcmp(nodeName,"star")==0){
  printf(">star\n");
    ImprimArbreRec(p1->left, prof);
    //printf("**okG**\n");
  }else if (strcmp(nodeName,"un")==0){
  printf(">un\n");
    ImprimArbreRec(p1->left, prof);
    //printf("**okG**\n");
  }else { //atome
    printf(">%s\n", nodeName);
    //printf("%s",p1->name);
    //printf("**okAt**\n");
  }

}
void ImprimArbre(nodeType * p1){
  ImprimArbreRec(p1, 0);
}

int main(){

  A = genForet();
 // nodeType* C = genAtom("POINTVIRGULE",0,Terminal);
  ImprimArbre(A[0]);
  ImprimArbre(A[1]);
  ImprimArbre(A[2]);
  ImprimArbre(A[3]);
  ImprimArbre(A[4]);
  return 0;
  
}
