#include "push_swap.h"

void	print_instruction(char *inst, bool silent)
{
	int	len;

	if (!silent)
	{
		len = ft_strlen(inst);
		write(1, inst, len);
	}
}