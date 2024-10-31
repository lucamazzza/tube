#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test_task(const char *name) {
    char cmd[100], fname[100], fres[100];

    strcpy(cmd, "./src/tube < test/io/");
    strcat(cmd, name);
    strcat(cmd, ".txt > tmp.txt");
    
    strcpy(fname, "test/io/");
    strcat(fname, name);
    strcpy(fres, fname);
    strcat(fname, ".txt");
    strcat(fres, ".out");
    
    system(cmd);
    FILE *file = fopen("tmp.txt", "r");
    FILE *rfile = fopen(fres, "r");
    int out, res;
    fscanf(file, "%d", &out);
    fscanf(rfile, "%d", &res);
    printf("expected: %-10d", res);
    printf("found: %-10d \t\t", out);
    return res == out;
}

int main() {
    for(int i = 10; i <= 10000;) {
        for(int j = 1; j <= 100;) {
           char tname[100];
           sprintf(tname, "task_%d_%d", i, j);
           int test = test_task(tname);
           printf("Testing task %s: \t%d\n", tname, test);
           if (j == 1) j = 10;
           else if (j == 10 || j == 50) j *= 2;
           else if(j == 20) j = 50;
           else break;
        }
        if (i == 10) i = 100;
        else if (i == 100) i = 300;
        else if (i == 300) i = 1000;
        else if (i == 1000) i = 5000;
        else if (i == 5000) i = 10000;
        else break;
    }
    return 0;
}

