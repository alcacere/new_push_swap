/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigarcia <gigarcia@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 15:44:57 by gigarcia          #+#    #+#             */
/*   Updated: 2026/04/26 15:45:10 by gigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	partition_a(t_stack *a, t_stack *b, int len, t_counts *cnt)
{
	int	pivot;
	int	i;

	pivot = get_median(a->top, len);
	i = 0;
	while (i < len)
	{
		if (a->top->value < pivot)
		{
			pb(a, b, false);
			cnt->pushed++;
		}
		else
		{
			ra(a, false);
			cnt->rotated++;
		}
		i++;
	}
}

static void	partition_b(t_stack *a, t_stack *b, int len, t_counts *cnt)
{
	int	pivot;
	int	i;

	pivot = get_median(b->top, len);
	i = 0;
	while (i < len)
	{
		if (b->top->value >= pivot)
		{
			pa(a, b, false);
			cnt->pushed++;
		}
		else
		{
			rb(b, false);
			cnt->rotated++;
		}
		i++;
	}
}

void	quicksort_a(t_stack *a, t_stack *b, int len)
{
	t_counts	cnt;

	if (len <= 3)
	{
		sort_small_a(a, len);
		return ;
	}
	cnt.pushed = 0;
	cnt.rotated = 0;
	partition_a(a, b, len, &cnt);
	rewind_a(a, cnt.rotated);
	quicksort_a(a, b, len - cnt.pushed);
	quicksort_b(a, b, cnt.pushed);
}

void	quicksort_b(t_stack *a, t_stack *b, int len)
{
	t_counts	cnt;

	if (len <= 3)
	{
		sort_small_b(a, b, len);
		return ;
	}
	cnt.pushed = 0;
	cnt.rotated = 0;
	partition_b(a, b, len, &cnt);
	rewind_b(b, cnt.rotated);
	quicksort_a(a, b, cnt.pushed);
	quicksort_b(a, b, len - cnt.pushed);
}

void	complex(t_stack *a, t_stack *b)
{
	quicksort_a(a, b, a->size);
}
