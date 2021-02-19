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

int	    ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	    ft_strcmp(char *s1, char *s2)
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

int	    ft_strstr(char *s1, char *s2)
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

int	    ft_strstr_cnt(char *s1, char *s2)
{
	int	i1;
	int	i2;
	int	cnt;

	i1 = 0;
	cnt = 0;
	while (s1[i1] != '\0')
	{
		i2 = 0;
		while (s2[i2] != '\0')
		{
			if (s1[i1] == s2[i2])
				cnt++;
			i2++;
		}
		i1++;
	}
	return (cnt);
}

int	check_str_content(char *s1, char *s2)
{
	int	i;
	char	c;

	i = 0;
	c = 33;
	while (c <= 126)
	{
		if (ft_strchr(s1, c) > -1 && (ft_strchr(s2, c) == -1))
		{
			printf("c: %c\n", c);
			return (1);
		}
		c++;
	}
	return (0);
}


char	**ft_tabdup(char **s, int i_max, int j_max)
{
	int	i;
	int	j;
	char	**res;

	i = 0;
	j = 0;
	res = (char**)malloc(sizeof(char*) * (i_max + 1));
	while (i < i_max)
	{
		res[i] = (char*)malloc(sizeof(char*) * (j_max + 1));
		i++;
	}
	if (!(res))
		return (NULL);
	i = 0;
	while (i < i_max)
	{
		while (j < j_max)
		{
			res[i][j] = s[i][j];
			j++;
		}
		res[i][j] = '\0';
		j = 0;
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	free_text_spr(char *s)
{
	if (s)
	{
		free(s);
		s = NULL;
	}
}

void free_int(int *d)
{
	if (d)
		free(d);
}

void free_double(double *d)
{
	if (d)
		free(d);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
		free(tab);
	}
}

void	free_map(t_param *p)
{
	free_tab(p->map);
	free_text_spr(p->t_no.t_path);
	free_text_spr(p->t_so.t_path);
	free_text_spr(p->t_we.t_path);
	free_text_spr(p->t_ea.t_path);
	free_text_spr(p->sprite.s_path);
	free_double(p->sprite.zbuffer);
	free_int(p->sprite.s_order);
	free_double(p->sprite.s_distsq);
	free_double(p->sprite.s_posx);
	free_double(p->sprite.s_posy);
}


int	    ft_exit(t_param *p)
{
	if (p->data.img_ptr)
		mlx_destroy_image(p->data.mlx_ptr, p->data.img_ptr);
	if (p->t_no.t_img)
		mlx_destroy_image(p->data.mlx_ptr, p->t_no.t_img);
	if (p->t_so.t_img)
		mlx_destroy_image(p->data.mlx_ptr, p->t_so.t_img);
	if (p->t_we.t_img)
		mlx_destroy_image(p->data.mlx_ptr, p->t_we.t_img);
	if (p->t_ea.t_img)
		mlx_destroy_image(p->data.mlx_ptr, p->t_ea.t_img);
	if (p->sprite.s_img)
		mlx_destroy_image(p->data.mlx_ptr, p->sprite.s_img);
	if (p->data.win_ptr)
	{
		mlx_clear_window(p->data.mlx_ptr, p->data.win_ptr);
		mlx_destroy_window(p->data.mlx_ptr, p->data.win_ptr);
	}
	if (p->data.mlx_ptr)
		mlx_destroy_display(p->data.mlx_ptr);
	if (p->data.mlx_ptr)
		free(p->data.mlx_ptr);
	free_map(p);
	exit(0);
}

void	ft_error(char *s, t_param *p)
{
	int	len;

	len = ft_strlen(s);
	write(1, &s[0], len);
	printf("p_exist: %d\n", p->exist);
	ft_exit(p);
	exit(0);
}

void	ft_init_3(t_param *p)
{
	p->data.win_ptr = NULL;
	p->data.img_ptr = NULL;
	p->sprite.s_path = NULL;
	p->sprite.s_posx = NULL;
	p->sprite.s_posy = NULL;
	p->sprite.s_img = NULL;
	p->sprite.s_addr = NULL;
	p->sprite.s_cnt = 0;
	p->sprite.zbuffer = NULL;
	p->sprite.s_order = NULL;
	p->sprite.s_distsq = NULL;
}

void	ft_init_2(t_param *p)
{
	p->exist_R = 0;
	p->exist_F = 0;
	p->exist_C = 0;
	p->exist_NO = 0;
	p->exist_SO = 0;
	p->exist_WE = 0;
	p->exist_EA = 0;
	p->exist_S = 0;
	p->player.exist_dir = 0;
	p->player.posx = 0;
	p->player.posy = 0;
	p->cnt_cells = 0;
	p->t_no.t_img = NULL;
	p->t_so.t_img = NULL;
	p->t_we.t_img = NULL;
	p->t_ea.t_img = NULL;
	ft_init_3(p);
}

void	ft_init(t_param *p)
{
	p->screen_x = 0;
	p->screen_y = 0;
	p->i = 0;
	p->exist = 0;
	p->t_no.t_path = NULL;
	p->t_so.t_path = NULL;
	p->t_we.t_path = NULL;
	p->t_ea.t_path = NULL;
	p->fl.f_red = -1;
	p->fl.f_green = -1;
	p->fl.f_blue = -1;
	p->cl.c_red = -1;
	p->cl.c_green = -1;
	p->cl.c_green = -1;
	p->nb_line_map = 0;
	p->nb_col_map = 0;
	p->map = NULL;
	p->save = 0;
	ft_init_2(p);
}

void	init_dir2(t_param *p)
{
	if (p->player.start_dir == 'E')
	{
		p->player.dirx = 0;
		p->player.diry = 1;
		p->player.planex = 0.66;
		p->player.planey = 0;
	}
	else if (p->player.start_dir == 'W')
	{
		p->player.dirx = 0;
		p->player.diry = -1;
		p->player.planex = -0.66;
		p->player.planey = 0;
	}
}

void	init_dir(t_param *p)
{
	if (p->player.start_dir == 'N')
	{
		p->player.dirx = -1;
		p->player.diry = 0;
		p->player.planex = 0;
		p->player.planey = 0.66;
	}
	else if (p->player.start_dir == 'S')
	{
		p->player.dirx = 1;
		p->player.diry = 0;
		p->player.planex = 0;
		p->player.planey = -0.66;
	}
	else
		init_dir2(p);
}

void	init_move(t_param *p)
{
	p->data.mv_forward = 0;
	p->data.mv_backward = 0;
	p->data.mv_left = 0;
	p->data.mv_right = 0;
	p->data.rotate_left = 0;
	p->data.rotate_right = 0;
}

void	init_delta(t_param *p)
{


	if (p->ray.raydiry == 0)
		p->ray.deltax = 0;
	else if (p->ray.raydirx == 0)
		p->ray.deltax = 1;
	else
	{
		p->ray.deltax = fabs( 1 / p->ray.raydirx);
		//p->ray.deltax = sqrt(1 + (p->ray.raydiry * p->ray.raydiry) /
		//		(p->ray.raydirx * p->ray.raydirx));
	}
	if (p->ray.raydirx == 0)
		p->ray.deltay = 0;
	else if (p->ray.raydiry == 0)
		p->ray.deltay = 1;
	else
	{
		p->ray.deltay = fabs( 1 / p->ray.raydiry);
		//p->ray.deltay = sqrt(1 + (p->ray.raydirx * p->ray.raydirx) /
		//		(p->ray.raydiry * p->ray.raydiry));
	}
}

void	init_cub_prm(t_param *p)
{
	init_dir(p);
	p->ray.pl_posx = (double)p->player.posx + 0.5;
	p->ray.pl_posy = (double)p->player.posy + 0.5;
	p->ray.movespeed = 0.02;
	p->ray.rotspeed = 0.05;
	init_move(p);
}

void	init_stepside(t_param *p)
{
      if(p->ray.raydirx < 0)
      {
        p->ray.stepx = -1;
        p->ray.sidex = (p->ray.pl_posx - p->ray.mapx) * p->ray.deltax;
      }
      else
      {
        p->ray.stepx = 1;
        p->ray.sidex = (p->ray.mapx + 1.0 - p->ray.pl_posx) * p->ray.deltax;
      }
      if(p->ray.raydiry < 0)
      {
        p->ray.stepy = -1;
        p->ray.sidey = (p->ray.pl_posy - p->ray.mapy) * p->ray.deltay;
      }
      else
      {
        p->ray.stepy = 1;
        p->ray.sidey = (p->ray.mapy + 1.0 - p->ray.pl_posy) * p->ray.deltay;
      }
}

void	init_cub_prm2(t_param *p)
{
	p->ray.wall_hit = 0;
	p->ray.perpwalldist = 0;
	p->ray.camerax = 2 * p->ray.x / (double)p->screen_x - 1;
	p->ray.raydirx = p->player.dirx + p->player.planex*p->ray.camerax;
	p->ray.raydiry = p->player.diry + p->player.planey*p->ray.camerax;
	p->ray.mapx = (int)p->ray.pl_posx;
	p->ray.mapy = (int)p->ray.pl_posy;
	init_delta(p);
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

int	check_mapname(char *s)
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

long	calc_ry(unsigned int i, char **line, t_param *p)
{
	long		n;

	n = 0;
	while ((*line)[i] != ' ' && (*line)[i] != '\0')
	{
		if (ft_isdigit((*line)[i]) == 0)
			ft_error("Error\nIncorrect resolution inputs.\n", p);
		else
			n = n * 10 + (*line)[i++] - '0';
	}
	return (n);
}

void	check_resolution(t_param *p)
{
	int	rx;
	int	ry;

	rx = 0;
	ry = 0;
	if (p->screen_x == 0 || p->screen_y == 0)
		ft_error("Error\nResolution inputs cannot be null.\n", p);
	printf("Rx: %d\n", p->screen_x);
	printf("Ry: %d\n", p->screen_y);
	mlx_get_screen_size(p->data.mlx_ptr, &rx, &ry);
	if (p->screen_x > rx)
		p->screen_x = rx;
	if (p->screen_y > ry)
		p->screen_y = ry;
	printf("Rx: %d\n", p->screen_x);
	printf("Ry: %d\n", p->screen_y);
}

void	get_resolution(char **line, t_param *p)
{
	unsigned int	i;
	long			n;

	i = 0;
	n = 0;

	while ((*line)[i] == ' ' || (*line)[i] == '\t')
		i++;
	if ((*line)[i] == 'R')
	{
		if (check_str_content(*line, "R0123456789 ,\n\t") == 1)
		{
			free(*line);
			ft_error("Error\nWrong character types found in resolution inputs.\n", p);
		}
		if (p->exist_R == 1)
		{
			free(*line);
			ft_error("Error\nAnother existing resolution input.\n", p);
		}
		p->exist_R = 1;
		i++;
		while ((*line)[i] == ' ' || (*line)[i] == '\t')
			i++;
		while ((*line)[i] != ' ' && (*line)[i] != '\t')
		{
			if (ft_isdigit((*line)[i]) == 0)
			{
				free(*line);
				ft_error("Error\nIncorrect resolution inputs.\n", p);
			}
			else
				n = n * 10 + (*line)[i++] - '0';
		}
		p->screen_x = n;
		while ((*line)[i] == ' ' || (*line)[i] == '\t')
			i++;
		p->screen_y = calc_ry(i, line, p);
		check_resolution(p);
	}
}

long	atoi_fc(char **line, t_param *p)
{
	long		n;

	n = 0;

	while ((*line)[p->i] != '\0' && (*line)[p->i] != ' ' && (*line)[p->i] != ','
		&& (*line)[p->i] != '\t')
	{
		if (ft_isdigit((*line)[p->i]) == 0)
			ft_error("Error\nIncorrect inputs type.\n", p);
		else
			n = n * 10 + (*line)[p->i++] - '0';
	}
	if (n > 255)
		ft_error("Error\n RGB values cannot be greater than 255.\n", p);
	return (n);
}

void	get_colors_floor(char **line, t_param *p)
{
	p->i = 0;
	while ((*line)[p->i] == ' ' || (*line)[p->i] == '\t')
		p->i++;
	if ((*line)[p->i] == 'F')
	{
		if (check_str_content(*line, "0123456789F ,\n\t") == 1)
		{
			free(*line);
			ft_error("Error\nWrong character types found in floor inputs.\n", p);
		}
		if (p->exist_F == 1)
		{
			free(*line);
			ft_error("Error\nAnother existing floor input.\n", p);
		}
		p->exist_F = 1;
		p->i++;
		while ((*line)[p->i] == ' ' || (*line)[p->i] == '\t')
			p->i++;
		p->fl.f_red = atoi_fc(line, p);
		while ((*line)[p->i] == ' ' || (*line)[p->i] == ',' || (*line)[p->i] == '\t')
			p->i++;
		if ((*line)[p->i] == '\0')
		{
			free(*line);
			ft_error("Error\nMissing 2 floor inputs.\n", p);
		}
		else
			p->fl.f_green = atoi_fc(line, p);
		while ((*line)[p->i] == ' '|| (*line)[p->i] == ',' || (*line)[p->i] == '\t')
			p->i++;
		if ((*line)[p->i] == '\0')
		{
			free(*line);
			ft_error("Error\nMissing 1 floor inputs.\n", p);
		}
		else
			p->fl.f_blue = atoi_fc(line, p);
		while ((*line)[p->i] == ' '|| (*line)[p->i] == ',' || (*line)[p->i] == '\t')
			p->i++;
		if (ft_isdigit((*line)[p->i]))
		{
			free(*line);
			ft_error("Error\nToo many floor inputs.\n", p);
		}
	}
}

void	get_colors_ceil(char **line, t_param *p)
{
	p->i = 0;
	while ((*line)[p->i] == ' ' || (*line)[p->i] == '\t')
		p->i++;
	if ((*line)[p->i] == 'C')
	{
		if (check_str_content(*line, "0123456789C ,\n\t") == 1)
		{
			free(*line);
			ft_error("Error\nWrong character types found in ceiling inputs.\n", p);
		}
		if (p->exist_C == 1)
		{
			free(*line);
			ft_error("Error\nAnother existing ceiling input.\n", p);
		}
		p->exist_C = 1;
		p->i++;
		while ((*line)[p->i] == ' ' || (*line)[p->i] == '\t')
			p->i++;
		p->cl.c_red = atoi_fc(line, p);
		while ((*line)[p->i] == ' ' || (*line)[p->i] == ',' || (*line)[p->i] == '\t')
			p->i++;
		if ((*line)[p->i] == '\0')
			ft_error("Error\nMissing 2 ceiling inputs.\n", p);
		else
			p->cl.c_green = atoi_fc(line, p);
		while ((*line)[p->i] == ' '|| (*line)[p->i] == ',' || (*line)[p->i] == '\t')
			p->i++;
		if ((*line)[p->i] == '\0')
		{
			free(*line);	
			ft_error("Error\nMissing 1 ceiling inputs.\n", p);
		}
		else
			p->cl.c_blue = atoi_fc(line, p);
		while ((*line)[p->i] == ' '|| (*line)[p->i] == ',' || (*line)[p->i] == '\t')
			p->i++;
		if (ft_isdigit((*line)[p->i]))
		{
			free(*line);
			ft_error("Error\nToo many ceiling inputs.\n", p);
		}
	}
}

int    calc_rgb(int r, int g, int b)
{
    int rgb;

    rgb = (1 << 24) + (r << 16) + (g << 8) + b;
    return (rgb);
}

void	check_redund(char **line, t_param *p)
{
	if ((*line)[p->i] == 'N' && (*line)[p->i + 1] == 'O')
	{
		if (p->exist_NO == 1)
			ft_error("Error\nAnother existing NO input.\n", p);
		p->exist_NO = 1;
	}
	else if ((*line)[p->i] == 'S' && (*line)[p->i + 1] == 'O')
	{
		if (p->exist_SO == 1)
			ft_error("Error\nAnother existing SO input.\n", p);
		p->exist_SO = 1;
	}
	else if ((*line)[p->i] == 'W' && (*line)[p->i + 1] == 'E')
	{
		if (p->exist_WE == 1)
			ft_error("Error\nAnother existing WE input.\n", p);
		p->exist_WE = 1;
	}
	else if ((*line)[p->i] == 'E' && (*line)[p->i + 1] == 'A')
	{
		if (p->exist_EA == 1)
			ft_error("Error\nAnother existing EA input.\n", p);
		p->exist_EA = 1;
	}
	else if ((*line)[p->i] == 'S' && (*line)[p->i + 1] == ' ')
	{
		if (p->exist_S == 1)
			ft_error("Error\nAnother existing sprite input.\n", p);
		p->exist_S = 1;
	}
}

void	get_path_text(char **line, char **txt, t_param *p)
{
	int	j;

	j = 0;
	p->i += 2;
	while ((*line)[p->i] == ' '|| (*line)[p->i] == '\t')
		p->i++;
	*txt = ft_strdup(&((*line)[p->i]));

}

void	get_text_spr(char **line, t_param *p)
{
	p->i = 0;
	while ((*line)[p->i] == ' ' || (*line)[p->i] == '\t' || (*line)[p->i] == '\t')
		p->i++;
	if ((*line)[p->i] == 'N' && (*line)[p->i + 1] == 'O')
	{
		check_redund(line, p);
		get_path_text(line, &p->t_no.t_path, p);
	}
	else if ((*line)[p->i] == 'S' && (*line)[p->i + 1] == 'O')
	{
		check_redund(line, p);
		get_path_text(line, &p->t_so.t_path, p);
	}
	else if ((*line)[p->i] == 'W' && (*line)[p->i + 1] == 'E')
	{
		check_redund(line, p);
		get_path_text(line, &p->t_we.t_path, p);
	}
	else if ((*line)[p->i] == 'E' && (*line)[p->i + 1] == 'A')
	{
		check_redund(line, p);
		get_path_text(line, &p->t_ea.t_path, p);
	}
	else if ((*line)[p->i] == 'S' && ((*line)[p->i + 1] == ' ' || (*line)[p->i] == '\t'))
	{
		check_redund(line, p);
		get_path_text(line, &p->sprite.s_path, p);
	}
}

void	find_sprites(t_param *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < p->nb_line_map)
	{
		while (j < p->nb_col_map)
		{
			if (p->map[i][j] == '2')
				p->sprite.s_cnt++;
			j++;
		}
		j = 0;
		i++;
	}
	if (p->sprite.s_cnt == 0)
		write(1, "The map does not contain any sprite\n", 36);
}

void	get_sprite_position(t_param *p)
{
	int	i;
	int	j;
	int	k;
	i = 0;
	j = 0;
	k = 0;
	find_sprites(p);
	p->sprite.s_posx = (double *)malloc(sizeof(double) * (p->sprite.s_cnt));
	p->sprite.s_posy = (double *)malloc(sizeof(double) * (p->sprite.s_cnt));
	while (i < p->nb_line_map)
	{
		while (j < p->nb_col_map)
		{
			if (p->map[i][j] == '2')
			{
				p->sprite.s_posx[k] = i + 0.5;
				p->sprite.s_posy[k] = j + 0.5;
				k++;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_sprites(t_param *p)
{
	int	k;
	int	stripe;
	int	texx;
	int	texy;
	int	d;
	int	y;
	int	m;
	int	n;
	k = 0;
	while (k < p->sprite.s_cnt)
	{
		p->sprite.s_x = p->sprite.s_posx[k] - p->ray.pl_posx;
		p->sprite.s_y = p->sprite.s_posy[k] - p->ray.pl_posy;
		p->sprite.invdet = 1 / (p->player.planex * p->player.diry
					- p->player.dirx * p->player.planey);
		p->sprite.transfx = p->sprite.invdet * (p->player.diry * p->sprite.s_x
					- p->player.dirx * p->sprite.s_y);
		p->sprite.transfy = p->sprite.invdet * (-p->player.planey * p->sprite.s_x
					+ p->player.planex * p->sprite.s_y);
		p->sprite.s_screenx = (int)((p->screen_x / 2) *
					(1 + p->sprite.transfx / p->sprite.transfy));
		p->sprite.height = abs((int)(p->screen_y / (p->sprite.transfy)));
		p->sprite.drawstarty = -p->sprite.height / 2 + p->screen_y / 2;
		if(p->sprite.drawstarty < 0)
			p->sprite.drawstarty = 0;
		p->sprite.drawendy = p->sprite.height / 2 + p->screen_y / 2;
		if(p->sprite.drawendy >= p->screen_y)
			p->sprite.drawendy = p->screen_y - 1;
		p->sprite.width = abs((int)(p->screen_y / (p->sprite.transfy)));
		p->sprite.drawstartx = -p->sprite.width / 2 + p->sprite.s_screenx;
		if(p->sprite.drawstartx < 0)
			p->sprite.drawstartx = 0;
		p->sprite.drawendx = p->sprite.width / 2 + p->sprite.s_screenx;
		if(p->sprite.drawendx >= p->screen_x)
			p->sprite.drawendx = p->screen_x - 1;
		stripe = p->sprite.drawstartx;
		while(stripe < p->sprite.drawendx)
		{
			texx = (int)(256 * (stripe - (-p->sprite.width / 2 +
				p->sprite.s_screenx)) * p->sprite.s_width
				/ p->sprite.width) / 256;
			if (p->sprite.transfy > 0 && stripe > 0 && stripe < p->screen_x
					&& p->sprite.transfy < (float)p->sprite.zbuffer[stripe])
			{
				y = p->sprite.drawstarty;
				while (y < p->sprite.drawendy)
				{
					d = y * 256 - p->screen_y * 128 + p->sprite.height * 128;
					texy = ((d * p->sprite.s_height) / p->sprite.height) / 256;
					m = y * p->data.sizeline / 4 + stripe;
					n = texy * p->sprite.s_sizeline / 4 + texx;
					if ((p->sprite.s_addr[n] & 0xFFFFFF) != 0)
						p->data.img_data_addr[m] = p->sprite.s_addr[n];
					y++;
				}
			}
			stripe++;
		}
		k++;
	}
}

void	sort_sprites(t_param *p)
{
	int	k;
	double	tmp;

	k = 0;
	while (k < p->sprite.s_cnt - 1)
	{
		if (p->sprite.s_distsq[k] < p->sprite.s_distsq[k + 1])
		{
			tmp = p->sprite.s_distsq[k];
			p->sprite.s_distsq[k] = p->sprite.s_distsq[k + 1];
			p->sprite.s_distsq[k + 1] = tmp;
			tmp = p->sprite.s_order[k];
			p->sprite.s_order[k] = p->sprite.s_order[k + 1];
			p->sprite.s_order[k + 1] = (int)tmp;
			k = -1;
		}
		k++;
	}
}

void	get_sprites(t_param *p)
{
	int	k;

	k = 0;
	while (k < p->sprite.s_cnt)
	{
		p->sprite.s_order[k] = k;
		p->sprite.s_distsq[k] = (p->ray.pl_posx - p->sprite.s_posx[k])
					* (p->ray.pl_posx - p->sprite.s_posx[k])
					+ (p->ray.pl_posy - p->sprite.s_posy[k])
					* (p->ray.pl_posy - p->sprite.s_posy[k]);
		k++;
	}
	sort_sprites(p);
	draw_sprites(p);
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

char	**get_raw_map4(t_param *p, char **tmp, int it, int jt)
{
	if (p->map)
	{
		tmp = ft_tabdup(p->map, it, jt);
		free_tab(p->map);
	}
	return (tmp);
}

int	get_raw_map3(t_param *p, char **tmp, int i, int j)
{
	if (tmp[i][j])
		p->map[i][j] = tmp[i][j];
	j++;
	return (j);
}

int	get_raw_map2(t_param *p, char **tmp, int len)
{
	int	it;
	int	jt;
	int	i;
	int	j;

	i = 0;
	j = 0;
	it = p->nb_line_map;
	jt = p->nb_col_map;
	tmp = get_raw_map4(p, tmp, it, jt);
	if (p->nb_col_map < len)
		p->nb_col_map = len;
	p->nb_line_map++;
	init_map(p);
	while (i < it)
	{
		while (j < jt)
			j = get_raw_map3(p, tmp, i, j);
		while (j < p->nb_col_map)
			p->map[i][j++] = '4';
		p->map[i][j] = '\0';
		j = 0;
		i++;
	}
	if (tmp)
		free_tab(tmp);
	return (i);
}

void	get_raw_map(char *line,  t_param *p)
{
	char	**tmp;
	int	len;
	int	i;
	int	j;

	len = ft_strlen(line);
	tmp = NULL;
	i = get_raw_map2(p, tmp, len);
	j = 0;
	while (line[j] != '\0')
	{
		if (line[j] == ' ')
			p->map[i][j] = '4';
		else
			p->map[i][j] = line[j];
		j++;
	}
	while (j < p->nb_col_map)
		p->map[i][j++] = '4';
	p->map[i][j] = '\0';
	i++;
	p->map[i] = NULL;
}

void	check_inputs(t_param *p)
{
	if (p->exist_R == 0 || p->exist_F == 0 || p->exist_C == 0 ||
		p->exist_NO == 0 || p->exist_SO == 0 || p->exist_WE == 0 ||
		p->exist_EA == 0 || p->exist_S == 0)
		ft_error("Error\n Some inputs are missing.\n", p);
	else
		write(1, "All inputs accounted for.\n", 27);
}

int	check_exists(t_param *p)
{
	if (p->exist_R == 1 && p->exist_F == 1 && p->exist_C == 1 &&
		p->exist_NO == 1 && p->exist_SO == 1 && p->exist_WE == 1 &&
		p->exist_EA == 1 && p->exist_S == 1)
		return (1);
	return (0);

}

void	get_param(char *filename, t_param *p)
{
	int		fd;
	int		r;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Error\n File not found.\n", p);
	r = 1;
	while (r > 0)
	{
		r = get_next_line(fd, &line, p);
		if (ft_strstr_cnt(line, "RNSWEFC") > 0 && p->exist == 0)
		{
			get_resolution(&line, p);
			get_colors_floor(&line, p);
			get_colors_ceil(&line, p);
			get_text_spr(&line, p);
			free(line);
			continue ;
		}
		if (ft_strstr_cnt(line, "01") > 0 && check_exists(p)
			&& p->exist == 0)
		{
			if (check_str_content(line, "012NEWS\n") == 1)
			{
				free(line);
				ft_error("Error\n Abnormal character found in map\n", p);
			}
			p->exist = 1;
		}
		if (p->exist == 1)
		{
			//printf("line: %s\n", line);
			if (check_str_content(line, "012NEWS\n") == 1)
			{
				free(line);
				ft_error("Error\n Abnormal character found in map\n", p);
			}
			get_raw_map(line, p);
		}
		free(line);
	}
		printf("f_red: %d\n", p->fl.f_red);
		printf("f_green: %d\n", p->fl.f_green);
		printf("f_blue: %d\n", p->fl.f_blue);
		printf("c_red: %d\n", p->cl.c_red);
		printf("c_green: %d\n", p->cl.c_green);
		printf("c_blue: %d\n", p->cl.c_blue);
		printf("t_no: %s\n", p->t_no.t_path);
		printf("t_so: %s\n", p->t_so.t_path);
		printf("t_we: %s\n", p->t_we.t_path);
		printf("t_ea: %s\n", p->t_ea.t_path);
		printf("sprite: %s\n", p->sprite.s_path);
	close(fd);
	printf("\nnb_line_map: %d\n", p->nb_line_map);
	printf("nb_col_map: %d\n", p->nb_col_map);
}

void	get_player_position(t_param *p)
{
	int	i;
	int	index;
	int	cnt;

	i = 0;
	index = -1;
	while (p->map[i])
	{
		printf("map[%d]: %s\n", i, p->map[i]);
		index = ft_strstr(p->map[i], "NSEW");
		cnt = ft_strstr_cnt(p->map[i], "NSEW");
		if (cnt > 1)
			ft_error("Error\n More than one player position on the map.\n", p);
		if (index != -1)
		{
			if (p->player.exist_dir != 0)
				ft_error("Error\n More than one player position on the map.\n", p);
			p->player.exist_dir = p->map[i][index];
			p->player.posx = i;
			p->player.posy = index;
			p->player.start_dir = p->map[i][index];
			printf("player direction: %c\n", p->player.exist_dir); //tmp
			printf("player x: %d\n", p->player.posx); //tmp
			printf("player y: %d\n", p->player.posy); //tmp
			p->map[i][index] = '0'; // replace player position by a 0
		}
		i++;
	}
	if (p->player.exist_dir == 0)
		ft_error("Error\n No initial player position found.\n", p);
}

void	ft_init_spr(t_param *p)
{
	if (!(p->sprite.zbuffer = (double *)malloc(sizeof(double) * p->screen_x)))
		ft_error("Error\nzbuffer malloc.\n", p);
	if (!(p->sprite.s_order = (int *)malloc(sizeof(int) * p->sprite.s_cnt)))
		ft_error("Error\nsprite order malloc.\n", p);
	if (!(p->sprite.s_distsq = (double *)malloc(sizeof(double) * p->sprite.s_cnt)))
		ft_error("Error\nsprite distance malloc.\n", p);
	p->sprite.s_img = mlx_xpm_file_to_image(p->data.mlx_ptr, p->sprite.s_path, &(p->sprite.s_width),
			&(p->sprite.s_height));
	if (!(p->sprite.s_img))
		ft_error("Error\n Problem with Sprite.\n", p);
	p->sprite.s_addr = (int *)mlx_get_data_addr(p->sprite.s_img, &(p->sprite.s_bpp),
			&(p->sprite.s_sizeline), &(p->sprite.s_endian));
	if (!(p->sprite.s_addr))
		ft_error("Error\n Problem with Sprite address.\n", p);
}


void	check_pl_pos(int x, int y, t_param *p, char **tmp)
{
	if (tmp[x][y] == '1' || tmp[x][y] == 'P')
		return ;
	if (tmp[x][y] == '4')
	{
		printf("pos 4: %c\n", tmp[x][y]);
		printf("cnt_cells: %d, x: %d, y: %d\n", p->cnt_cells, x, y);
		free_tab(tmp);
		ft_error("Error\n This map has holes.\n", p);
	}
	if ((tmp[x][y] == '0' || tmp[x][y] == '2') && (x == 0 || y == 0 ||\
		x == p->nb_line_map - 1 || y == p->nb_col_map - 1))
	{
		printf("pos 02: %c\n", tmp[x][y]);
		printf("cnt_cells: %d, x: %d, y: %d\n", p->cnt_cells, x, y);
		free_tab(tmp);
		ft_error("Error\n This map has holes.\n", p);
	}
	if (tmp[x][y] == '0' || tmp[x][y] == '2')
	{
		tmp[x][y] = 'P';
		p->cnt_cells++;
		check_pl_pos(x + 1, y, p, tmp);
		check_pl_pos(x, y + 1, p, tmp);
		check_pl_pos(x - 1, y, p, tmp);
		check_pl_pos(x, y - 1, p, tmp);
	}
}

void	check_map(t_param *p)
{
	int	i;
	char	**tmp;

	i = 0; //tmp
	while (p->map[i]) //tmp
	{ //tmp
		printf("map: %s\n", p->map[i]); //tmp
		i++; //tmp
	} //tmp
	get_player_position(p);
	tmp = ft_tabdup(p->map, p->nb_line_map, p->nb_col_map);
	check_pl_pos(p->player.posx, p->player.posy, p, tmp);
	free_tab(tmp);
}

void	get_text_addr(t_param *p)
{
	p->t_no.t_addr = (int *)mlx_get_data_addr(p->t_no.t_img, &(p->t_no.t_bpp),
			&(p->t_no.t_sizeline), &(p->t_no.t_endian));
	if (!(p->t_no.t_addr))
		ft_error("Error\n Problem with NORTH texture address.\n", p);
	p->t_so.t_addr = (int *)mlx_get_data_addr(p->t_so.t_img, &(p->t_so.t_bpp),
			&(p->t_so.t_sizeline), &(p->t_so.t_endian));
	if (!(p->t_so.t_addr))
		ft_error("Error\n Problem with SOUTH texture address.\n", p);
	p->t_we.t_addr = (int *)mlx_get_data_addr(p->t_we.t_img, &(p->t_we.t_bpp),
			&(p->t_we.t_sizeline), &(p->t_we.t_endian));
	if (!(p->t_we.t_addr))
		ft_error("Error\n Problem with WEST texture address.\n", p);
	p->t_ea.t_addr = (int *)mlx_get_data_addr(p->t_ea.t_img, &(p->t_ea.t_bpp),
			&(p->t_ea.t_sizeline), &(p->t_ea.t_endian));
	if (!(p->t_ea.t_addr))
		ft_error("Error\n Problem with EAST texture address.\n", p);

}

void	get_textures(t_param *p)
{
	p->t_no.t_img = mlx_xpm_file_to_image(p->data.mlx_ptr, p->t_no.t_path, &(p->t_no.t_width),
			&(p->t_no.t_height));
	if (!(p->t_no.t_img))
		ft_error("Error\n Problem with NORTH texture.\n", p);
	p->t_so.t_img = mlx_xpm_file_to_image(p->data.mlx_ptr, p->t_so.t_path, &(p->t_so.t_width),
			&(p->t_so.t_height));
	if (!(p->t_so.t_img))
		ft_error("Error\n Problem with SOUTH texture.\n", p);
	p->t_we.t_img = mlx_xpm_file_to_image(p->data.mlx_ptr, p->t_we.t_path, &(p->t_we.t_width),
			&(p->t_we.t_height));
	if (!(p->t_we.t_img))
		ft_error("Error\n Problem with WEST texture.\n", p);
	p->t_ea.t_img = mlx_xpm_file_to_image(p->data.mlx_ptr, p->t_ea.t_path, &(p->t_ea.t_width),
			&(p->t_ea.t_height));
	if (!(p->t_ea.t_img))
		ft_error("Error\n Problem with EAST texture.\n", p);
	get_text_addr(p);
}

void	parse_file(char *filename, t_param *p)
{
	p->data.mlx_ptr = mlx_init();
	if (!(p->data.mlx_ptr))
		ft_error("Error\n Problem with mlx_init.\n", p);
	get_param(filename, p);
	check_map(p);
	get_sprite_position(p);
	ft_init_spr(p);
	get_textures(p);
}

int	key_press(int keycode, t_param *p)
{
	if (keycode == FORWARD_W)
		p->data.mv_forward = 1;
	if (keycode == BACKWARD_S)
		p->data.mv_backward = 1;
	if (keycode == MOVE_LEFT_A)
		p->data.mv_left = 1;
	if (keycode == MOVE_RIGHT_D)
		p->data.mv_right = 1;
	if (keycode == ROTATE_LEFT)
		p->data.rotate_left = 1;
	if (keycode == ROTATE_RIGHT)
		p->data.rotate_right = 1;
	else if (keycode == ESC_KEY)
		ft_error("Exit game.\n", p);
	return (1);
}

int	key_release(int keycode, t_param *p)
{
	if (keycode == FORWARD_W)
		p->data.mv_forward = 0;
	if (keycode == BACKWARD_S)
		p->data.mv_backward = 0;
	if (keycode == MOVE_LEFT_A)
		p->data.mv_left = 0;
	if (keycode == MOVE_RIGHT_D)
		p->data.mv_right = 0;
	if (keycode == ROTATE_LEFT)
		p->data.rotate_left = 0;
	if (keycode == ROTATE_RIGHT)
		p->data.rotate_right = 0;
	return (1);
}

void	dda_algo(t_param *p)
{
      while (p->ray.wall_hit == 0)
      {
        if(p->ray.sidex < p->ray.sidey)
        {
          p->ray.sidex += p->ray.deltax;
          p->ray.mapx += p->ray.stepx;
          p->ray.sidewall_hit = 0;
        }
        else
        {
          p->ray.sidey += p->ray.deltay;
          p->ray.mapy += p->ray.stepy;
          p->ray.sidewall_hit = 1;
        }
	if (p->ray.mapx < 0)
		p->ray.mapx = 0;
	if (p->ray.mapy < 0)
		p->ray.mapy = 0;
        if(p->map[p->ray.mapx][p->ray.mapy] == '1')
		p->ray.wall_hit = 1;
      }
}

void	calc_proj_dist(t_param *p)
{
	if(p->ray.sidewall_hit == 0)
		p->ray.perpwalldist = ((double)p->ray.mapx - p->ray.pl_posx + (1 - (double)p->ray.stepx) / 2)
					 / p->ray.raydirx;
	else
		p->ray.perpwalldist = (p->ray.mapy - p->ray.pl_posy + (1 - p->ray.stepy) / 2)
					 / p->ray.raydiry;
}

void	calc_pixels_bound(t_param *p)
{
	p->ray.lineheight = (int)(p->screen_y / p->ray.perpwalldist);
	p->ray.drawstart = -p->ray.lineheight / 2 + p->screen_y / 2;
	//printf("ray_x: %d\n", p->ray.x);
	//printf("perpwalldist: %f\n", p->ray.perpwalldist);
	//printf("drawstart: %d, lineheight: %d, ", p->ray.drawstart, p->ray.lineheight);
	if (p->ray.drawstart < 0)
		p->ray.drawstart = 0;
	//printf("drawstart: %d, lineheight: %d, ", p->ray.drawstart, p->ray.lineheight);
	p->ray.drawend = p->ray.lineheight / 2 + p->screen_y / 2;
	if (p->ray.drawend >= p->screen_y) // || p->ray.drawend < 0)
		p->ray.drawend = p->screen_y - 1;
	//printf("drawend: %d\n", p->ray.drawend);
	//if (p->ray.drawstart >= p->ray.drawend)
	//	p->ray.drawstart = 0;
}

void	calc_raydist(t_param *p)
{
	init_cub_prm2(p);
	init_stepside(p);
	dda_algo(p);
	calc_proj_dist(p);
	calc_pixels_bound(p);
}

void	init_texture(t_param *p)
{
	if (p->ray.sidewall_hit == 0 && p->ray.raydirx < 0)  // N
		p->txt.t_dir = 0;
	if (p->ray.sidewall_hit == 0 && p->ray.raydirx >= 0)  // S
		p->txt.t_dir = 1;
	if (p->ray.sidewall_hit == 1 && p->ray.raydiry < 0)  // W
		p->txt.t_dir = 2;
	if (p->ray.sidewall_hit == 1 && p->ray.raydiry >= 0) // E
		p->txt.t_dir = 3;
	if (p->ray.sidewall_hit == 0)
		p->txt.wall_x = p->ray.pl_posy + p->ray.perpwalldist \
						* p->ray.raydiry;
	else
		p->txt.wall_x = p->ray.pl_posx + p->ray.perpwalldist \
						* p->ray.raydirx;
	p->txt.wall_x -= floor((p->txt.wall_x));
	p->txt.t_x = (int)(p->txt.wall_x * (double)p->t_no.t_width);
	if ((p->ray.sidewall_hit == 0 && p->ray.raydirx > 0) ||
		(p->ray.sidewall_hit == 1 && p->ray.raydiry < 0))
		p->txt.t_x = p->t_no.t_width - p->txt.t_x - 1;
	p->txt.t_step = 1.0 * p->t_no.t_height / p->ray.lineheight;
	p->txt.t_pos = (p->ray.drawstart - p->screen_y / 2 +
			p->ray.lineheight / 2) * p->txt.t_step;
}

void	draw_textures(t_param *p, int x)
{
	int	i;
	int	y;

	init_texture(p);
	y = p->ray.drawstart;
	while (y <= p->ray.drawend)
	{
		p->txt.t_y = (int)p->txt.t_pos & p->t_no.t_height - 1;
		p->txt.t_pos += p->txt.t_step;
		if (y < p->screen_y && x < p->screen_x)
		{
			i = y * p->data.sizeline / 4 + x;
			if (p->txt.t_dir == 0)
				p->data.img_data_addr[i] = p->t_no.t_addr[p->txt.t_y *
				p->t_no.t_sizeline / 4 + p->txt.t_x];
			if (p->txt.t_dir == 1)
				p->data.img_data_addr[i] = p->t_so.t_addr[p->txt.t_y *
				p->t_so.t_sizeline / 4 + p->txt.t_x];
			if (p->txt.t_dir == 2)
				p->data.img_data_addr[i] = p->t_we.t_addr[p->txt.t_y *
				p->t_we.t_sizeline / 4 + p->txt.t_x];
			if (p->txt.t_dir == 3)
				p->data.img_data_addr[i] = p->t_ea.t_addr[p->txt.t_y *
				p->t_ea.t_sizeline / 4 + p->txt.t_x];
		}
		y++;
	}
}

void	draw_ceil_text_floor(t_param *p)
{
	int	y;
	int	k;

	p->ray.drawend = p->screen_y - p->ray.drawstart;
	y = 0;
	while (y < p->ray.drawstart)
	{
		k = y * p->data.sizeline / 4 + p->ray.x;
		p->data.img_data_addr[k] = calc_rgb(p->cl.c_red, p->cl.c_green,
                                            p->cl.c_blue);
		y++;
	}
	if (y <= p->ray.drawend)
		draw_textures(p, p->ray.x);
	y = p->ray.drawend + 1;
	while (y < p->screen_y)
	{
		k = y * p->data.sizeline / 4 + p->ray.x;
        	p->data.img_data_addr[k] = calc_rgb(p->fl.f_red, p->fl.f_green,
                                            p->fl.f_blue);
		y++;
	}
}


void	move_back(t_param *p)
{
	int	i;
	int	j;

	if(p->data.mv_backward == 1)
	{
		i = (int)(p->ray.pl_posx - p->ray.raydirx * p->ray.movespeed);
		j = (int)p->ray.pl_posy;
		if(p->map[i][j] == '0')
			p->ray.pl_posx -= p->player.dirx * p->ray.movespeed;

		i = (int)p->ray.pl_posx;
		j = (int)(p->ray.pl_posy - p->ray.raydiry * p->ray.movespeed);
		if(p->map[i][j] == '0')
			p->ray.pl_posy -= p->player.diry * p->ray.movespeed;
	}
}

void	move_for(t_param *p)
{
	int	i;
	int	j;

	if(p->data.mv_forward == 1)
	{
		i = (int)(p->ray.pl_posx + p->ray.raydirx * p->ray.movespeed);
		j = (int)p->ray.pl_posy;
		if(p->map[i][j] == '0')
			p->ray.pl_posx += p->player.dirx * p->ray.movespeed;

		i = (int)p->ray.pl_posx;
		j = (int)(p->ray.pl_posy + p->ray.raydiry * p->ray.movespeed);
		if(p->map[i][j] == '0')
			p->ray.pl_posy += p->player.diry * p->ray.movespeed;
	}
}

void	move_left(t_param *p)
{
	int	i;
	int	j;

	if(p->data.mv_left == 1)
	{
		i = (int)(p->ray.pl_posx - p->ray.raydiry * p->ray.movespeed);
		j = (int)p->ray.pl_posy;
		if(p->map[i][j] == '0')
			p->ray.pl_posx -= p->player.diry * p->ray.movespeed;

		i = (int)p->ray.pl_posx;
		j = (int)(p->ray.pl_posy + p->ray.raydirx * p->ray.movespeed);
		if(p->map[i][j] == '0')
			p->ray.pl_posy += p->player.dirx * p->ray.movespeed;
	}

}

void	move_right(t_param *p)
{
	int	i;
	int	j;

	if(p->data.mv_right == 1)
	{
		i = (int)(p->ray.pl_posx + p->ray.raydiry * p->ray.movespeed);
		j = (int)p->ray.pl_posy;
		if(p->map[i][j] == '0')
			p->ray.pl_posx += p->player.diry * p->ray.movespeed;

		i = (int)p->ray.pl_posx;
		j = (int)(p->ray.pl_posy - p->ray.raydirx * p->ray.movespeed);
		if(p->map[i][j] == '0')
			p->ray.pl_posy -= p->player.dirx * p->ray.movespeed;
	}
}

void	rotate_left(t_param *p)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = p->player.dirx;
	old_planex = p->player.planex;
	if(p->data.rotate_left == 1)
	{
		p->player.dirx = p->player.dirx * cos(p->ray.rotspeed)
				- p->player.diry * sin(p->ray.rotspeed);
		p->player.diry = old_dirx * sin(p->ray.rotspeed)
				+ p->player.diry * cos(p->ray.rotspeed);
		p->player.planex = p->player.planex * cos(p->ray.rotspeed)
				- p->player.planey * sin(p->ray.rotspeed);
		p->player.planey = old_planex * sin(p->ray.rotspeed)
				+ p->player.planey * cos(p->ray.rotspeed);
	}
}

void	rotate_right(t_param *p)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = p->player.dirx;
	old_planex = p->player.planex;
	if(p->data.rotate_right == 1)
	{
		p->player.dirx = p->player.dirx * cos(-p->ray.rotspeed)
				- p->player.diry * sin(-p->ray.rotspeed);
		p->player.diry = old_dirx * sin(-p->ray.rotspeed)
				+ p->player.diry * cos(-p->ray.rotspeed);
		p->player.planex = p->player.planex * cos(-p->ray.rotspeed)
				- p->player.planey * sin(-p->ray.rotspeed);
		p->player.planey = old_planex * sin(-p->ray.rotspeed)
				+ p->player.planey * cos(-p->ray.rotspeed);
	}
}

void	read_keys(t_param *p)
{
	move_for(p);
	move_back(p);
	move_left(p);
	move_right(p);
	rotate_left(p);
	rotate_right(p);
}

int	run_cub(t_param *p)
{
	read_keys(p);
	p->ray.x = 0;
	while (p->ray.x < p->screen_x)
	{
		calc_raydist(p);
		draw_ceil_text_floor(p);
		p->sprite.zbuffer[p->ray.x] = p->ray.perpwalldist;
		p->ray.x++;
	}
	get_sprites(p);
	mlx_put_image_to_window(p->data.mlx_ptr, p->data.win_ptr, p->data.img_ptr, 0, 0);
	return (0);
}

void	start_cub(t_param *p)
{
	init_cub_prm(p);
	p->data.img_ptr = mlx_new_image(p->data.mlx_ptr, p->screen_x, p->screen_y);
	if (!(p->data.img_ptr))
		ft_error("Error\nProblem with mlx_new_image.\n", p);
	p->data.img_data_addr = (int *)mlx_get_data_addr(p->data.img_ptr, &p->data.bpp, 
				&p->data.sizeline, &p->data.endian);
	if (!(p->data.img_data_addr))
		ft_error("Error\nProblem with mlx_get_data_addr.\n", p);
	/*if (p->save == 1)
		run_cub(p);*/
	p->data.win_ptr = mlx_new_window(p->data.mlx_ptr, p->screen_x, p->screen_y, "Cub3D");
	if (!(p->data.win_ptr))
		ft_error("Error\nProblem with mlx_new_window.\n", p);

	mlx_hook(p->data.win_ptr, 2, 0, key_press, (void *)p);
	mlx_hook(p->data.win_ptr, 3, 2, key_release, (void *)p);
	mlx_hook(p->data.win_ptr, 33, 1, ft_exit, (void *)p);
	mlx_loop_hook(p->data.mlx_ptr, run_cub, (void *)p);
	mlx_loop(p->data.mlx_ptr);
}

int	main(int ac, char **av)
{
	t_param	p;

	ft_init(&p);
	if (ac == 3 && check_save(av[2]) == 0)
		ft_error("Error\n Incorrect second input argument.\n", &p);
	if ((ac == 2 && av[0]) || (ac == 3 && check_save(av[2]) == 1))
	{
		if (ac == 3)
			p.save = 1;
		if (check_mapname(av[1]) == 1)
		{
			parse_file(av[1], &p);
			start_cub(&p);
		}
		else
			ft_error("Error\n .cub extension of map file is incorrect.\n", &p);
	}
	else
		ft_error("Error\n Arguments are not valid.\n", &p);
	return (0);
}
