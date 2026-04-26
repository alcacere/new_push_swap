/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_cases_b.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigarcia <gigarcia@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 15:53:07 by gigarcia          #+#    #+#             */
/*   Updated: 2026/04/26 15:53:20 by gigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_3_b_part2(t_stack *b, int t, int m, int bt)
{
	if (t < m && m > bt && t < bt)
	{
		sb(b, false);
		rb(b, false);
		sb(b, false);
		rrb(b, false);
	}
	else if (t > m && m < bt && t > bt)
	{
		rb(b, false);
		sb(b, false);
		rrb(b, false);
	}
	else if (t > m && m < bt && t < bt)
	{
		rb(b, false);
		sb(b, false);
		rrb(b, false);
		sb(b, false);
	}
}

static void	sort_3_b(t_stack *b)
{
	int	t;
	int	m;
	int	bt;

	t = b->top->value;
	m = b->top->next->value;
	bt = b->top->next->next->value;
	if (t < m && m > bt && t > bt)
		sb(b, false);
	else if (t < m && m < bt)
	{
		sb(b, false);
		rb(b, false);
		sb(b, false);
		rrb(b, false);
		sb(b, false);
	}
	else
		sort_3_b_part2(b, t, m, bt);
}

void	sort_small_b(t_stack *a, t_stack *b, int len)
{
	if (len <= 0)
		return ;
	if (len == 1)
	{
		pa(a, b, false);
		return ;
	}
	if (len == 2)
	{
		if (b->top->value < b->top->next->value)
			sb(b, false);
		pa(a, b, false);
		pa(a, b, false);
		return ;
	}
	if (len == 3)
	{
		sort_3_b(b);
		pa(a, b, false);
		pa(a, b, false);
		pa(a, b, false);
	}
}
