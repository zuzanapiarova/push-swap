/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:58:25 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/08/12 18:36:23 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void ft_lstadd_back(t_stack *stack, t_node *new)
{
	t_node *temp;

	if (!stack || !new)
		return;
	if(stack->head == NULL)
		stack->head = new;
	else
	{
		temp = stack->head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

t_node	*ft_lstnew(int value)
{
	t_node	*result;

	result = (t_node *)malloc(sizeof(t_node));
	if (!result)
		return (NULL);
	result->value = value;
	result->next = NULL;
	return (result);
}

void print_stack(t_stack *n)
{
	printf("size: %d\n", n->size);
	t_node *current = n->head;
	while (current)
	{
		printf("%d\n", current->value);
		current = current->next;
	}
}

void check_duplicates(int value, t_node *n)
{
	t_node *current = n;
	while (current)
	{
		if (current->value == value)
		{
			ft_putstr_fd(2, "Error\n");
			exit(EXIT_FAILURE);
		}
		else
			current = current->next;
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ds1;
	unsigned char	*ds2;

	i = 0;
	ds1 = (unsigned char *)s1;
	ds2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n && ds1[i])
	{
		if (ds1[i] != ds2[i] || i == n - 1)
			return (ds1[i] - ds2[i]);
		i++;
	}
	return (ds1[i] - ds2[i]);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(int fd, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_atoi(const char *nptr)
{
	int	r;
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	r = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		r = r * 10 + (nptr[i] - '0');
		i++;
	}
	return (r * sign);
}
