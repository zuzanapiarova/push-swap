/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:19 by zpiarova          #+#    #+#             */
/*   Updated: 2024/10/03 08:01:48 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int is_bigger_than_int(const char *num_str, int value) {
	if (!ft_strncmp(num_str, "2147483648", 10) && value == -1)
		return 0;
    while (*num_str == '0') {
        num_str++;
    }
    // Define the string representation of INT_MAX for manual comparison
    const char *int_max_str = "2147483647";  // INT_MAX for 32-bit systems

    // Get the length of the input string
    int len = ft_strlen(num_str);
    int int_max_len = ft_strlen(int_max_str);

    // Compare lengths first
    if (len > int_max_len) {
        return 1;  // num_str is longer, so it's definitely bigger than INT_MAX
    } else if (len < int_max_len) {
        return 0;  // num_str is shorter, so it's definitely smaller than INT_MAX
    }

    // If lengths are equal, compare each digit manually
    for (int i = 0; i < len; i++) {
        if (num_str[i] > int_max_str[i]) {
            return 1;  // num_str has a greater digit at position i
        } else if (num_str[i] < int_max_str[i]) {
            return 0;  // num_str has a smaller digit at position i
        }
    }

    // If all digits are equal, the number is equal to INT_MAX
    return 0;
}

// fills stack a from numbers received in program arguments
// checks for 0, +0 and -0 are there because atoi returns 0 in some cases
// so we shouldn't s it if it is not normal value 0
void	fill_a(t_stack *a, char *str)
{
	int		value;
	char	*temp;

	if (!str) // Check if the string pointer is NULL
	{
		ft_putstr_fd("Error.\n", 2);
		ft_stackclear(a);
		exit(EXIT_SUCCESS);
	}
	value = 1;
	if (ft_strlen(str) == 0) //1. if string is empty just ignore it
		return ;
	if (*str == '+' || *str == '-') //2. we accept only numbers with one sign, else it is wrong, so we remember the sign and move past it
	{
		if (*str == '-')
			value *= -1;
		str++;
	}
	temp = str;
	while (*temp && (*temp >= '0' && *temp <= '9')) // 3. while string contains digits move through it, if does not end in NULL means we encountered other character so we error and exit
		temp++;
	if (*temp != '\0')
	{
		ft_putstr_fd("Error.\n", 2);
		ft_stackclear(a);
		exit(EXIT_SUCCESS);
	}
	// TODO: handle string bigger than int
	if (is_bigger_than_int(str, value))
	{
		ft_putstr_fd("Error.\n", 2);
		ft_stackclear(a);
		exit(EXIT_SUCCESS);
	}
	// TODO: add checks if atoi is 0 and number is not 0
	value = value * ft_atoi(str);
	if (value == 0 && ft_strncmp(str, "0", 1) && ft_strncmp(str, "+0", 2)
		&& ft_strncmp(str, "-0", 2))
	{
		ft_putstr_fd("Error.\n", 2);
		ft_stackclear(a);
		exit(EXIT_SUCCESS);
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
	int i;

	arr = ft_split(str, ' ');
	if (!arr)
	{
		ft_putstr_fd("Error.\n", 2);
		ft_stackclear(a);
		exit(EXIT_SUCCESS);
	}
	i = 0;
	while (arr[i])
	{
		if (!arr[i])
		{
			ft_putstr_fd("Error.\n", 2);
			free(arr);
			ft_stackclear(a);
			exit(EXIT_SUCCESS);
		}
		fill_a(a, arr[i]);

	}
	free(arr);
	// int		j;
	// int		len;
	// char	*temp;

	// j = 0;
	// while (str[j])
	// {
	// 	if (j > (int)ft_strlen(str))
	// 		break ;
	// 	len = 0;
	// 	if (str[j] == 32)
	// 		j++;
	// 	while (ft_isdigit(str[j]) || str[j] == '-' || str[j] == '+')
	// 	{
	// 		len++;
	// 		j++;
	// 	}
	// 	if (j == 0)
	// 	{
	// 		ft_putstr_fd("Error.\n", 2);
	// 		ft_stackclear(a);
	// 		exit(EXIT_SUCCESS);
	// 	}
	// 	temp = ft_substr(str, j - len, len);
	// 	fill_a(a, temp);
	// 	free(temp);
	// 	j++;
	// }
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
			fill_a(&a, argv[i]);
	}
	find_values(&a);
	algorithm(&a, &b);
	print_stack(&a);
	ft_stackclear(&a);
	ft_stackclear(&b);
	return (0);
}

// TODO: max int value
// saving to stack from str  not work properly
// handle passing in one or more spaces in str
// handle min int must allow -2147483648
