/* tests/test_turk_metrics.c */

#include <stdio.h>
#include <stdlib.h>
#include "../include/push_swap.h"
#include "../include/algorithms.h"

void run_test(char *test_name, int condition)
{
    printf("Test: %-50s -> ", test_name);
    if (condition)
        printf("\033[0;32m[OK]\033[0m\n");
    else
        printf("\033[0;31m[KO]\033[0m\n");
}

void fill_stack_manual(t_stack *stack, int *nums, int *indices, int size)
{
    for (int i = 0; i < size; i++)
    {
        t_node *n = malloc(sizeof(t_node));
        n->value = nums[i];
        n->index = indices[i];
        n->pos = -1;
        n->target_pos = -1;
        n->next = NULL;
        n->prev = NULL;
        append_node(stack, n);
    }
}

int main(void)
{
    t_stack a, b;
    t_node *curr;

    printf("=== TESTS ASALTO FINAL: EL RADAR DEL TURCO ===\n\n");
    init_stacks(&a, &b);

    /* * STACK A: [42, 10, 99, 2] -> indices [3, 1, 4, 0]
     * STACK B: [50, 40, 5]     -> indices [2, 5, 0] (Nota: inventamos indices para la prueba)
     */
    int val_a[] = {42, 10, 99, 2};
    int ind_a[] = {42, 10, 99, 2}; // Usamos el mismo valor como indice para facilitar la lectura
    fill_stack_manual(&a, val_a, ind_a, 4);

    int val_b[] = {50, 40, 5};
    int ind_b[] = {50, 40, 5};
    fill_stack_manual(&b, val_b, ind_b, 3);

    /* PASO 1: Actualizar métricas previas obligatorias */
    find_node_by_size(&a); // Para setear a.smallest y a.highest
    find_node_by_size(&b); // Para setear b.smallest y b.highest

    /* --- TEST 1: POSICIONES Y MITADES --- */
    printf("--- Probando update_positions ---\n");
    update_positions(&a);
    update_positions(&b);
    
    curr = a.top; // Nodo 42
    run_test("Nodo 42: Posicion 0, above_median TRUE", curr->pos == 0 && curr->above_median == true);
    curr = curr->next; // Nodo 10
    run_test("Nodo 10: Posicion 1, above_median TRUE", curr->pos == 1 && curr->above_median == true);
    curr = curr->next; // Nodo 99
    run_test("Nodo 99: Posicion 2, above_median TRUE", curr->pos == 2 && curr->above_median == true);
    curr = curr->next; // Nodo 2
    run_test("Nodo 2: Posicion 3, above_median FALSE", curr->pos == 3 && curr->above_median == false);


    /* --- TEST 2: TARGET A -> B (Buscando el menor mas cercano) --- */
    printf("\n--- Probando set_target_a_to_b ---\n");
    set_target_a_to_b(&a, &b);
    
    curr = a.top; // Nodo 42
    // El menor mas cercano a 42 en B es el 40 (que esta en la pos 1 de B)
    run_test("Target de 42 es 40 (posicion 1 de B)", curr->target_pos == 1);
    
    curr = curr->next; // Nodo 10
    // El menor mas cercano a 10 en B es el 5 (pos 2)
    run_test("Target de 10 es 5 (posicion 2 de B)", curr->target_pos == 2);
    
    curr = curr->next; // Nodo 99
    // El menor mas cercano a 99 en B es el 50 (pos 0)
    run_test("Target de 99 es 50 (posicion 0 de B)", curr->target_pos == 0);
    
    curr = curr->next; // Nodo 2
    // El 2 es mas pequeño que todos. Como es el "Nuevo Rey", su target debe ser el MAYOR de B (50, pos 0)
    run_test("Target de 2 (Nuevo Rey) es 50 (posicion 0 de B)", curr->target_pos == 0);


    /* --- TEST 3: TARGET B -> A (Buscando el MAYOR mas cercano) --- */
    printf("\n--- Probando set_target_b_to_a ---\n");
    // Vamos a vaciar A y llenarlo con algo facil para la vuelta
    free_stack(&a);
    int val_a2[] = {10, 40, 90}; // indices: 10, 40, 90. Pos: 0, 1, 2
    fill_stack_manual(&a, val_a2, val_a2, 3);
    find_node_by_size(&a);
    update_positions(&a);
    
    // Stack B actual: 50, 40, 5
    set_target_b_to_a(&a, &b);
    
    curr = b.top; // Nodo 50
    // Mayor mas cercano a 50 en A es 90 (pos 2)
    run_test("Target de 50 en A es 90 (posicion 2 de A)", curr->target_pos == 2);
    
    curr = curr->next; // Nodo 40
    // Como en A esta el 40, debe buscar el estrictamente mayor -> 90 (pos 2)
    run_test("Target de 40 en A es 90 (posicion 2 de A)", curr->target_pos == 2);
    
    curr = curr->next; // Nodo 5
    // Mayor mas cercano a 5 en A es 10 (pos 0)
    run_test("Target de 5 en A es 10 (posicion 0 de A)", curr->target_pos == 0);

    free_stack(&a);
    free_stack(&b);
    printf("\n=== TESTS FINALIZADOS ===\n");
    return (0);
}