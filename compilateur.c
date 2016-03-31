#include "lectureFichier.c"
#include "interpreter.c"
// auteur : Benjamin MOREAU, Dennis BORDET

//--------------------------------DEFINITION DES
// TYPES--------------------------------
typedef enum { TERMINAL, NONTERMINAL } AtomType;
typedef enum { IDNTER, ELTER, OPERATION, ENT, IDENT, SYMBOLE } Code;

typedef struct nodeType {
  struct nodeType *left;
  struct nodeType *right;
  int action;
  AtomType aType;
  Code code;
  char name[15];
} nodeType;

typedef struct Dico {
  char **tab; // tableau de chaine de char
  int taille;
} Dico;

typedef struct Dicos {
  Dico *dicoNT;
  Dico *dicoT;
} Dicos;

typedef struct g0Type {
  char **g0;
  int ind;
} g0Type;

typedef struct Pile {
  nodeType **elem; // tableau d'éléments
  int size;
} Pile;

typedef struct TableDesSymboles {
  char **table;
  int size;
} TableDesSymboles;
typedef struct ATAB {
  int *table;
  int size;
} ATAB;
int recherche_simple(Dico *dico, AtomType type, char *scan);

//--------------------------------VARIABLES
// GLOBALES--------------------------------
nodeType **A;
int tailleForet = 5;

g0Type g0;
g0Type gpl;
Dicos *dicos;
Pile *pile;
ATAB *atab;
TableDesSymboles *itab;
TableDesSymboles *tableDesSymboles;

//--------------------------------FONCTIONS DE BASES
// GRAMMAIRE--------------------------------
nodeType *genConc(nodeType *p1, nodeType *p2) {
  nodeType *node;
  node = malloc(sizeof(nodeType));
  node->left = p1;
  node->right = p2;
  strcpy(node->name, "conc");
  return (node);
}

nodeType *genUnion(nodeType *p1, nodeType *p2) {
  nodeType *node;
  node = malloc(sizeof(nodeType));
  node->left = p1;
  node->right = p2;
  strcpy(node->name, "union");
  return (node);
}

nodeType *genStar(nodeType *p1) {
  nodeType *node;
  node = malloc(sizeof(nodeType));
  node->left = p1;
  node->right = NULL;
  strcpy(node->name, "star");
  return (node);
}

nodeType *genUn(nodeType *p1) {
  nodeType *node;
  node = malloc(sizeof(nodeType));
  node->left = p1;
  node->right = NULL;
  strcpy(node->name, "un");
  return (node);
}

nodeType *genAtom(char name[], int action, AtomType atomeT) {
  nodeType *node;
  node = malloc(sizeof(nodeType));
  node->right = NULL;
  node->action = action;
  node->aType = atomeT;
  if (atomeT == NONTERMINAL) {
    if (strcmp(name, "S") == 0) {
      node->left = A[0];
    } else if (strcmp(name, "N") == 0) {
      node->left = A[1];
    } else if (strcmp(name, "E") == 0) {
      node->left = A[2];
    } else if (strcmp(name, "T") == 0) {
      node->left = A[3];
    } else if (strcmp(name, "F") == 0) {
      node->left = A[4];
    } else {
      int ind = nameToIndexGPL(name);
      if (ind != -1) {
        node->left = A[nameToIndexGPL(name)];
      } else {
        printf("erreur du type de NONTERMINAL de %s\n", name);
      }
    }
    strcpy(node->name, name);
    node->code = IDNTER;

  } else {
    node->code = OPERATION;
    if (strcmp(name, "IDNTER") == 0) {
      node->code = IDNTER;
    } else if (strcmp(name, "ELTER") == 0) {
      node->code = ELTER;
    }
    node->left = NULL;
    strcpy(node->name, name);
  }
  return (node);
}

