// TODO: Comment Functions and Structs

// START IMPORTS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// END IMPORTS

// START DEFINES
#define MAX_N 10000
// END  DEFINES

// START STRUCTS
typedef struct {
  int time;
  int parent;
  int id;
} Joint;
// END STRUCTS

// START GLOBALS
Joint joints[MAX_N];
int children[MAX_N][MAX_N];
int childc[MAX_N];
int leaves[MAX_N];
int memory[MAX_N];
// END GLOBALS

// START DEFINITIONS
int dfs(int node, int *dl);
int minimize_time(int root, int N, int C, int k);
// END DEFINITIONS

// TODO: Document as flowchart
int dfs(int node, int *dl) {
  if (memory[node] != -1) {
    *dl = leaves[node];
    return memory[node];
  }
  int mb = 0;
  int ml = node;

  for (int i = 0; i < childc[node]; i++) {
    int child_leaf;
    int child = children[node][i];
    int child_weight = dfs(child, &child_leaf);
    if (child_weight > mb) {
      mb = child_weight;
      ml = child_leaf;
    }
  }
  memory[node] = joints[node].time + mb;
  leaves[node] = ml;
  *dl = ml;
  return memory[node];
}

int minimize_time(int root, int N, int C, int k) {
  if (N <= C)
    return 0;
  if (C == 0)
    return dfs(root, &k);
  int leaf = -1;
  int hb = dfs(root, &leaf);
  int bt = hb;
  int bj = leaf;

  printf("\nC = %d------------------\n", C);
  printf("HB: %d\n", hb);
  printf("Start: %d\n", leaf);

  while (leaf != -1) {
    if (joints[leaf].time != 0) {
      int joint_time = joints[leaf].time;
      int mem_time = memory[leaf];
      int dummy = 0;
      joints[leaf].time = 0;
      hb = dfs(root, &dummy);
      joints[leaf].time = joint_time;
      memory[leaf] = mem_time;
      if (hb < bt) {
        bt = hb;
        bj = leaf;

        printf("New HB: %d\n", hb);
      }
    }
    leaf = joints[leaf].parent;
    k++;
  }

  printf("Removed %d, with weight %d\n", bj, joints[bj].time);

  joints[bj].time = 0;

  printf("K: %d\n", k);

  return minimize_time(root, N, C - 1, k);
}

int main() {
  int N, C;
  scanf("%d %d", &N, &C);
  for (int i = 0; i < N; i++) {
    memory[i] = -1;
    childc[i] = 0;
  }
  for (int i = 0; i < N; i++) {
    int t, p;
    scanf("%d %d", &t, &p);
    joints[i].time = t;
    joints[i].parent = p;
    joints[i].id = i;
    if (p != -1)
      children[p][childc[p]++] = i;
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
