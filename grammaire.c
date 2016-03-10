#include "lectureFichier.c"


//--------------------------------DEFINITION DES TYPES--------------------------------
typedef enum {TERMINAL, NONTERMINAL} AtomType;
typedef enum {IDNTER, ELTER, OPERATION} Code;

typedef struct nodeType{
    struct nodeType *left;
    struct nodeType *right;
    int action;
    AtomType aType;
    Code code;
    char name[15];
}nodeType;

typedef struct Dico{
	char ** tab;//tableau de chaine de char
	int taille;
}Dico;

typedef struct Dicos{
	Dico *dicoNT;
	Dico *dicoT;
}Dicos;

typedef struct gplType{
	char **gpl;
	int ind;
}gplType;

typedef struct Pile{
  nodeType** elem; //tableau d'éléments
  int size;
}Pile;

typedef struct TableDesSymboles{
	char** table;
	int size;
}TableDesSymboles;



//--------------------------------VARIABLES GLOBALES--------------------------------
nodeType **A;
//TODO size
gplType gpl;
Dicos *dicos;
Pile* pile;
TableDesSymboles* tableDesSymboles;


//--------------------------------FONCTIONS DE BASES GRAMMAIRE--------------------------------
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

nodeType *genAtom(char name[], int action, AtomType atomeT){
	nodeType *node;
	node = malloc(sizeof(nodeType));
	node->right = NULL; 
	node->aType = atomeT;
	if(atomeT == NONTERMINAL){
		switch (name[0]){
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
				printf("erreur du type de NONTERMINAL de %s", name);
			break;
		}
		strcpy(node->name, name);
		node->code= IDNTER;
	}else{
		node->code= OPERATION;
		if(strcmp(name, ")")==0){
			node->action =7;
		}else if(strcmp(name, "]")==0){
			node->action =6;
		}else if(strcmp(name, ",")==0 || strcmp(name, ";")==0){
			node->action =1;
		}else if(strcmp(name, "IDNTER")==0){
			node->action = 2; //TODO cours c 'est marqué 5 aussi, a verif
			node->code= IDNTER;
		}else if(strcmp(name, "ELTER")==0){
			node->action = 5;
			node->code= ELTER;
		}
		node->left = NULL;
		strcpy(node->name, name);
		
	}
	return (node);
}