nodeType *genAtomGPL(char name[], int action, AtomType atomeT) {
  nodeType *node;
  node = malloc(sizeof(nodeType));
  node->right = NULL;
  node->action = action;
  node->aType = atomeT;
  if (atomeT == NONTERMINAL) {
      int ind = nameToIndexGPL(name);
      if (ind != -1) {
        node->left = A[nameToIndexGPL(name)];
      } else {
        printf("erreur du type de NONTERMINAL de %s\n", name);
      }
    strcpy(node->name, name);
    node->code = SYMBOLE;
  } else {
  	if(recherche_simple(dicos->dicoNT, TERMINAL, name) || strcmp(name,"'ident'")==0){
  		node->code = IDENT;
  	}else if((name[0] >= '0' && name[0] <= '9') || (strcmp(name,"'Ent'")==0)){
  	  node->code = ENT;
  	}else{
  		node->code = SYMBOLE;
  	}
		node->left = NULL;
    strcpy(node->name, name);
  }
  return (node);
}

nodeType **genForet() {
  A = (nodeType **)malloc(50 * sizeof(nodeType *));
  // S
  A[0] = genConc(genStar(genConc(genConc(genConc(genAtom("N", 0, NONTERMINAL),
                                                 genAtom("->", 0, TERMINAL)),
                                         genAtom("E", 0, NONTERMINAL)),
                                 genAtom(",", 1, TERMINAL))),
                 genAtom(";", 0, TERMINAL));
  // N
  A[1] = genAtom("IDNTER", 2, TERMINAL);

  // E
  A[2] = genConc(genAtom("T", 0, NONTERMINAL),
                 genStar(genConc(genAtom("+", 0, TERMINAL),
                                 genAtom("T", 3, NONTERMINAL))));

  // T
  A[3] = genConc(genAtom("F", 0, NONTERMINAL),
                 genStar(genConc(genAtom(".", 0, TERMINAL),
                                 genAtom("F", 4, NONTERMINAL))));
  // F
  A[4] = genUnion(
      genUnion(genUnion(genUnion(genAtom("IDNTER", 2, TERMINAL),
                                 genAtom("ELTER", 5, TERMINAL)),
                        genConc(genAtom("(", 0, TERMINAL),
                                genConc(genAtom("E", 0, NONTERMINAL),
                                        genAtom(")", 0, TERMINAL)))),
               genConc(genAtom("[", 0, TERMINAL),
                       genConc(genAtom("E", 0, NONTERMINAL),
                               genAtom("]", 6, TERMINAL)))),
      genConc(genAtom("(/", 0, TERMINAL),
              genConc(genAtom("E", 0, NONTERMINAL), genAtom("/)", 7, TERMINAL)))

          );
  return A;
}

void ImprimArbreRec(nodeType *p1, int prof) {
  ++prof;
  char nodeName[15];
  strcpy(nodeName, p1->name);
  int i;
  for (i = 1; i < prof; i++) {
    printf("---");
  }
  if (strcmp(nodeName, "conc") == 0) {
    printf(">conc\n");
    ImprimArbreRec(p1->left, prof);
    ImprimArbreRec(p1->right, prof);

  } else if (strcmp(nodeName, "union") == 0) {
    printf(">union\n");
    ImprimArbreRec(p1->left, prof);
    ImprimArbreRec(p1->right, prof);
  } else if (strcmp(nodeName, "star") == 0) {
    printf(">star\n");
    ImprimArbreRec(p1->left, prof);
  } else if (strcmp(nodeName, "un") == 0) {
    printf(">un\n");
    ImprimArbreRec(p1->left, prof);
  } else { // atome
    printf(">%s, code: %d, #%d\n", nodeName, p1->code, p1->action);
  }
}

void ImprimArbre(nodeType *p1) { ImprimArbreRec(p1, 0); }

//--------------------------------FONCTIONS DU
// SCANNER--------------------------------

void scan() { (g0.ind)++; }
void scan_GPL() { (gpl.ind)++; }
void init_scan() {
  g0.g0 = lectureFichier("gram");
  g0.ind = 0;
}
void init_scanGPL() {
  gpl.g0 = lectureFichier("program");
  gpl.ind = 0;
}
char *val_scan() {
  if (g0.g0[g0.ind][0] == '#')
    scan();
  return g0.g0[g0.ind];
}

