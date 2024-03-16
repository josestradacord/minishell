/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:48:28 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/10 17:50:07 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list_e	*ft_lste_new(char *key, char *value)
{
	t_list_e	*node;

	node = (t_list_e *) malloc(sizeof(t_list_e));
	if (!node)
		perror("malloc error");
	if (!node)
		return (NULL);
	node->name = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

int	ft_lste_size(t_list_e *lst)
{
	int			size;
	t_list_e	*node;

	size = 0;
	node = lst;
	while (node != NULL)
	{
		size++;
		node = node->next;
	}
	return (size);
}

void	ft_lste_addback(t_list_e **lst, t_list_e *new)
{
	t_list_e	*node;

	node = *lst;
	if (node == NULL)
		*lst = new;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
}

/**
 * @brief 			This function removes a node of a list of integers
 * 
 * @param lst 		A pointer to the node which we want to remove
 * @param del 		A pointer to the remove function
 */
void	ft_lste_delone(t_list_e *lst, void (*del)(void *))
{
	del(lst->name);
	del(lst->value);
	free(lst);
}

/**
 * @brief 			This function clears (removes of elements) of the
 * 					given list
 * 
 * @param lst 		The list to be cleared
 * @param del 		A pointer to the remove function
 */
void	ft_lste_clear(t_list_e *lst, void (*del)(void *))
{
	t_list_e	*node;

	node = lst;
	while (lst != NULL)
	{
		node = lst->next;
		ft_lste_delone(lst, del);
		lst = node;
	}
	lst = NULL;
}
