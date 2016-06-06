#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct floating_point {
    char signal;
    char exponent[8];
    char mantissa[23];
};


struct floating_point toLeft(struct floating_point floating_point, char signal, char *string);//trata o caso onde vc deve andar com a virgula para esquerda
struct floating_point toRight(struct floating_point floating_point, char signal, char *string);//trata o caso onde vc deve andar com a virgula para direita
int verify(char *string);//verifica se o input é valido;

int main() {
    char number[1024];
	char *n=number;
    struct floating_point floating_point;
    printf("Informe o valor: ");
    scanf("%s*C", n);
	floating_point.signal='0';
	switch (n[0]){//remove sinal
		case '-':floating_point.signal='1';
		case '|':n++;
	}
	switch (verify(n)){
		case 0:floating_point=toLeft(floating_point,floating_point.signal,n);break;
		case 1:toRight(floating_point,floating_point.signal,n);break;
		case 2:strcpy(floating_point.exponent,"00000000");
			   strcpy(floating_point.mantissa,"00000000000000000000000000000000");break;
		case 3:strcpy(floating_point.exponent,"11111111");
			   strcpy(floating_point.mantissa,"00000000000000000000000000000000");break;
		default:printf("ERROR.");return 0;
	}
    printf("Signal:%c\nExponent:%s\nMantissa:%s", floating_point.signal, floating_point.exponent, floating_point.mantissa);
    
    return 0;
}

struct floating_point toLeft(struct floating_point floating_point, char signal, char *string){//em construcao
	int cont=0,i=0;
	floating_point.signal=signal;
	while(*string!='1') string++;
	while(*(string+1)!=','){
		cont++;
	}
}

struct floating_point toRight(struct floating_point floating_point, char signal, char *string) {
	
}

int verify(char *string){
	printf("\n%s\n",string);
	int i=0,flag=0;
	/*   flag status: 0 - s/ 1 e ,
				   1 - s/ ,
				   2 - a direita
				   3 - a esquerda
				   4 - s/ 1   */
	if (*string=='i' && *(string+1)=='n' && *(string+2)=='f') return 3;
	while (*(string+i)!='\0') {
		
	printf("\n%c\n",*(string+i));
		switch (*(string+i)) {
			case ',':if (flag==4 || flag==3) return -2;
					 if (flag==0) flag=4;
					 if (flag==1) flag=3;
					 break;
			case '1':if (flag==4) flag=2;
					 if (flag==0) flag=1;
					 break;
			default : if(*(string+i)!='0') return -1;
		}
		printf("\n\n\n	%d	\n\n\n",flag);
		i++;
	}
	printf("\n%d\n",flag);
	switch (flag){
		case 0:return 2;
		case 1:return 0;
		case 2:return 1;
		case 4:return 2;
		default :return -3;
	}
}