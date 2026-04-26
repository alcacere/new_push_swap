#include "push_swap.h"

/* 1. El Singleton para guardar las stats */
t_stats	*get_stats(void)
{
	static t_stats	s = {0};
	return (&s);
}

/* 2. Helper para no saturar la funcion principal de ifs */
static void	count_rotates(char *i, t_stats *s)
{
	if (i[0] == 'r' && i[1] == 'a' && i[2] == '\n')
		s->ra++;
	else if (i[0] == 'r' && i[1] == 'b' && i[2] == '\n')
		s->rb++;
	else if (i[0] == 'r' && i[1] == 'r' && i[2] == '\n')
		s->rr++;
	else if (i[0] == 'r' && i[1] == 'r' && i[2] == 'a')
		s->rra++;
	else if (i[0] == 'r' && i[1] == 'r' && i[2] == 'b')
		s->rrb++;
	else if (i[0] == 'r' && i[1] == 'r' && i[2] == 'r')
		s->rrr++;
}

/* 3. La aduana principal: Perfectamente tabulada para la Norma */
void	print_instruction(char *inst, bool silent)
{
	t_stats	*s;

	s = get_stats();
	if (!silent)
	{
		s->total_ops++;
		if (inst[0] == 's' && inst[1] == 'a')
			s->sa++;
		else if (inst[0] == 's' && inst[1] == 'b')
			s->sb++;
		else if (inst[0] == 's' && inst[1] == 's')
			s->ss++;
		else if (inst[0] == 'p' && inst[1] == 'a')
			s->pa++;
		else if (inst[0] == 'p' && inst[1] == 'b')
			s->pb++;
		else
			count_rotates(inst, s);
		if (s->bench_mode == false)
			ft_putstr_fd(inst, 1);
	}
}

/* 4. Helper mágico: Reduce 2 lineas de impresión a 1 sola */
static void	print_stat(char *name, int val)
{
	ft_putstr_fd(name, 2);
	ft_putnbr_fd(val, 2);
}

/* 5. Helper para la cabecera del benchmark (Calcula el float) */
static void	print_header(float disorder, t_strategy exec)
{
	ft_putstr_fd("[bench] disorder: ", 2);
	ft_putnbr_fd((int)(disorder * 100), 2);
	ft_putstr_fd(".", 2);
	if ((int)(disorder * 10000) % 100 < 10)
		ft_putstr_fd("0", 2);
	ft_putnbr_fd((int)(disorder * 10000) % 100, 2);
	ft_putstr_fd("%\n[bench] strategy: Adaptive / ", 2);
	if (exec == STRAT_SIMPLE)
		ft_putstr_fd("Simple O(n^2)\n", 2);
	else if (exec == STRAT_MEDIUM)
		ft_putstr_fd("Medium O(n root n)\n", 2);
	else if (exec == STRAT_COMPLEX)
		ft_putstr_fd("Complex O(n log n)\n", 2);
}

/* 6. La función final: Limpia, corta y totalmente segura para FD 2 */
void	print_bench_stats(float dis, t_strategy orig, t_strategy exec)
{
	t_stats	*s;

	(void)orig; /* Evitamos el error de 'variable no usada' */
	s = get_stats();
	print_header(dis, exec);
	print_stat("[bench] total_ops: ", s->total_ops);
	print_stat("\n[bench] sa: ", s->sa);
	print_stat(" sb: ", s->sb);
	print_stat(" ss: ", s->ss);
	print_stat(" pa: ", s->pa);
	print_stat(" pb: ", s->pb);
	print_stat("\n[bench] ra: ", s->ra);
	print_stat(" rb: ", s->rb);
	print_stat(" rr: ", s->rr);
	print_stat(" rra: ", s->rra);
	print_stat(" rrb: ", s->rrb);
	print_stat(" rrr: ", s->rrr);
	ft_putstr_fd("\n", 2);
}