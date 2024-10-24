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
int joint_ids[MAX_N];

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
    printf("%d\n", current_branch_time);
    return current_branch_time;
}

int compare(const void *a, const void *b) {
    int idx_a = *(int *)a;
    int idx_b = *(int *)b;
    return joint_times[idx_b] - joint_times[idx_a];
}

int minimize_time(int root, int C) {
    int size = 0;
    int heaviest_branch = 0;
    dfs(root, &size, &heaviest_branch);  
    int indices[MAX_N];
    for (int i = 0; i < size; i++) {
        indices[i] = i; 
    }
    // TODO: Replace with self-made sort
    qsort(indices, size, sizeof(int), compare);
    printf("Removed nodes: ");
    for (int i = 0; i < C && i < size; i++) {
        printf("%d: {%d} ", joints[indices[i]].id, joints[indices[i]].time);
        joints[indices[i]].time = 0;
    }
    printf("\n");
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
        printf("Joint %d: {time=%d, parent=%d}\n", joints[i].id, joints[i].time, joints[i].parent);
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
    int result = minimize_time(root, C);
    printf("Minimized time: %d\n", result);
    return 0;
}

