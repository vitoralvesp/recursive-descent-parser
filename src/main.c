/**
 * @brief Avaliador de Expressoes Aritmeticas
 * @details Avaliador de expressoes utilizando um Analisador Sintatico Descendente Recursivo (ASDR) para as gramaticas apresentadas
 * @date 20-05-2025
 * @version 1.0
 * @authors Jessica Bispo (10410798); Vitor Alves Pereira (10410862)
 * 
 * ----------------------------------------------------------------------
 * 
 * Fatoração da Gramática:
 * expr   -> term expr'
 * expr'  -> + term expr' | - term expr' | term | ε
 * term   -> factor term'
 * term'  -> * factor term' | % factor term' | ε
 * factor -> num | (expr)
 * 
 * -----------------------------------------------------------------------
 * 
 * Referências:
 * [1] https://www.geeksforgeeks.org/fgets-function-in-c/
 * [2] https://github.com/zewuchen/asdr/blob/master/asdr.c
 * [3] https://www.geeksforgeeks.org/implement-stack-using-array/
 */

#include <stdio.h>
#include <stdlib.h>

// Gramática
int expr(char **word, char** posfix);
int expr_(char **word, char** posfix);
int term(char **word, char** posfix);
int term_(char **word, char** posfix);
int factor(char **word, char** posfix);

// Estrutura da Pilha
struct Stack {
    int top;
    int capacity;
    int *array;
};

struct Stack *stack;

struct Stack *createStack(int capacity);
void deleteStack(struct Stack *stack);
int isFull(struct Stack *stack);
int isEmpty(struct Stack *stack);
int push(struct Stack *stack, int x);
int pop(struct Stack *stack);
int peek(struct Stack *stack);

int main() {

    char *posfix = (char *) malloc(50 * sizeof(char));
    char *word = (char *) malloc(50 * sizeof(char));
    char *aux = word;

    stack = createStack(50);

    printf(">> enter a word: ");
    fgets(word, 50, stdin);

    // Adiciona \0 na após o último caractere da palavra
    while (*aux != '\0') {
        if (*aux == '\n') {
            *aux = '\0';
            break;
        }
        aux++;
    }

    // Impede erro de referência ao utilizar o free
    // word++ afeta a referencia 
    aux = word;
    expr(&aux, &posfix);

    // A palavra é aceita se chegar ao final \0
    if (*aux == '\0') printf(">> %s => palavra aceita!!", posfix);
    else printf(">> status: palavra não aceita!!");

    free(word);
    // free(posfix);

    return 0;
}

/**
 * @brief Reconhece os fatores da palavra
 * @details Os fatores são 1,2,3,4,5,6,7,8,9,(,)
 */
int factor(char **word, char** posfix) {
    switch(**word) {
        case '(':
            (*word)++;
            expr(word, posfix);
            if (**word == ')') {
                (*word)++;
                break;
            } else return 1;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            *(*posfix)++ = **word;
            (*word)++;
            break;
        default:
            break;
    }
}

/**
 * @brief Reconhece os termos da palavra 
 */
int term(char **word, char** posfix) {
    factor(word, posfix);
    term_(word, posfix);
}

/**
 * @brief Função auxiliar ao 'term' 
 */
int term_(char **word, char** posfix) {
    int calc = 0;
    char op;
    switch(**word) {
        case '*':
            op = **word;
            (*word)++;
            factor(word, posfix);
            *(*posfix)++ = op;
            term_(word, posfix);
            break;
        case '/':
            op = **word;
            (*word)++;
            factor(word, posfix);
            *(*posfix)++ = op;
            term_(word, posfix);
            break;
        case '%':
            op = **word;
            (*word)++;
            factor(word, posfix);
            *(*posfix)++ = op;
            term_(word, posfix);
            break;
        default:
            factor(word, posfix);
            break;
    }
}

/**
 * @brief Reconhece as expressões da palavra
 */
int expr(char **word, char** posfix) {
    term(word, posfix);
    expr_(word, posfix);
    return 0;
}

/**
 * @brief Função auxiliar à 'expr' 
 */
int expr_(char **word, char** posfix) {
    char op;
    switch(**word) {
        case '+':
            op = **word;
            (*word)++;
            term(word, posfix);
            *(*posfix)++ = op;
            expr_(word, posfix);
            break;
        case '-':
            op = **word;
            (*word)++;
            term(word, posfix);
            *(*posfix)++ = op;
            expr_(word, posfix);
            break;
        default:
            term(word, posfix);
            break;
    }
}

/**
 *
 */
struct Stack *createStack(int capacity) {
    struct Stack *stack = (struct Stack*) malloc (sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *) malloc(capacity * sizeof(int));
    return stack;
}

/**
 * 
 */
void deleteStack(struct Stack *stack) {
    free(stack->array);
    free(stack);
}

/**
 * 
 */
int isFull(struct Stack *stack) {
    return stack->top >= stack->capacity-1;
}

/**
 * 
 */
int isEmpty(struct Stack *stack) {
    return stack->top < 0;
}

/**
 * 
 */
int push(struct Stack *stack, int x) {
    if (isFull(stack)) return 1;
    stack->array[++stack->top] = x;
    return 0;
}

/**
 * 
 */
int pop(struct Stack *stack) {
    if (isEmpty(stack)) return 1;
    return stack->array[stack->top--];
}

/**
 * 
 */
int peek(struct Stack *stack) {
    if (isEmpty(stack)) return 0;
    return stack->array[stack->top];
}