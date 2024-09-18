/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:19 by zpiarova          #+#    #+#             */
/*   Updated: 2024/09/17 23:26:09 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

// TODO: ADD INDEX OF EACH NODE OF EACH LIST
// this means atoi could not convert the number thus returns 0, but we shouldnt do it if it is normal value 0
// 	if (value == 0 && ft_strncmp(val, "0", ft_strlen(val)) != 0)
// fills stack a from numbers received in program arguments
void	fill_a(t_stack *a, char *val)
{
	int		value;
	t_node	*node;
	int		i;

	i = 0;
	while(i < (int)ft_strlen(val)) //we do this because we want to check if input value is a valid number
	{
		if (!ft_isdigit(val[i]) && val[i] != '+' && val[i] != '-')
		{
			ft_putstr_fd("Error in filing stack. Invalid arguments. Must be numbers only.\n", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	value = ft_atoi(val);
	if (value == 0 && ft_strncmp(val, "0", 1) && ft_strncmp(val, "+0", 2) && ft_strncmp(val, "-0", 2))
	{
		ft_putstr_fd("Error in filing stack. Invalid arguments. Must be numbers only.\n", 2);
		exit(EXIT_FAILURE);
		// TODO: FREE AND DELETE ENTIRE STACK
	}
	check_duplicates(value, a->head);
	node = ft_stacknew(value);
	ft_stackadd_back(a, node);
	a->size += 1;
}

void	fill_a_from_str(t_stack *a, char *str)
{
	int		j;
	char	*temp;
	int		len;

	j = 0;
	while (str[j])
	{
		if (j > (int)ft_strlen(str)) // if j is already after the string
			break;
		len = 0;
		if (str[j] == 32)
			j++;
		while (ft_isdigit(str[j]) || str[j] == '-' || str[j] == '+')
		{
			len++;
			j++;
		}
		if (j == 0)
		{
			ft_putstr_fd("Error in filing stack. Invalid arguments. Must be numbers only.\n", 2);
			exit(EXIT_FAILURE);
		}
		temp = ft_substr(str, j - len, len);
		fill_a(a, temp);
		free(temp);
		j++;
	}
}

// ideas
// stallin sort but each deleted element is pushed to a new array into the correct sorted spot
//then when we finish first iteration of stalin we have 2 sorted arrays
// now we just combine them back

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
	{
		ft_putstr_fd("No arguments input. Enter numbers or string of numbers.\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (argc == 2)
		fill_a_from_str(&a, argv[1]);
	else
	{
		while (++i < argc)
			fill_a(&a, argv[i]);
	}
	find_values(&a);
	print_stack(&a);
	algorithm(&a, &b);
	print_stack(&a);
	ft_stackclear(&a);
	ft_stackclear(&b);
	// TODO: free both stacks and all their nodes
	return (0);
}

// TODO
// handle if int is bigger than max value for its data type
// proper memory allocation and freeing - leaks
// ./push_swap 1a, .. 4 5 1a, "4a 5a 6a": includes number if it ends with character when it shouldnt. in string every number and last in single arguments
// how to put functions into buffer: functions return string with their name and this is then assigned to buffer variable
// WHAT IF WE ADD FIRST, LAST, MAX, MIN PARAMETERS TO OUR LISTS
// handle if we want to pb but there is nothign left to pb, same with pa
// add value of middle element and then perform operations based on it - if element is smalle than middle value
