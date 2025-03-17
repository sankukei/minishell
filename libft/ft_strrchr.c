/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:20:11 by amedenec          #+#    #+#             */
/*   Updated: 2024/11/06 23:20:11 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *string, int c)
{
	char	*d;

	d = NULL;
	while (*string)
	{
		if (*string == (char)c)
			d = (char *)string;
		string++;
	}
	if (*string == (char)c)
	{
		d = (char *)string;
	}
	return (d);
}
