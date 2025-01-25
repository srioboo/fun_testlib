/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_test_utils.c                                                          */
/*                                                                            */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"

char	*fun_free_str(char *text)
{
	free(text);
	text = NULL;
	return (text);
}

char	*fun_method_name(char *text)
{
	char	*method_message;
	int		len;

	len = strlen(text) + 1;
	method_message = (char *)malloc(len * sizeof(char *));
	if (!method_message)
		return (NULL);
	strcpy(method_message, text); // copy text to method_message (avoid leaks)
	return (method_message);
}
