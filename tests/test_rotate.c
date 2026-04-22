#include <stdio.h>
#include <stdlib.h>
#include "../include/push_swap.h"
#include "../include/instructions.h"

void run_test(char *test_name, int condition)
{
    printf("Test: %-40s -> ", test_name);
    if (condition)
        printf("\033[0;32m[OK]\033[0m\n");
    else
        printf("\033[0;31m[KO]\033[0m\n");
}

t_node *create_mock_node(int val)
{
    t_node *n = malloc(sizeof(t_node));
    n->value = val;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

int main(void)
{
    t_stack a;
    t_stack b;

    printf("=== TESTS ASALTO 2: ROTATE & REVERSE ===\n\n");

    init_stacks(&a, &b);

    /* Llenamos el Stack A:
       El Stack quedará: TOP-> 10, 20, 30 <-BOTTOM */
    push_node(&a, create_mock_node(30));
    push_node(&a, create_mock_node(20));
    push_node(&a, create_mock_node(10));

    /* --- TEST 1: ROTATE (ra) --- */
    printf("--- Probando ROTATE (ra) ---\n");
    // El 10 debe irse al fondo. El 20 debe subir al top.
    ra(&a, true); 
    run_test("ra: Nuevo Top es 20", a.top->value == 20);
    run_test("ra: Nuevo Bottom es 10", a.bottom->value == 10);
    run_test("ra: Top->prev es NULL", a.top->prev == NULL);
    run_test("ra: Bottom->next es NULL", a.bottom->next == NULL);
    run_test("ra: Size sigue siendo 3", a.size == 3);


    /* --- TEST 2: REVERSE ROTATE (rra) --- */
    printf("\n--- Probando REVERSE ROTATE (rra) ---\n");
    // El 10 (que ahora esta en el fondo) vuelve a la cima.
    rra(&a, true);
    run_test("rra: Top vuelve a ser 10", a.top->value == 10);
    run_test("rra: Bottom vuelve a ser 30", a.bottom->value == 30);
    run_test("rra: Top->next es 20", a.top->next->value == 20);
    run_test("rra: Bottom->prev es 20", a.bottom->prev->value == 20);


    /* --- TEST 3: EDGE CASES (Casos Límite) --- */
    printf("\n--- Probando CASOS LIMITE ---\n");
    rb(&b, true); // B está vacío
    run_test("rb en stack vacio: No explota", b.size == 0);

    rrb(&b, true); // B está vacío
    run_test("rrb en stack vacio: No explota", b.size == 0);

    push_node(&b, create_mock_node(42)); // B tiene 1 elemento
    rb(&b, true); 
    rrb(&b, true);
    run_test("rb/rrb con 1 elemento: No explotan", b.size == 1 && b.top->value == 42 && b.bottom->value == 42);

    free_stack(&a);
    free_stack(&b);
    printf("\n=== TESTS FINALIZADOS ===\n");
    return (0);
}