/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:13:42 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/30 01:04:41 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


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
