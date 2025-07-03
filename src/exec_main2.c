/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:13:42 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/02 04:49:13 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	get_fd(t_dup dups)
{
	int	fd;

	fd = 1;
	if (dups.outfile_redir)
	{
		fd = dups.outfile_fd;
	}
	return (fd);
}

void	exec_builtin(int selector, char **args, t_data *data, t_dup dups)
{
	int	fd;

	fd = get_fd(dups);
	if (selector == 1)
		echo(data, args, fd);
	else if (selector == 2)
		cd(data, args);
	else if (selector == 3)
		pwd(data, fd);
	else if (selector == 4)
		export(data, args);
	else if (selector == 5)
		unset(data, args);
	else if (selector == 6)
		env(data);
	else if (selector == 7)
		ft_exit(data, args);
	return ;
}
