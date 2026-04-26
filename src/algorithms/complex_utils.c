/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigarcia <gigarcia@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 15:31:06 by gigarcia          #+#    #+#             */
/*   Updated: 2026/04/26 15:31:19 by gigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_median(t_node *top, int len)
{
	int	*arr;
	int	i;
	int	ret;

	if (!top || len == 0)
		return (-1);
	arr = (int *)malloc(sizeof(int) * len);
	if (!arr)
		return (-1);
	i = 0;
	while (i < len)
	{
		arr[i] = top->value;
		top = top->next;
		i++;
	}
	ft_bubble_sort(arr, len);
	ret = arr[len / 2];
	free(arr);
	return (ret);
}

void	rewind_a(t_stack *a, int rotated)
{
	if (rotated != a->size && a->size > 2)
	{
		while (rotated > 0)
		{
			rra(a, false);
			rotated--;
		}
	}
}

void	rewind_b(t_stack *b, int rotated)
{
	if (rotated != b->size)
	{
		while (rotated > 0)
		{
			rrb(b, false);
			rotated--;
		}
	}
}
