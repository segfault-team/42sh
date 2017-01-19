
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *segv = NULL;

	//segv = malloc(sizeof(*segv) * 6);
	//segv = strcpy(segv, "Hello");

	if (segv[30])
	{
		printf("Oh it has magically not segv! %s\n", &segv[30]);
		return (0);
	}
	printf("This will never be printed. Or not. %s -- %s\n", segv, &segv[30]);
	return (-1);
}
