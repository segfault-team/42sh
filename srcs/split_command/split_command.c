#include "shell.h"

size_t		get_array_size(char **array)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (array[i])
		size += ft_strlen(array[i++]);
	return (size + size - 1);
}

void		join_and_delete(char **dest, char *to_join)
{
	char	*del;

	del = *dest;
	*dest = ft_strjoin(*dest, to_join);
	ft_strdel(&del);
}

void		copy_array_in_str(char **str, char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		join_and_delete(str, array[i]);
		i++;
		if (array[i])
			join_and_delete(str, " ");
	}
}

char		*make_str_from_array(char **array)
{
	char	*str;
	size_t	size;

	size = get_array_size(array);
	if (!(str = (char *)ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	copy_array_in_str(&str, array);
	return (str);
}

char		*split_command(char *line, char **delim)
{
	int		len_tab;
	char	**formatted_array;
	char	*formatted_string;
	int		i;

	len_tab = counter_argument(line, delim);
	formatted_array = (char **)malloc(sizeof(*formatted_array) * (len_tab + 1));
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
