/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:54:48 by amedenec          #+#    #+#             */
/*   Updated: 2024/11/06 23:54:48 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*sb1;
	const unsigned char	*sb2;

	sb1 = s1;
	sb2 = s2;
	while (n--)
	{
		if (*sb1 != *sb2)
			return (*sb1 - *sb2);
		sb1++;
		sb2++;
	}
	return (0);
}
