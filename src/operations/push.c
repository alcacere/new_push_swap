#include "push_swap.h"
#include "instructions.h"

void	pa(t_stack *a, t_stack *b, bool silent)
{
	t_node	*to_push;

	if (!b || b->size == 0)
		return ;
	to_push = pop_node(b);
	push_node(a, to_push);
	if (silent == false)
		write(1, "pa\n", 3);
}

void	pb(t_stack *a, t_stack *b, bool silent)
{
	t_node	*to_push;

	if (!a || a->size == 0)
		return ;
	to_push = pop_node(a);
	push_node(b, to_push);
	if (silent == false)
		write(1, "pb\n", 3);
}
