#include "push_swap.h"

void	pa(t_stack *a, t_stack *b, bool silent)
{
	t_node	*to_push;

	if (!b || b->size == 0)
		return ;
	to_push = pop_node_top(b);
	push_node(a, to_push);
	print_instruction("pa\n", silent);
}

void	pb(t_stack *a, t_stack *b, bool silent)
{
	t_node	*to_push;

	if (!a || a->size == 0)
		return ;
	to_push = pop_node_top(a);
	push_node(b, to_push);
	print_instruction("pb\n", silent);
}
