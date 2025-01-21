#include "shell.h"

Job jobs[MAX_JOBS] = {0};
int job_count = 0;
char history[HISTORY_SIZE][MAX_LINE] = {0};
int history_count = 0;