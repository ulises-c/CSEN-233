#include <time.h>
clock_t start, end;
double cpu_time_used;
start = clock();
... /* Time-consuming process. */
end = clock();
cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
