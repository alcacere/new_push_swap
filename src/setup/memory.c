/* src/setup/memory.c */

#include "push_swap.h"

/* Libera iterativamente todos los nodos de un stack (si existe) */
void	free_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*tmp;

	if (!stack || !stack->top)
		return ;
	current = stack->top;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
}

/* Boton del panico: Limpia la memoria de ambos stacks y aborta */
void	error_exit(t_stack *a, t_stack *b)
{
	if (a)
		free_stack(a);
	if (b)
		free_stack(b);
	write(2, "Error\n", 6);
	exit(1);
}