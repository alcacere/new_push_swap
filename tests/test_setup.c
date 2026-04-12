/* tests/test_setup.c */

#include <stdio.h>
#include <stdlib.h>
#include "../include/push_swap.h"

/* Helper para imprimir resultados */
void run_test(char *test_name, int condition)
{
    printf("Test: %-40s -> ", test_name);
    if (condition)
        printf("\033[0;32m[OK]\033[0m\n");
    else
        printf("\033[0;31m[KO]\033[0m\n");
}

/* Helper para crear nodos falsos rápidos para testear */
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
    t_node  *popped;

    printf("=== INICIANDO TESTS DE STACK SETUP ===\n\n");

    /* TEST 1: Inicialización */
    init_stacks(&a, &b);
    run_test("init_stacks: sizes = 0", a.size == 0 && b.size == 0);
    run_test("init_stacks: top/bottom NULL", a.top == NULL && a.bottom == NULL);

    /* TEST 2: Push del primer nodo (Edge case) */
    t_node *node1 = create_mock_node(42);
    push_node(&a, node1);
    run_test("push_node (1st): size = 1", a.size == 1);
    run_test("push_node (1st): top == bottom", a.top == node1 && a.bottom == node1);

    /* TEST 3: Push de un segundo nodo (Lista doble enlazada) */
    t_node *node2 = create_mock_node(21);
    push_node(&a, node2);
    run_test("push_node (2nd): size = 2", a.size == 2);
    run_test("push_node (2nd): top != bottom", a.top == node2 && a.bottom == node1);
    run_test("push_node (2nd): enlaces dobles (next)", a.top->next == node1);
    run_test("push_node (2nd): enlaces dobles (prev)", a.bottom->prev == node2);

    /* TEST 4: Pop del nodo superior (node2) */
    popped = pop_node(&a);
    run_test("pop_node: retorna nodo correcto", popped == node2);
    run_test("pop_node: size actualiza a 1", a.size == 1);
    run_test("pop_node: top vuelve a ser node1", a.top == node1);
    run_test("pop_node: prev del nuevo top es NULL", a.top->prev == NULL);
    free(popped);

    /* TEST 5: Pop del último nodo (vaciar stack) */
    popped = pop_node(&a);
    run_test("pop_node (last): retorna nodo correcto", popped == node1);
    run_test("pop_node (last): size = 0", a.size == 0);
    run_test("pop_node (last): top y bottom = NULL", a.top == NULL && a.bottom == NULL);
    free(popped);

    /* TEST 6: Pop de un stack vacío (Safe guard) */
    popped = pop_node(&a);
    run_test("pop_node (empty): retorna NULL", popped == NULL);

    printf("\n=== TESTS FINALIZADOS ===\n");
    return (0);
}