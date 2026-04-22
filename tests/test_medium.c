/* tests/test_medium.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

/* Inyecta N numeros aleatorios sin repetir */
void fill_random_stack(t_stack *a, int size)
{
    int i = 0;
    int j;
    int *nums = malloc(sizeof(int) * size);
    int is_duplicate;

    srand(time(NULL));
    while (i < size)
    {
        nums[i] = (rand() % 2000) - 1000; // Numeros entre -1000 y +999
        is_duplicate = 0;
        for (j = 0; j < i; j++)
        {
            if (nums[j] == nums[i])
                is_duplicate = 1;
        }
        if (!is_duplicate)
        {
            t_node *n = malloc(sizeof(t_node));
            n->value = nums[i];
            n->index = -1;
            n->next = NULL;
            n->prev = NULL;
            append_node(a, n);
            i++;
        }
    }
    free(nums);
}

int main(void)
{
    t_stack a;
    t_stack b;

    printf("=== TESTS ASALTO 5: CHUNK SORT (N = 100) ===\n\n");
    init_stacks(&a, &b);
    printf("--- Generando 100 numeros aleatorios ---\n");
    fill_random_stack(&a, 100);
    assign_index(&a);
    medium(&a, &b); 
    find_node_by_size(&a);
    run_test("El stack A esta ordenado perfectamente", is_sorted(&a));
    run_test("El stack A tiene sus 100 elementos", a.size == 100);
    run_test("El stack B esta completamente vacio", b.size == 0);
    free_stack(&a);
    printf("\n=== TESTS FINALIZADOS ===\n");
    return (0);
}