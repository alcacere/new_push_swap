/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigarcia <gigarcia@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 15:12:44 by gigarcia          #+#    #+#             */
/*   Updated: 2026/04/26 15:15:50 by gigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_node_pos(t_stack *stack, int target_index)
{
	t_node	*curr;
	int		position;

	curr = stack->top;
	position = 0;
	while (curr)
	{
		if (curr->index == target_index)
			return (position);
		position++;
		curr = curr->next;
	}
	return (0);
}

static void	push_chunks_to_b(t_stack *a, t_stack *b, int chunk_size)
{
	int	i;

	i = 0;
	while (a->size > 0)
	{
		if (a->top->index <= i)
		{
			pb(a, b, false);
			rb(b, false);
			i++;
		}
		else if (a->top->index <= i + chunk_size)
		{
			pb(a, b, false);
			i++;
		}
		else
			ra(a, false);
	}
}

static void	push_back_to_a(t_stack *a, t_stack *b)
{
	int	max_idx;
	int	position;

	while (b->size > 0)
	{
		max_idx = b->size - 1;
		position = get_node_pos(b, max_idx);
		if (position <= b->size / 2)
		{
			while (b->top->index != max_idx)
				rb(b, false);
		}
		else
		{
			while (b->top->index != max_idx)
				rrb(b, false);
		}
		pa(a, b, false);
	}
}

void	medium(t_stack *a, t_stack *b)
{
	int	chunk_size;

	if (is_sorted(a) || a->size == 0)
		return ;
	if (a->size <= 100)
		chunk_size = 15;
	else
		chunk_size = 35;
	push_chunks_to_b(a, b, chunk_size);
	push_back_to_a(a, b);
}
