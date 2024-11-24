#include <limits.h>
#include <stdio.h>

#define MAXN 10000          // Maximum amount of joints
#define MAXC 100            // Maximum amount of spares

typedef long long ll;       // `long long` is now `ll` for short

int N, C;
ll  T[MAXN];                // Maintenance time of each joint
int adj[MAXN][MAXN];        // Static adjacency matrice
int child_count[MAXN];      // Child count for each joint
ll  mem[MAXN][MAXC + 1];    // Memory for dynamic programming

// Minimum between `a` and `b`
ll min(ll a, ll b) { return a < b ? a : b; }

// Maximum between `a` and `b`
ll max(ll a, ll b) { return a > b ? a : b; }

// Minimizes the time taken to start production by removing C joints
// and so nullifying their maintenance time.
//
// - Input:     the root of the system
// - Base case: a leaf, so given it has no children, the weight of the subtree is determined by the leaf itsself.
// - Rec. case: computes the max time for children; for each spare, try to apply `x` spares and `(c - x)` for the rest.
//              Save the minimum between current values, considering the max between the child result and the subtree.
// - Wrap-up:   Consider installing a spare, computing the minimum between installing and using a spare and not.
//
// Time Complexity:     O(N * C^2)
// Space Complexity:    O(N * C)
void minimize_time(int u) {
  // Base case
  if (child_count[u] == 0) { 
    mem[u][0] = T[u];
    for (int c = 1; c <= C; c++) {
      mem[u][c] = 0;
    }
    return;
  }
  // Recursive case
  for (int i = 0; i < child_count[u]; i++) {
    int v = adj[u][i];
    minimize_time(v);
    ll cur[MAXC + 1];
    for (int c = 0; c <= C; c++) {
      cur[c] = LLONG_MAX; // Inizializza a infinito
    }
    for (int c = 0; c <= C; c++) {
      for (int x = 0; x <= c; x++) {
        cur[c] = min(cur[c], max(mem[v][x], mem[u][c - x]));
      }
    }
    for (int c = 0; c <= C; c++) {
      mem[u][c] = cur[c];
    }
  }
  ll cur[MAXC + 1];
  cur[0] = T[u] + mem[u][0];
  // Wrap-up
  for (int c = 1; c <= C; c++) {
    cur[c] = min(T[u] + mem[u][c], mem[u][c - 1]);
  }
  for (int c = 0; c <= C; c++) {
    mem[u][c] = cur[c];
  }
}

int main() {
  scanf("%d %d", &N, &C);
  int root = -1;
  for (int i = 0; i < N; i++) {
    int p;
    ll t;
    scanf("%lld %d", &t, &p);
    T[i] = t;
    if (p != -1) {
      adj[p][child_count[p]++] = i;
    } else {
      root = i;
    }
  }
  minimize_time(root);
  printf("%lld\n", mem[root][C]);
  return 0;
}
