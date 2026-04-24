/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigarcia <gigarcia@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:59:19 by gigarcia          #+#    #+#             */
/*   Updated: 2026/04/12 20:00:32 by gigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHMS_H
# define ALGORITHMS_H

# include "push_swap.h"

typedef struct s_node t_node;

void	assign_index(t_stack *stack);
float	compute_disorder(t_stack *stack);
void	update_positions(t_stack *stack);
void	set_target_a_to_b(t_stack *a, t_stack *b);
void	set_target_b_to_a(t_stack *a, t_stack *b);
void	find_node_by_size(t_stack *stack);

void	calculate_costs(t_stack *a, t_stack *b);
void	calc_cost_a(t_node *node, int len_a);
void	calc_cost_b(t_node *node, int len_b);
t_node	*get_cheapest(t_stack *stack);

/* Módulo 1: Adaptive Router (El Main del Módulo) */
void	select_strategy(t_stack *a, t_stack *b);

/* Módulo 3 y 4: Las Estrategias */

void	push_chunk_to_b(t_stack *a, t_stack *b);
void	simple(t_stack *a, t_stack *b);     /* small_sort (<= 5) */
void	medium(t_stack *a, t_stack *b);     /* chunk_sort (O(n√n)) */
void	complex(t_stack *a, t_stack *b);    /* Radix / Turk_greedy */

#endif
