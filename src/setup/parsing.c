#include "push_swap.h"

/* Convierte el string actual a long. Se detiene al encontrar un espacio */
static long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

/* Verifica si la palabra a la que apunta el puntero empieza como numero */
static int	is_valid_number(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str < '0' || *str > '9')
		return (0);
	return (1);
}

/* Magia de punteros: Escanea todos los argv anteriores y el string actual
   justo hasta la posicion de nuestro puntero (cur_ptr) para buscar duplicados */
static int	has_duplicate(char **argv, int cur_arg, char *cur_ptr, long val)
{
	int		i;
	char	*ptr;

	i = 1;
	while (i <= cur_arg)
	{
		ptr = argv[i];
		while (*ptr)
		{
			while (*ptr == ' ')
				ptr++;
			if (!*ptr || (i == cur_arg && ptr == cur_ptr))
				break ;
			if (ft_atol(ptr) == val)
				return (1);
			if (*ptr == '-' || *ptr == '+')
				ptr++;
			while (*ptr >= '0' && *ptr <= '9')
				ptr++;
		}
		i++;
	}
	return (0);
}

/* Procesa un solo string de argv, saltando espacios y validando cada bloque */
static int	process_string(char **argv, int i)
{
	char	*ptr;
	long	val;
	int		has_num;

	ptr = argv[i];
	has_num = 0;
	while (*ptr)
	{
		while (*ptr == ' ')
			ptr++;
		if (!*ptr)
			break ;
		if (!is_valid_number(ptr))
			return (0);
		val = ft_atol(ptr);
		if (val > 2147483647 || val < -2147483648)
			return (0);
		if (has_duplicate(argv, i, ptr, val))
			return (0);
		has_num = 1;
		if (*ptr == '-' || *ptr == '+')
			ptr++;
		while (*ptr >= '0' && *ptr <= '9')
			ptr++;
		if (*ptr != ' ' && *ptr != '\0')
			return (0);
	}
	return (has_num);
}

/* Funcion principal (exportada en push_swap.h) */
int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 2)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (!process_string(argv, i))
			return (0);
		i++;
	}
	return (1);
}