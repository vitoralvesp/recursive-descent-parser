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

    char *word;        // palavra inserida pelo usuario
    char *posfix;      // expressao posfixa da palavra inserida pelo usuario 
    char *aux_word;    // ponteiro auxiliar para percorrer cada caractere da palavra
    char *aux_posfix;  // ponteiro auxiliar para percorrer cada caractere da posfixa
    int result;        // resultado da expressao inserida pelo usuario

    posfix = (char *) malloc(50 * sizeof(char));
    word = (char *) malloc(50 * sizeof(char));
    aux_word = word;
    aux_posfix = posfix;
    result = 0;

    printf(">> insira uma palavra: ");
    fgets(word, 50, stdin);

    // Busca pelo ultimo caractere da palavra e adiciona o '\0' na proxima posicao
    while (*aux_word != '\0') {
        if (*aux_word == '\n') {
            *aux_word = '\0';
            break;
        }
        aux_word++;
    }

    // 'aux_word' volta a apontar para a primeira posicao de 'word', apos os incrementos realizados na repeticao acima
    aux_word = word;

    // 'expr' recebe os ponteiros auxiliares para garantir que nao existam erros de apontamento apos as incrementacoes sucessivas que serao realizadas
    result = expr(&aux_word, &aux_posfix);
    *aux_posfix = '\0';

    // A palavra é aceita se chegar ao final '\0'
    if (*aux_word == '\0') printf(">> resultado: %s => %s=%d OK", word, posfix, result);
    else printf(">> resultado: %s => palavra nao aceita por erro sintatico", word);

    free(word);
    free(posfix);

    return 0;
}

/**
 * @brief Reconhece os fatores da palavra
 * @details Os fatores são 1,2,3,4,5,6,7,8,9,(,)
 * @param word ponteiro de ponteiro para a palavra
 * @param posfix ponteiro de ponteiro para a expressao posfixa
 * @return retorna o resultado de uma expressao entre parenteses ou um inteiro de 1 a 9 
 */
int factor(char **word, char** posfix) {
    int result;
    char number;

    switch(**word) {
        case '(':
            (*word)++;
            result = expr(word, posfix);
            if (**word == ')') {
                (*word)++;
                return result;
            } else {
                printf(">> resultado: erro sintatico");
                exit(1);
            }
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            number = **word;      
            *(*posfix)++ = number;
            (*word)++;
            return number - '0';
        
    }
}

/**
 * @brief Reconhece os termos da palavra
 * @param word ponteiro de ponteiro para a palavra
 * @param posfix ponteiro de ponteiro para a expressao posfixa
 * @return retorna o resultado de um termo
 */
int term(char **word, char** posfix) {
    int result = factor(word, posfix);
    return term_(word, posfix, result);
}

/**
 * @brief Função auxiliar ao 'term' para obter o resultado de um termo
 * @param word ponteiro de ponteiro para a palavra
 * @param posfix ponteiro de ponteiro para a expressao posfixa
 * @param result resultado de um termo
 * @return retorna o resultado de um termo
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
 * @brief Reconhece as expressoes da palavra
 * @param word ponteiro de ponteiro para a palavra
 * @param posfix ponteiro de ponteiro para a expressao posfixa
 * @return retorna o resultado de uma expressao
 */
int expr(char **word, char** posfix) {
    int result = term(word, posfix);
    return expr_(word, posfix, result);
}

/**
 * @brief Função auxiliar à 'expr' para obter o resultado de uma expressao
 * @param word ponteiro de ponteiro para a palavra
 * @param posfix ponteiro de ponteiro para a expressao posfixa
 * @param result resultado de uma expressao
 * @return retorna o resultado de uma expressao
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