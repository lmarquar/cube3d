#include "cube3d.h"

static
int	close_win(void *param)
{
	t_args	*x;

	write(1, "hello\n", 6);
	x = (t_args *) param;
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
	t_args	*x;

	x = (t_args *) param;
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

int	fillmatrix(t_args *mlx)
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
t_args	*createwindow(int argc, char *argv[])
{
    argc++;
    (void) argv;
	t_args	*x;

	x = malloc(sizeof(t_args));
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
	t_args	*x;

	x = createwindow(argc, argv);
	mlx_put_image_to_window(x->mlx_ptr, x->win_ptr, x->img_ptr, 0, 0);
	mlx_hook(x->win_ptr, 17, 0L, close_win, x);
	mlx_key_hook(x->win_ptr, khook, x);
	mlx_mouse_hook(x->win_ptr, mhook, x);
	mlx_loop(x->mlx_ptr);
	return (0);
}
