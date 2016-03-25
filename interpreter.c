
int *pilex;
int spx;

int* pcode;
int c0;

void init(){
	pilex = malloc(100*sizeof(int));
	spx=0;

	pcode = malloc(100*sizeof(int));
	c0=0;

}

typedef enum{
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
}Instr;


void interpreter(int instr){
	switch (instr){
	case LDA:{
		spx++;
		pilex[spx] = pcode[c0+1]; // on met dans la pile d'execution la valeur suivante du code
		c0+=2;
	}break;
	case LDV:{
		spx++;
		pilex[spx] = pilex[pcode[c0+1]];// on met dans la pile d'execution la valeur de la variable en parametre dans le code apres ldv
		c0+=2;
	}break;
	case LDC:{
		spx++;
		pilex[spx] = pcode[c0+1];// on met dans la pile d'execution la valeur suivante du code
		c0+=2;
    }break;
	case JMP:{
		c0=pcode[c0+1];
    }break;
	case JIF:{
		if(pilex[spx]==0){
			c0=pcode[c0+1];
		}else{
			c0+=2;
		}
    }break;
	case JSR:{
    }break;
	case RSR:{
    }break;
	case SUP:{
		spx--; // on descend car apres la comparaison, on pourra écraser une des 2 valeurs et ne garder que le booleen correspondant
		if(pilex[spx]>pilex[spx+1]){
			pilex[spx] = 1;
		}else{
			pilex[spx] = 0;
		}
		c0++;
    }break;
	case SUPE:{
		spx--; 
		if(pilex[spx] >= pilex[spx+1]){
			pilex[spx] = 1;
		}else{
			pilex[spx] = 0;
		}
		c0++;
    }break;
	case INF:{
		spx--; 
		if(pilex[spx] < pilex[spx+1]){
			pilex[spx] = 1;
		}else{
			pilex[spx] = 0;
		}
		c0++;
    }break;
	case INFE:{
		spx--; 
		if(pilex[spx] <= pilex[spx+1]){
			pilex[spx] = 1;
		}else{
			pilex[spx] = 0;
		}
		c0++;
    }break;
	case EG:{
		spx--; 
		if(pilex[spx] == pilex[spx+1]){
			pilex[spx] = 1;
		}else{
			pilex[spx] = 0;
		}
		c0++;
    }break;
	case DIFF:{
		spx--; 
		if(pilex[spx] != pilex[spx+1]){
			pilex[spx] = 1;
		}else{
			pilex[spx] = 0;
		}
		c0++;
    }break;
	case RD:{
    }break;
	case RDLN:{
    }break;
	case WRT:{
    }break;
	case WRTLN:{
    }break;
	case ADD:{
    }break;
	case MOINS:{
    }break;
	case DIV:{
    }break;
	case NEG:{
    }break;
	case MULT:{
    }break;
	case INC:{
    }break;
	case DEC:{
    }break;
	case AND:{
    }break;
	case OR:{
    }break;
	case NOT:{
    }break;
	case AFF:{
	
    }break;
	case STOP:{
	
    }break;
	case INDA:{
    }break;
	case INDV:{
	}break;
	default:{
	}break;
	
	}
}
int main() {
init();
return 0;
}
