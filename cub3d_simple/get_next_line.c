/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:40:49 by esommier          #+#    #+#             */
/*   Updated: 2019/12/03 15:59:07 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static int	free_str(char **str, int k, t_param *p)
{
	if (!(str == NULL))
	{
		free(*str);
		*str = NULL;
	}
	if (k == -1)
		ft_error("Error\nParsing error.\n", p);
	return (k);
}

static int	new_line(char **line, char **dest, t_param *p)
{
	int		len;
	char	*tmp;

	len = 0;
	while ((*dest)[len] != '\n' && (*dest)[len] != '\0')
		len++;
	if ((*dest)[len] == '\0')
	{
		if (!(*line = ft_strdup(*dest)))
			return (free_str(dest, -1, p));
		return (free_str(dest, 0, p));
	}
	if ((*dest)[len] == '\n')
	{
		if (!(*line = ft_substr(*dest, 0, len)))
			return (free_str(dest, -1, p));
		if (!(tmp = ft_strdup(&(*dest)[len + 1])))
			return (free_str(dest, -1, p));
		free(*dest);
		*dest = tmp;
	}
	return (1);
}

static int	next_line(char **line, char **dest, int nb, t_param *p)
{
	if (nb < 0)
		return (free_str(dest, -1, p));
	if (nb == 0 && (*dest == NULL))
	{
		if (!(*line == (char *)malloc(sizeof(char))))
			return (free_str(dest, -1, p));
		(*line)[0] = '\0';
		return (free_str(dest, 0, p));
	}
	return (new_line(line, dest, p));
}

int	get_next_line(int fd, char **line, t_param *p, int clean_buf)
{
	char	buf[BUFFER_SIZE + 1];
	static char	*dest;
	ssize_t		nb;
	int		i;

	i = 0;
	//if (!(buf = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
	//	return (free_str(&dest, -1, p));
	if (clean_buf)
	{
		while (i < BUFFER_SIZE + 1)
		{
			dest[i] = '\0';
			i++;
		}
		printf("clean_buf");
		return (0);
	}
	if (line == NULL || fd < 0)
		return (free_str(&dest, -1, p));
	i = 0;
	while (i < BUFFER_SIZE + 1)
	{
		buf[i] = '\0';
		i++;
	}
	while ((nb = read(fd, buf, BUFFER_SIZE)) > 0)
	//while(ft_strchr(dest, '\n') == -1)
	{
		//nb = read(fd, buf, BUFFER_SIZE);
		//printf("nb: %zd\n", nb);
		//buf[nb] = '\0';
		if (dest == NULL)
		{
			if (!(dest = ft_strdup(buf)))
				return (free_str(&dest, -1, p));
		}
		else if (!(dest = ft_strjoin(dest, buf)))
			return (free_str(&dest, -1, p));
	}
	//free(buf);
	return (next_line(line, &dest, nb, p));
}