char *val_scanGPL() { return gpl.g0[gpl.ind]; }

int action_scan() {
  if (strcmp(val_scan(), ";") == 0) {
    return 0;
  } else if (g0.g0[g0.ind + 1][0] == '#') {
    char *action_str;
    action_str = malloc(4 * sizeof(char));
    strcpy(action_str, g0.g0[g0.ind + 1] + 1); // on eleve le #
    // strcpy(action_str, action_str +1);
    return atoi(action_str);
  } else {
    return 0;
  }
}


int action_scanGPL() {
  if (strcmp(val_scan(), ";") == 0) {
    return 0;
  } else if (gpl.g0[gpl.ind + 1][0] == '#') {
    char *action_str;
    action_str = malloc(4 * sizeof(char));
    strcpy(action_str, gpl.g0[gpl.ind + 1] + 1); // on eleve le #
    // strcpy(action_str, action_str +1);
    scan_GPL();
    return atoi(action_str);
  } else {
    return 0;
  }
}

void afficher_scan() {
  // init_scan();
  while (g0.ind < 15) {
    g0.ind++;
  }
}

Code code() {
  char *val = val_scan();
  if (val[0] == '\'') {
    return ELTER;
  } else if (strcmp(val, "->") == 0 || strcmp(val, "+") == 0 ||
             strcmp(val, ".") == 0 || strcmp(val, "*") == 0 ||
             strcmp(val, "[") == 0 || strcmp(val, "]") == 0 ||
             strcmp(val, "(") == 0 || strcmp(val, ")") == 0 ||
             strcmp(val, "(/") == 0 || strcmp(val, "/)") == 0 ||
             strcmp(val, ",") == 0 || strcmp(val, ";") == 0) {
    return OPERATION;
  }
  return IDNTER;
}
Code codeGPL() {
  char *val = val_scanGPL();
  if (val[0] >= '0' && val[0] <= '9') {
    return ENT;
  } else if (val[0] >= 'A' && val[0] <= 'z') {
  	if(recherche_simple(dicos->dicoT, TERMINAL, val) || recherche_simple(dicos->dicoNT, NONTERMINAL, val)){
  		return SYMBOLE;
  	}
    return IDENT;
  }
  return SYMBOLE;
}
//----------------------------FONCTIONS DE LA TABLE DES
// SYMBOLES--------------------------------

void init_dicos() {
  dicos = malloc(2 * sizeof(Dico *));
  dicos->dicoNT = malloc(sizeof(Dico *));
  dicos->dicoT = malloc(sizeof(Dico *));
  dicos->dicoNT->tab = malloc(50 * sizeof(char *));
  dicos->dicoT->tab = malloc(50 * sizeof(char *));
  dicos->dicoNT->taille = 0;
  dicos->dicoT->taille = 0;
}

// PRECOND: Verifier la précense du dicos
void ajout_symbole(char *symb, AtomType type) {
  char copie[50];
  switch (type) {
  case TERMINAL:
    strcpy(copie, symb);
    symb = strtok(copie, "\'");
    dicos->dicoT->tab[dicos->dicoT->taille] = malloc(20 * sizeof(char));
    strcpy(dicos->dicoT->tab[dicos->dicoT->taille], symb);
    dicos->dicoT->taille++;
    break;
  case NONTERMINAL:
  	dicos->dicoNT->tab[dicos->dicoNT->taille] = malloc(20 * sizeof(char));
  	strcpy(dicos->dicoNT->tab[dicos->dicoNT->taille], symb);
    dicos->dicoNT->taille++;
    break;
  default:
    printf("erreur dans l'ajout de dicos -> pas de type correspondant "
           "(Terminal ou non terminal)\n");
    break;
  }
}

