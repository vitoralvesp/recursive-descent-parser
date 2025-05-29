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
int expr_(char **word, char** posfix, int result);
int term(char **word, char** posfix);
int term_(char **word, char** posfix, int result);
int factor(char **word, char** posfix);

int main() {

    char *posfix = (char *) malloc(50 * sizeof(char));
    char *word = (char *) malloc(50 * sizeof(char));
    char *aux_word = word;
    char *aux_posfix = posfix;
    int result = 0;

    printf(">> insira uma palavra: ");
    fgets(word, 50, stdin);

    // Adiciona \0 na após o último caractere da palavra
    while (*aux_word != '\0') {
        if (*aux_word == '\n') {
            *aux_word = '\0';
            break;
        }
        aux_word++;
    }

    // Impede erro de referência ao utilizar o free
    // word++ afeta a referencia 
    aux_word = word;
    result = expr(&aux_word, &aux_posfix);

    *aux_posfix = '\0';

    // A palavra é aceita se chegar ao final \0
    if (*aux_word == '\0') printf(">> resultado: %s => %s=%d OK", word, posfix, result);
    else printf(">> resultado: %s => palavra nao aceita por erro sintatico", word);

    free(word);
    free(posfix);

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
            int result = expr(word, posfix);
            if (**word == ')') {
                (*word)++;
                return result;
            } else exit(1);
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            char value = **word;      
            *(*posfix)++ = value;
            (*word)++;
            return value - '0';
    }
}

/**
 * @brief Reconhece os termos da palavra 
 */
int term(char **word, char** posfix) {
    int result = factor(word, posfix);
    return term_(word, posfix, result);
}

/**
 * @brief Função auxiliar ao 'term' 
 */
int term_(char **word, char** posfix, int result) {
    int factor_result;
    char op;
    switch(**word) {
        case '*':
            op = **word;
            (*word)++;
            factor_result = factor(word, posfix);
            *(*posfix)++ = op;
            return term_(word, posfix, result * factor_result);
        case '/':
            op = **word;
            (*word)++;
            factor_result = factor(word, posfix);
            *(*posfix)++ = op;
            return term_(word, posfix, result / factor_result);
        case '%':
            op = **word;
            (*word)++;
            factor_result = factor(word, posfix);
            *(*posfix)++ = op;
            return term_(word, posfix, result % factor_result);
        default:
            return result;
    }
}

/**
 * @brief Reconhece as expressões da palavra
 */
int expr(char **word, char** posfix) {
    int result = term(word, posfix);
    return expr_(word, posfix, result);
}

/**
 * @brief Função auxiliar à 'expr' 
 */
int expr_(char **word, char** posfix, int result) {
    int term_result;
    char op;
    switch(**word) {
        case '+':
            op = **word;
            (*word)++;
            term_result = term(word, posfix);
            *(*posfix)++ = op;
            return expr_(word, posfix, result + term_result);
        case '-':
            op = **word;
            (*word)++;
            term_result = term(word, posfix);
            *(*posfix)++ = op;
            return expr_(word, posfix, result - term_result);
        default:
            return result;
    }
}