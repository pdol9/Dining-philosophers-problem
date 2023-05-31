
# define NC	"\e[0m"
# define YELLOW	"\e[1;33m"

// C program for variable length members in
// structures in GCC
#include<string.h>
#include<stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

void	*routine(void *data)
{
	pthread_t tid;

	tid = pthread_self();
	printf("%sThread [%ld]: %s\n", YELLOW, tid, NC);
	return (NULL); // The thread ends here.
}

/*struct student
{
	int stud_id;
	int name_len;
	int struct_size;
	char stud_name[6]; //character array of length 6
};
*/

// A structure of type student
struct student
{
	// This is used to store size of flexible
	// character array stud_name[]
	int struct_size;

	// Flexible Array Member(FAM)
	// variable length array must be last
	// member of structure
	pthread_t class[];
};

// Memory allocation and initialisation of structure
struct student *createStudent(struct student *s, int class_size)
{
	// Allocating memory according to user provided
	// array of characters
	int	j;

	s = malloc( sizeof(*s) + class_size * sizeof(pthread_t));

	j = 0;
	while (j < class_size)
	{
		if (pthread_create(&s->class[j], NULL, &routine, NULL) != 0)
			return (NULL);
		j++;
	}
	// Assigning size according to size of stud_name
	// which is a copy of user provided array a[].
	s->struct_size = (sizeof(*s) + sizeof(pthread_t) * class_size);

	return s;
}

// Print student details
/*void printStudent(struct student *s)
{
	printf("Student_id : %d\n"
		"Stud_Name : %ln\n"
		"Name_Length: %d\n"
		"Allocated_Struct_size: %d\n\n",
		s->class_id, s->class, s->name_len,
		s->struct_size);

	// Value of Allocated_Struct_size is in bytes here
}*/

// Driver Code
int main()
{
	int class_size = 10;
	struct student *s1 = createStudent(s1, class_size);

	int j = 0;
	while (j < class_size)
	{	
		if (pthread_join(s1->class[j], NULL) != 0)
			return (1);
		j++;
	}
	//struct student *s2 = createStudent(s2, 535, "Sanjayulsha");

	//printStudent(s1);
	//printStudent(s2);

	// Size in struct student
	printf("Size of Struct student: %lu\n", sizeof(struct student));

	// Size in struct pointer
	printf("Size of Struct pointer: %lu\n", sizeof(s1));

	free(s1);
	//free(s2);
	return 0;
}



