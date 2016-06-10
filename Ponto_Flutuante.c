#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct FloatingPoint {
    char signal;
    char exponent[9];//caractere extra por causa do \0
    char mantissa[23];//caractere extra por causa do \0
};

//o to Left e Rigth podem virar um funcao só ps: fazer direito fds
struct FloatingPoint toLeft(struct FloatingPoint floating_point, char signal, char *string);//trata o caso onde vc deve andar com a virgula para esquerda
struct FloatingPoint toRight(struct FloatingPoint floating_point, char signal, char *string);//trata o caso onde vc deve andar com a virgula para direita
int verify(char *string);//verifica se o input é valido;

int main() {
    char number[1024];
	char *n=number;
    struct FloatingPoint floating_point;
    printf("Informe o valor: ");
    scanf("%s*C", n);
	floating_point.signal='0';
	switch (n[0]){//remove sinal
		case '-':floating_point.signal='1';
		case '|':n++;
	}
	switch (verify(n)){
		case 0:floating_point=toLeft(floating_point,floating_point.signal,n);break;
		case 1:floating_point=toRight(floating_point,floating_point.signal,n);break;
		case 2:strcpy(floating_point.exponent,"00000000");
			   strcpy(floating_point.mantissa,"00000000000000000000000000000000");break;
		case 3:strcpy(floating_point.exponent,"11111111");
			   strcpy(floating_point.mantissa,"00000000000000000000000000000000");break;
		default:printf("ERROR.");return 0;
	}
	floating_point.exponent[8]='\0';//bugava sem ele
	floating_point.mantissa[23]='\0';
    printf("Signal:%c\nExponent:%s\nMantissa:%s", floating_point.signal, floating_point.exponent, floating_point.mantissa);
    
    return 0;
}

struct FloatingPoint toLeft(struct FloatingPoint floating_point, char signal, char *string){
	int cont=0,i=0,j;
	floating_point.signal=signal;//só repete o sinal pro retorno
	while(*string!='1') string++;//ignora os zeros de numeros como 00001,
	string++;
	while(*string!=',' && *string!='\0'){//conta o expoente
		if(cont<23)floating_point.mantissa[cont]=*string;
		cont++;
		string++;
	}
	if(*string==',') string++;//pula a ,
	j=127+cont;//calcula o expoente
	for (i=7;i>=0;i--){
		if(j==0)floating_point.exponent[i]='0';
		else {
			floating_point.exponent[i]= j%2 + '0';
			j=j/2;
		}
	}
	while(cont<23 ){//preenche a mantissa
		if(*string=='\0') {//caso o vetor acabe preeenche com 0
			floating_point.mantissa[cont]='0';
			cont++;
		}
		else {
			floating_point.mantissa[cont]=*string;
			cont++;
			string++;
		}
	}
		
	return (floating_point);
}

struct FloatingPoint toRight(struct FloatingPoint floating_point, char signal, char *string) {
	int cont=1,j,i=0;
	floating_point.signal=signal;
	while(*string!=',') string++;//como nao há nehum 1 antes da virgula garantido pela verify posiciona o numero depois da virgula em casos de input como 00000,
	string++;
	while(*string!='1'){//conta o expoente
		cont++;
		string++;
		if(cont==127){//caso nao formalizado
			strcpy(floating_point.exponent,"00000000");
			for (i=0;i<32;i++){
				if(*string=='\0') floating_point.mantissa[i]='0';
				else{
					floating_point.mantissa[i]=*string;
					string++;
				}
			}
			return (floating_point);
		}
	}
	j=127-cont;//calcula o expoente
	for (i=7;i>=0;i--){
		if(j==0)floating_point.exponent[i]='0';
		else {
			floating_point.exponent[i]= j%2 + '0';
			j=j/2;
		}
	}
	while(i<23){//calcula a mantissa
		if(*string=='\0'){
			floating_point.mantissa[i]='0';
			i++;
		}
		else{
			floating_point.mantissa[i]=*string;
			i++;
			string++;
		}
	}
	return (floating_point);
}

int verify(char *string){
	int i=0,flag=0;
	/*   flag status: 0 - s/ 1 e ,
				   1 - s/ ,
				   2 - a direita
				   3 - a esquerda
				   4 - s/ 1   */
	if (*string=='i' && *(string+1)=='n' && *(string+2)=='f') return 3;
	while (*(string+i)!='\0') {
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
		i++;
	}
	switch (flag){
		case 0:return 2;
		case 1:return 0;
		case 2:return 1;
		case 3:return 0;
		case 4:return 2;
		default :return -3;
	}
}