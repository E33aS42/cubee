/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:24:12 by esommier          #+#    #+#             */
/*   Updated: 2020/11/18 12:39:29 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# define BUFFER_SIZE		10
# define CLEAN_BUFFER		1
# define NO_CLEAN_BUFFER	0


typedef struct		s_textures
{
char	*t_no;
char	*t_so;
char	*t_we;
char	*t_ea;
}			t_textures;

typedef struct		s_sprite
{
char	*s_init;
char	*spr;
}			t_sprite;

typedef struct		s_floor
{
int	f_red;
int	f_green;
int	f_blue;
}			t_floor;

typedef struct		s_ceiling
{
int	c_red;
int	c_green;
int	c_blue;
}			t_ceiling;

typedef struct		s_player
{
//char	*p_init;
char	token_dir;
int		pos_x;
int		pos_y;
}			t_player;

typedef struct		s_param
{
int		screen_x;
int		screen_y;
unsigned int	i;
int		token;
int		i1;
int		i2;
int		nb_line_map;
int		nb_col_map;
t_textures	txt;
t_floor		fl;
t_ceiling	cl;
t_sprite	sprite;
int		token_R;
int		token_F;
int		token_C;
int		token_NO;
int		token_SO;
int		token_WE;
int		token_EA;
int		token_S;
t_player	player;
char		**map;
int		save;
}			t_param;

int	ft_strlen(char *s);
//int	ft_tablen(char **tab);
int	ft_isspace(int c);
int	ft_strcmp(char *s1, char *s2);
void	free_text_spr(char *s);
void	free_map(t_param *p);
void	ft_error(char *s, t_param *p);
void	ft_init(t_param *p);
void	ft_init_2(t_param *p);
int	check_save(char *s);
int	check_map_name(char *s);
int	get_next_line(int fd, char **line, t_param *p, int clean_buf);
int	ft_strchr(char *str, int c);
int	ft_strstr(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
char	*ft_substr(char *s, int start, int len);
int	ft_isdigit(char c);
long	calc_ry(unsigned int i, char **line, t_param *p);
void	get_resolution(char **line, t_param *p);
long	atoi_fc(char **line, t_param *p);
void	get_colors_floor(char ** line, t_param *p);
void	get_colors_ceil(char ** line, t_param *p);
void	get_text_spr(char **line, t_param *p);
void	get_size_map(char *line, t_param *p);
void	check_inputs(t_param *p);
void	check_redund(char **line, t_param *p);
void	get_param(char *filename, t_param *p);
void	init_map(t_param *p);
void	fill_raw_map(int i, char *line, t_param *p);
void	get_map(char *filename, t_param *p, int fd);
void	get_player_position(t_param *p);
void	check_map(t_param *p);
void	parse_file(char *filename, t_param *p);


#endif