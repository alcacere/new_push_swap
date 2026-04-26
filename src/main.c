/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gigarcia <gigarcia@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 15:06:54 by gigarcia          #+#    #+#             */
/*   Updated: 2026/04/26 15:06:57 by gigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* main.c                                             :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: gigarcia <gigarcia@student.42madrid.com>   +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/04/26 14:00:00 by gigarcia          #+#    #+#             */
/* Updated: 2026/04/26 14:00:00 by gigarcia         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "push_swap.h"
#include "algorithms.h"

static t_strategy	run_auto(t_stack *a, t_stack *b, float dis)
{
	if (dis < 0.2)
	{
		simple(a, b);
		return (STRAT_SIMPLE);
	}
	if (dis < 0.5)
	{
		medium(a, b);
		return (STRAT_MEDIUM);
	}
	complex(a, b);
	return (STRAT_COMPLEX);
}

t_strategy	select_strategy(t_stack *a, t_stack *b, t_config cfg, float dis)
{
	if (cfg.strategy == STRAT_SIMPLE)
	{
		simple(a, b);
		return (STRAT_SIMPLE);
	}
	if (cfg.strategy == STRAT_MEDIUM)
	{
		medium(a, b);
		return (STRAT_MEDIUM);
	}
	if (cfg.strategy == STRAT_COMPLEX)
	{
		complex(a, b);
		return (STRAT_COMPLEX);
	}
	return (run_auto(a, b, dis));
}

static int	init_prog(t_stack *a, int ac, char **av, t_config *cfg)
{
	*cfg = parse_flags(ac, av);
	get_stats()->bench_mode = cfg->bench_mode;
	if (cfg->arg_start == ac || check_args(ac, av, cfg->arg_start) == -1)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	if (populate_stack_a(a, av, cfg->arg_start) == 0)
	{
		free_stack(a);
		return (0);
	}
	assign_index(a);
	return (1);
}

int	main(int ac, char **av)
{
	t_stack		a;
	t_stack		b;
	t_config	cfg;
	t_strategy	exec_strat;
	float		disorder;

	if (ac < 2)
		return (0);
	init_stacks(&a, &b);
	if (!init_prog(&a, ac, av, &cfg))
		return (1);
	disorder = compute_disorder(&a);
	exec_strat = select_strategy(&a, &b, cfg, disorder);
	if (cfg.bench_mode)
		print_bench_stats(disorder, cfg.strategy, exec_strat);
	free_stack(&a);
	free_stack(&b);
	return (0);
}
