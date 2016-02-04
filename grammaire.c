#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {TERMINAL, NONTERMINAL/*, Operation*/} AtomType;
typedef enum {IDNTER, ELTER, OPERATION} Code;

typedef struct nodeType{
    struct nodeType *left;
    struct nodeType *right;
    int action;
    AtomType aType;
    Code code;
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
	if(atomeT == NONTERMINAL){
		switch (code[0]){
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
				node->action = 3;
			break;
			case 'F':
				node->left = A[4];
				node->action = 4;
			break;
			default:
				printf("erreur du type de NONTERMINAL de %s", code);
			break;
		}
		strcpy(node->name, code);
		node->code= IDNTER;
	}else{
		if(strcmp(code, ")")){
			node->action =7;
		}else if(strcmp(code, "]")){
			node->action =6;
		}else if(strcmp(code, ",") || strcmp(code, ";")){
			node->action =1;
		}else if(strcmp(code, "IDNTER")){
			node->action = 2; //TODO cours c 'est marqué 5 aussi, a verif
		}else if(strcmp(code, "ELTER")){
			node->action = 5;
		}
		node->left = NULL;
		strcpy(node->name, code);
		node->code= ELTER;
	}
	
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
 												genAtom("N",0,NONTERMINAL),
 												genAtom("FLECHE",0,TERMINAL)
 												),
 										genAtom("E",0,NONTERMINAL)),
 								genAtom("VIRGULE",0,TERMINAL))),
 				genAtom("POINTVIRGULE",0,TERMINAL));
  //N
  A[1] = 	genAtom("IDNTER", 0, TERMINAL);
  
  //E
  A[2] =	genConc(
			      genAtom("T", 0, NONTERMINAL),
				    genStar(
					    genConc(
						    genAtom("+", 0, TERMINAL),
						    genAtom("T", 0, NONTERMINAL)
					    )
				    )
		    );

  //T
  A[3] =	genConc(
			      genAtom("F", 0, NONTERMINAL),
			      genStar(
				      genConc(
					      genAtom(".", 0, TERMINAL),
					      genAtom("F", 0, NONTERMINAL)
				      )
			      )
		      );
  //F	
  A[4] = genUnion(
		      genUnion(
		        genUnion(
				      genUnion(
				        genAtom("IDNTER", 0, TERMINAL),
				        genAtom("ELTER", 0, TERMINAL)
			        ),
					    genConc(
						    genAtom("(", 0, TERMINAL),
						    genConc(
							    genAtom("E", 0, NONTERMINAL),
							    genAtom(")", 0, TERMINAL)
						    )
					    )
					  ),
					  genConc(
						  genAtom("[", 0, TERMINAL),
						  genConc(
							  genAtom("E", 0, NONTERMINAL),
							  genAtom("]", 0, TERMINAL)
						  )
					  )
				  ),
			    genConc(
					  genAtom("(/", 0, TERMINAL),
					  genConc(
						  genAtom("E", 0, NONTERMINAL),
						  genAtom("/)", 0, TERMINAL)
					  )
				  )
				
			    );
  return A;									
}

void ImprimArbreRec(nodeType *p1, int prof){
  ++prof;
  char nodeName[15];
  strcpy(nodeName,p1->name);
  int i;
  for(i=1; i<prof; i++){
    printf("---");
  }
  if (strcmp(nodeName,"conc")==0){
     printf(">conc\n");
     ImprimArbreRec(p1->left, prof);
     ImprimArbreRec(p1->right, prof);
 
  }else if (strcmp(nodeName,"union")==0){
  printf(">union\n");
    ImprimArbreRec(p1->left, prof);
    ImprimArbreRec(p1->right, prof);
  }else if (strcmp(nodeName,"star")==0){
  printf(">star\n");
    ImprimArbreRec(p1->left, prof);
  }else if (strcmp(nodeName,"un")==0){
  printf(">un\n");
    ImprimArbreRec(p1->left, prof);
  }else { //atome
    printf(">%s\n", nodeName);
  }
}

void ImprimArbre(nodeType *p1){
  ImprimArbreRec(p1, 0);
}
void Action(int act){
	switch (act){
		case 1:
		break;
		case 2:
		break;
		case 3:
		break;
		case 4:
		break;
		case 5:
		break;
		case 6:
		break;
		case 7:
		break;
		default:
			printf("erreur action numéro %d", act);
		break;
		
	}
}
int nameToIndex(char * name){
	switch (name[0]){
		case 'S':
			return 0;
		break;
		case 'N':
			return 1;
		break;
		case 'E':
			return 2;
		break;
		case 'T':
			return 3;

		break;
		case 'F':
			return 4;

		break;
		default:
			printf("erreur dans nameToIndex du nom %s", name);
		break;
	}
}
int Analyse(nodeType *p1){
  char nodeName[15];
  strcpy(nodeName,p1->name);
  int boolAnalyse = 1;
  char *scan;
  int i=0;
  /*scan = resullt fonction scan*/
  if (strcmp(nodeName,"conc")==0){
    if(Analyse(p1->left) == 1){
    	Analyse(p1->right);
    }else{
    	boolAnalyse = 0;
    }
  }else if (strcmp(nodeName,"union")==0){
    if(Analyse(p1->left) == 1){
    	boolAnalyse = 1;
    }else{
    	boolAnalyse = Analyse(p1->right);
    }
  }else if (strcmp(nodeName,"star")==0){
  	while(Analyse(p1->left)==1){}
  }else if (strcmp(nodeName,"un")==0){
	Analyse(p1->left);
  }else { //atome
	if(p1->aType==TERMINAL){
		if(p1->code = scan[i]){
			boolAnalyse = 1;
			if (p1->action !=0){
				//TODO FAIRE L''ACTION
			}
			++i;
			
		}

	}else if(p1->aType==NONTERMINAL && Analyse(A[nameToIndex(p1->name)])==1){
		if (p1->action !=0){
			//TODO FAIRE L''ACTION
		}
		boolAnalyse = 1;
		++i;
			
	}else{
		boolAnalyse=0;
	}

  }
  return boolAnalyse;
}

int main(){

  A = genForet();
  ImprimArbre(A[2]);
  return 0;
  
}
