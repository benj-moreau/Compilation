
char **pilex;
int spx;

char **pcode;
int co;

void init(){
	pilex = malloc(100*sizeof(char*));
	spx=0;

	pcode = malloc(100*sizeof(char*));
	co=0;

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
	case LDA:
	
	break;
	case LDV:
	break;
	case LDC:
	
    break;
	case JMP:
    break;
	case JIF:
    break;
	case JSR:
    break;
	case RSR:
    break;
	case SUP:
    break;
	case SUPE:
    break;
	case INF:
    break;
	case INFE:
    break;
	case EG:
    break;
	case DIFF:
    break;
	case RD:
    break;
	case RDLN:
    break;
	case WRT:
    break;
	case WRTLN:
    break;
	case ADD:
    break;
	case MOINS:
    break;
	case DIV:
    break;
	case NEG:
    break;
	case MULT:
    break;
	case INC:
    break;
	case DEC:
    break;
	case AND:
    break;
	case OR:
    break;
	case NOT:
    break;
	case AFF:
	
    break;
	case STOP:
	
    break;
	case INDA:
    break;
	case INDV:
	default:
	break;
	}
}
int main() {
init();
return 0;
}
