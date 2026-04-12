#include "push_swap.h"

/* Inicializa los contenedores de los stacks asegurando que esten limpios */
void	init_stacks(t_stack *a, t_stack *b)
{
	if (a)
	{
		a->top = NULL;
		a->bottom = NULL;
		a->size = 0;
	}
	if (b)
	{
		b->top = NULL;
		b->bottom = NULL;
		b->size = 0;
	}
}

/* Inserta un nodo en la CIMA (top) del stack. Actualiza bottom si es el 1ro */
void	push_node(t_stack *stack, t_node *new_node)
{
	if (!stack || !new_node)
		return ;
	if (stack->size == 0)
	{
		new_node->next = NULL;
		new_node->prev = NULL;
		stack->top = new_node;
		stack->bottom = new_node;
	}
	else
	{
		new_node->next = stack->top;
		new_node->prev = NULL;
		stack->top->prev = new_node;
		stack->top = new_node;
	}
	stack->size++;
}

/* Extrae y devuelve el nodo de la CIMA del stack. Desconecta sus punteros */
t_node	*pop_node(t_stack *stack)
{
	t_node	*popped;

	if (!stack || stack->size == 0)
		return (NULL);
	popped = stack->top;
	if (stack->size == 1)
	{
		stack->top = NULL;
		stack->bottom = NULL;
	}
	else
	{
		stack->top = stack->top->next;
		stack->top->prev = NULL;
	}
	popped->next = NULL;
	popped->prev = NULL;
	stack->size--;
	return (popped);
}