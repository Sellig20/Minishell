/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 20:12:11 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/07 15:56:35 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cdquotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && str[i + 1] == '\'')
			|| (str[i] == '"' && str[i + 1] == '"'))
			return (1);
		i++;
	}
	return (0);
}

void	ft_cd_is_quotes(char *str)
{
	if (ft_cdquotes(str) == 1)
		return ;
	else
		str = ft_check_str(str);
}

char	*ft_check_str(char *str)
{
	DIR	*d;

	d = opendir(str);
	if (access(str, X_OK) != 0)
		dprintf(2, "babaja\n");
	if (d == NULL)
	{
		ft_putstr_fd("Minimichel : ", 2);
		perror(str);
		return (NULL);
	}
	closedir(d);
	return (str);
}

void	ft_cd_unset(char *str, char *str1, t_list *cpenv, t_data *x)
{
	t_list	**words;
	t_list	**oldpwd;
	t_list	*new;

	words = malloc(sizeof(t_list *));
	if (!words)
		return ;
	*words = ft_lstnew((void *) words_init(str, TOK_WORD));
	new = ft_lstnew((void *) words_init(str1, TOK_WORD));
	ft_lstadd_back(words, new);
	oldpwd = malloc(sizeof(t_cmdredir *));
	if (!oldpwd)
		return ;
	*oldpwd = ft_lstnew((void *) cmdredir_init(*words));
	ft_unset(*oldpwd, &cpenv, x);
	ft_lstclear(words, ft_free_words);
	ft_lstclear(oldpwd, ft_free_cmd_redir);
}

void	ft_cd_export(char *str, char *word, t_list *cpenv, t_data *x)
{
	t_list	**words;
	t_list	**oldpwd;
	t_list	*new;

	words = malloc(sizeof(t_list *));
	if (!words)
		return ;
	*words = ft_lstnew((void *) words_init(str, TOK_WORD));
	new = ft_lstnew((void *) words_init(word, TOK_WORD));
	ft_lstadd_back(words, new);
	oldpwd = malloc(sizeof(t_cmdredir *));
	if (!oldpwd)
		return (ft_lstclear(words, ft_free_words));
	*oldpwd = ft_lstnew((void *) cmdredir_init(*words));
	ft_export(*oldpwd, &cpenv, x);
	ft_lstclear(words, ft_free_words);
	ft_lstclear(oldpwd, ft_free_cmd_redir);
}
