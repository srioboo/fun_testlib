/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_test_utils.c                                                          */
/*                                                                            */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"

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
