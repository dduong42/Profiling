#include <stdlib.h>
#include <stdio.h>

int			main(void)
{
	void	*ptr1;
	void	*ptr2;

	ptr1 = malloc(40);
	ptr2 = malloc(60);
	free(ptr2);
	free(ptr1);
	getchar();
	return (0);
}
