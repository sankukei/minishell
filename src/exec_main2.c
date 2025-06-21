/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:13:42 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/20 22:14:43 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	get_fd_from_reddir(char *fd_name, int type)
{
	int	fd;

	printf("CHECK REDDIR %s, %d\n", fd_name, type);
	if (type == 4)
	{
		fd = open(fd_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			exit(1);
		dup2(fd, 1);
	}
	else if (type == 3)
	{
		fd = open(fd_name, O_RDONLY);
		if (fd < 0)
			exit(1);
		dup2(fd, 0);
	}
	else if (type == 2)
	{
		fd = open(fd_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			exit(1);
		dup2(fd, 1);
	}
	return (fd);
}

void	exec_builtin(int selector, char **args, t_data *data, int fd)
{
	if (selector == 1)
		echo(args, fd);
	else if (selector == 2)
		cd(args);
	else if (selector == 3)
		pwd(fd);
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
