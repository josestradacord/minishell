#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>

# include "libft/libft.h"

# define FALSE	0
# define TRUE	1

typedef struct s_list_e
{
	char			*name;
	char			*value;
	struct s_list_e	*next;
}	t_list_e;

typedef struct s_ms
{
	t_list_e	*env;
}	t_ms;



int			ft_check_args(int n_arg);
void		ft_usage(void);
void		ft_get_env(t_ms *ms, char **envp);

t_list_e	*ft_lste_new(char *key, char *value);
int			ft_lste_size(t_list_e *lst);
void		ft_lste_addback(t_list_e **lst, t_list_e *new);
void		ft_lste_delone(t_list_e *lst, void (*del)(void *));
void		ft_lste_clear(t_list_e **lst, void (*del)(void *));

void		ft_print_env(char **envp);
void		ft_print_env_lst(t_list_e *env);
#endif