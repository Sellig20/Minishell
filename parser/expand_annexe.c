/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_annexe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:20:15 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/03 12:26:42 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_after_doll(char *word)
{
	int	i;

	i = 0;
	if (word[0] == '?')
		return (5);
	if (word[i] >= '0' && word[i] <= '9')
		return (1);
	else if (!((word[i] >= 'a' && word[i] <= 'z')
			|| (word[i] >= '0' && word[i] <= '9')
			|| (word[i] >= 'A' && word[i] <= 'Z')))
		return (2);
	while (word[i])
	{
		if (!((word[i] >= 'a' && word[i] <= 'z')
				|| (word[i] >= '0' && word[i] <= '9')
				|| (word[i] >= 'A' && word[i] <= 'Z')))
			return (4);
		i++;
	}
	return (3);
}

char	*ft_expand_found_3(t_dollar *d, char *new_word, int len)
{
	int		i;

	i = 0;
	d->len_env = ft_strlen((((t_words *)d->envcp->content)->word)) - (len + 1);
	new_word = malloc(sizeof(char) * d->len_env + 1);
	while (((t_words *)d->envcp->content)->word[len + 1 + i])
	{
		new_word[i] = ((t_words *)d->envcp->content)->word[len + 1 + i];
		i++;
		d->comp = i;
	}
	new_word[i] = '\0';
	return (new_word);
}

char	*ft_expand_not_found_4(t_dollar *d, char *new_word)
{
	int		j;
	char	*null;

	null = NULL;
	j = 0;
	null = malloc(sizeof(char) * 1 + 1);
	null[j] = '\0';
	new_word = ft_strjoin(null, d->save);
	free(d->save);
	free(null);
	free(d->tmp);
	return (new_word);
}

char	*ft_expand_found_4(t_dollar *d, char *new_word)
{
	int		j;

	j = 0;
	d->len_env = ft_strlen((((t_words *)d->envcp->content)->word))
		- (d->len_word + 1);
	new_word = malloc(sizeof(char) * d->len_env + 1);
	while (((t_words *)d->envcp->content)->word[d->len_word + 1 + j])
	{
		new_word[j] = ((t_words *)d->envcp->content)->word[d->len_word + 1 + j];
		j++;
		d->comp = j;
	}
	new_word[j] = '\0';
	return (new_word);
}

char	*ft_expand_4(char *new_word, t_dollar *d)
{
	char	*tmp;

	d->comp = 0;
	while (d->envcp)
	{
		d->len_word = ft_strlen(d->tmp);
		tmp = ft_strjoin(d->tmp, "=");
		if (ft_strncmp(((t_words *)d->envcp->content)->word,
				tmp, d->len_word + 1) == 0)
			new_word = ft_expand_found_4(d, new_word);
		free(tmp);
		d->envcp = d->envcp->next;
	}
	if (d->comp == 0)
	{
		new_word = ft_expand_not_found_4(d, new_word);
		return (new_word);
	}
	new_word = ft_strjoin(new_word, d->save);
	free(d->save);
	free(d->tmp);
	return (new_word);
}
