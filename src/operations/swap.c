#include "push_swap.h"
#include "instructions.h"

void	sa(t_stack *a, bool silent)
{
	t_node	*top;
	t_node	*second;

	if (!a || a->size < 2)
		return ;
	top = pop_node(a);
	second = pop_node(a);
	push_node(a, top);
	push_node(a, second);
	
	if (silent == false)
		write(1, "sa\n", 3);
}

void	sb(t_stack *b, bool silent)
{
	t_node	*top;
	t_node	*second;

	if (!b || b->size < 2)
		return ;
		
	top = pop_node(b);
	second = pop_node(b);
	
	push_node(b, top);
	push_node(b, second);
	
	if (silent == false)
		write(1, "sb\n", 3);
}

void	ss(t_stack *a, t_stack *b, bool silent)
{
	sa(a, true);
	sb(b, true);
	if (silent == false)
		write(1, "ss\n", 3);
}