/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 05:38:35 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/14 05:38:52 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_flag(char *arg)
{
	return (arg && ft_strncmp(arg, "-n", ft_strlen("-n")) == 0);
}

char	*join_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (ft_join(count, args, " "));
}
