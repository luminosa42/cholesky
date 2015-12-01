#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#define ARGS 2
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

double get_clock() {
    struct timeval tv;
    int status;
    status = gettimeofday(&tv, (void *) 0);
    if(status<0)
        printf("gettimeofday error");
    return (tv.tv_sec * 1.0 + tv.tv_usec * 1.0E-6);
}

void init_array(int n, double *a) {
    int i,j,k;
    double *b;
    b = (double *)malloc(n * n * sizeof(double));
    for(i = 0; i < n * n; i++)
        a[i] = 0;
    srand((unsigned) time(NULL));
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++) {
            b[i * n + j] = rand() % 100;
//          printf("%lf ", b[i * n + j]);
        }

//    printf("\n");

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++) {
            for(k = 0; k < n; k++)
                a[i * n + j] += b[i * n + k] * b[j * n + k];
//	printf("%lf, ", a[i * n + j]);
        }
//    printf("\n");
}

int main(int argc, char* argv[]) {

    int n;
    double ts, te; /* Starting time and ending time */
    double *a, *l;
    double temp;
    if(argc < ARGS) {
        fprintf(stderr,"Wrong # of arguments.\nUsage: %s array_size",argv[0]);
        return -1;
    }
    n = atoi(argv[1]);

    a = (double *)malloc(n*n*sizeof(double));
    l = (double *)malloc(n*n*sizeof(double));
    init_array(n,a);
/*    printf("Initial matrix:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            printf("%lf ", a[i*n+j]);
        printf("\n");
    }
*/
    ts=get_clock();

    /*Serial decomposition*/
    for (int i = 0; i < n; i++){
        for (int j = 0; j < (i+1); j++) {
            temp = 0;
            for (int k = 0; k < j; k++)
                temp += l[i * n + k] * l[j * n + k];
            if (i == j)
                l[i * n + j] = sqrt(a[i * n + i] - temp);
            else {
                l[i * n + j] = (a[i * n + j] - temp)/ l[j * n + j];
            }
	      }
    }
    te=get_clock();
/*    printf("Decomposed matrix:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            printf("%lf ", l[i*n+j]);
        printf("\n");
    }
*/
    printf("Elapsed time=%e\n", te - ts);

    free(a);
    free(l);
    return 0;
}
