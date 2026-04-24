#include "push_swap.h"
#include "instructions.h"
#include "algorithms.h"

/* 1. Helper: Nos dice en qué posición (de 0 a N) está el número que buscamos */
static int	get_node_pos(t_stack *stack, int target_index)
{
	t_node	*curr;
	int		position;

	curr = stack->top;
	position = 0;
	while (curr)
	{
		if (curr->index == target_index)
			return (position);
		position++;
		curr = curr->next;
	}
	return (0);
}

/* 2. Fase 1: El Filtrado Inteligente de A hacia B (Ventana Deslizante) */
static void	push_chunks_to_b(t_stack *a, t_stack *b, int chunk_size)
{
	int	i;

	i = 0;
	while (a->size > 0)
	{
		if (a->top->index <= i)
		{
			pb(a, b, false);
			rb(b, false); // Es de la mitad pequeña: lo mandamos al fondo de B
			i++;
		}
		else if (a->top->index <= i + chunk_size)
		{
			pb(a, b, false); // Es de la mitad grande: se queda arriba en B
			i++;
		}
		else
			ra(a, false); // No nos interesa aún: lo mandamos al fondo de A
	}
}

/* 3. Fase 2: Recoger el más grande de B y devolverlo a A */
static void	push_back_to_a(t_stack *a, t_stack *b)
{
	int	max_idx;
	int	position;

	while (b->size > 0)
	{
		// Como pasamos TODOS los numeros a B y 
		// los indices van de 0 a N-1, el numero más grande que queda 
		// en B SIEMPRE es exactamente (b->size - 1).
		max_idx = b->size - 1; 
		position = get_node_pos(b, max_idx);
		
		// Si esta en la mitad de arriba, giramos normal
		if (position <= b->size / 2)
		{
			while (b->top->index != max_idx)
				rb(b, false);
		}
		// Si esta en la mitad de abajo, giramos al reves (atajo)
		else
		{
			while (b->top->index != max_idx)
				rrb(b, false);
		}
		pa(a, b, false);
	}
}

/* 4. La Función Maestra que llama el Main */
void	medium(t_stack *a, t_stack *b)
{
	int	chunk_size;

	if (is_sorted(a) || a->size == 0)
		return ;
	// Para 100 números, un bloque de 15 a 20 es el "Sweet Spot" de eficiencia.
	if (a->size <= 100)
		chunk_size = 15;
	else
		chunk_size = 35; // Si le meten 500 números, ampliamos la red
	push_chunks_to_b(a, b, chunk_size);
	push_back_to_a(a, b);
}
