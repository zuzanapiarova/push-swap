/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:52:23 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/08/17 09:23:43 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
bool	is_valid_arg(char *s)
{
	int i;
	int len;

	len = ft_strlen(s);
	i = 0;
	while (*s == 32 || ft_isdigit(*s))
	{
		i++;
		s++;
	}
	if (i == len)
		return (1);
	else
		return (0);
}

void fill_a(t_stack *a, char *val)
{
	int		value;
	t_node	*node;

	value = ft_atoi(val);
	check_duplicates(value, a->head);
	if (value == 0 && ft_strncmp(val, "0", ft_strlen(val)) != 0) // this means atoi could not convert the number thus returns 0, but we shouldnt do it if it is normal value 0
	{
		ft_putstr_fd(2, "Error\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		node = ft_lstnew(value);
		ft_lstadd_back(a, node);
		a->size += 1;
	}
}

// ideas
// stallin sort but each deleted element is pushed to a new array into the correct sorted spot
// when adding element to b, compare to first element, if not push it back
// then when we finish first iteration of stalin we have 2 sorted arrays
// now we just combine them back

//check with 2 1 3 6 5 8:
/*

	sa(a);
	pb(a, b);
	pb(a, b);
	pb(a, b);
	ra(a);
	rb(b);
	rra(a);
	rrb(b);
	sa(a);
	pa(a, b);
	pa(a, b);
	pa(a, b);
*/
void algorithm(t_stack *a, t_stack *b)
{
	sa(a);
	pb(a, b);
	pb(a, b);
	pb(a, b);
	ra(a);
	rb(b);
	rra(a);
	rrb(b);
	sa(a);
	pa(a, b);
	pa(a, b);
	pa(a, b);
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
	if (argc <= 1)
	{
		ft_putstr_fd(2, "Error\n");
		exit(EXIT_FAILURE);
	}
	// if the arguments are passed in as string
	else if (argc == 2 && is_valid_arg(argv[1]))
	{
		char *str = argv[1];
		int j = 0;
		char *temp;

		while (str[j])
		{
			int len = 0;
			if (j > (int)ft_strlen(str))
				break;
			if (str[j] == 32)
				j++;
			while (ft_isdigit(str[j]))
			{
				len++;
				j++;
			}
			temp = ft_substr(str, j - len, len);
			fill_a(&a, temp);
			free(temp);
			j++;
		}
	}
	// if the arguments are passed in as multiple strings one after another
	else
	{
		while (++i < argc)
			fill_a(&a, argv[i]);
	}
	print_stack(&a);

	// ----- THE ACTUAL PUSH SWAP SORTING ALGORITHM
	algorithm(&a, &b);
	// ---------------------------------------------

	print_stack(&a);
	return 0;
}

// TODO
// handle if int is bigger than max value for its data type
