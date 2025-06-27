/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:08:55 by amedenec          #+#    #+#             */
/*   Updated: 2025/06/27 06:59:23 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*dest;
	int		len;

	len = ft_strlen(src);
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	ft_bzero(dest, (len + 1) * sizeof(char));
//	dest[len] = '\0';
	while (len--)
		dest[len] = src[len];
	return (dest);
}
