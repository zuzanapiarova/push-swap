/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:20:21 by zpiarova          #+#    #+#             */
/*   Updated: 2024/10/03 20:20:35 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	get_sign(char *str)
{
	int	value;

	value = 1;
	if (*str == '-')
		value *= -1;
	return (value);
}

void	free_array(char **arr)
{
	char	*temp;
	int		i;

	i = 0;
	while (arr[i])
	{
		temp = arr[i];
		if (!temp)
			i++;
		free(temp);
		i++;
	}
	free(arr);
}

int	is_only_spaces(char *str)
{
	while (*str && *str == ' ')
		str++;
	if (*str == '\0')
		return (1);
	return (0);
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
		return (0);
	while (*num_str == '0')
		num_str++;
	len = ft_strlen(num_str);
	if (len > (int)ft_strlen(int_max_str))
		return (1);
	else if (len < (int)ft_strlen(int_max_str))
		return (0);
	while (i < len)
	{
		if (num_str[i] > int_max_str[i])
			return (1);
		else if (num_str[i] < int_max_str[i])
			return (0);
		i++;
	}
	return (0);
}
