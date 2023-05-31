
/* create a progm with a gas station which will fuel vehicles in perpetuity

--> 2 threads

-- > multiple threads


https://stackoverflow.com/questions/1345670/stack-smashing-detected
 */

#include <stdio.h>
#include <stdlib.h>

#define N 5
#define M 4

void transform(int* buf, int** matr, int n, int m);
void resetMatrix(int** ptr, int n, int m);
void printMatrix(int** mt, int n, int m);

int main(void)
{
    int matrix[N][M];
    int* ptr = (int*)(matrix + N);

    transform(ptr, (int**)matrix, N, M);
    resetMatrix((int**)matrix, N, M);
    printMatrix((int**)matrix, N, M);

    return 0;
}

void resetMatrix(int** ptr, int n, int m)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ptr[i][j] = 0;
        }
    }
}

void transform(int* buf, int** matr, int n, int m)
{
    for (int i = 0; i < n; i++) {
        matr[i] = buf + i * m;
    }
}

void printMatrix(int** mt, int n, int m)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            printf("%d ", mt[i][j]);
        printf("\n");
    }
}

