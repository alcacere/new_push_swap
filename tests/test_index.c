/* tests/test_index.c */

#include <stdio.h>
#include <stdlib.h>
#include "../include/push_swap.h"
#include "../include/algorithms.h"

void run_test(char *test_name, int condition)
{
    printf("Test: %-40s -> ", test_name);
    if (condition)
        printf("\033[0;32m[OK]\033[0m\n");
    else
        printf("\033[0;31m[KO]\033[0m\n");
}

/* Helper para inyectar nodos */
void fill_stack(t_stack *a, int *nums, int size)
{
    for (int i = 0; i < size; i++)
    {
        t_node *n = malloc(sizeof(t_node));
        n->value = nums[i];
        n->index = -1; // Lo inicializamos en -1 para asegurar que nuestra funcion lo cambia
        n->next = NULL;
        n->prev = NULL;
        append_node(a, n);
    }
}

int main(void)
{
    t_stack a;
    t_stack b;
    t_node  *current;

    printf("=== TESTS ASALTO 4: INDEXACION (PRE-CHUNK) ===\n\n");

    init_stacks(&a, &b);

    /* Vamos a meter: 42, -5, 10, 0, 99 
       Orden lógico esperado:
       -5  -> index 0
        0  -> index 1
       10  -> index 2
       42  -> index 3
       99  -> index 4
    */
    int nums[] = {42, -5, 10, 0, 99}; 
    fill_stack(&a, nums, 5);
    
    printf("--- Asignando indices ---\n");
    assign_index(&a); // La funcion que vamos a crear en metrics.c
    
    /* Extraemos los nodos uno a uno de arriba hacia abajo para comprobarlos */
    current = a.top; // Nodo 42
    run_test("El 42 tiene el index 3", current->value == 42 && current->index == 3);
    
    current = current->next; // Nodo -5
    run_test("El -5 tiene el index 0", current->value == -5 && current->index == 0);
    
    current = current->next; // Nodo 10
    run_test("El 10 tiene el index 2", current->value == 10 && current->index == 2);
    
    current = current->next; // Nodo 0
    run_test("El 0 tiene el index 1", current->value == 0 && current->index == 1);
    
    current = current->next; // Nodo 99
    run_test("El 99 tiene el index 4", current->value == 99 && current->index == 4);

    free_stack(&a);
    printf("\n=== TESTS FINALIZADOS ===\n");
    return (0);
}