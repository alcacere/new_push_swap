#include "push_swap.h"
#include "algorithms.h"

bool	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack || !stack->top)
		return (true);
	current = stack->top;
	while (current->next)
	{
		if (current->value > current->next->value)
			return (false);
		current = current->next;
	}
	return (true);
}

void	find_node_by_size(t_stack *stack)
{
	t_node	*aux;
	t_node	*small;
	t_node	*high;

	if (!stack || stack->size == 0)
		return ;
	aux = stack->top;
	small = aux;
	high = aux;
	while (aux)
	{
		if (aux->value < small->value)
			small = aux;
		if (aux->value > high->value)
			high = aux;
		aux = aux->next;
	}
	stack->highest = high;
	stack->smallest = small;
}

/* Helper: Ordena un array de enteros de menor a mayor (Bubble Sort) */
static void	sort_int_array(int *arr, int size)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	set_index(t_stack *stack, int *arr)
{
	t_node	*curr;
	int	i;

	curr = stack->top;
	while (curr)
	{
		i = 0;
		while (i < stack->size)
		{
			if (curr->value == arr[i])
			{
				curr->index = i;
				break ;
			}
			i++;
		}
		curr = curr->next;
	}
}

/* Asigna un indice (0 a N-1) copiando a un array, ordenando y mapeando */
void	assign_index(t_stack *stack)
{
	int		*arr;
	int		i;
	t_node	*curr;

	if (!stack || stack->size == 0)
		return ;
	arr = malloc(sizeof(int) * stack->size);
	if (!arr)
		return ;
	curr = stack->top;
	i = 0;
	while (curr)
	{
		arr[i++] = curr->value;
		curr = curr->next;
	}
	sort_int_array(arr, stack->size);
	set_index(stack, arr);
	free(arr);
}