#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H

# include "push_swap.h"

/* PUSH */
void	pa(t_stack **a, t_stack **b, bool print);
void	pb(t_stack **b, t_stack **a, bool print);

/* SWAP */
void	sa(t_stack **a, bool print);
void	sb(t_stack **b, bool print);
void	ss(t_stack **a, t_stack **b, bool print);

/* ROTATE  */
void	ra(t_stack **a, bool print);
void	rb(t_stack **b, bool print);
void	rr(t_stack **a, t_stack **b, bool print);

/* REVERSE ROTATE  */
void	rra(t_stack **a, bool print);
void	rrb(t_stack **b, bool print);
void	rrr(t_stack **a, t_stack **b, bool print);

/* OUTPUT */

#endif