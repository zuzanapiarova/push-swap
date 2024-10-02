/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:19 by zpiarova          #+#    #+#             */
/*   Updated: 2024/10/02 20:32:05 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

// fills stack a from numbers received in program arguments
// a. if (value == 0 && ft_strncmp(val, "0", ft_strlen(val)) != 0) :
// --> this means atoi could not convert the number thus returns 0
// but we shouldnt do it if it is normal value 0
// b. (int)ft_strlen(val))
// --> we do this because we want to check if input value is a valid number
/* void	fill_a(t_stack *a, char *str)
{
	int	value;
	int	i;

	i = 0;
	while (i < (int)ft_strlen(str))
	{
		if (!ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-')
		{
			ft_putstr_fd("Error.\n", 2);
			ft_stackclear(a);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	value = ft_atoi(str);
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
} */

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
		ft_putstr_fd("Errorrr.\n", 2);
		ft_stackclear(a);
		exit(EXIT_SUCCESS);
	}
	// TODO: handle string bigger than int
	// TODO: add checks if atoi is 0 and number is not 0
	value = value * ft_atoi(str);
	printf("%d\n", value);
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
	int		j;
	int		len;
	char	*temp;

	j = 0;
	while (str[j])
	{
		if (j > (int)ft_strlen(str))
			break ;
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
			ft_putstr_fd("Error.\n", 2);
			ft_stackclear(a);
			exit(EXIT_SUCCESS);
		}
		temp = ft_substr(str, j - len, len);
		fill_a(a, temp);
		free(temp);
		j++;
	}
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
// handle passing in one or more spaces
// handle first argument not being sorted properly
