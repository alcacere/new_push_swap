#include "push_swap.h"
#include "algorithms.h"

/* Helper 1: Consigue el puntero exacto del alma gemela usando la posicion */
static t_node *get_target_node(t_stack *stack, int target_pos)
{
	t_node	*target;
	int		i;

	if (!stack)
		return (NULL);
	i = 0;
	target = stack->top;
	while (i++ < target_pos)
		target = target->next;
	return (target);
}

/* Helper 2: Ejecuta las rotaciones (dobles y simples) y hace el 'pb' */
static void move_a_to_b(t_stack *a, t_stack *b, t_node *cheapest)
{
	t_node	*target_node;

	if (!a || !b || !cheapest)
		return ;
	target_node = get_target_node(b, cheapest->target_pos);
	if (cheapest->pos <= a->size / 2 && target_node->pos <= b->size / 2)
	{
		while (a->top != cheapest && b->top != target_node)
			rr(a, b, false);
	}
	else if (cheapest->pos > a->size / 2 && target_node->pos > b->size / 2)
	{
		while (a->top != cheapest && b->top != target_node)
			rrr(a, b, false);
	}
	while (a->top != cheapest)
	{
		if (cheapest->pos <= a->size / 2)
			ra(a, false);
		else
			rra(a, false);
	}
	while (b->top != target_node)
	{
		if (target_node->pos <= b->size / 2)
			rb(b, false);
		else
			rrb(b, false);
	}
	pb(a, b, false);
}
/* Helper 3: Prepara el Stack A para recibir el nodo de B y hace 'pa' */
static void move_b_to_a(t_stack *a, t_stack *b, t_node *node_b)
{
	t_node	*target_node;

	if(!a || !b || !node_b)
		return ;
	target_node = get_target_node(a, node_b->target_pos);
	while (a->top != target_node)
	{
		if (target_node->pos <= a->size / 2)
			ra(a, false);
		else
			rra(a, false);
	}
	pa(a, b, false);
}

/* La función principal que el main va a llamar */
void complex(t_stack *a, t_stack *b)
{
	t_node	*cheapest;

	if (!a || !b)
		return ;
	if (a->size > 3)
	{
		pb(a, b, false);
		pb(a, b, false);
	}
	while (a->size > 3)
	{
		find_node_by_size(a);
		find_node_by_size(b);
		update_positions(a);
		update_positions(b);
		set_target_a_to_b(a, b);
		calculate_costs(a, b);
		cheapest = get_cheapest(a);
		move_a_to_b(a, b, cheapest);
	}
	simple(a, b);
	while (b->size > 0)
	{
		find_node_by_size(a);
		find_node_by_size(b);
		update_positions(a);
		update_positions(b);
		set_target_b_to_a(a, b);
		move_b_to_a(a, b, b->top);
	}
	find_node_by_size(a);
	find_node_by_size(b);
	update_positions(a);
	while (a->smallest != a->top)
	{
		if (a->smallest->above_median == true)
			ra(a, false);
		else
			rra(a, false);
	}
}