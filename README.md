# Tube

## Description

The project consists of solving an optimisation problem with regard to a chocolate factory.

This factory has a chocolate canister (*root*) from which several pipes lead to the production stations. 
production stations; these pipes are interconnected by joints (*nodes*) that periodically have to be maintained, and this
must be maintained, and this takes time.

However, replacement joints (*nodes*) are available which reduce maintenance time to zero.

It is therefore necessary to find out which joints in the tube branch it is best to change in order to achieve the shortest possible time
for the start of production.

### Input

The first line contains two integers $N$, $C$; the first represents the total number of joints in the system,
while the second represents the number of available spares.
The next lines are composed of the parameter $t_n$ (*maintenance time*) and $p_n$ (*parent node*). 

```
N C
t0 p0
t1 p1
 ...
ti pi
```

#### Constraints

- Integer $1 \le N \le 10000$
- Integer $0 C \le 100$
- Integer $0 \le T_i \le 10^4$
- Only one value $P_i = -1$ while for all others $0 \le P_i < N$
- There is always a sequence from $n_i$ leading to the main tank
- You are allowed to perform maintenance operations in parallel

### Output

A single integer value representing the minimum time within which the last station can start production.

### Requirements

A solution is required to find the optimal solution to the problem by using utilising the paradigm of dynamic programming.

## Solution

Analysing the problem request, we guessed that the required algorithm had to solve an
optimisation on a rooted tree, where each node has an associated value (the maintenance time) and where you have
of ‘spare parts’ with which the associated value can be reset.

The objective is to minimise the maximum value in the resulting subtrees, distributing spares optimally
among the nodes.

It is therefore evident that there is an arborescent structure, representing the problem in its entirety, whose nodes must be
nodes must be explored, and then its maximum value calculated.

This problem was first addressed by consulting the course material, in which we found different
options for the recursive exploration of nodes, starting with a root; of these we immediately chose to approach the problem on the basis of the
problem on the basis of the `DFS` prototype.

In summary, the algorithm traverses the tree, from root to leaves, giving priority to depth, calculating
all the part combinations in the subtree of the current node, and then minimising the maximum between the result of the
subtree and that of the current node.

The algorithm was then implemented recursively, which starts from the root and visits the nodes following a
transversal *post-order*, so the children are visited first, then the current node.
The results calculated for the children are combined to calculate the result for the current node.

### Pseudocode

```
```

As can be gathered from the pseudocode, the algorithm consists of three steps:

#### 1. Base case

The base case represents the eventuality in which the algorithm is on a *leaf node*, i.e. a node where there are no
children are present.

In this case the algorithm has two paths it can follow:

* if the number of residual spares $c$ is $0$, the maximum value is simply the value of the node itself;
* if, on the other hand, the number of residual spares $c$ is strictly greater than $0$, the maximum is $0$, since there are no 
children to use them on.

#### 2. General case

For a node with $u$ children, the spares distributions on the subtree are first computed:

* All children $v$ of $n$ are iterated and the solutions computed for the subtrees rooted in $v$ are combined.
* Every possible distribution $x$ of the $c$ spares is attempted where:
    * $x$ spares are applied to the subtree of the child $v$;
    * $c-x$ spares are applied to the remaining children and to $n$.

The formula used is therefore:

$$cur(c) = \min(cur(c), \max(S_v(x), S_u(c - x)))$$

where $cur(c)$ represents the present value calculated for $c$ parts distributed in the subtree,
$S_v(x)$ the optimal solution for $x$ spares applied to the child $v$ and $S_n(c-x)$ is the optimal solution of the
remaining $c-x$ spares applied to node $n$ or its other children.

This minimises the maximum result of the subtree of child $v$ and that of the current node.

#### 3. ‘Wrap-up

Finally, the improvement directly on the current node $n$ is considered, a decision that is saved in the memory
dynamic programming memory:

$$mem(n,c) = \min(T_n + mem(n, c), mem(n, c - 1))$$

# Time statistics

The solution we implemented is fast enough to be judged satisfactory, in our opinion;
we noted the following statistical values (considered for 10 executions of the same instance):

| Data                    | Value      |
| ----------------------- | ---------: |
| Average                 | $175.3$ µs |
| Median                  | $172.5$ µs |
| Range                   | $200.0$ µs |
| Minimum                 | $117.0$ µs |
| Maximum                 | $317.0$ µs |

These data refer to the set of tasks of numerosity $n$ of $30$, with a total execution time of $5,259$ 
ms.

The time complexity thus results to be $O(N\cdot C^2)$, where $N$ is the input size and $C$ is the number of
available spares.

## Space statistics

The algorithm is quite memory-hungry, given its static memory management, with no use of memory 
dynamic memory. This is known to us and will be indicated in future developments;
we have noted the following statistical values (considered for 10 executions of the same instance):

| Data                    | Value       |
| ----------------------- | ----------: |
| Average                 | $5.556$ MB  |
| Median                  | $2.575$ MB  |
| Range                   | $14.850$ MB |
| Minimum                 | $1.650$ MB  |
| Maximum                 | $16.500$ MB |

These data refer to the set of tasks of $n$ $30 in number, with a total utilisation of $33,400$ MB. 
ms.

The spatial complexity thus results to be $O(N\cdot C)$, where $N$ is the input size and $C$ is the number of
available spares.



