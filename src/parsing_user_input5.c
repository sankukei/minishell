/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_user_input5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 03:03:08 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/14 05:33:42 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	var_is_in_env(t_data *data, char *var, int len)
{
	char	**env;
	int		i;

	i = 0;
	env = data->env;
	if (ft_strncmp(var, "?", 2) == 0)
		return (1);
	while (env[i])
	{
		if (ft_strncmp(var, env[i], len) == 0)
			return (1);
		i++;
	}
	free(var);
	return (0);
}

void	quote_check(t_data *data, int i)
{
	if ((data->input[i] == '\"') && (data->single_quote == false))
		data->double_quote = !(data->double_quote);
	else if ((data->input[i] == '\'') && (data->double_quote == false))
		data->single_quote = !(data->single_quote);
}

static int	ft_nblen(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
		n = -n;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_fillnum(char *buf, long n, int len)
{
	buf[len] = '\0';
	if (n == 0)
		buf[0] = '0';
	if (n < 0)
	{
		buf[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		buf[--len] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa_stack(int n)
{
	static char	buf[12];
	long		nb;
	int			len;

	nb = (long)n;
	len = ft_nblen(nb);
	ft_fillnum(buf, nb, len);
	return (buf);
}
