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
int nullifyments[MAX_N][2];
int leaf[MAX_N];
int mem[MAX_N];

int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

// TODO: Document as flowchart
int dfs(int node, int *dl) {
  if (mem[node] != -1) {  
    *dl = leaf[node];
    return mem[node];
  }
  int max_branch_weight = 0;
  int max_leaf = node;
  for (int i = 0; i < child_count[node]; i++) {
    int child = children[node][i];
    int child_leaf;
    int child_weight = dfs(child, &child_leaf);
    if (child_weight > max_branch_weight) {
      max_branch_weight = child_weight;
      max_leaf = child_leaf;
    }
  }
  mem[node] = joints[node].time + max_branch_weight;
  leaf[node] = max_leaf;
  *dl = max_leaf;
  return mem[node];
}

int minimize_time(int root, int N, int C, int k) {
  if (N <= C)
    return 0;
  if (C == 0 ) {
    //for (int i = 0; i < 10; i++) {
    //    printf("%d | %d\n", nullifyments[i][0], nullifyments[i][1]);
    //}
    return nullifyments[0][1]; 
  }
  
  int leaf, hb = dfs(root, &leaf);
  while (leaf != -1 && k < MAX_N) {
    int dummyptr = 0, joint_time = joints[leaf].time, mem_leaf = mem[leaf];
    joints[leaf].time = 0;
    mem[leaf] = -1;
    hb = dfs(root, &dummyptr);
    nullifyments[k][0] = leaf;
    nullifyments[k][1] = hb;
    joints[leaf].time = joint_time;
    mem[leaf] = mem_leaf;
    int parent = joints[leaf].parent;
    leaf = parent;
    k++;
  }
  qsort(nullifyments, k, sizeof(nullifyments[0]), compare);
  return minimize_time(root, N, C - 1, k);
}

int main() {
  int N, C;
  scanf("%d %d", &N, &C);
  for (int i = 0; i < N; i++) {
    mem[i] = -1;
    child_count[i] = 0;
    nullifyments[i][0] = -1;
    nullifyments[i][1] = -2;
  }
  for (int i = 0; i < N; i++) {
    int t, p;
    scanf("%d %d", &t, &p);
    joints[i].time = t;
    joints[i].parent = p;
    joints[i].id = i;
    if (p != -1) {
      children[p][child_count[p]++] = i;
    }
    //printf("Joint %d, (parent: %d)\n", joints[i].id, joints[i].parent);
  }
  int root = -1;
  for (int i = 0; i < N; i++) {
    if (joints[i].parent == -1) {
      root = i;
      break;
    }
  }
  int result = minimize_time(root, N, C, 0);
  printf("%d\n", result);
  return 0;
}
