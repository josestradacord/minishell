/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:55:12 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/02/07 20:31:36 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_temp(char *wtd, int fdin)
{
	char	*str;
	char	*str2;

	str = "";
	write(1, "heredoc> ", 9);
	str2 = get_next_line(0);
	while (ft_strncmp(str2, wtd, ft_strlen(str2) - 1))
	{
		write(1, "heredoc> ", 9);
		str = ft_strjoin(str, str2);
		str2 = get_next_line(0);
	}
	dup2(fdin, STDOUT_FILENO);
	ft_printf("%s", str);
}

int	here_doc(char *str, t_data *data, char *outfl)
{
	int	fdin;

	fdin = open(".tmp", O_WRONLY | O_CREAT, 0644);
	if (ft_search(data, outfl) == 1)
		data->fdout = open(outfl, O_WRONLY | O_CREAT | O_APPEND, 0777);
	ft_temp(str, fdin);
	close(fdin);
	fdin = open(".tmp", O_RDONLY);
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	return (3);
}

int	ft_enter(int argc, char **argv, t_data *data)
{
	int	i;
	int	fdin;

	if (!ft_strncmp(argv[1], "here_doc", 8))
		return (i = here_doc(argv[2], data, argv[argc - 1]));
	else
	{
		if (ft_search(data, argv[argc - 1]) == 1)	//si no existe el ultimo argv lo crea y mete el resultado
			data->fdout = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (ft_search(data, argv[1]) == 1)			//si el primer argv no es un comando es un archivo y lo lee
		{	
			fdin = open(argv[1], O_RDONLY, 0777);
			if (fdin < 0)
			{
				ft_error(1);
				ft_allfree(data);
				exit(1);
			}
			dup2(fdin, STDIN_FILENO);
			return (i = 2);
		}
		return (i = 1);
	}
}
