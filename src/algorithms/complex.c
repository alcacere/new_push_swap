#include "push_swap.h"
#include "algorithms.h"

void	quicksort_b(t_stack *a, t_stack *b, int len);

/* Helper para encontrar la mediana de un bloque específico de 'len' tamaño */
int		get_median(t_node *top, int len)
{
	int	*arr;
	int	i;
	int	ret;

	if (!top || len == 0)
		return (-1);
	arr = (int *)malloc(sizeof(int) * len);
	if (!arr)
		return (-1);
	i = 0;
	while (i < len)
	{
		arr[i] = top->value;
		top = top->next;
		i++;
	}
	sort_int_array(arr, len);
	ret = arr[len / 2];
	return (free(arr), ret);
}

/* Los motores recursivos */
void quicksort_a(t_stack *a, t_stack *b, int len)
{
    int pivot;
    int pushed;
    int rotated;
    int i;

    pushed = 0;
    rotated = 0;
    i = 0;
    if (len <= 3)
    {
        sort_small_a(a, len);
        return ;
    }
    pivot = get_median(a->top, len);
    while (i < len)
    {
        if (a->top->value < pivot)
        {
            pb(a, b, false);
            pushed++;
        }
        else
        {
            ra(a, false);
            rotated++;
        }
        i++;
    }
    if (rotated != a->size && a->size > 2)
    {
        while (rotated > 0)
        {
            rra(a, false);
            rotated--;
        }
    }
    quicksort_a(a, b, len - pushed);
    quicksort_b(a, b, pushed);
}

void	quicksort_b(t_stack *a, t_stack *b, int len)
{
    int pivot;
    int pushed;
    int rotated;
    int i;

    pushed = 0;
    rotated = 0;
    i = 0;
    if (len <= 3)
    {
        sort_small_b(a, b, len);
        return ;
    }
    pivot = get_median(b->top, len);
    while (i < len)
    {
        if (b->top->value >= pivot)
        {
            pa(a, b, false);
            pushed++;
        }
        else
        {
            rb(b, false);
            rotated++;
        }
        i++;
    }
    if (rotated != b->size)
    {
        while (rotated > 0)
        {
            rrb(b, false);
            rotated--;
        }
    }
    quicksort_a(a, b, pushed);
    quicksort_b(a, b, len - pushed);
}
/* El director que reemplazará a complex() */
void	complex(t_stack *a, t_stack *b)
{
	quicksort_a(a, b, a->size);
}