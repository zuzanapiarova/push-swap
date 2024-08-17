/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:58:25 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/08/17 09:57:01 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void ft_lstadd_back(t_stack *stack, t_node *new_node)
{
	t_node *temp;

	if (!stack || !new_node)
		return;
	if(stack->head == NULL)
		stack->head = new_node;
	else
	{
		temp = stack->head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
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

void print_stack(t_stack *stack)
{
	printf("size: %d\n", stack->size);
	t_node *current = stack->head;
	printf("-------------\n");
	while (current)
	{
		printf("%d\n", current->value);
		current = current->next;
	}
	printf("-------------\n");
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

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	str_len;
	size_t			i;

	i = 0;
	if (s == NULL)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substring = (char *)malloc((len + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	while (i < len)
	{
		substring[i] = s[i + start];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*copy;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
