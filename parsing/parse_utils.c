#include "../cub3d.h"

int	print_error(char *msg)
{
	static int has_printed;

	if (!has_printed)
	{
		has_printed = 1;
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	return (1);
}

int skipwhitespace(char *str, int pos)
{
	int i;

	i = pos;
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	return i;
}

int	count_elems(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == ' ')
		i++;
	while (s[i] != '\0')
	{
		if (s[i] != ' ' && (i == 0 || s[i - 1] == ' '))
			count++;
		i++;
	}
	return (count);
}

int parse_color_code(char *color, int *i)
{
	int value;
	int delta_i;

	value = 0;
	delta_i = 0;
	while (color[*i] && color[*i] != ',')
	{
		if (!ft_isdigit(color[*i]))
			return (-1);
		value = value * 10 + (color[*i] - '0');
		(*i)++;
		delta_i++;
	}
	if ((delta_i == 0 || delta_i > 3) || value > 255)
		return (-1);
	(*i)++;
	return (value);
}

char	*buildline(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	totallen;
	char	*final_s;

	len1 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	totallen = len1 + len2 + sizeof(char);
	final_s = (char *)malloc(sizeof(char) * totallen);
	if (final_s == NULL)
		return (NULL);
	if (s1)
	{
		ft_strlcpy(final_s, s1, totallen);
		ft_strlcat(final_s, s2, totallen);
	}
	else
		ft_strlcpy(final_s, s2, totallen);
	free(s1);
	return (final_s);
}
