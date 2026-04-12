#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include "../libft/libft.h"

typedef struct s_stack
{
	int				value;			/* El valor real del número */
	int				index;			/* Posición ideal en el stack ordenado (útil para Radix) */
	int				push_cost;		/* Coste de mover este nodo (para estrategias complejas) */
	bool			above_median;	/* Flag de optimización para saber qué dirección rotar */
	struct s_stack	*target_node;	/* Puntero al nodo objetivo en el otro stack */
	struct s_stack	*next;			/* Siguiente nodo */
	struct s_stack	*prev;			/* Nodo anterior (Lista Doblemente Enlazada) */
}	t_stack;

bool	check_syntax(char *str_n);
bool	check_duplicates(t_stack *a, int n);
void	parse_input(t_stack **a, char **argv, bool is_split);
int	check_args(int argc, char **argv);

void	append_node(t_stack **stack, int n);
t_stack	*find_last(t_stack *stack);
t_stack	*find_smallest(t_stack *stack);
t_stack	*find_highest(t_stack *stack);
int		stack_len(t_stack *stack);
bool	is_sorted(t_stack *stack);

void	free_stack(t_stack **stack);
void	free_matrix(char **matrix);
void	error_exit(t_stack **a, char **matrix, bool is_split);

#endif