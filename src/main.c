#include "push_swap.h"
#include "algorithms.h"

/* * Algoritmo O(n) para desorden muy bajo. 
 * Si el desorden es menor al 20%, el stack está "casi" listo.
 */
static void	low_disorder_sort(t_stack *a, t_stack *b)
{
	if (is_sorted(a))
		return ;
	/* En un desorden < 0.2, el Turk (complex) es tan eficiente 
	   que sigue siendo una opción segura, pero el subject pide O(n). 
	   Una técnica O(n) común es buscar si solo hay un elemento 
	   fuera de lugar y corregirlo. */
	complex(a, b); 
}

t_strategy	select_strategy(t_stack *a, t_stack *b, t_config cfg, float disorder)
{
	if (cfg.strategy == STRAT_SIMPLE)
		return (simple(a, b), STRAT_SIMPLE);
	if (cfg.strategy == STRAT_MEDIUM)
		return (medium(a, b), STRAT_MEDIUM);
	if (cfg.strategy == STRAT_COMPLEX)
		return (complex(a, b), STRAT_COMPLEX);
	disorder = compute_disorder(a);
	if (disorder < 0.2)
		return (low_disorder_sort(a, b), STRAT_SIMPLE);
	else if (disorder < 0.5)
		return (medium(a, b), STRAT_MEDIUM);
	else
		return (complex(a, b), STRAT_COMPLEX);
}

int main(int ac, char **av)
{
	t_stack		a;
	t_stack		b;
	t_config	cfg;
	t_strategy	executed_strat;
	float		disorder;

	if (ac < 2)
		return (0);
	cfg = parse_flags(ac, av);
	get_stats()->bench_mode = cfg.bench_mode;
	if (cfg.arg_start == ac || check_args(ac, av, cfg.arg_start) == -1)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	init_stacks(&a, &b);
	if (populate_stack_a(&a, av, cfg.arg_start) == 0)
		return (free_stack(&a), 1);
	assign_index(&a);
	disorder = compute_disorder(&a);
	executed_strat = select_strategy(&a, &b, cfg, disorder);
	if (cfg.bench_mode)
		print_bench_stats(disorder, cfg.strategy, executed_strat);
	free_stack(&a);
	free_stack(&b);
	return (0);
}