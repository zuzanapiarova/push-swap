/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:19 by zpiarova          #+#    #+#             */
/*   Updated: 2024/10/07 21:25:59 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

// show error, free memory, end program
void	put_error(t_stack *a, char **arr)
{
	if (arr != NULL)
		free_array(arr);
	ft_putstr_fd("Error\n", 2);
	ft_stackclear(a);
	exit(EXIT_SUCCESS);
}

// fills stack a from string input
// if string is empty don't process it and go to next one
// checks for sign - we accept only numbers with one sign
// checks if we string consists of digits only
// checks for 0, +0 and -0 are there because atoi returns 0 in some cases
// so we shouldn't s it if it is not normal value 0
// should free variable is set to 1 if yes and 0 if no
void	fill_a(t_stack *a, char *str)
{
	int		value;
	char	*temp;

	if (!str)
		put_error(a, NULL);
	if (ft_strlen(str) == 0)
		return ;
	value = get_sign(str);
	if (*str == '+' || *str == '-')
		str++;
	temp = str;
	while (*temp && (*temp >= '0' && *temp <= '9'))
		temp++;
	if (*temp != '\0')
		put_error(a, NULL);
	if (is_bigger_than_int(str, value))
		put_error(a, NULL);
	value = value * ft_atoi(str);
	if (value == 0 && ft_strncmp(str, "0", 1) && ft_strncmp(str, "+0", 2)
		&& ft_strncmp(str, "-0", 2))
		put_error(a, NULL);
	if (has_duplicates(value, a))
		put_error(a, NULL);
	ft_stackadd_back(a, ft_stacknew(value));
	a->size += 1;
}

void	fill_a_free(t_stack *a, char *str, char **arr)
{
	int		value;
	char	*temp;

	if (!str)
		put_error(a, arr);
	if (ft_strlen(str) == 0)
		return ;
	value = get_sign(str);
	if (*str == '+' || *str == '-')
		str++;
	temp = str;
	while (*temp && (*temp >= '0' && *temp <= '9'))
		temp++;
	if (*temp != '\0')
		put_error(a, arr);
	if (is_bigger_than_int(str, value))
		put_error(a, arr);
	value = value * ft_atoi(str);
	if (value == 0 && ft_strncmp(str, "0", 1) && ft_strncmp(str, "+0", 2)
		&& ft_strncmp(str, "-0", 2))
		put_error(a, arr);
	if (has_duplicates(value, a))
		put_error(a, arr);
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
		put_error(a, NULL);
	}
	i = 0;
	while (arr[i] != NULL)
	{
		temp = arr[i];
		if (!temp)
		{
			free_array(arr);
			put_error(a, NULL);
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
	print_stack(&a);
	ft_stackclear(&a);
	ft_stackclear(&b);
	return (0);
}
