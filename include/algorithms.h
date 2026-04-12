#ifndef ALGORITHMS_H
# define ALGORITHMS_H

# include "push_swap.h"

/* metrics.c */
float	calculate_disorder(t_stack *a);
void	set_nodes_index(t_stack *a); /* Indexa de 0 a N para facilitar algoritmos */

/* router.c (o dentro de main.c) */
void	select_strategy(t_stack **a, t_stack **b);

/* algo_simple.c (O(n^2) - Fallback para <= 5 elementos) */
void	sort_three(t_stack **a);
void	sort_five(t_stack **a, t_stack **b);

/* algo_medium.c (O(n*sqrt(n)) - Chunking) */
void	sort_chunks(t_stack **a, t_stack **b);

/* algo_complex.c (O(n log n) - Radix o Turk Algorithm) */
void	sort_complex(t_stack **a, t_stack **b);

/* costs.c (Optimización y cálculo de heurísticas) */
void	prep_for_push(t_stack **stack, t_stack *top_node, char stack_name);
void	calculate_costs(t_stack *a, t_stack *b);

#endif