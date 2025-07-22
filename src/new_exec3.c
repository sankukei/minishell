/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 05:30:57 by amedenec          #+#    #+#             */
/*   Updated: 2025/07/22 05:31:07 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	handle_single_builtin_new(t_exec *vars, t_cmd *commands, t_data *data)
{
	t_dup	dups;

	(void)vars;
	if (!(check_if_builtin(commands->cmd[0]) && commands && commands->cmd))
		return (0);
	dups = handle_redir(data, commands->redirs, vars);
	exec_builtin(check_if_builtin(commands->cmd[0]), commands->cmd, data, dups);
	return (1);
}
