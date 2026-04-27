/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metrics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigarcia <gigarcia@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 15:16:38 by gigarcia          #+#    #+#             */
/*   Updated: 2026/04/26 17:55:14 by gigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"
#include "instructions.h"

bool	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack || !stack->top)
		return (true);
	current = stack->top;
	while (current->next)
	{
		if (current->value > current->next->value)
			return (false);
		current = current->next;
	}
	return (true);
}

void	find_node_by_size(t_stack *stack)
{
	t_node	*aux;
	t_node	*small;
	t_node	*high;

	if (!stack || stack->size == 0)
		return ;
	aux = stack->top;
	small = aux;
	high = aux;
	while (aux)
	{
		if (aux->value < small->value)
			small = aux;
		if (aux->value > high->value)
			high = aux;
		aux = aux->next;
	}
	stack->highest = high;
	stack->smallest = small;
}

void	set_index(t_stack *stack, int *arr)
{
	t_node	*curr;
	int		i;

	curr = stack->top;
	while (curr)
	{
		i = 0;
		while (i < stack->size)
		{
			if (curr->value == arr[i])
			{
				curr->index = i;
				break ;
			}
			i++;
		}
		curr = curr->next;
	}
}

void	assign_index(t_stack *stack)
{
	int		*arr;
	int		i;
	t_node	*curr;

	if (!stack || stack->size == 0)
		return ;
	arr = malloc(sizeof(int) * stack->size);
	if (!arr)
		return ;
	curr = stack->top;
	i = 0;
	while (curr)
	{
		arr[i++] = curr->value;
		curr = curr->next;
	}
	ft_bubble_sort(arr, stack->size);
	set_index(stack, arr);
	free(arr);
}

float	compute_disorder(t_stack *stack)
{
	t_node	*curr_i;
	t_node	*curr_j;
	int		mistakes;
	int		total_pairs;

	if (!stack || stack->size < 2)
		return (0.0f);
	mistakes = 0;
	total_pairs = 0;
	curr_i = stack->top;
	while (curr_i)
	{
		curr_j = curr_i->next;
		while (curr_j)
		{
			total_pairs++;
			if (curr_i->value > curr_j->value)
				mistakes++;
			curr_j = curr_j->next;
		}
		curr_i = curr_i->next;
	}
	if (total_pairs == 0)
		return (0.0f);
	return ((float)mistakes / (float)total_pairs);
}
