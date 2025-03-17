/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:08:47 by amedenec          #+#    #+#             */
/*   Updated: 2024/11/06 23:08:47 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int c)
{
	char	*d;

	d = NULL;
	while (*string)
	{
		if (*string == (char)c)
		{
			d = (char *)string;
			return (d);
		}
		string++;
	}
	if (*string == (char)c)
		d = (char *)string;
	return (d);
}
