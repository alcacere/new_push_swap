/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigarcia <gigarcia@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:59:19 by gigarcia          #+#    #+#             */
/*   Updated: 2026/04/26 15:33:33 by gigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHMS_H
# define ALGORITHMS_H

# include "push_swap.h"

typedef struct s_node t_node;
typedef enum e_strategy t_strategy;
typedef struct s_config t_config;

void	assign_index(t_stack *stack);
float	compute_disorder(t_stack *stack);
void	update_positions(t_stack *stack);
void	find_node_by_size(t_stack *stack);

void	sort_small_a(t_stack *a, int len);
void	sort_small_b(t_stack *a, t_stack *b, int len);

/* Módulo 1: Adaptive Router (El Main del Módulo) */
t_strategy	select_strategy(t_stack *a, t_stack *b, t_config cfg, float disorder);

/* Módulo 3 y 4: Las Estrategias */

void	simple(t_stack *a, t_stack *b);     /* small_sort (<= 5) */
void	medium(t_stack *a, t_stack *b);     /* chunk_sort (O(n√n)) */
void	complex(t_stack *a, t_stack *b);

/*Complex_utils*/
void    quicksort_a(t_stack *a, t_stack *b, int len);
void    quicksort_b(t_stack *a, t_stack *b, int len);
int     get_median(t_node *top, int len);
void    rewind_a(t_stack *a, int rotated);
void    rewind_b(t_stack *b, int rotated);
#endif
