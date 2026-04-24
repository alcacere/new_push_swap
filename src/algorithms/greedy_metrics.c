#include "push_swap.h"

void	update_positions(t_stack *stack)
{
	t_node	*current;
	int	i;

	if (!stack)
		return ;
	current = stack->top;
	i = 0;
	while (current)
	{
		current->pos = i;
		if (current->pos <= stack->size / 2)
			current->above_median = true;
		else
			current->above_median = false;
		current = current->next;
		i++;
	}
}

void	set_target_a_to_b(t_stack *a, t_stack *b)
{
	t_node	*current_a;
	t_node	*current_b;
	int		current_diff;
	int		best_diff;
// TODO: comprobar si el smallest es mas grande que el nodo actual de a;
	if (!a || !b)
		return ;
	current_a = a->top;
	while (current_a)
	{
		current_b = b->top;
		best_diff = INT_MAX;
		while (current_b)
		{
			current_diff = current_a->index - current_b->index;
			if (current_diff > 0 && current_diff < best_diff)
			{
				best_diff = current_diff;
				current_a->target_pos = current_b->pos;
			}
			current_b = current_b->next;
		}
		if (best_diff == INT_MAX)
			current_a->target_pos = b->highest->pos;
		current_a = current_a->next;
	}
}

void	set_target_b_to_a(t_stack *a, t_stack *b)
{
	t_node	*current_a;
	t_node	*current_b;
	int		best_diff;

	if (!a || !b)
		return ;
	current_b = b->top;
	while (current_b)
	{
		current_a = a->top;
		best_diff = INT_MAX;
		while (current_a)
		{
		if ((current_a->index - current_b->index) > 0 
			&& (current_a->index - current_b->index) < best_diff)
			{
				best_diff = current_a->index - current_b->index;
				current_b->target_pos = current_a->pos;
			}
			current_a = current_a->next;
		}
		if (best_diff == INT_MAX)
			current_b->target_pos = a->smallest->pos;
		current_b = current_b->next;
	}
}