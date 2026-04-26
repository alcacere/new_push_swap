/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigarcia <gigarcia@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:45:45 by gigarcia          #+#    #+#             */
/*   Updated: 2026/04/26 13:46:28 by gigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_stacks(t_stack *a, t_stack *b)
{
	if (a)
	{
		a->top = NULL;
		a->bottom = NULL;
		a->smallest = NULL;
		a->highest = NULL;
		a->size = 0;
	}
	if (b)
	{
		b->top = NULL;
		b->bottom = NULL;
		b->smallest = NULL;
		b->highest = NULL;
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

t_node	*pop_node_top(t_stack *stack)
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

t_node	*pop_node_bottom(t_stack *stack)
{
	t_node	*popped;

	if (!stack || stack->size == 0)
		return (NULL);
	popped = stack->bottom;
	if (stack->size == 1)
	{
		stack->top = NULL;
		stack->bottom = NULL;
	}
	else
	{
		stack->bottom = stack->bottom->prev;
		stack->bottom->next = NULL;
	}
	popped->next = NULL;
	popped->prev = NULL;
	stack->size--;
	return (popped);
}

void	append_node(t_stack *stack, t_node *new_node)
{
	if (!stack || !new_node)
		return ;
	if (!stack->top)
	{
		stack->top = new_node;
		stack->bottom = new_node;
	}
	else
	{
		stack->bottom->next = new_node;
		new_node->prev = stack->bottom;
		stack->bottom = new_node;
	}
	stack->size++;
}

static t_node	*init_node(int val)
{
	t_node	*n;

	n = malloc(sizeof(t_node));
	if (!n)
		error_exit(NULL, NULL);
	n->value = val;
	n->index = 0;
	n->pos = 0;
	n->above_median = false;
	n->next = NULL;
	n->prev = NULL;
	return (n);
}

int	populate_stack_a(t_stack *a, char **argv, int start)
{
	char	*ptr;
	t_node	*new_node;

	while (argv[start])
	{
		ptr = argv[start];
		while (*ptr)
		{
			while (ft_isspace(*ptr))
				ptr++;
			if (!*ptr)
				break ;
			new_node = init_node(ft_atoi(ptr));
			if (!new_node)
				return (0);
			append_node(a, new_node);
			if (ft_issign(*ptr))
				ptr++;
			while (ft_isdigit(*ptr))
				ptr++;
		}
		start++;
	}
	return (find_node_by_size(a), 1);
}
