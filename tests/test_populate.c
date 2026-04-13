/* tests/test_populate.c */

#include <stdio.h>
#include <stdlib.h>
#include "../include/push_swap.h"

void run_test(char *test_name, int condition)
{
    printf("Test: %-40s -> ", test_name);
    if (condition)
        printf("\033[0;32m[OK]\033[0m\n");
    else
        printf("\033[0;31m[KO]\033[0m\n");
}

int main(void)
{
    t_stack a;
    t_stack b;
    
    // Simulamos un argv maligno (con strings mixtas)
    char *args[] = {"./push_swap", "42", "  -21   0", "100", NULL};

    printf("=== INICIANDO TESTS DE POPULATION ===\n\n");

    init_stacks(&a, &b);
    populate_stack_a(&a, args);

    // El stack deberia ser: TOP-> 42, -21, 0, 100 <-BOTTOM
    run_test("Size = 4", a.size == 4);
    run_test("TOP value = 42", a.top->value == 42);
    run_test("TOP->next value = -21", a.top->next->value == -21);
    run_test("BOTTOM value = 100", a.bottom->value == 100);
    run_test("BOTTOM->prev value = 0", a.bottom->prev->value == 0);

    free_stack(&a); // Evitamos leaks en el test
    printf("\n=== TESTS FINALIZADOS ===\n");
    return (0);
}