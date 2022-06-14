#include "cube3d.h"

static
int	close_win(void *param)
{
	t_graphic	*x;

	write(1, "hello\n", 6);
	x = (t_graphic *) param;
	x->img_e = 10;
	mlx_destroy_image(x->mlx_ptr, x->img_ptr);
	mlx_destroy_window(x->mlx_ptr, x->win_ptr);
	mlx_loop_end(x->mlx_ptr);
	free(x->img_matrix[x->img_size - 1]);
	free(x->img_matrix);
	free(x->mlx_ptr);
	free(x);
	exit(1);
	return (0);
}

static
int	khook(int key, void *param)
{
	t_graphic	*x;

	x = (t_graphic *) param;
	if (key == 65307)
	{
		mlx_destroy_image(x->mlx_ptr, x->img_ptr);
		mlx_destroy_window(x->mlx_ptr, x->win_ptr);
		mlx_loop_end(x->mlx_ptr);
		free(x->img_matrix[x->img_size - 1]);
		free(x->img_matrix);
		free(x->mlx_ptr);
		free(x);
		exit(1);
	}
	return (0);
}

static
int	mhook(int button, int x, int y, void *param)
{
    button++;
    x++;
    y++;
    (void) param;
	return (0);
}

int	fillmatrix(t_graphic *mlx)
{
	int		row;
	int		col;

	row = -1;
	col = -1;
	while (++row < mlx->img_size)
	{
		while (++col < mlx->img_size)
		{
            (mlx->img_matrix)[row][col][0] = (char)255;
            (mlx->img_matrix)[row][col][1] = (char)255;
            (mlx->img_matrix)[row][col][2] = (char)255;
            (mlx->img_matrix)[row][col][3] = 0;
		}
		col = -1;
	}
	return (0);
}

char	***creatematrix(char *img, int img_size, int img_sl)
{
	int		i;
	char	*ptr;
	char	**pptr;
	char	***ppptr;

	ptr = img;
	pptr = malloc(sizeof(char *) * img_size * img_size);
	i = 0;
	while (ptr < (img + img_size * img_sl))
	{
		pptr[i++] = ptr;
		ptr = ptr + 4;
	}
	i = 0;
	ppptr = malloc(img_size * sizeof(char **));
	i = img_size - 1;
	while (i >= 0)
	{
		ppptr[i--] = pptr;
		pptr = pptr + img_size;
	}
	return (ppptr);
}

static
t_graphic	*createwindow(void)
{
	t_graphic	*x;

	x = malloc(sizeof(t_graphic));
	x->img_size = 500;
	x->mlx_ptr = mlx_init();
	x->img_ptr = mlx_new_image(x->mlx_ptr, x->img_size, x->img_size);
	x->win_ptr = mlx_new_window(x->mlx_ptr, x->img_size, x->img_size, "cube3d");
	x->img = mlx_get_data_addr(x->img_ptr, &x->img_bp, &x->img_sl, &x->img_e);
	x->img_matrix = creatematrix(x->img, x->img_size, x->img_sl);
	fillmatrix(x);
	return (x);
}

int	main(int argc, char *argv[])
{
	t_data		*data;

	if (argc != 2)
	{
		perror("wrong count of arguments provided");
	//	return (1);
	}
	data = ft_calloc(1, sizeof(data));
	data->map = parse(argv[1]);
	data->graphic = createwindow();
	mlx_put_image_to_window(data->graphic->mlx_ptr, data->graphic->win_ptr, data->graphic->img_ptr, 0, 0);
	mlx_hook(data->graphic->win_ptr, 17, 0L, close_win, data->graphic);
	mlx_key_hook(data->graphic->win_ptr, khook, data->graphic);
	mlx_mouse_hook(data->graphic->win_ptr, mhook, data->graphic);
	mlx_loop(data->graphic->mlx_ptr);
	return (0);
}
