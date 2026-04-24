#include "push_swap.h"

int	ft_issign(char c)
{
	return (c == '+' || c == '-');
}

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

/* 1. Convierte el string a long */
static long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (ft_issign(*str))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

/*
* @brief evalua signos, digitos y super overflow
* @param string de argv
* @return int 0 en error 1 en exito
*/
bool	is_valid_number(char *str)
{
	int	len;

	len = 0;
	if (ft_issign(*str))
		str++;
	if (!ft_isdigit(*str))
		return (false);
	while (*str == '0')
		str++;
	while (ft_isdigit(str[len]))
		len++;
	if (len > 10)
		return (false);
	return (true);
}

/* 3. Búsqueda de duplicados sin gastar memoria */

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
			while (ft_isspace(*ptr))
				ptr++;
			if (!*ptr || (i == cur_arg && ptr == cur_ptr))
				break ;
			if (ft_atol(ptr) == val)
				return (1);
			if (ft_issign(*ptr))
				ptr++;
			while (ft_isdigit(*ptr))
				ptr++;
		}
		i++;
	}
	return (0);
}

/* 4. Procesa string: Retorna -1 si hay error, o la CANTIDAD de números que halló */
static int	process_string(char **argv, int i)
{
	char	*ptr;
	long	val;
	int		count;

	ptr = argv[i];
	count = 0;
	while (*ptr)
	{
		while (ft_isspace(*ptr))
			ptr++;
		if (!*ptr)
			break ;
		if (!is_valid_number(ptr))
			return (-1);
		val = ft_atol(ptr);
		if (val > 2147483647 || val < -2147483648)
			return (-1);
		if (has_duplicate(argv, i, ptr, val))
			return (-1);
		count++;
		if (ft_issign(*ptr))
			ptr++;
		while (ft_isdigit(*ptr))
			ptr++;
		if (ft_isspace(*ptr) && *ptr != '\0')
			return (-1);
	}
	return (count);
}

/* 5. Función principal: Falla rápido (-1) o devuelve la cantidad total exacta */
int	check_args(int argc, char **argv)
{
	int	i;
	int	total_numbers;
	int	current_count;

	i = 1;
	total_numbers = 0;
	while (i < argc)
	{
		current_count = process_string(argv, i);
		if (current_count == -1)
			return (-1);
		total_numbers += current_count;
		i++;
	}
	return (total_numbers);
}