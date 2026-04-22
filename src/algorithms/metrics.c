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
/* * NOTA: Aqií añadiremos en el futuro assign_index, compute_disorder, etc.
 * Por ahora lo dejamos asi para pasar el test del small_sort.
 */