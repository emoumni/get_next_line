/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoumni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:06:30 by emoumni           #+#    #+#             */
/*   Updated: 2023/03/12 15:06:32 by emoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*function_togetline(char *stored)
{
	size_t	j;
	size_t	k;
	char	*str;

	j = 0;
	if (!stored[j])
		return (NULL);
	while (stored[j] && stored[j] != '\n')
		j++;
	str = (char *)malloc(sizeof(char) * (j + 2));
	if (!str)
		return (NULL);
	j = 0;
	k = 0;
	while (stored[j] && stored[j] != '\n')
		str[k++] = stored[j++];
	if (stored[j] == '\n')
		str[k++] = stored[j++];
	str[k] = '\0';
	return (str);
}

char	*memorize_function(char *stored)
{
	size_t	j;
	size_t	k;
	char	*str;

	j = 0;
	while (stored[j] && stored[j] != '\n')
		j++;
	if (!stored[j])
	{
		free(stored);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(stored) - j + 1));
	if (!str)
		return (NULL);
	j++;
	k = 0;
	while (stored[j])
		str[k++] = stored[j++];
	str[k] = '\0';
	free(stored);
	return (str);
}

char	*readleft_memorize_function(int fd, char *stored)
{
	char	*buf;
	int		rd_byts;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
	{
		free(buf);
		return (NULL);
	}
	rd_byts = 1;
	while (!ft_strchr(stored, '\n') && rd_byts != 0)
	{
		rd_byts = read(fd, buf, BUFFER_SIZE);
		if (rd_byts == -1)
		{
			free(buf);
			return (NULL);
		}	
		buf[rd_byts] = '\0';
		stored = ft_strjoin(stored, buf);
	}
	free(buf);
	return (stored);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stored;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stored = readleft_memorize_function(fd, stored);
	if (!stored)
	{
		free(stored);
		return (NULL);
	}
	line = function_togetline(stored);
	stored = memorize_function(stored);
	return (line);
}
