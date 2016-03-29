int *pilex;
int spx;
int *pcode;
int c0;

void init_interpreter() {
  pilex = malloc(100 * sizeof(int));
  spx = 0;

  pcode = malloc(100 * sizeof(int));
  c0 = 0;
}

typedef enum {
  LDA,
  LDV,
  LDC,
  JMP,
  JIF,
  JSR,
  RSR,
  SUP,
  SUPE,
  INF,
  INFE,
  EG,
  DIFF,
  RD,
  RDLN,
  WRT,
  WRTLN,
  ADD,
  MOINS,
  DIV,
  NEG,
  MULT,
  INC,
  DEC,
  AND,
  OR,
  NOT,
  AFF,
  STOP,
  INDA,
  INDV
} Instr;

void interpreter(int instr) {
  switch (instr) {
  case LDA: {
    spx++;
    pilex[spx] =
        pcode[c0 +
              1]; // on met dans la pile d'execution la valeur suivante du code
    c0 += 2;
  } break;
  case LDV: {
    spx++;
    pilex[spx] = pilex[pcode[c0 + 1]]; // on met dans la pile d'execution la
                                       // valeur de la variable en parametre
                                       // dans le code apres ldv
    c0 += 2;
  } break;
  case LDC: {
    spx++;
    pilex[spx] =
        pcode[c0 +
              1]; // on met dans la pile d'execution la valeur suivante du code
    c0 += 2;
  } break;
  case JMP: {
    c0 = pcode[c0 + 1];
  } break;
  case JIF: {
    if (pilex[spx] == 0) {
      c0 = pcode[c0 + 1];
    } else {
      c0 += 2;
    }
  } break;
  case JSR: {
    // TODO
  } break;
  case RSR: {
    // TODO
  } break;
  case SUP: {
    spx--; // on descend car apres la comparaison, on pourra écraser une des 2
           // valeurs et ne garder que le booleen correspondant
    if (pilex[spx] > pilex[spx + 1]) {
      pilex[spx] = 1;
    } else {
      pilex[spx] = 0;
    }
    c0++;
  } break;
  case SUPE: {
    spx--;
    if (pilex[spx] >= pilex[spx + 1]) {
      pilex[spx] = 1;
    } else {
      pilex[spx] = 0;
    }
    c0++;
  } break;
  case INF: {
    spx--;
    if (pilex[spx] < pilex[spx + 1]) {
      pilex[spx] = 1;
    } else {
      pilex[spx] = 0;
    }
    c0++;
  } break;
  case INFE: {
    spx--;
    if (pilex[spx] <= pilex[spx + 1]) {
      pilex[spx] = 1;
    } else {
      pilex[spx] = 0;
    }
    c0++;
  } break;
  case EG: {
    spx--;
    if (pilex[spx] == pilex[spx + 1]) {
      pilex[spx] = 1;
    } else {
      pilex[spx] = 0;
    }
    c0++;
  } break;
  case DIFF: {
    spx--;
    if (pilex[spx] != pilex[spx + 1]) {
      pilex[spx] = 1;
    } else {
      pilex[spx] = 0;
    }
    c0++;
  } break;
  case RD: {
    int entier;
    spx++;
    scanf("%d",&entier);
    pilex[spx] = entier;
    c0++;
  } break;
  case RDLN: {
    int entier;
    spx++;
    scanf("%d",&entier);
    pilex[spx] = entier; 
    printf("\n");
    c0++;
  } break;
  case WRT: {
    printf("%d", pilex[spx]);
    spx++;
    c0++;
  } break;
  case WRTLN: {
    printf("%d\n", pilex[spx]);
    spx++;
    c0++;
  } break;
  case ADD: {
    spx--;
    pilex[spx] += pilex[spx + 1];
    c0++;
  } break;
  case MOINS: {
    spx--;
    pilex[spx] -=
        pilex[spx + 1]; // TODO a savoir si on fait 1-2 ou 2-1 pareil pour DIV
    c0++;
  } break;
  case DIV: {
    spx--;
    pilex[spx] /= pilex[spx + 1]; // TODO
    c0++;
  } break;
  case MULT: {
    spx--;
    pilex[spx] *= pilex[spx + 1];
    c0++;
  } break;
  case NEG: {
    pilex[spx] = -pilex[spx];
    c0++;
  } break;
  case INC: {
    pilex[spx]++;
    c0++;
  } break;
  case DEC: {
    pilex[spx]--;
    c0++;
  } break;
  case AND: {
  	spx--;
    pilex[spx] = pilex[spx] && pilex[spx + 1];
    c0++;
  } break;
  case OR: {
  	spx--;
    pilex[spx] = pilex[spx] || pilex[spx + 1];
    c0++;
  } break;
  case NOT: {
    pilex[spx] = (!pilex[spx]);
    c0++;
  } break;
  case AFF: {
    pilex[pilex[spx - 1]] = pilex[spx];
    spx = spx - 2;
    c0++;
  } break;
  case STOP: {
  } break;
  case INDA: {
    // TODO
  } break;
  case INDV: {
    // TODO
  } break;
  default: { } break; }
}

void exec() {
  while (pcode[c0] != STOP) {
    interpreter(pcode[c0]);
  }
}
