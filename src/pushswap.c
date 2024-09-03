/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:52:23 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/08/17 16:42:02 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void check_duplicates(int value, t_node *n)
{
	t_node *current = n;
	while (current)
	{
		if (current->value == value)
		{
			printf("Duplicates");
			ft_putstr_fd(2, "Error\n");
			exit(EXIT_FAILURE);
			// TODO: FREE AND DELETE ENTIRE STACK
		}
		else
			current = current->next;
	}
}

bool	is_valid_arg(char *s)
{
	int i;
	int len;

	len = ft_strlen(s);
	i = 0;
	while (*s == 32 || ft_isdigit(*s) || *s == '-' || *s == '+')
	{
		i++;
		s++;
	}
	return (i == len);
}

void fill_a(t_stack *a, char *val)
{
	int		value;
	t_node	*node;

	value = ft_atoi(val);
	check_duplicates(value, a->head);
	if (value == 0 && ft_strncmp(val, "0", ft_strlen(val)) != 0) // this means atoi could not convert the number thus returns 0, but we shouldnt do it if it is normal value 0
	{
		printf("error fill_a");
		ft_putstr_fd(2, "Error\n");
		exit(EXIT_FAILURE);
		// TODO: FREE AND DELETE ENTIRE STACK
	}
	else
	{
		node = ft_lstnew(value);
		ft_lstadd_back(a, node);
		a->size += 1;
	}
}

void fill_a_from_str(t_stack *a, char *str)
{
		int j = 0;
		char *temp;

		while (str[j])
		{
			int len = 0;
			if (j > (int)ft_strlen(str))
				break;
			if (str[j] == 32)
				j++;
			while (ft_isdigit(str[j]) || str[j] == '-' || str[j] == '+')
			{
				len++;
				j++;
			}
			temp = ft_substr(str, j - len, len);
			fill_a(a, temp);
			free(temp);
			j++;
		}
}

bool is_sorted(t_stack *a)
{
	t_node *node = a->head;

	while (node && node->next && node->value < node->next->value)
		node = node->next;
	if (!node -> next)
		return 1;
	else
		return 0;
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
	t_node *node;
	int midpoint;

	if (is_sorted(a))
		EXIT_SUCCESS;
	node = a->head;
	if (node->next == NULL || (node->next && node->value < node->next->value))
		midpoint = node->value;
	else if (node->next && node->value > node->next->value)
		midpoint = node->next->value;

	while (a->head)
	{
		// compare the two first elements
		// keep the bigger in a, push the smaller to b
		// keep midpoint value against which each value is compared
		node = a->head;
		// if midpoint is smaller than smaller one of the two values
		if (node->next && node->value < node->next->value)
		{
			if (node->value < midpoint)
			{
				midpoint = node->value;
				pb(a, b);
			}
			else if (node->value > midpoint)
			{
				ra(a);
			}
		}
		else if (node->next && node->value > node->next->value)
		{
			if (midpoint > node->next->value)
			{
				midpoint = node->next->value;
				sa(a);
				pb(a, b);
			}
			else if (node->value > midpoint)
				ra(a);
		}
		printf("midpoint: %d\n", midpoint);
		// // if the midpoint is bigger than both the values
		// if (node->next && node->value > node->next->value)
		// {
		// 	sa(a);
		// 	pb(a, b);
		// 	continue;
		// }
		// else if (node->next && node->value < node->next->value)
		// 	ra(a);
		// else
		// 	pb(a, b);
	}
}

int	main(int argc, char *argv[])
{
	int		i;
	t_stack	a;
	t_stack	b;

	i = 0;
	a.head = NULL;
	a.size = 0;
	a.name = "a";
	b.head = NULL;
	b.size = 0;
	b.name = "b";
	if (argc <= 1)
	{
		ft_putstr_fd(2, "Error\n");
		exit(EXIT_FAILURE);
	}
	// if we want to pass one string of arguments but it is not valid
	else if (!is_valid_arg(argv[1]))
	{
		ft_putstr_fd(2, "Error\n");
		exit(EXIT_FAILURE);
	}
	// if the arguments are passed in as string
	else if (argc == 2 && is_valid_arg(argv[1]))
		fill_a_from_str(&a, argv[1]);
	// if the arguments are passed in as multiple strings one after another
	else
	{
		while (++i < argc)
			fill_a(&a, argv[i]);
	}
	// print_stack(&a);

	// ----- THE ACTUAL PUSH SWAP SORTING ALGORITHM
	algorithm(&a, &b);
	// ---------------------------------------------

	print_stack(&a);
	print_stack(&b);
	// TODO: FREE AND DELETE BOTH STACKS
	return 0;
}

// TODO
// argument as string cannot handle - and returns error
// handle if int is bigger than max value for its data type
// free stacks in all pointed cases
