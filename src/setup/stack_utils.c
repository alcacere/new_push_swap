/* src/setup/stack_utils.c */

#include "push_swap.h"

void	init_stacks(t_stack *a, t_stack *b)
{
	if (a)
	{
		a->top = NULL;
		a->bottom = NULL;
		a->size = 0;
	}
	if (b)
	{
		b->top = NULL;
		b->bottom = NULL;
		b->size = 0;
	}
}

void	push_node(t_stack *stack, t_node *new_node)
{
	if (!stack || !new_node)
		return ;
	if (stack->size == 0)
	{
		new_node->next = NULL;
		new_node->prev = NULL;
		stack->top = new_node;
		stack->bottom = new_node;
	}
	else
	{
		new_node->next = stack->top;
		new_node->prev = NULL;
		stack->top->prev = new_node;
		stack->top = new_node;
	}
	stack->size++;
}

t_node	*pop_node(t_stack *stack)
{
	t_node	*popped;

	if (!stack || stack->size == 0)
		return (NULL);
	popped = stack->top;
	if (stack->size == 1)
	{
		stack->top = NULL;
		stack->bottom = NULL;
	}
	else
	{
		stack->top = stack->top->next;
		stack->top->prev = NULL;
	}
	popped->next = NULL;
	popped->prev = NULL;
	stack->size--;
	return (popped);
}

/* Helper estatico: Inserta por ABAJO para mantener el orden del argv */
static void	append_node(t_stack *a, int val)
{
	t_node	*n;

	n = malloc(sizeof(t_node));
	if (!n)
		error_exit(a, NULL);
	n->value = val;
	n->index = 0;
	n->pos = 0;
	n->target_pos = 0;
	n->cost_a = 0;
	n->cost_b = 0;
	n->total_cost = 0;
	n->above_median = false;
	n->next = NULL;
	n->prev = NULL;
	if (!a->top)
	{
		a->top = n;
		a->bottom = n;
	}
	else
	{
		a->bottom->next = n;
		n->prev = a->bottom;
		a->bottom = n;
	}
	a->size++;
}

/* Lee el argv, extrae numeros saltando espacios y los inyecta en Stack A */
void	populate_stack_a(t_stack *a, char **argv)
{
	int		i;
	char	*ptr;

	i = 1;
	while (argv[i])
	{
		ptr = argv[i];
		while (*ptr)
		{
			while (*ptr == ' ')
				ptr++;
			if (!*ptr)
				break ;
			append_node(a, ft_atoi(ptr));
			if (*ptr == '-' || *ptr == '+')
				ptr++;
			while (*ptr >= '0' && *ptr <= '9')
				ptr++;
		}
		i++;
	}
}