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
	tmp = NULL;
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
			return (0);
		(*line)[0] = '\0';
		return (free_str(dest, 0, p));
	}
	return (new_line(line, dest, p));
}

int	get_next_line(int fd, char **line, t_param *p)
{
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;
	static char	*dest;
	ssize_t		nb;

	if (line == NULL || fd < 0)
		return (free_str(&dest, -1, p));
	//buf = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	//nb = read(fd, buf, BUFFER_SIZE);
	while ((nb = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[nb] = '\0';
		if (dest == NULL)
		{
			if (!(dest = ft_strdup(buf)))
				return (free_str(&(dest), -1, p));
		}
		else
		{
			tmp = ft_strjoin(dest, buf);
			free(dest);
			dest = tmp;
		}
		if (ft_strchr(dest, '\n') != -1)
			break ;
		//nb = read(fd, buf, BUFFER_SIZE);
	}
	//free(buf);
	return (next_line(line, &dest, nb, p));
}
