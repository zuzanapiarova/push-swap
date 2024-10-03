/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:19 by zpiarova          #+#    #+#             */
/*   Updated: 2024/10/03 20:05:29 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

// show Error. and end program, free memory
void	put_error(t_stack *a)
{
	ft_putstr_fd("Error.\n", 2);
	ft_stackclear(a);
	exit(EXIT_SUCCESS);
}

// fills stack a from string input
// if string is empty don't process it and go to next one
// check for sign - we accept only numbers with one sign
// checks for 0, +0 and -0 are there because atoi returns 0 in some cases
// so we shouldn't s it if it is not normal value 0
// should free variable is set to 1 if yes and 0 if no
void	fill_a(t_stack *a, char *str)
{
	int		value;
	char	*temp;

	if (!str)
		put_error(a);
	value = 1;
	if (ft_strlen(str) == 0)
		return ;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			value *= -1;
		str++;
	}
	temp = str;
	while (*temp && (*temp >= '0' && *temp <= '9'))
		temp++;
	if (*temp != '\0')
		put_error(a);
	if (is_bigger_than_int(str, value))
		put_error(a);
	value = value * ft_atoi(str);
	if (value == 0 && ft_strncmp(str, "0", 1) && ft_strncmp(str, "+0", 2)
		&& ft_strncmp(str, "-0", 2))
		put_error(a);
	if (has_duplicates(value, a))
		put_error(a);
	ft_stackadd_back(a, ft_stacknew(value));
	a->size += 1;
}

void	fill_a_free(t_stack *a, char *str, char **arr)
{
	int		value;
	char	*temp;

	if (!str)
	{
		free_array(arr);
		put_error(a);
	}
	value = 1;
	if (ft_strlen(str) == 0)
		return ;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			value *= -1;
		str++;
	}
	temp = str;
	while (*temp && (*temp >= '0' && *temp <= '9'))
		temp++;
	if (*temp != '\0')
	{
		free_array(arr);
		put_error(a);
	}
	if (is_bigger_than_int(str, value))
	{
		free_array(arr);
		put_error(a);
	}
	value = value * ft_atoi(str);
	if (value == 0 && ft_strncmp(str, "0", 1) && ft_strncmp(str, "+0", 2)
		&& ft_strncmp(str, "-0", 2))
	{
		free_array(arr);
		put_error(a);
	}
	if (has_duplicates(value, a))
	{
		free_array(arr);
		put_error(a);
	}
	ft_stackadd_back(a, ft_stacknew(value));
	a->size += 1;
}

/*  fills a stack from string input
a. if (j > (int)ft_strlen(str)) --> if j
 is already after string we can quit because then we would go out of scope */
void	fill_a_from_str(t_stack *a, char *str)
{
	char	**arr;
	char	*temp;
	int		i;

	arr = ft_split(str, ' ');
	if (!arr)
	{
		free_array(arr);
		put_error(a);
	}
	i = 0;
	while (arr[i] != NULL)
	{
		temp = arr[i];
		if (!temp)
		{
			free_array(arr);
			put_error(a);
		}
		fill_a_free(a, temp, arr);
		i++;
	}
	free_array(arr);
}

int	main(int argc, char *argv[])
{
	int		i;
	t_stack	a;
	t_stack	b;

	i = 0;
	a.head = NULL;
	a.size = 0;
	b.head = NULL;
	b.size = 0;
	if (argc <= 1 || (argc == 2 && ft_strlen(argv[1]) == 0)
		|| is_only_spaces(argv[1]))
		exit(EXIT_SUCCESS);
	else if (argc == 2)
		fill_a_from_str(&a, argv[1]);
	else
	{
		while (++i < argc)
			fill_a(&a, argv[i]);
	}
	find_values(&a);
	algorithm(&a, &b);
	ft_stackclear(&a);
	ft_stackclear(&b);
	return (0);
}
