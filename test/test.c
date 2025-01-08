#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_ORANGE  "\x1b[33m"
#define ANSI_COLOR_GREY    "\x1b[37m"
#define ANSI_COLOR_YELLOW  "\x1b[93m"
#define ANSI_COLOR_BRED    "\x1b[91m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_INVERT_BOLD   "\e[1;7m"
#define ANSI_REGULAR       "\e[m"

double times[30];
int current_task = 0;

float avg_time(void) {
    float sum = 0;
    for (int i = 0; i < current_task; i++) {
        sum += times[i];
    }
    return sum / current_task;
}

int test_task(const char *name) {
    char cmd[100], fname[100], fres[100];
    strcpy(cmd, "{ ./src/tube < test/io/");
    strcat(cmd, name);
    strcat(cmd, ".txt > tmp.txt; } 2> errors.txt");
    strcpy(fname, "test/io/");
    strcat(fname, name);
    strcpy(fres, fname);
    strcat(fname, ".txt");
    strcat(fres, ".out");
    clock_t start = clock();
    system(cmd);
    clock_t end = clock();
    float time_taken = ((float)(end - start) / CLOCKS_PER_SEC) * 1000;
    times[current_task++] = time_taken;
    FILE *file  = fopen("tmp.txt", "r");
    FILE *efile = fopen("errors.txt", "r");
    FILE *rfile = fopen(fres, "r");
    int out, res;
    char errors;
    fscanf(file, "%d", &out);
    fscanf(rfile, "%d", &res);
    fscanf(efile, "%s", &errors);
    printf("%-20s", name);
    printf(ANSI_COLOR_GREY "%-12d %-12d %-20f" ANSI_COLOR_RESET, res, out,  time_taken);
    if (strcmp(&errors, "")) {
        return -1;
    }
    return res == out;
}

int main() {
    int passed  = 0;
    int failed  = 0;
    int total   = 0;
    printf(ANSI_INVERT_BOLD "Task                Expected     Got         Time taken [ms]      Status" ANSI_REGULAR "\n");
    for(int i = 10; i <= 10000;) {
        for(int j = 1; j <= 100;) {
            char tname[100];
            sprintf(tname, "task_%d_%d", i, j);
            int test = test_task(tname);
            if (test == 1) {
                printf(ANSI_COLOR_GREEN "Passed" ANSI_COLOR_RESET "\n");
                passed++;
            } else if (test == -1) {
                printf(ANSI_COLOR_BRED "Errors" ANSI_COLOR_RESET "\n");
                failed++;
            } else {
                printf(ANSI_COLOR_RED "Failed" ANSI_COLOR_RESET "\n");
                failed++;
            }
            total++;
            if (j == 1)                  j = 10;
            else if (j == 10 || j == 50) j *= 2;
            else if(j == 20)             j = 50;
            else break;
        }
        if (i == 10)        i = 100;
        else if (i == 100)  i = 300;
        else if (i == 300)  i = 1000;
        else if (i == 1000) i = 5000;
        else if (i == 5000) i = 10000;
        else break;
    }
    printf("\nTesting done, ");
    if      (!failed)                               printf(ANSI_COLOR_GREEN);
    else if (failed > 0 && failed < (total/2))      printf(ANSI_COLOR_YELLOW);
    else if (failed >= (total/2) && failed < total) printf(ANSI_COLOR_ORANGE);
    else                                            printf(ANSI_COLOR_RED);
    printf("%d%%" ANSI_COLOR_RESET " passed\n", ((passed*100)/total));
    printf("\nAverage time taken: %fs\n", avg_time());
    return 0;
}
