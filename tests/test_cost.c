/* tests/test_turk_costs.c */

#include <stdio.h>
#include <stdlib.h>
#include "../include/push_swap.h"
#include "../include/algorithms.h"

void run_test(char *test_name, int condition)
{
    printf("Test: %-60s -> ", test_name);
    if (condition)
        printf("\033[0;32m[OK]\033[0m\n");
    else
        printf("\033[0;31m[KO]\033[0m\n");
}

/* Helper para inyectar nodos con posiciones falsas para la prueba */
void add_mock_node(t_stack *stack, int value, int pos, int target_pos)
{
    t_node *n = malloc(sizeof(t_node));
    n->value = value;
    n->pos = pos;
    n->target_pos = target_pos;
    n->cost_a = 0;
    n->cost_b = 0;
    n->total_cost = 0;
    n->next = NULL;
    n->prev = NULL;
    append_node(stack, n);
}

int main(void)
{
    t_stack a, b;
    t_node *curr;
    t_node *cheapest;

    printf("=== TESTS ASALTO FINAL: EL CONTABLE DEL TURCO ===\n\n");
    init_stacks(&a, &b);


    /* NODO 1: Sinergia hacia arriba (Ambos <= 5) 
       Pos en A: 2 (Cuesta 2 ra)
       Target B: 4 (Cuesta 4 rb)
       Sinergia: Max(2, 4) = 4 (Serían 2 rr y 2 rb) */
    add_mock_node(&a, 100, 2, 4);

    /* NODO 2: Sinergia hacia abajo (Ambos > 5)
       Pos en A: 8 (Cuesta 10-8 = 2 rra)
       Target B: 7 (Cuesta 10-7 = 3 rrb)
       Sinergia: Max(2, 3) = 3 (Serían 2 rrr y 1 rrb) */
    add_mock_node(&a, 200, 8, 7);

    /* NODO 3: Sin Sinergia (Cruzados)
       Pos en A: 2 (Mitad arriba -> Cuesta 2 ra)
       Target B: 8 (Mitad abajo -> Cuesta 10-8 = 2 rrb)
       Total: 2 + 2 = 4 movimientos separados */
    add_mock_node(&a, 300, 2, 8);

    /* NODO 4: El GANADOR indiscutible
       Pos en A: 1 (Cuesta 1 ra)
       Target B: 1 (Cuesta 1 rb)
       Sinergia: Max(1, 1) = 1 (Solo 1 hermoso rr) */
    add_mock_node(&a, 42, 1, 1);


    /* Simulamos que ambos stacks tienen un size de 10 para facilitar los cálculos.
       La mitad superior es de pos 0 a 5. La mitad inferior es de pos 6 a 9. */
    a.size = 10;
    b.size = 10;
    printf("--- Calculando Costes ---\n");
    calculate_costs(&a, &b);

    /* Extraemos los resultados */
    curr = a.top; // Nodo 1 (100)
    run_test("Nodo 1 (Sinergia Arriba): cost_a=2, cost_b=4, total=4", 
             curr->cost_a == 2 && curr->cost_b == 4 && curr->total_cost == 4);

    curr = curr->next; // Nodo 2 (200)
    run_test("Nodo 2 (Sinergia Abajo): cost_a=2, cost_b=3, total=3", 
             curr->cost_a == 2 && curr->cost_b == 3 && curr->total_cost == 3);

    curr = curr->next; // Nodo 3 (300)
    run_test("Nodo 3 (Sin Sinergia): cost_a=2, cost_b=2, total=4", 
             curr->cost_a == 2 && curr->cost_b == 2 && curr->total_cost == 4);

    curr = curr->next; // Nodo 4 (42)
    run_test("Nodo 4 (El Favorito): cost_a=1, cost_b=1, total=1", 
             curr->cost_a == 1 && curr->cost_b == 1 && curr->total_cost == 1);


    printf("\n--- Buscando al mas barato (get_cheapest) ---\n");
    cheapest = get_cheapest(&a);
    
    run_test("El nodo elegido es el 42 (costo 1)", cheapest && cheapest->value == 42);

    /* Limpieza manual porque hackeamos el size */
    a.size = 4; // Lo restauramos al valor real para que free_stack funcione bien
    free_stack(&a);
    // Stack B no tiene nodos reales en este test, solo simulamos su size
    
    printf("\n=== TESTS FINALIZADOS ===\n");
    return (0);
}