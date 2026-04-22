#include "push_swap.h"
#include "instructions.h"

void	sa(t_stack *a, bool silent)
{
	t_node	*top;
	t_node	*second;

	if (!a || a->size < 2)
		return ;
	top = pop_node_top(a);
	second = pop_node_top(a);
	push_node(a, top);
	push_node(a, second);
	print_instruction("sa\n", silent);
}

void	sb(t_stack *b, bool silent)
{
	t_node	*top;
	t_node	*second;

	if (!b || b->size < 2)
		return ;
		
	top = pop_node_top(b);
	second = pop_node_top(b);
	
	push_node(b, top);
	push_node(b, second);
	print_instruction("sb\n", silent);
}

void	ss(t_stack *a, t_stack *b, bool silent)
{
	sa(a, true);
	sb(b, true);
	print_instruction("ss\n", silent);
}