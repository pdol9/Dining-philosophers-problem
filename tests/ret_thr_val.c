#include "../include/philo.h"

void	*roll_dice()
{
	int *value = malloc(sizeof(int));
	*value = (rand() % 6) + 1;
	//printf("%d\n", value);
	printf("address of *val = %p\n", value);
	return (void *) value;
}

int main(int ac, char *av[])
{
	int *res;
	pthread_t th;

	srand(time(NULL));
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
		return 1;
	if (pthread_join(th, (void **) &res) != 0)
		return 2;
	printf("Result is: %d\n", *res);
	printf("address of *val in MAIN = %p\n", res);

	free(res);
	return 0;
}