char *recherche(Dico *dico, AtomType type, char *scan) {
  char *symb;
  int bool_trouve = 0;
  int i;

  if (type == TERMINAL) {
    for (i = 0; i < dicos->dicoT->taille; i++) {
      symb = dicos->dicoT->tab[i];
      if (strcmp(scan, symb) == 0) {
        bool_trouve = 1;
        break;
      }
    }
  } else {
    for (i = 0; i < dicos->dicoNT->taille; i++) {
      symb = dicos->dicoNT->tab[i];
      if (strcmp(scan, symb) == 0) {
        bool_trouve = 1;
        break;
      }
    }
  }
  if (bool_trouve == 0) {
    ajout_symbole(scan, type);
  }
  return scan;
}

int recherche_simple(Dico *dico, AtomType type, char *scan) {
  char *symb;
  int bool_trouve = 0;
  int i;
  if (type == TERMINAL) {
    for (i = 0; i < dicos->dicoT->taille; i++) {
      symb = dicos->dicoT->tab[i];
      if (strcmp(scan, symb) == 0) {
        bool_trouve = 1;
        break;
      }
    }
  } else {
    for (i = 0; i < dicos->dicoNT->taille; i++) {
      symb = dicos->dicoNT->tab[i];
      if (strcmp(scan, symb) == 0) {
        bool_trouve = 1;
        break;
      }
    }
  }
  return bool_trouve;
}

void init_pile_table() {
  pile = malloc(sizeof(Pile));
  pile->elem = malloc(50 * sizeof(nodeType *));
  pile->size = 0;
  atab = malloc(sizeof(TableDesSymboles));
  atab->table = malloc(50 * sizeof(int));
  atab->size = 0;
  itab = malloc(sizeof(TableDesSymboles));
  itab->table = malloc(50 * sizeof(char *));
  itab->size = 0;
  
  tableDesSymboles = malloc(sizeof(TableDesSymboles));
  tableDesSymboles->table = malloc(50 * sizeof(char *));
  tableDesSymboles->size = 0;
}

// TODO voir si besoin recopie ?????
void empiler(nodeType *e) {
  pile->elem[pile->size] = e;
  pile->size++;
}

// precond: pile non vide
nodeType *depiler() {
  pile->size--;
  return pile->elem[pile->size];
}

// retourne index de name sinon -1
int nameToIndexGPL(char *name) {
  int i;
  for (i = 0; i < dicos->dicoNT->taille; i++) {
    if (strcmp(name, dicos->dicoNT->tab[i]) == 0) {
      return i + 5;
    }
  }
  return -1;
}

// precond : pas plus de 50 dicos
void addToSymboles(char *name) {
  strcpy(tableDesSymboles->table[tableDesSymboles->size], name);
  tableDesSymboles->size++;
}

//----------------------------FONCTIONS
// D'ANALYSE--------------------------------

void action(int act) {
  nodeType *t1, *t2;
  switch (act) {
  case 1: //-----------nouvelle case tab

    t1 = depiler();
    t2 = depiler();
    A[nameToIndexGPL(t2->name)] = t1;
    tailleForet++;
    break;
  case 2: //-----------genAtom
    empiler(genAtomGPL(recherche(dicos->dicoNT, NONTERMINAL, val_scan()),
                    action_scan(), NONTERMINAL));
    break;
  case 3: //-----------genUnion
    t1 = depiler();
    t2 = depiler();
    empiler(genUnion(t2, t1));
    break;
  case 4: //-----------genConc
    t1 = depiler();
    t2 = depiler();
    empiler(genConc(t2, t1));
    break;
  case 5: //-----------genAtome
    empiler(genAtomGPL(recherche(dicos->dicoT, TERMINAL, val_scan()),
                    action_scan(), TERMINAL));
    break;
  case 6: //-----------genStar
    t1 = depiler();
    empiler(genStar(t1));
    break;
  case 7: //-----------genUn
    t1 = depiler();
    empiler(genUn(t1));
    break;
  default:
    printf("erreur action numéro %d", act);
    break;
  }
}

