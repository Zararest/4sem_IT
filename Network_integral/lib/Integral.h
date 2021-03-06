#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/sysinfo.h>
#include <math.h>
#include <time.h>

#include "Error.h"

#define DELTA_X 0.0002
#define RANGE 10000
#define PAGE_SIZE 4096

typedef struct Integral Integral;

double definite_integral(double from, double to);

double get_result(Integral* integr);
void set_threads(Integral* integr, int num_of_busy_cores);

Integral* create_integral(int num_of_threads, double range_per_thread, double start_point);
void clean_integral(Integral* integr);