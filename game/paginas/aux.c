#include <stdio.h>

typedef struct node{
    char question[50];
    char op1[20];
    char op2[20];
    char op3[20];
    int correct;
} Question1;

typedef struct node2{
    char* question;
    char op1[20];
    char op2[20];
    int correct;
} Question2;



int main(){

    FILE* archivo;
    Question1 q1;
    Question2 q2;

//para agregar

    archivo = fopen("preguntas.txt", "a");
    if (archivo != NULL)
    {
        printf("Ingrese la pregunta: ");
        scanf("%s", q1.question);
        printf("Ingrese la opcion 1: ");
        scanf("%s", q1.op1);
        printf("Ingrese la opcion 2: ");
        scanf("%s", q1.op2);
        printf("Ingrese la opcion 3: ");
        scanf("%s", q1.op3);
        printf("Ingrese la respuesta correcta: ");
        scanf("%d", &q1.correct);
        fprintf(archivo, "%s %s %s %s %d \n", q1.question, q1.op1, q1.op2, q1.op3, q1.correct);
        fclose(archivo);
    }
    else
    {
        printf("No se pudo abrir el archivo");
    }

//para leer

    // archivo = fopen("preguntas.txt", "r");
    // if (archivo != NULL)
    // {
    //     while (!feof(archivo))
    //     {
    //         fscanf(archivo, "%s %s %s %s %d \n", q1.question, q1.op1, q1.op2, q1.op3, &q1.correct);
    //         printf("%s %s %s %s %d \n", q1.question, q1.op1, q1.op2, q1.op3, q1.correct);
    //     }
    //     fclose(archivo);
    // }
    // else
    // {
    //     printf("No se pudo abrir el archivo");
    // }

    return 0;
}