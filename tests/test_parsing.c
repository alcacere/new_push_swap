// tests/test_parsing.c

#include <stdio.h>
#include <assert.h>
#include "../include/push_swap.h" 

void run_test(char *test_name, int argc, char **argv, int expected_result)
{
    printf("Test: %-30s -> ", test_name);
    
    int result = check_args(argc, argv); 
    
    if (result == expected_result)
        printf("\033[0;32m[OK]\033[0m\n");
    else
        printf("\033[0;31m[KO] Esperaba %d, obtuve %d\033[0m\n", expected_result, result);
}

int main(void)
{
    printf("=== INICIANDO TESTS DE PARSING ===\n");

    // Tests Basicos
    char *args1[] = {"./push_swap", "1", "2", "3", "-4", "5"};
    run_test("Numeros validos simples", 6, args1, 1);

    char *args2[] = {"./push_swap", "1", "dos", "3"};
    run_test("Caracteres invalidos", 4, args2, 0);

    char *args3[] = {"./push_swap", "1", "2147483648", "3"};
    run_test("Integer Overflow", 4, args3, 0);

    char *args4[] = {"./push_swap", "1", "2", "3", "2"};
    run_test("Numeros duplicados simples", 5, args4, 0);

    // Tests OKEOSOS (Evaluacion de 42)
    char *args5[] = {"./push_swap", "123", "12", "4", "58 34 22 6", "75"};
    run_test("String con multiples nums", 6, args5, 1);

    char *args6[] = {"./push_swap", "123", "      4727 77899 23424534   "};
    run_test("String con espacios extremos", 3, args6, 1);

    char *args7[] = {"./push_swap", "1", " 2 a 3 "};
    run_test("Letra escondida en string", 3, args7, 0);

    char *args8[] = {"./push_swap", "1", ""};
    run_test("Argumento vacio (comillas)", 3, args8, 0);

    char *args9[] = {"./push_swap", "1", "     "};
    run_test("Solo espacios en comillas", 3, args9, 0);

    return (0);
}