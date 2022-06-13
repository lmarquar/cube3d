#ifndef PARSER_H
# define PARSER_H

#include <fcntl.h>
#include <unistd.h>
/* Map data */
typedef struct s_map
{
	int		**layout;
	char	*texure_nose[4];
	char	*texture_top_down[2];
}	t_map;

t_map	*parse(char *map_file);

#endif
