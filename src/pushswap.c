/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:19 by zpiarova          #+#    #+#             */
/*   Updated: 2024/10/03 15:44:45 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

// throw error and end program, free memory
void	put_error(t_stack *a)
{
	ft_putstr_fd("Error.\n", 2);
	ft_stackclear(a);
	exit(EXIT_SUCCESS);

}

// fills stack a from string input in parameter which is input from program arguments
// if string is empty don't process it and go to next one
// check for sign - we accept only numbers with one sign
// checks for 0, +0 and -0 are there because atoi returns 0 in some cases
// so we shouldn't s it if it is not normal value 0
// should free variable is set to 1 if yes and 0 if no
void	fill_a(t_stack *a, char *str, int should_free)
{
	int		value;
	char	*temp;

	if (!str)
	{
		if (should_free)
			free(str);
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
	// handle passing in just spaces - one or more - causes segfault
	// while (*temp && *temp == ' ')
	// 	temp++;
	// if (*temp != '\0')
	// {
	// 	return ;
	// }
	temp = str;
	while (*temp && (*temp >= '0' && *temp <= '9')) // 3. while string contains digits move through it, if does not end in NULL means we encountered other character so we error and exit
		temp++;
	if (*temp != '\0')
	{
		// should free str if it is from one large string input type
		if (should_free)
			free(str);
		put_error(a);
	}
	if (is_bigger_than_int(str, value))
	{
		// should free str if it is from one large string input type
		if (should_free)
			free(str);
		put_error(a);
	}
	value = value * ft_atoi(str);
	if (value == 0 && ft_strncmp(str, "0", 1) && ft_strncmp(str, "+0", 2)
		&& ft_strncmp(str, "-0", 2))
	{
		// should free str if it is from one large string input type
		if (should_free)
			free(str);
		put_error(a);
	}
	check_duplicates(value, a);
	ft_stackadd_back(a, ft_stacknew(value));
	a->size += 1;
}

/*  fills a stack from string input
a. if (j > (int)ft_strlen(str)) --> if j
 is already after string we can quit because then we would go out of scope */
void	fill_a_from_str(t_stack *a, char *str)
{
	char **arr;
	char *temp;
	int i;

	arr = ft_split(str, ' ');
	if (!arr)
	{
		ft_putstr_fd("Error.\n", 2);
		ft_stackclear(a);
		exit(EXIT_SUCCESS);
	}
	i = 0;
	while (arr[i] != NULL)
	{
		temp = arr[i];
		if (!temp)
		{
			ft_putstr_fd("Error.\n", 2);
			free(temp);
			ft_stackclear(a);
			exit(EXIT_SUCCESS);
		}
		fill_a(a, temp, 1);
		free(temp);
		i++;
	}
	free(arr);
}

void	init_stacks(t_stack *a, t_stack *b)
{
	a->head = NULL;
	a->size = 0;
	a->name = "a";
	b->head = NULL;
	b->size = 0;
	b->name = "b";
}

int	main(int argc, char *argv[])
{
	int		i;
	t_stack	a;
	t_stack	b;

	i = 0;
	init_stacks(&a, &b);
	if (argc <= 1 || (argc == 2 && ft_strlen(argv[1]) == 0))
		exit(EXIT_SUCCESS);
	else if (argc == 2)
		fill_a_from_str(&a, argv[1]);
	else
	{
		while (++i < argc)
			fill_a(&a, argv[i], 0);
	}
	find_values(&a);
	algorithm(&a, &b);
	print_stack(&a);
	ft_stackclear(&a);
	ft_stackclear(&b);
	return (0);
}

// TODO:
// !! passing in one or more spaces in str without number makes segfault
// maybe we need to free strings from array allocated for string input in the fill_a function too
