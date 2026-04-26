#include "push_swap.h"

t_config	parse_flags(int argc, char **argv)
{
	t_config	cfg;
	int			i;

	cfg.strategy = STRAT_ADAPTIVE;
	cfg.bench_mode = false;
	cfg.arg_start = 1;
	i = 1;
	while (i < argc && argv[i][0] == '-')
	{
		if (ft_isdigit(argv[i][1]))
			break ;
		if (ft_strncmp(argv[i], "--bench", 8) == 0)
			cfg.bench_mode = true;
		else if (ft_strncmp(argv[i], "--simple", 9) == 0)
			cfg.strategy = STRAT_SIMPLE;
		else if (ft_strncmp(argv[i], "--medium", 9) == 0)
			cfg.strategy = STRAT_MEDIUM;
		else if (ft_strncmp(argv[i], "--complex", 10) == 0)
			cfg.strategy = STRAT_COMPLEX;
		else if (ft_strncmp(argv[i], "--adaptive", 11) == 0)
			cfg.strategy = STRAT_ADAPTIVE;
		else
			break ;
		i++;
	}
	cfg.arg_start = i;
	return (cfg);
}
