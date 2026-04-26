#include "push_swap.h"

/* Helpers para sort_small_a que evitan superar las 25 lineas de la norma */
static void	sort_3_a_part2(t_stack *a, int t, int m, int bt)
{
	if (t < m && m > bt && t < bt)
	{
		ra(a, false);
		sa(a, false);
		rra(a, false);
	}
	else if (t < m && m > bt && t > bt)
	{
		ra(a, false);
		sa(a, false);
		rra(a, false);
		sa(a, false);
	}
}

static void	sort_3_a(t_stack *a)
{
	int	t;
	int	m;
	int	bt;

	t = a->top->value;
	m = a->top->next->value;
	bt = a->top->next->next->value;
	if (t > m && m < bt && t < bt)
		sa(a, false);
	else if (t > m && m > bt)
	{
		sa(a, false); ra(a, false); sa(a, false);
		rra(a, false); sa(a, false);
	}
	else if (t > m && m < bt && t > bt)
	{
		sa(a, false); ra(a, false);
		sa(a, false); rra(a, false);
	}
	else
		sort_3_a_part2(a, t, m, bt);
}

/* Helpers para sort_small_b que ordenan de forma descendente */
static void	sort_3_b_part2(t_stack *b, int t, int m, int bt)
{
	if (t > m && m < bt && t > bt)
	{
		rb(b, false); sb(b, false); rrb(b, false);
	}
	else if (t > m && m < bt && t < bt)
	{
		rb(b, false); sb(b, false);
		rrb(b, false); sb(b, false);
	}
}

static void	sort_3_b(t_stack *b)
{
	int	t;
	int	m;
	int	bt;

	t = b->top->value;
	m = b->top->next->value;
	bt = b->top->next->next->value;
	if (t < m && m > bt && t > bt)
		sb(b, false);
	else if (t < m && m < bt)
	{
		sb(b, false); rb(b, false); sb(b, false);
		rrb(b, false); sb(b, false);
	}
	else if (t < m && m > bt && t < bt)
	{
		sb(b, false); rb(b, false);
		sb(b, false); rrb(b, false);
	}
	else
		sort_3_b_part2(b, t, m, bt);
}

/* -------------------------------------------------------- */
/* LAS FUNCIONES PRINCIPALES DE LOS CASOS BASE              */
/* -------------------------------------------------------- */

void	sort_small_a(t_stack *a, int len)
{
	if (len <= 1 || a->size < 2)
		return ;
	if (len == 2)
	{
		if (a->top->value > a->top->next->value)
			sa(a, false);
		return ;
	}
	if (len == 3)
		sort_3_a(a);
}

void	sort_small_b(t_stack *a, t_stack *b, int len)
{
	if (len <= 0)
		return ;
	if (len == 1)
	{
		pa(a, b, false);
		return ;
	}
	if (len == 2)
	{
		if (b->top->value < b->top->next->value)
			sb(b, false);
		pa(a, b, false);
		pa(a, b, false);
		return ;
	}
	if (len == 3)
	{
		sort_3_b(b);
		pa(a, b, false);
		pa(a, b, false);
		pa(a, b, false);
	}
}