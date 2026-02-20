/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:21:36 by adkhan            #+#    #+#             */
/*   Updated: 2025/11/05 13:47:02 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_revcpy(char *dest, const char *src, size_t n)
{
	while (n > 0)
	{
		dest[n - 1] = src[n - 1];
		n--;
	}
}

static void	ft_forwardcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (!dest || !src)
		return (NULL);
	d = (char *)dest;
	s = (const char *)src;
	if (dest > src)
		ft_revcpy(d, s, n);
	else
		ft_forwardcpy(d, s, n);
	return (dest);
}
