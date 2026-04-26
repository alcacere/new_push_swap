/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigarcia <gigarcia@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 15:09:56 by gigarcia          #+#    #+#             */
/*   Updated: 2026/04/26 15:11:59 by gigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	update_positions(t_stack *stack)
{
	t_node	*current;
	int		i;

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

static void	sort_three(t_stack *stack)
{
	find_node_by_size(stack);
	if (stack->top == stack->highest)
		ra(stack, false);
	else if (stack->top->next == stack->highest)
		rra(stack, false);
	if (stack->top->value > stack->top->next->value)
		sa(stack, false);
}

static void	push_smallest_to_b(t_stack *a, t_stack *b)
{
	update_positions(a);
	find_node_by_size(a);
	while (a->top != a->smallest)
	{
		if (a->smallest->above_median == true)
			ra(a, false);
		else
			rra(a, false);
	}
	pb(a, b, false);
}

void	simple(t_stack *a, t_stack *b)
{
	if (is_sorted(a) || a->size <= 1)
		return ;
	if (a->size == 2)
		sa(a, false);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size > 3)
	{
		while (a->size > 3)
			push_smallest_to_b(a, b);
		sort_three(a);
		while (b->size > 0)
			pa(a, b, false);
	}
}
