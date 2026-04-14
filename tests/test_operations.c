/* tests/test_operations.c */

#include <stdio.h>
#include <stdlib.h>
#include "../include/push_swap.h"
#include "../include/instructions.h"

void run_test(char *test_name, int condition)
{
    printf("Test: %-35s -> ", test_name);
    if (condition)
        printf("\033[0;32m[OK]\033[0m\n");
    else
        printf("\033[0;31m[KO]\033[0m\n");
}

/* Helper para inyectar nodos rápido en los tests */
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

    printf("=== TESTS ASALTO 1: PUSH & SWAP ===\n\n");

    init_stacks(&a, &b);

    /* Llenamos el Stack A usando push_node (LIFO). 
       Para que el 10 quede arriba, metemos primero 30, luego 20, luego 10 */
    push_node(&a, create_mock_node(30));
    push_node(&a, create_mock_node(20));
    push_node(&a, create_mock_node(10));

    /* --- TEST 1: SWAP (sa) --- */
    printf("--- Probando SWAP (sa) ---\n");
    sa(&a, true); // true = modo silencioso (no imprime "sa\n")
    run_test("sa: Top ahora es 20", a.top->value == 20);
    run_test("sa: Segundo ahora es 10", a.top->next->value == 10);
    run_test("sa: Bottom sigue siendo 30", a.bottom->value == 30);
    run_test("sa: Enlaces prev correctos", a.top->next->prev == a.top);


    /* --- TEST 2: PUSH (pb) --- */
    printf("\n--- Probando PUSH (pb) ---\n");
    pb(&a, &b, true); // Pasamos el 20 (que estaba en el top de A) al B
    run_test("pb: Size de B es 1", b.size == 1);
    run_test("pb: Top de B es 20", b.top->value == 20);
    run_test("pb: Size de A es 2", a.size == 2);
    run_test("pb: Nuevo Top de A es 10", a.top->value == 10);


    /* --- TEST 3: PUSH (pa) --- */
    printf("\n--- Probando PUSH (pa) ---\n");
    pa(&a, &b, true); // Devolvemos el 20 al Stack A
    run_test("pa: Size de A vuelve a 3", a.size == 3);
    run_test("pa: Top de A vuelve a ser 20", a.top->value == 20);
    run_test("pa: Size de B es 0", b.size == 0);
    run_test("pa: Top de B es NULL", b.top == NULL);

/* --- TEST 4: EDGE CASES (Casos Límite anti-Segfaults) --- */
    printf("\n--- Probando CASOS LIMITE ---\n");
    sb(&b, true); // B está vacío
    run_test("sb en stack vacio: No explota", b.size == 0);

    push_node(&b, create_mock_node(99)); // B tiene 1 elemento
    sb(&b, true); 
    run_test("sb con 1 elemento: No explota", b.size == 1 && b.top->value == 99);

    /* Vaciamos B de golpe pasándolo a A */
    pb(&b, &a, true); // B se queda vacío (size 0), A recibe el 99 (size 4)
    
    /* ¡AQUÍ ESTÁ LA MAGIA ARREGLADA! Intentamos sacar de B estando vacío */
    pb(&b, &a, true); // Debería retornar inmediatamente sin hacer nada
    pb(&a, &a, true); // Debería retornar inmediatamente sin hacer nada
    
    run_test("pb en stack vacio: No explota", a.size == 4 && b.size == 0); 

    free_stack(&a);
    free_stack(&b);
    printf("\n=== TESTS FINALIZADOS ===\n");
    return (0);
}