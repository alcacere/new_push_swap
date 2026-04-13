#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include "libft.h"

/* Nodo individual: Contiene los datos, metadatos del algoritmo y punteros */
typedef struct s_node
{
	int				value;			/* Valor numérico real */
	int				index;			/* Valor normalizado (0 a N-1) para Radix */
	int				pos;			/* Posición actual en el stack */
	int				target_pos;		/* Posición ideal en el stack opuesto */
	int				cost_a;			/* Rotaciones necesarias en A */
	int				cost_b;			/* Rotaciones necesarias en B */
	int				total_cost;		/* Coste absoluto combinado */
	bool			above_median;	/* Flag: ¿Está en la mitad superior? */
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

/* Contenedor del Stack: Maneja la lista de forma global (Optimización O(1)) */
typedef struct s_stack
{
	t_node			*top;			/* Puntero al primer nodo */
	t_node			*bottom;		/* Puntero al último nodo (optimiza rra/rrb) */
	int				size;			/* Tamaño actual del stack */
}	t_stack;

/* parsing.c */
int		check_args(int argc, char **argv);

/* flags.c */
bool	parse_flags(int argc, char **argv, bool *bench_mode);

/* stack_utils.c (Stack API Design) */
void	init_stacks(t_stack *a, t_stack *b);
void	populate_stack_a(t_stack *a, char **argv);
void	push_node(t_stack *stack, t_node *new_node);
t_node	*pop_node(t_stack *stack);
bool	is_sorted(t_stack *stack);

/* memory.c */
void	free_stack(t_stack *stack);
void	error_exit(t_stack *a, t_stack *b);

#endif