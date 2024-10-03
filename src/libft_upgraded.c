/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_upgraded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:52:29 by zpiarova          #+#    #+#             */
/*   Updated: 2024/10/03 14:45:25 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	ft_stackadd_back(t_stack *stack, t_node *new_node)
{
	t_node	*temp;

	if (!stack || !new_node)
		return ;
	if (stack->head == NULL)
		stack->head = new_node;
	else
	{
		temp = stack->head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

t_node	*ft_stacknew(int value)
{
	t_node	*result;

	result = (t_node *)malloc(sizeof(t_node));
	if (!result)
		return (NULL);
	result->value = value;
	result->next = NULL;
	return (result);
}

t_node	*ft_stacklast(t_stack *s)
{
	t_node	*temp;

	if (!s)
		return (NULL);
	temp = s->head;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	ft_stackclear(t_stack *s)
{
	t_node	*current_el;
	t_node	*temp;

	if (!s || !s->head)
		return ;
	current_el = s->head;
	while (current_el)
	{
		temp = current_el->next;
		free(current_el);
		current_el = temp;
	}
	s->head = NULL;
}

// compares if int represented as string is bigger than max int value
// if string is longer than max int length, it is definitelly bigger - return 1
// if string is shorter than max int length, it is definitely smaller - return 0
// else compare max int string and input string character by character
int	is_bigger_than_int(const char *num_str, int value)
{
	const char	*int_max_str;
	int			len;
	int			i;

	i = 0;
	int_max_str = "2147483647";
	if (!ft_strncmp(num_str, "2147483648", 10) && value == -1)
		return 0;
	while (*num_str == '0')
		num_str++;
	len = ft_strlen(num_str);
	if (len > (int)ft_strlen(int_max_str))
		return 1;
	else if (len < (int)ft_strlen(int_max_str))
		return 0;
	while (i < len)
	{
		if (num_str[i] > int_max_str[i])
			return 1;
		else if (num_str[i] < int_max_str[i])
			return 0;
		i++;
	}
	return (0);
}
