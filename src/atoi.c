int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	answer;
	int	index;

	index = 0;
	answer = 0;
	while (str[index] == '\n' || str[index] == '\t' || str[index] == ' ')
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
            return -1; 
            index++;
	}
	while (ft_isdigit(str[index]))
	{
		answer *= 10;
		answer += (str[index]) - '0';
		index++;
	}
	return (answer);
}

