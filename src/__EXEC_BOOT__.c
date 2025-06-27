/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_BOOT__.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 00:13:06 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/27 02:37:05 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	minishell_launcher(t_data *data)
{
	char	*input;
	t_cmd		*cmds;

	cmds = (t_cmd *)malloc(sizeof(t_cmd));
	setup_signals();
	while (1)
	{
		input = readline("minishell> ");
		printf("HAA\n");
		if (ft_strlen(input))
		{
			data->input = input;
			add_history(input);
			if (parsing(data))
			{
				prepare_next_input(data, &cmds);
				continue ;
			}
			parser(data, &cmds);
			data->cmd = cmds;
			printf("%x\n", cmds->redirs);
			__exec_startup__(data, cmds);
			prepare_next_input(data, &data->cmd);
		}
	}
}