nodeType** genForet(){
	A =(nodeType**) malloc(50*sizeof(nodeType*));
  //S
	A[0] = genConc(
 				  genStar(
 						genConc(
 								genConc(
 										genConc(
 												genAtom("N",0,NONTERMINAL),
 												genAtom("->",0,TERMINAL)
 												),
 										genAtom("E",0,NONTERMINAL)),
 								genAtom(",",0,TERMINAL))),
 				genAtom(";",0,TERMINAL));
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


//--------------------------------FONCTIONS DU SCANNER--------------------------------

void scan(){
	(gpl.ind)++;
}
void init_scan(){
	gpl.gpl = lectureFichier();
	gpl.ind = 0;
}
char * val_scan(){
	return gpl.gpl[gpl.ind];
}
int action_scan(){
	if (strcmp(val_scan(),";")==0){
		return 0;
	}else if(gpl.gpl[gpl.ind+1][0]=='#'){
		char * action_str;
		action_str = malloc (4*sizeof(char));
		strcpy(action_str,gpl.gpl[gpl.ind+1]+1);//on eleve le #
		//strcpy(action_str, action_str +1);
		return atoi(action_str);
	}else{
		return 0;
	}
}
void afficher_scan(){
	//init_scan();
	while(gpl.ind<15){
		printf("fct affichage scan : %s\n", val_scan());
		gpl.ind ++;
	}
}

Code code(){
	char *val = val_scan();
	if(val[0]=='\''){
		return ELTER;
	}else if (strcmp(val,"->")==0 || strcmp(val,"+")==0 || strcmp(val,".")==0 || strcmp(val,"*")==0 || strcmp(val,"[")==0 || strcmp(val,"]")==0 || strcmp(val,"(")==0 || strcmp(val,")")==0 || strcmp(val,"(/")==0 || strcmp(val,"/)")==0 || strcmp(val,",")==0 || strcmp(val,";")==0){
		return OPERATION;
	}
		return IDNTER;
}
//----------------------------FONCTIONS DE LA TABLE DES SYMBOLES--------------------------------

void init_dicos(){
	dicos = malloc(2*sizeof(Dico*));
	dicos->dicoNT = malloc(sizeof(Dico*));
	dicos->dicoT = malloc(sizeof(Dico*));
	dicos->dicoNT->tab = malloc(50*sizeof(char*));
	dicos->dicoT->tab = malloc(50*sizeof(char*));
	dicos->dicoNT->taille = 0;
	dicos->dicoT->taille = 0;
}

//PRECOND: Verifier la précense du dicos
void ajout_symbole(char* symb, AtomType type){
	switch (type){
	case TERMINAL:
		dicos->dicoT->tab[dicos->dicoT->taille] = symb;
		dicos->dicoT->taille++;
	break;
	case NONTERMINAL:
		dicos->dicoNT->tab[dicos->dicoNT->taille] = symb;
		dicos->dicoNT->taille++;
	break;
	default:
		printf("erreur dans l'ajout de dicos -> pas de type correspondant (Terminal ou non terminal)\n");
	break;
	}
}
char* recherche(Dico* dico, AtomType type, char* scan){
	char* symb;
	int bool_trouve=0;
	int i;
	
	if(type==TERMINAL){
	printf("recherche if\n");
		for(i=0; i<dicos->dicoT->taille;i++){
			symb = dicos->dicoT->tab[i];
			if(strcmp(scan,symb)==0){
				bool_trouve=1;
				break;
			}
		}
	}else{
	printf("recherche else\n");
		printf("dicotaille : %d\n",dicos->dicoNT->taille);
		//TODO ERREUR SEG PAR ICI 
		for(i=0; i<dicos->dicoNT->taille;i++){
			symb = dicos->dicoNT->tab[i];
			if(strcmp(scan,symb)==0){
				bool_trouve=1;
				break;
			}
		}
		
	}
	if(bool_trouve==0){
		ajout_symbole(scan,type);
	}
	
	return symb;
}

void init_pile_table(){
  	pile=malloc(sizeof(Pile));
    pile->elem = malloc(50*sizeof(nodeType*));
    pile->size=0;
    tableDesSymboles = malloc(sizeof(TableDesSymboles));
    tableDesSymboles->table = malloc(50*sizeof(char*));
    tableDesSymboles->size = 0;
}

//TODO voir si besoin recopie ?????
void empiler(nodeType* e){
	pile->elem[pile->size] = e;
	pile->size++;
}

//precond: pile non vide
nodeType* depiler(){
  pile->size--;
  return pile->elem[pile->size];
}

//retourne index de name sinon -1
int nameToIndexGPL(char* name){
	int i;
	for(i=0;i<tableDesSymboles->size;i++){
		if(strcmp(name,tableDesSymboles->table[i])==0){
			return i+5;
		}
	}
	return -1;
}

//precond : pas plus de 50 dicos
void addToSymboles(char* name){
	strcpy(tableDesSymboles->table[tableDesSymboles->size],name);
	tableDesSymboles->size++;
}

//----------------------------FONCTIONS D'ANALYSE--------------------------------


void action(int act){
	nodeType *t1,*t2;
	switch (act){
		case 1://-----------nouvelle case tab
		printf("//////action 1 : %s\n",val_scan());
		
			t1 = depiler();
			printf("ok\n");
			t2 = depiler();
			printf("//////action 1 name2ind : %d\n",nameToIndex(t2->name));
			A[nameToIndex(t2->name)] = t1;
		break;
		case 2://-----------genAtom
		printf("//////action 2 : %s\n",val_scan());
			printf("action scan\n");
			printf(">%d\n", action_scan());
			empiler(genAtom(recherche(dicos->dicoNT, NONTERMINAL, val_scan()),action_scan(),NONTERMINAL));
			printf("emiler ok\n");
		break;
		case 3://-----------genUnion
		printf("//////action 3 : %s\n",val_scan());
			t1 = depiler();
			t2 = depiler();
			empiler(genUnion(t2,t1));
		break;
		case 4://-----------genConc
		printf("//////action 4 : %s\n",val_scan());
			t1 = depiler();
			t2 = depiler();
			empiler(genConc(t2,t1));
		break;
		case 5://-----------genAtome
		printf("//////action 5 : %s\n",val_scan());
		printf("action scan\n");
			printf(">%d\n", action_scan());
			empiler(genAtom(recherche(dicos->dicoT, TERMINAL, val_scan()),action_scan(),TERMINAL));
		break;
		case 6://-----------genStar
		printf("//////action 6 : %s\n",val_scan());
			t1 = depiler();
			empiler(genStar(t1));
		break;
		case 7://-----------genUn
		printf("//////action 7 : %s\n",val_scan());
			t1 = depiler();
			empiler(genUn(t1));
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
			//appeler nameToIndexGPL(name)
			printf("erreur dans nameToIndex du nom %s", name);
		break;
	}
}

int Analyse(nodeType *p1){
  char nodeName[15];
  strcpy(nodeName,p1->name);
  int boolAnalyse = 1;
  printf("---p1->name : %s\n", nodeName);
  if (strcmp(nodeName,"conc")==0){
    if(Analyse(p1->left) == 1){
    	return Analyse(p1->right);
    }else{
    	return 0;
    }
  }else if (strcmp(nodeName,"union")==0){
    if(Analyse(p1->left) == 1){
    	return 1;
    }else{
    	return Analyse(p1->right);
    }
  }else if (strcmp(nodeName,"star")==0){
  	while(Analyse(p1->left)==1){}
  	return 1;
  }else if (strcmp(nodeName,"un")==0){
	return Analyse(p1->left);
  }else { //atome
	if(p1->aType==TERMINAL){
		printf("****val scan : %s\n", val_scan());
		printf("%d - %d\n", p1->code, code());
		if(p1->code == code()){
			if (p1->action !=0){
					action(p1->action);
			}
			if (code()==OPERATION){
				if(strcmp(p1->name, val_scan())==0){
					printf("scan+1\n");
					scan();
					return 1;
				}else{
					return 0;
				}
				
			}else{
				printf("scan+1\n");
				scan();
				return 1;
			}
			
		}else {
			return 0;
		}
	}else if(p1->aType==NONTERMINAL && Analyse(A[nameToIndex(p1->name)])==1){
		if (p1->action !=0){
			action(p1->action);
		}
		return 1;
	}else{
		return 0;
	}

  }
  return 0;// normalement on ne passe pas la
}

int main(){
  init_dicos();
	init_pile_table();
	init_scan();


	A = genForet();
	printf("resultat analyse %d\n", Analyse(A[0]));
	return 0;
}
