#include "shell.h"

int		ft_isquote(int c)
{
	return (c == '\"');
}

int		ft_isprint_special(int c)
{
	if (c == '!')
		return (1);
	if (c >= '#' && c <= '&')
		return (1);
	if (c >= '\'' && c <= ';')
		return (1);
	if (c == '=')
		return (1);
	if (c >= '?' && c <= '@')
		return (1);
	if (c >= '{' && c <= '~')
		return (1);
	if (c >= '[' && c <= '`')
		return (1);
	return (0);
}

int		ft_isalnum_isprint_special(int c)
{
	return (ft_isalnum(c) || ft_isprint_special(c));
}

int		counter_argument(char *line, char **delim)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (*line)
	{
		while (*line == ' ')
			line++;
		while (delim[i])
		{
			if (!ft_strncmp(line, delim[i], (int)ft_strlen(delim[i])))
			{
				line = line + (int)ft_strlen(delim[i]) - 1;
				if (*line != delim[i][0])
					counter++;
				break ;
			}
			i++;
		}
		if (ft_isalnum_isprint_special(*line))
		{
			while (ft_isalnum_isprint_special(*line))
				line++;
			counter++;
		}
		else if (ft_isquote(*line))
		{
			counter++;
			while (*line++)
			{
				if (*line == '\"')
				{
					line++; //moche
					break ;
				}
			}
		}
		i = 0;
	}
	return (counter);
}

char	*cut_word_by_delim(char **str, char **delim)
{
	char	*dup;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while ((str[0]) && ((*str[0]) == ' '))
		str[0]++;
	while (delim[len])
	{
		if (str[0][0] == '"')
		{
			i = 1;
			while (str[0][i] != '"')
				i++;
			dup = str[0];
			str[0] = str[0] + ++i;
			return (ft_strsub(dup, 0, i));
		}
		if (ft_strncmp(str[0], delim[len], (int)ft_strlen(delim[len])) == 0)
		{
			if (((str[0][ft_strlen(delim[len])]) != delim[len][0]))
			{
				str[0] = str[0] + strlen(delim[len]);
				return (ft_strsub(delim[len], 0, ft_strlen(delim[len])));
			}
			break ;
		}
		len++;
	}
	while (str[0][i] && ((ft_isalnum_isprint_special(str[0][i])
					|| str[0][i] == '-') || (delim[len]
						&& (str[0][i] == delim[len][0]))))
		i++;
	dup = ft_strsub(str[0], 0, i);
	str[0] = str[0] + i;
	return (dup);
}