void actionGPL(int act) {
  switch (act) {
  case 1:
    	pcode[c0] = LDA;
    	c0++;
		pcode[c0] = spx;
		spx++;
		c0++;
		itab->table[itab->size] = malloc(20*sizeof(char));
		strcpy(itab->table[itab->size], val_scanGPL());
		atab->table[atab->size] = spx-1;
		itab->size++;
		atab->size++;
    break;
	case 2:
    	pcode[c0] = LDC;
		c0++;
		pcode[c0] = atoi(val_scanGPL());
		c0++;
		pcode[c0] = AFF;
		c0++;
		
	break;
	case 3:
	{
		int indice, i;
		char car[50];
		strcpy(car, val_scanGPL());
		for(i=0; i<atab->size;i++){
			if(strcmp(car,itab->table[i])==0){
				indice = i;
				break;
			}
		}
		pcode[c0] = LDV;
		c0++;
	  	pcode[c0] = indice;
		c0++;
	  	pcode[c0] = WRTLN;
		c0++;
  	break;
  	}
  default:
    printf("erreur action numéro %d\n", act);
    break;
  }
}

int nameToIndex(char *name) {
  if (strcmp(name, "S") == 0) {
    return 0;
  } else if (strcmp(name, "N") == 0) {
    return 1;
  } else if (strcmp(name, "E") == 0) {
    return 2;
  } else if (strcmp(name, "T") == 0) {
    return 3;
  } else if (strcmp(name, "F") == 0) {
    return 4;
  } else {

    nameToIndexGPL(name);
  }
}

int AnalyseG0(nodeType *p1) {

  char nodeName[15];
  strcpy(nodeName, p1->name);
  int boolAnalyse = 1;
  if (strcmp(nodeName, "conc") == 0) {
    if (AnalyseG0(p1->left) == 1) {
      return AnalyseG0(p1->right);
    } else {
      return 0;
    }
  } else if (strcmp(nodeName, "union") == 0) {
    if (AnalyseG0(p1->left) == 1) {
      return 1;
    } else {
      return AnalyseG0(p1->right);
    }
  } else if (strcmp(nodeName, "star") == 0) {
    while (AnalyseG0(p1->left) == 1) {
    }
    return 1;
  } else if (strcmp(nodeName, "un") == 0) {
    return AnalyseG0(p1->left);
  } else { // atome
    if (p1->aType == TERMINAL) {
      if (p1->code == code()) {
        if (p1->action != 0) {
          action(p1->action);
        }
        if (code() == OPERATION) {
          if (strcmp(p1->name, val_scan()) == 0) {
            scan();
            return 1;
          } else {
            return 0;
          }

        } else {
          scan();
          return 1;
        }

      } else {
        return 0;
      }
    } else if (p1->aType == NONTERMINAL &&
               AnalyseG0(A[nameToIndex(p1->name)]) == 1) {
      if (p1->action != 0) {
        action(p1->action);
      }
      return 1;
    } else {
      return 0;
    }
  }
  return 0; // normalement on ne passe pas la
}

int AnalyseGPL(nodeType *p1) {

  char nodeName[15];
  strcpy(nodeName, p1->name);
  int boolAnalyse = 1;
  if (strcmp(nodeName, "conc") == 0) {
    if (AnalyseGPL(p1->left) == 1) {
      return AnalyseGPL(p1->right);
    } else {
      return 0;
    }
  } else if (strcmp(nodeName, "union") == 0) {
    if (AnalyseGPL(p1->left) == 1) {
      return 1;
    } else {
      return AnalyseGPL(p1->right);
    }
  } else if (strcmp(nodeName, "star") == 0) {
    while (AnalyseGPL(p1->left) == 1) {
    }
    return 1;
  } else if (strcmp(nodeName, "un") == 0) {
    return AnalyseGPL(p1->left);
  } else { // atome
  if(val_scanGPL()==NULL){
  	return 1;
  }
    if (p1->aType == TERMINAL) {
      if (p1->code == codeGPL()) {
        if (p1->action != 0) {
          actionGPL(p1->action);
        }
        	char copie[50] = "\'";
        	strcat(copie,val_scanGPL());
        	strcat(copie,"\'");
         if ((strcmp(p1->name, copie) == 0 || strcmp(p1->name, "\'ident\'") == 0 ||
         strcmp(p1->name, "\'Ent\'") == 0)/* || strcmp(val_scanGPL(), "\';\'")==0*/) {
          scan_GPL();
          
          return 1;
          
      } else {
        return 0;
      }
      }
    } else if (p1->aType == NONTERMINAL &&
               AnalyseGPL(A[nameToIndex(p1->name)]) == 1) {
      if (p1->action != 0) {
        actionGPL(p1->action);
      }
      return 1;
    } else {
      return 0;
    }
  }
  return 0; // normalement on ne passe pas la
}

