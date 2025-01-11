/* ************************************************************************** */
/*                                                                            */
/*   testlib.h                                          :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTLIB_H
# define TESTLIB_H

# include <assert.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <limits.h>
// add libraries of the tested project
// # include "../../app.h"
// Utils
char	*fun_method_name(char *name);
char	*fun_free_str(char *str);

// prototipes from the src funcions
void	fun_start(const char *method_name);
void	fun_end(const char *method_name);
void	fun_test_header(int num);
void	fun_test_header_label(int num, char *str);
void	fun_show_data(char **test);
void	fun_show_orig_new(int (*f1)(const char *),
			int (*f2)(const char *), const char *c);

// asserts
void	fun_assert_int(int orig, int new);

#endif
