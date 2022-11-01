/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_error_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:54:44 by jecolmou          #+#    #+#             */
/*   Updated: 2022/10/31 21:23:42 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

int	ft_exist_error(char *infile, t_data *x)
{
	ft_putstr_fd("minimichel: ", 2);
	write(2, infile, ft_strlen(infile));
	ft_putstr_fd(" : No such file or directory", 2);
	write(2, "\n", 1);
	//no pipe no cmd ou no pipe builtin
	if (x->flag_no_pipe_no_cmd_ok_redir == 0)
		ft_exit_bis("1", x);
	// else
	// 	g_status = 1;
	return (false);
}

int	ft_exist_error_directory(char *infile, t_data *x)
{
	ft_putstr_fd("minimichel: ", 2);
	write(2, infile, ft_strlen(infile));
	write(2, ": Not a directory", 18);
	write(2, "\n", 1);
	if (x->flag_no_pipe_no_cmd_ok_redir == 0)
		ft_exit_bis("1", x);
	// else
	// 	g_status = 1;
	return (false);
}

int	ft_perm_error(char *file, t_data *x)
{
	ft_putstr_fd("minimichel: ", 2);
	write(2, file, ft_strlen(file));
	write(2, ": permission denied", 19);
	write(2, "\n", 1);
	if (x->flag_no_pipe_no_cmd_ok_redir == 0)
		ft_exit_bis("1", x);
	// else
	// 	g_status = 1;
	return (false);
}