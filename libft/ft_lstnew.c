/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:17:53 by adkhan            #+#    #+#             */
/*   Updated: 2025/11/05 13:18:03 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}
// #include <stdio.h>
// #include <string.h> // For strcmp
// #include <stdlib.h> // For free
// #include "libft.h"

// // Your ft_lstnew function prototype would be in libft.h

// int main(void)
// {
//     char    *my_string = "Hello World";
//     t_list  *new_node;

//     printf("--- Testing ft_lstnew ---\n");

//     // 1. Call the function to create the node
//     new_node = ft_lstnew(my_string);

//     // 2. Check if the allocation was successful
//     if (new_node == NULL)
//     {
//         printf("❌ FAIL: ft_lstnew returned NULL.\n");
//         return (1);
//     }

//     // 3. Check the content
//     // We cast void* back to char* and compare it to our original string
//     if (strcmp((char *)new_node->content, my_string) == 0)
//     {
//         printf("✅ PASS: Content is correct (\"%s\").\n",
	// (char *)new_node->content);
//     }
//     else
//     {
//         printf("❌ FAIL: Content is incorrect.\n");
//     }

//     // 4. Check the next pointer
//     if (new_node->next == NULL)
//     {
//         printf("✅ PASS: node->next is NULL.\n");
//     }
//     else
//     {
//         printf("❌ FAIL: node->next is not NULL.\n");
//     }

//     // 5. Clean up the memory (this is the free() you mentioned)
//     free(new_node);

//     printf("--- Test complete ---\n");
//     return (0);
// }