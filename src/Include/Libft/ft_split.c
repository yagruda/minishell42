/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:25:41 by yhruda            #+#    #+#             */
/*   Updated: 2025/01/05 17:18:37 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Function name ft_split
Prototype char **ft_split(char const *s, char c);
Turn in files-
Parameters s: The string to be split.
c: The delimiter character.
Return value The array of new strings resulting from the split.
NULL if the allocation fails.
External functs. malloc, free
Description Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimite */

#include "libft.h"

static int	is_delim(char c, char delim)
{
	return (c == delim);
}

static int	count_words(const char *str, char delim)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && is_delim(*str, delim))
			str++;
		if (*str)
		{
			count++;
			while (*str && !is_delim(*str, delim))
				str++;
		}
	}
	return (count);
}

static char	*alloc_word(const char *str, char delim)
{
	int		len;
	char	*word;
	int		i;

	len = 0;
	i = 0;
	while (str[len] && !is_delim(str[len], delim))
		len++;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static void	free_all(char **result, int i)
{
	while (i >= 0)
		free(result[i--]);
	free(result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	result = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (*s)
	{
		while (*s && is_delim(*s, c))
			s++;
		if (*s)
		{
			result[i] = alloc_word(s, c);
			if (!result[i])
				return (free_all(result, i - 1), NULL);
			i++;
			while (*s && !is_delim(*s, c))
				s++;
		}
	}
	result[i] = NULL;
	return (result);
}

/* int	main(void)
{
	char **words = ft_split("Hello,world,this,is,a,test", ',');
	int i = 0;
	if (!words)
		return (1);
	while (words[i])
	{
		printf("%s\n", words[i]);
		free(words[i]);
		i++;
	}
	free(words);
	return (0);
} */