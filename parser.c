#include "minishell.h"

void	ft_getcmd(t_ms *ms, char *line, int *p)
{
	int	index;

	//printf("DEBUG: Obteniendo el comando. La linea es: %s, posición: %d\n", line, *p);
	index = *p;
	while (line[index] && line[index] != ' ')
		index++;
	//printf("DEBUG: Obteniendo posición: %d\n", index);
	ms->cmd->name = ft_substr(line, (*p), index - (*p));
	//printf("DEBUG: El comando es: %s\n", ms->cmd->name);
	*p = index;
}

void	ft_getargs(t_ms *ms, char *line, int *p)
{
	int		index;
	int		n_arg;
	t_list	*arg_node;

	(*p)++;
	index = *p;
	n_arg = 0;
	//ft_printf("DEBUG: Dentro de getargs. Obteniendo posición: %d, contenido: %c\n", index, line[index]);
	while (line[index])
	{
		while (line[index] && line[index] != ' ')
			index++;
		//ft_printf("DEBUG: Dentro del bucle de getargs. Obteniendo posición: %d, contenido: %c\n", index, line[index]);
		arg_node = ft_lstnew(ft_substr(line, (*p), index - (*p)));
		ft_lstadd_back(&ms->cmd->args, arg_node);
		while (line[index] && line[index] == ' ')
			index++;
		*p = index;
	}
	*p = index;
}
void	ft_parser(t_ms *ms, char *line)
{
	int	pos;

	//printf("DEBUG: Dentro del parser. La linea es: %s\n", line);
	pos = 0;
	ft_getcmd(ms, line, &pos);
	//printf("DEBUG: El comando es: %s\n", ms->cmd->name);
	ft_getargs(ms, line, &pos);
	//printf("DEBUG: El comando tiene %d argumentos\n", ft_lstsize(ms->cmd->args));
}
