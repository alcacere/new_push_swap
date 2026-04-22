/* tests/test_simple.c */

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

/* Helper súper rápido para inyectar arrays enteros en el Stack A */
void fill_stack(t_stack *a, int *nums, int size)
{
    for (int i = 0; i < size; i++)
    {
        t_node *n = malloc(sizeof(t_node));
        n->value = nums[i];
        n->next = NULL;
        n->prev = NULL;
        append_node(a, n);
    }
}

int main(void)
{
    t_stack a;
    t_stack b;

    printf("=== TESTS ASALTO 3: SMALL SORT (N <= 5) ===\n\n");

    /* --- TEST 1: Ordenar 3 números (El caso inverso) --- */
    printf("--- Probando Sort 3 (Caso 3 2 1) ---\n");
    init_stacks(&a, &b);
    int nums3[] = {3, 2, 1}; 
    fill_stack(&a, nums3, 3);
    
    simple(&a, &b); // Actualizado al nuevo nombre de la funcion
    
    // Al final del sort, actualizamos los punteros para hacer las comprobaciones
    find_node_by_size(&a); 

    run_test("El stack A esta ordenado", is_sorted(&a));
    run_test("El stack A tiene 3 elementos", a.size == 3);
    run_test("El puntero smallest apunta al 1", a.smallest && a.smallest->value == 1);
    run_test("El puntero highest apunta al 3", a.highest && a.highest->value == 3);
    run_test("El stack B esta vacio", b.size == 0);
    free_stack(&a);


    /* --- TEST 2: Ordenar 5 números (Caos total) --- */
    printf("\n--- Probando Sort 5 (Caso Caotico) ---\n");
    init_stacks(&a, &b);
    int nums5[] = {42, 1, 99, -5, 10}; 
    fill_stack(&a, nums5, 5);
    
    simple(&a, &b);
    
    find_node_by_size(&a);

    run_test("El stack A esta ordenado (-5, 1, 10, 42, 99)", is_sorted(&a));
    run_test("El stack A tiene 5 elementos", a.size == 5);
    run_test("El puntero smallest apunta al -5", a.smallest && a.smallest->value == -5);
    run_test("El puntero highest apunta al 99", a.highest && a.highest->value == 99);
    run_test("El stack B esta vacio", b.size == 0);
    free_stack(&a);

    printf("\n=== TESTS FINALIZADOS ===\n");
    return (0);
}