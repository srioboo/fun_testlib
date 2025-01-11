/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srioboo- <srioboo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:31:14 by srioboo-          #+#    #+#             */
/*   Updated: 2025/01/10 11:09:42 by srioboo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/testlib.h"

char	*fun_free_str(char *str)
{
	free(str);
	str = NULL;
	return (str);
}

char	*fun_method_name(char *name)
{
	char	*method_name;
	int		len;

	len = strlen(name) + 1;
	method_name = (char *)malloc(len * sizeof(char *));
	if (!method_name)
		return (NULL);
	return (method_name);
}
