/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:23:08 by adkhan            #+#    #+#             */
/*   Updated: 2025/11/05 13:23:10 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	slen;
	char	*dup_str;

	if (!s)
		return (NULL);
	slen = ft_strlen(s) + 1;
	dup_str = malloc(slen * sizeof(char));
	if (!dup_str)
		return (NULL);
	ft_strlcpy(dup_str, s, slen);
	return (dup_str);
}
