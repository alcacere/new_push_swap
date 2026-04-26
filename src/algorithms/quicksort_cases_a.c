/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_cases_a.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigarcia <gigarcia@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 15:52:39 by gigarcia          #+#    #+#             */
/*   Updated: 2026/04/26 15:52:57 by gigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_3_a_part2(t_stack *a, int t, int m, int bt)
{
	if (t > m && m < bt && t > bt)
	{
		sa(a, false);
		ra(a, false);
		sa(a, false);
		rra(a, false);
	}
	else if (t < m && m > bt && t < bt)
	{
		ra(a, false);
		sa(a, false);
		rra(a, false);
	}
	else if (t < m && m > bt && t > bt)
	{
		ra(a, false);
		sa(a, false);
		rra(a, false);
		sa(a, false);
	}
}

static void	sort_3_a(t_stack *a)
{
	int	t;
	int	m;
	int	bt;

	t = a->top->value;
	m = a->top->next->value;
	bt = a->top->next->next->value;
	if (t > m && m < bt && t < bt)
		sa(a, false);
	else if (t > m && m > bt)
	{
		sa(a, false);
		ra(a, false);
		sa(a, false);
		rra(a, false);
		sa(a, false);
	}
	else
		sort_3_a_part2(a, t, m, bt);
}

void	sort_small_a(t_stack *a, int len)
{
	if (len <= 1 || a->size < 2)
		return ;
	if (len == 2)
	{
		if (a->top->value > a->top->next->value)
			sa(a, false);
		return ;
	}
	if (len == 3)
		sort_3_a(a);
}
