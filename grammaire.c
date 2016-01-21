#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {Terminal, NonTerminal, Operation} AtomType;
typedef struct nodeType{
    struct nodeType *left;
    struct nodeType *right;
    int action;
    AtomType aType;
    char name[10];
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
	/*
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
	*/
	strcpy(node->name, code);
	return (node);
}

nodeType** genForet(){
  nodeType** A;
  /*int *B;
  B = malloc(2 * sizeof(int));
 
  B[0]=2;
  B[1] = 3;
  */
  A = malloc(5*sizeof(nodeType*));
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
  A[1] = 	genAtom("IDNTER", 0, NonTerminal);
  
  //E
  A[3] =	genConc(
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
				        genAtom("IDNTER", 0, NonTerminal),
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
  char nodeName[10];
  nodeName[0]='0';
  strcpy(nodeName,p1->name);
  int i;
  for(i=1; i<prof; i++){
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
    
  }

}
void ImprimArbre(nodeType * p1){
  ImprimArbreRec(p1, 1);
}

int main(){
  
  A = genForet();
  //printf("A : %p",A);
  int i=0;
  /*for(i=0; i<5;i++){
  
    ImprimArbre(A[i]);
  }*/
  ImprimArbre(A[4]);
  i++;
  /*ImprimArbre(A[i]);
  i++;
  //ImprimArbre(A[i]);
  i++;
  ImprimArbre(A[i]);
  i++;
  ImprimArbre(A[i]);
  i++;*/
  
 /*int *B;
 B = malloc(2 * sizeof(int));
 
  B[0]=2;
  B[1] = 3;
  printf("%d %d",B[0], B[1]);*/
	return 0;
}
