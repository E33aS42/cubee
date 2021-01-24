/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:24:12 by esommier          #+#    #+#             */
/*   Updated: 2020/11/18 12:39:29 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_strstr(char *s1, char *s2)
{
	int	i1;
	int	i2;

	i1 = 0;
	while (s1[i1] != '\0')
	{
		i2 = 0;
		while (s2[i2] != '\0')
		{
			if (s1[i1] == s2[i2])
				return (i1);
			i2++;
		}
		i1++;
	}
	return (-1);
}

void	free_text_spr(char *s)
{
	if (s)
		free(s);
}

void	free_map(t_param *p)
{
	int	i;

	i = 0;
	if (p->map)
	{
		while (p->map[i])
		{
			free(p->map[i]);
			i++;
		}
		free(p->map);
	}
}

void	ft_error(char *s, t_param *p)
{
	int	len;

	len = ft_strlen(s);
	write(1, &s[0], len);
	free_map(p);
	exit(1);
}

void	ft_init(t_param *p)
{
	p->i = 0;
	p->token = 0;
	p->i1 = -1;
	p->i2 = 0;
	p->nb_line_map = 0;
	p->nb_col_map = 0;
	p->map = NULL;
	p->save = 0;
}

int	check_save(char *s)
{
	int		i;
	char	*cmp;

	cmp = "--save";
	i = 0;
	if (ft_strlen(s) == 6)
		return (ft_strcmp(s, cmp));
	return (0);
}

int	check_map_name(char *s)
{
	int		len;
	char	*cub;

	cub = ".cub";
	len = ft_strlen(s);
	if (ft_strlen(&s[len - 4]) == 4)
		return (ft_strcmp(&s[len - 4], cub));
	return (0);
}

int	ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);	
}

void	init_map(t_param *p)
{
	int	i;

	i = 0;
	p->map = malloc(sizeof(char *) * (p->nb_line_map + 1));
	while (i < p->nb_line_map)
	{
		p->map[i] = malloc(sizeof(char) * (p->nb_col_map + 1));
		i++;
	}
	p->map[i] = NULL;
}

void	get_size_map(char *line, t_param *p)
{
	int	len;

	if (ft_strstr(line, "01") > -1 && ft_strstr(line, "RFC") == -1
		&& p->token == 1)
	{
		p->nb_line_map++;
		len = ft_strlen(line);
		if (p->nb_col_map < len)
			p->nb_col_map = len;
	}
}

void	fill_raw_map(int i, char *line, t_param *p)
{
	int	j;

	j = 0;
	//printf("C\n");
	//printf("line[j]: %c\n", line[j]);
	while (line[j])
	{
		//printf("line[j]: %c\n", line[j]);
		//printf("1-p->map[i][j]: %c\n", p->map[i][j]);
		if (line[j] == ' ')
			p->map[i][j] = '4';
		else
			p->map[i][j] = line[j];
		//printf("2-p->map[i][j]: %c\n", p->map[i][j]);
		j++;
	}
	//printf("D\n");
	while (j < p->nb_col_map)
	{
		p->map[i][j] = '4';
		j++;
	}
	//printf("E\n");
	p->map[i][j] = '\0';
	//printf("line_map: %s\n", p->map[i]);
}

void	get_map(char *filename, t_param *p, int fd)
{
	int		fd2;
	int		r;
	char	*line;
	int		i;

	i = 0;
	init_map(p);
	p->token = 0;
	printf("fd; %d\n", fd);
	//fd2 = fd + 1;
	//openat(fd2, filename, O_RDONLY);
	fd2 = open(filename, O_RDONLY);
	//r = get_next_line(fd2, &line, p);
	while ((r = get_next_line(fd2, &line, p, NO_CLEAN_BUFFER)) > 0)
	{
		printf("A\n");
		if (ft_strstr(line, "01") == -1 && p->token == 1)
			break ;
		//printf("i1: %d\n", i);
		printf("line2: %s\n", line);
		if (ft_strstr(line, "01") > -1 && ft_strstr(line, "RFC") == -1
			&& p->token == 0)
			p->token = 1;
		printf("B\n");
		if (ft_strstr(line, "01") > -1 && ft_strstr(line, "RFC") == -1
			&& p->token == 1)
		{
			//printf("i: %d\nline_raw: %s\n", i, line);
			fill_raw_map(i, line, p);
			i++;
		}

		free(line);
		//r = get_next_line(fd, &line, p);
		//printf("r2: %d\n", r);
		//printf("i1: %d\n", i);
		//printf("line2: %s\n", line);
	}
	free(line);
	close(fd2);
}

void	get_param(char *filename, t_param *p)
{
	int		fd;
	int		r;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Error\n File not found.\n", p);
	r = get_next_line(fd, &line, p, NO_CLEAN_BUFFER);
	while (r > 0)
	{
		printf("line1: %s\n", line);
		if (ft_strstr(line, "01") == -1 && p->token == 1)
			break ;
		if (ft_strstr(line, "01") > -1 && ft_strstr(line, "RFC") == -1
			&& p->token == 0)
			p->token = 1;
		if (ft_strstr(line, "01") > -1 && p->token == 1)
			get_size_map(line, p);
		free(line);
		//r = get_next_line(fd, &line, p, NO_CLEAN_BUFFER);
	}
	get_next_line(fd, &line, p, CLEAN_BUFFER);
	free(line);

	printf("\nnb_line_map: %d\n", p->nb_line_map);
	printf("nb_col_map: %d\n", p->nb_col_map);
	close(fd);
	get_map(filename, p, fd);
}

void	check_map(t_param *p)
{
	int	i;

	i = 0;
	while (p->map[i]) //tmp
	{ //tmp
		printf("map: %s\n", p->map[i]); //tmp
		i++; //tmp
	} //tmp
}

void	parse_file(char *filename, t_param *p)
{
	get_param(filename, p);
	check_map(p);

}

int	main(int ac, char **av)
{
	t_param	p;

	ft_init(&p);
	if ((ac == 2 && av[0]) || (ac == 3 && check_save(av[2]) == 1))
	{
		if (ac == 3)
			p.save = 1;
		if (check_map_name(av[1]) == 1)
			parse_file(av[1], &p);
		else
			ft_error("Error\n .cub extension of map file is incorrect.\n", &p);
	}
	else
		ft_error("Error\n Arguments are not valid.\n", &p);
	free_map(&p);
	return (0);
}
