/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:01:33 by adkhan            #+#    #+#             */
/*   Updated: 2025/11/05 13:01:40 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res;
	size_t	max;

	if (nmemb == 0 || size == 0)
	{
		res = (char *)malloc(1);
		ft_memset(res, 0, 1);
		return (res);
	}
	max = (size_t)-1;
	if (nmemb > max / size)
		return (NULL);
	res = (char *)malloc(nmemb * size);
	if (!res)
		return (NULL);
	ft_memset(res, 0, (nmemb * size));
	return (res);
}
