#include "codexion.h"

int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (SUCCESS);
	return (FAILURE);
}

static int	ft_isnumber(const char *s)
{
	int	i;

	// guard against empty strings
	if (!s || !s[0])
		return (FAILURE);
	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	ft_atoi(const char *str)
{
	int	answer;
	int	index;
	int	digit;

	index = 0;
	answer = 0;
	while (str[index] == '\n' || str[index] == '\t' || str[index] == ' ')
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			return (-1);
		index++;
	}
	// CHANGE: ADD OVERFLOW CHECK
	while (str[index])
	{
		digit = str[index] - '0';
		if (answer > (INT_MAX - digit) / 10)
			return (-1);
		answer *= 10;
		answer += digit;
		index++;
	}
	return (answer);
}

int	parsing_args(char **args)
{
	int		i;
	char	*c;

	i = 1;
	while (i < 8)
	{
		c = args[i];
		// CHANGE: removed redundent print statement and guard against empty input
		if (ft_isnumber(c) == FAILURE)
			return (FAILURE);
		if (ft_atoi(c) == -1)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
