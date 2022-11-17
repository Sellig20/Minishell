/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:52:02 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/09 14:28:51 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*atmp;

	if (new != NULL)
	{
		atmp = *alst;
		if (atmp == NULL)
			*alst = new;
		else
		{
			while (atmp->next)
				atmp = atmp->next;
			atmp->next = new;
		}
	}
}

void	ft_insert(t_list *new, t_list *tmp)
{
	t_list	*swp;

	if (new == NULL || tmp == NULL)
		return ;
	swp = tmp->next;
	tmp->next = new;
	new->next = swp;
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	if (!content)
		new->content = NULL;
	else
		new->content = content;
	return (new);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		if (lst->content)
		{
			(*del)(lst->content);
		}
		free(lst);
	}
}
