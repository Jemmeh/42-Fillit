/*
**	Test function for the various elements of parser.c
*/

#include "fillit.h"
#include <stdio.h>

t_piece *printpiecelist(t_piece *piecelist);
void	printpiece(t_piece *piece);

t_piece		*makepiece(char* buf, char pieceletter)
{
	t_piece	*piece_ptr;
	int	x;
	int y;
	int i;

	i = 0;
	x = 0;
	y = 1;
	if (!(piece_ptr = (t_piece*)malloc(sizeof(t_piece))))
		return (NULL);
	while(i < 20)
	{
		if(buf[i] == '#')
		{
			piece_ptr->blockcoords[x] = (i > 5) ? (i % 5) : i;
			piece_ptr->blockcoords[y] = i / 5;
			x += 2;
			y += 2;
		}
		i++;
	}
	piece_ptr->pieceletter = pieceletter;
	//align(piece_ptr);
	return (piece_ptr);
}

t_piece		*makelist(char *buf)
{
	t_piece *current;
	t_piece *beginning;
	int 	i;
	char	pieceletter;

	i = 0;
	pieceletter = 'A';
	while (buf[i])
	{
		if (pieceletter == 'A')
		{
			beginning = makepiece(buf + i, pieceletter);
			current = beginning;
		}
		else
		{
			current->next = makepiece(buf + i, pieceletter);
			current = current->next;
		}
		pieceletter++;
		i += 21;
	}
	return (beginning);
}

t_piece		*parser(char *filename)
{
	char	buf[545];
	int		fd;
	int		bytecount;

	fd = open(filename, O_RDONLY);
	bytecount = read(fd, buf, 545);
	if (bytecount > 544 || bytecount < 19)
		return (NULL);
	buf[bytecount] = '\0';
	if (valid(buf))
		printf("%s", buf);
/*	if(!valid(buf))
		return(NULL);
	printf("validity: %d\n", valid(buf));
	return (makelist(buf));
*/	return (NULL);
}

int	main(void)
{
	parser("../TestFiles/invalid_sample");
	return (0);	
}
