#include "shell.h"

static int ft_isquote(int c)
{
    if(c == '\"')
        return 1;
    return 0;
}

int	ft_isprint_special(int c)
{
    if (c == 33)
        return (1);
    if (c >= 35 && c <= 37)
        return (1);
    if (c >= 39 && c <= 59)
        return (1);
    if (c == 61)
        return (1);
    if (c >= 63 && c <= 64)
        return (1);
    return (0);
}

int ft_isalnum_isprint_special(int c)
{
    return (ft_isalnum(c) || ft_isprint_special(c));
}

int counter_argument(char *line, char **delim)
{
    int i;
    int counter;

    i = 0;
    counter = 0;
    while(*line)
    {
        while(*line == ' ')
            line++;
        while(delim[i])
        {
            if(strncmp(line, delim[i], (int)strlen(delim[i])) == 0)
            {
                line = line + strlen(delim[i]);
                if(*line != delim[i][0])
                    counter++;
                break;
            }
            i++;
        }
        if(ft_isalnum_isprint_special(*line))
        {
            while(ft_isalnum_isprint_special(*line))
                line++;
            counter++;
        }
        else if(ft_isquote(*line))
        {
            counter++;
            while(*line++)
            {
                if(*line == '\"')
                {
                    line++; //moche
                    break;
                }
            }
        }
        i = 0;
    }
    return (counter);
}

static char *cut_word_by_delim(char **str, char **delim)
{
    char *dup;
    int len;
    int i;

    i = 0;
    len = 0;

    while ((str[0]) && ((*str[0]) == ' '))
        str[0]++;
    while(delim[len])
    {
        if(str[0][0] == '"')
        {
            i = 1;
            while(str[0][i] != '"')
                i++;
            dup = str[0];
            str[0] = str[0] + ++i;
            return (ft_strsub(dup, 0, i));
        }

        if(strncmp(str[0], delim[len], (int)strlen(delim[len])) == 0)
        {
            if(((str[0][strlen(delim[len])]) != delim[len][0]))
            {
                str[0] = str[0] + strlen(delim[len]);
                return (ft_strsub(delim[len], 0, strlen(delim[len])));
            }
            break;
        }
        len++;
    }
    while (str[0][i] && ((ft_isalnum_isprint_special(str[0][i]) || str[0][i] == '-') ||
                         (delim[len] && (str[0][i] == delim[len][0]))))
        i++;
    dup = ft_strsub(str[0], 0, i);
    str[0] = str[0] + i;
    return (dup);
}

size_t	get_array_size(char **array)
{
	size_t	size;
	int	i;

	size = 0;
	i = 0;
	while (array[i])
		size += ft_strlen(array[i++]);
	return (size + size - 1);
}

void	join_and_delete(char **dest, char *to_join)
{
	char	*del;

	del = *dest;
	*dest = ft_strjoin(*dest, to_join);
	ft_strdel(&del);
}

void	copy_array_in_str(char **str, char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		join_and_delete(str, array[i]);
		i++;
		if (array[i])
			join_and_delete(str, " ");
	}
}

char	*make_str_from_array(char **array)
{
	char	*str;
	size_t	size;

	size = get_array_size(array);
	if (!(str = (char *)ft_memalloc(sizeof(char) * size + 1)))
		return (NULL);
	copy_array_in_str(&str, array);
	return (str);
}

char *split_command(char *line, char **delim)
{
    int len_tab;
    char **formatted_array;
    char *formatted_string;
    int i;

    len_tab = counter_argument(line, delim);
    formatted_array = (char **)malloc(sizeof(*formatted_array) * len_tab + 1);
    i = 0;
    if (formatted_array)
    {
        while (i < len_tab)
        {
            formatted_array[i] = cut_word_by_delim(&line, delim);
            i++;
        }
    }
    formatted_array[i] = NULL;
    formatted_string = make_str_from_array(formatted_array);
    erase_char_array(formatted_array);
    return (formatted_string);
}
