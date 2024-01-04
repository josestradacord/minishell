#include "minishell.h"

void	ft_echo(t_ms *ms)
{
	int		index;
	t_list	*node;

	node = ms->cmd->args;
	index = ft_lstsize(node);
	while (index > 0)
	{
		printf("%s ", node->content);
		node = node->next;
		index--;
	}
	printf("\n");
}
