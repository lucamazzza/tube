// TODO: Comment Functions and Structs

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

typedef struct {
    int time;
    int parent;
    int id;
} Joint;

Joint joints[MAX_N];
int children[MAX_N][MAX_N];
int child_count[MAX_N];
int joint_times[MAX_N];
// TODO: joint_ids is possibly useless?
int joint_ids[MAX_N];

// TODO: Document as flowchart
// TODO: Check if return/hb param is necessary
int dfs(int node, int *size, int *heaviest_branch) {
    int max_child_time = 0;
    for (int i = 0; i < child_count[node]; i++) {
        int child = children[node][i];
        int child_time = dfs(child, size, heaviest_branch);
        if (child_time > max_child_time) {
            max_child_time = child_time;
        }
    }
    int current_branch_time = max_child_time + joints[node].time;
    if (current_branch_time > *heaviest_branch) {
        *heaviest_branch = current_branch_time; 
    }
    joint_times[(*size)] = joints[node].time;
    joint_ids[(*size)++] = node; 
    return current_branch_time;
}

int compare(const void *a, const void *b) {
    int idx_a = *(int *)a;
    int idx_b = *(int *)b;
    // TODO: Find out why is inverted correct
    return joint_times[idx_a] - joint_times[idx_b];
}

int minimize_time(int root, int N, int C) {
    if (N <= C) return 0;
    if (C == 0) return 0;
    int size = 0;
    int heaviest_branch = 0;
    dfs(root, &size, &heaviest_branch);  
    int indices[MAX_N];
    for (int i = 0; i < size; i++) {
        indices[i] = i;
    }
    // TODO: Replace with self-made sort
    qsort(indices, size, sizeof(int), compare);
    joints[indices[0]].time = 0;
    minimize_time(indices[0], N, C - 1);
    size = 0;
    heaviest_branch = 0;
    int hb_new = dfs(root, &size, &heaviest_branch);
    return hb_new;
}

int main() {
    int N, C;
    scanf("%d %d", &N, &C);
    for (int i = 0; i < N; i++) {
        int t, p;
        scanf("%d %d", &t, &p);
        joints[i].time = t;
        joints[i].parent = p;
        joints[i].id = i;
        if (p != -1) {
            children[p][child_count[p]++] = i;
        }
    }
    int root = -1;
    for (int i = 0; i < N; i++) {
        if (joints[i].parent == -1) {
            root = i;
            break;
        }
    }
    int result = minimize_time(root, N, C);
    printf("%d\n", result);
    return 0;
}

