/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:25:51 by adkhan            #+#    #+#             */
/*   Updated: 2025/11/05 13:31:49 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	slen;
	size_t	avail_len;
	size_t	len2mal;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
	{
		res = (char *)malloc(1);
		if (!res)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	avail_len = slen - start;
	len2mal = ft_min(avail_len, len);
	res = (char *)malloc((len2mal + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, (s + start), (len2mal + 1));
	return (res);
}
