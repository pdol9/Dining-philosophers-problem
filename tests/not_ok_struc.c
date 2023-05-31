# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> 
# include <string.h>

typedef struct s_test
{
    char    *name;
    char    *class;
    char    *rollno;
}   t_test;

t_test *sample_function ()
{
    t_test *abc;
    
    abc = malloc(sizeof(t_test));
    printf("sizeof struct - %lu\n",sizeof(*abc));
    printf("sizeof struct ptr - %lu\n",sizeof(abc));
    printf("abc addr ptr - %p\n",abc);

    abc->name = strdup("Surya");
    abc->class = "MD5";
    abc->rollno = "12345";
    printf("%s %s %s\n",abc->name,abc->class,abc->rollno);
    return abc;
}

int main()
{
    t_test   *digest_abc = NULL;
    t_test   *abc = NULL;

    abc = sample_function();

    digest_abc = abc;
    printf(" %s  %s  %s \n",digest_abc->name,digest_abc->class,digest_abc->rollno);

    free(abc->name);
    free(digest_abc);

    return 0;
}
