/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:22:18 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/12 15:43:25 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

int	ft_unset_others(t_list *tmp, char *bf_eq)
{
	t_list	*swp;
	int		i;

	i = 0;
	while (tmp && tmp->next && i == 0)
	{
		if (ft_strncmp(bf_eq, ((t_words *)tmp->next->content)->word,
				ft_strlen(bf_eq)) == 0)
		{
			if (tmp->next->next)
				swp = tmp->next->next;
			else
				swp = NULL;
			ft_lstdelone(tmp->next, ft_free_words);
			tmp->next = swp;
			i = 1;
		}
		tmp = tmp->next;
	}
	if (i == 0 && tmp && ((t_words *)tmp->content) && ft_strncmp(bf_eq,
			((t_words *)tmp->content)->word, ft_strlen(bf_eq)) == 0 && i++ == 0)
		ft_lstdelone(tmp, ft_free_words);
	return (i);
}

int	ft_unset_first(t_list **tmp, char *before_eq)
{
	t_list	*swp;
	t_words	*content;
	int		check;

	swp = NULL;
	check = 0;
	if (!(*tmp))
		return (1);
	content = (t_words *)(*tmp)->content;
	if (ft_strncmp(before_eq, content->word, ft_strlen(before_eq)) == 0)
	{
		swp = (*tmp)->next;
		ft_lstdelone(*tmp, ft_free_words);
		*tmp = swp;
		check = 1;
	}
	return (check);
}

int	ft_unset(t_list *cmdredir, t_list **cpenv, t_data *x)
{
	t_words	*content;
	t_list	*cmd;

	cmd = ((t_cmdredir *)cmdredir->content)->cmd;
	(void) x;
	if (!(cmd->next))
		return (1);
	cmd = cmd->next;
	while (cmd)
	{
		content = (t_words *) cmd->content;
		if (check_if_equal(content->word) == 0)
			if (ft_unset_first(cpenv, content->word) == 0)
				ft_unset_others(*cpenv, content->word);
		cmd = cmd->next;
	}
	return (0);
}
