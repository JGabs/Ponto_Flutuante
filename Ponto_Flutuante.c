#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct binaryFloat {
    char signal;
    char index[9];
    char matissa[24];
};

void to_struct(struct binaryFloat * number, char * n);//converte a string de entrada na estruta binaryFloat
void signal(struct binaryFloat * number);//sub-funcao de to_struct para separar o sinal
void index(struct binaryFloat * number);//sub-funcao de to_struct para calcular o expoente
void matissa(struct binaryFloat * number);//sub-funcao de to_struct para calcular a matissa junto com index
void special(struct binaryFloat * number, char * n);//trata os casos especiais de infinito, zero, e not a number
void denormalized(struct binaryFloat * number, char * n);//trata o caso de numeros que comecam com zero (Ex.: 0,011001)

int main() {
    char n[];//inserir um tamanho maximo para o numero de entrada
    struct binaryFloat * number = (struct binaryFloat *) malloc(sizeof(struct binaryFloat));

    printf("Informe o valor: ");
    scanf("%s*C", n);

    if (
        (strstr (n, "inf") != NULL)
        ||
        (strstr (n, "NaN") != NULL)
        ||
        (n == '0')
        ||
        (n == '-0')
    )
        special(number, n);
    else if (strstr (n, '0,') != NULL)
        denormalized(number, n);
     else
        to_struct(number, n);

    printf("%c%s%s", number -> signal, number -> index, number -> mantissa);
    
    return 0;
}
