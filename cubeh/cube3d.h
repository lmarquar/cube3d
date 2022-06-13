#ifndef CUBE3D_H
# define CUBE3D_H

# include "./mlx/mlx.h"
# include "libft/libft.h"
# include "parser/parser.h"
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>

/* Player data */
typedef struct s_player
{
	//position
	//orientation
}	t_player;

/* Main data */
typedef struct s_graphic
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img;
	char	***img_matrix;
	int		img_bp;
	int		img_sl;
	int		img_e;
	int		img_size;
}	t_graphic;

typedef struct s_data
{
	t_graphic	*graphic;
	t_player	player;
	t_map		*map;
}	t_data;

#endif
