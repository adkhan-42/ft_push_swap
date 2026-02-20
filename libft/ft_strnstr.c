/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:24:56 by adkhan            #+#    #+#             */
/*   Updated: 2025/11/05 13:25:00 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	needle_len;
	size_t	i;
	int		res;

	if (*little == '\0')
		return ((char *)big);
	needle_len = ft_strlen(little);
	i = 0;
	while ((i + needle_len <= len) && big[i])
	{
		res = ft_strncmp(&big[i], little, needle_len);
		if (res == 0)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
