#include "minishell.h"

int	ft_check_args(int n_arg)
{
	if (n_arg != 1)
		return (FALSE);
	return (TRUE);
}

void	ft_usage(void)
{
	printf("Usage ./minishell\n");
}
