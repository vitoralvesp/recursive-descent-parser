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
 * 
 */

#include <stdio.h>
#include <stdlib.h>

// Gramática
int expr(char **word);
int expr_(char **word);
int term(char **word);
int term_(char **word);
int factor(char **word);

int main() {

    char *word = (char *) malloc(50 * sizeof(char));
    char *aux = word;

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
    expr(&aux);

    // A palavra é aceita se chegar ao final \0
    if (*word == '\0') printf("\nstatus: palavra aceita!!");
    else printf("\nstatus: palavra não aceita!!");

    free(word);

    return 0;
}

/**
 * @brief Reconhece os fatores da palavra
 * @details Os fatores são 1,2,3,4,5,6,7,8,9,(,)
 */
int factor(char **word) {
    switch(**word) {
        case '(':
            (*word)++;
            expr(word);
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
            (*word)++;
            break;
        default:
            break;
    }
}

/**
 * @brief Reconhece os termos da palavra 
 */
int term(char **word) {
    factor(word);
    term_(word);
}

/**
 * @brief Função auxiliar ao 'term' 
 */
int term_(char **word) {
    switch(**word) {
        case '*':
            (*word)++;
            factor(word);
            term_(word);
            break;
        case '/':
            (*word)++;
            factor(word);
            term_(word);
            break;
        case '%':
            (*word)++;
            factor(word);
            term_(word);
            break;
        default:
            factor(word);
            break;
    }
}

/**
 * @brief Reconhece as expressões da palavra
 */
int expr(char **word) {
    term(word);
    expr_(word);
    return 0;
}

/**
 * @brief Função auxiliar à 'expr' 
 */
int expr_(char **word) {
    switch(**word) {
        case '+':
            (*word)++;
            term(word);
            expr_(word);
            break;
        case '-':
            (*word)++;
            term(word);
            expr_(word);
            break;
        default:
            term(word);
            break;
    }
}