int main() {
  init_dicos();
  init_pile_table();
  init_scan();
  
  A = genForet();
  {// imprim foret G0
  	printf("-------- *********************** ---------\n");
  	printf("-------- Affichage foret G0 ---------\n");
  	printf("-------- *********************** ---------\n");
		ImprimArbre(A[0]);
		ImprimArbre(A[1]);
		ImprimArbre(A[2]);
		ImprimArbre(A[3]);
		ImprimArbre(A[4]);
  }

  printf("-------- *********************** ---------\nresultat analyse G0 : %d\n", AnalyseG0(A[0]));
  printf("-------- *********************** ---------\n\n");
  {//imprim foret GPL
		int i;
  	printf("-------- *********************** ---------\n");
  	printf("-------- Affichage foret GPL ---------\n");
  	printf("-------- *********************** ---------\n");
		for(i=5 ; i<tailleForet ; i++){
			ImprimArbre(A[i]);
		}
  }
  init_interpreter();
  init_scanGPL();
  printf("-------- *********************** ---------\nresultat analyse GPL : %d\n", AnalyseGPL(A[5]));
	printf("-------- *********************** ---------\n\n");
	
	printf("S = ");
	//on affiche la valeur de S avec du PCODE
	/*pcode[c0] = LDV;
	c0++;
  pcode[c0] = 0;
	c0++;
  pcode[c0] = WRTLN;
	c0++;*/
	pcode[c0] = STOP;
	c0++;
	c0=0;
	exec();
  
  
    printf("-------- *********************** ---------\n");
  	printf("-------- Test interpreter :---------\n");
  	printf("* Somme des N premiers entiers, entrez N *\n");
  	printf("-------- *********************** ---------\n");
  //test interpreter
  spx = 2;//3 variables
  
  //I=0;
  pcode[0] = LDA;
  pcode[1] = 0;
  pcode[2] = LDC;
  pcode[3] = 0;
  pcode[4] = AFF;
  //S=0;
  pcode[5] = LDA;
  pcode[6] = 1;
  pcode[7] = LDC;
  pcode[8] = 0;
  pcode[9] = AFF;
  //N=read();
  pcode[10] = LDA;
  pcode[11] = 2;
  pcode[12] = RDLN;
  pcode[13] = AFF;
  //while(I<=N){
  pcode[14] = LDV;
  pcode[15] = 0;
  pcode[16] = LDV;
  pcode[17] = 2;
  pcode[18] = INFE;
  pcode[19] = JIF;
  pcode[20] = 37;
  //S=S+I;
  pcode[21] = LDA;
  pcode[22] = 1;
  pcode[23] = LDV;
  pcode[24] = 1;
  pcode[25] = LDV;
  pcode[26] = 0;
  pcode[27] = ADD;
  pcode[28] = AFF;
  //I++;
  pcode[29] = LDA;
  pcode[30] = 0;
  pcode[31] = LDV;
  pcode[32] = 0;
  pcode[33] = INC;
  pcode[34] = AFF;
  
  //}
  pcode[35] = JMP;
  pcode[36] = 14;
  //writeln(S);
  pcode[37] = LDV;
  pcode[38] = 1;
  pcode[39] = WRTLN;
  pcode[40] = STOP;
  c0 = 0;
  
  exec();

  return 0;
}
