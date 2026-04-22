#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H

# include "push_swap.h"

typedef struct s_stack t_stack;

/* push.c */
void	pa(t_stack *a, t_stack *b, bool silent);
void	pb(t_stack *a, t_stack *b, bool silent);

/* swap.c */
void	sa(t_stack *a, bool silent);
void	sb(t_stack *b, bool silent);
void	ss(t_stack *a, t_stack *b, bool silent);

/* rotate.c */
void	ra(t_stack *a, bool silent);
void	rb(t_stack *b, bool silent);
void	rr(t_stack *a, t_stack *b, bool silent);

/* rev_rotate.c */
void	rra(t_stack *a, bool silent);
void	rrb(t_stack *b, bool silent);
void	rrr(t_stack *a, t_stack *b, bool silent);

/* output.c */
void	print_instruction(char *inst, bool silent);
void	print_bench_stats(t_stack *a, int moves, float disorder);

#endif