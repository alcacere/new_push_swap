/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigarcia <gigarcia@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:39:53 by gigarcia          #+#    #+#             */
/*   Updated: 2026/04/26 15:41:15 by gigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include "libft.h"
# include "instructions.h"
# include "algorithms.h"

/*Node metadata*/
typedef struct s_node
{
	int				value;
	int				index;
	int				pos;
	bool			above_median;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

/*Structs to keep count on the pushed/rotated elements in quicksort*/
typedef struct s_counts
{
	int	pushed;
	int	rotated;
}	t_counts;

typedef enum e_strategy
{
	STRAT_ADAPTIVE,
	STRAT_SIMPLE,
	STRAT_MEDIUM,
	STRAT_COMPLEX,
}	t_strategy;

typedef struct s_config
{
	t_strategy	strategy;
	bool		bench_mode;
	int			arg_start;
}	t_config;

typedef struct s_stats
{
	bool	bench_mode;
	int	total_ops;
	int	sa;
	int	sb;
	int	ss;
	int	pa;
	int	pb;
	int	ra;
	int	rb;
	int	rr;
	int	rra;
	int	rrb;
	int	rrr;
}	t_stats;

typedef struct s_stack
{
	t_node			*top;
	t_node			*bottom;
	t_node			*smallest;
	t_node			*highest;
	int				size;
}	t_stack;


/* bench mode flag manager*/
t_stats		*get_stats(void);
void	print_bench_stats(float disorder, t_strategy original, t_strategy executed);

/* parsing */
int		check_args(int argc, char **argv, int start);
int		populate_stack_a(t_stack *a, char **argv, int start);

t_config	parse_flags(int argc, char **argv);

/* stack_utils */
void	init_stacks(t_stack *a, t_stack *b);
void	push_node(t_stack *stack, t_node *new_node);
t_node	*pop_node_top(t_stack *stack);
t_node	*pop_node_bottom(t_stack *stack);
bool	is_sorted(t_stack *stack);
void	append_node(t_stack *stack, t_node *new_node);

/* memory management */
void	free_stack(t_stack *stack);
void	error_exit(t_stack *a, t_stack *b);

#endif
