# Dynamic programming
1. Memory Saving:
$$
F(X,Y,...) = G(F(X - L_{x1}, Y, ...), F(X - L_{x2}, Y, ...), ..., F(X - L_{xn}, Y, ...), F(X_{xi}, Y_{y1}, ...), ..., F(X_{xi}, Y_{yn}))
for x1 < x2 < ... < xn, y1 < y2 < .. < yn
$$
For X, Y, Z, ... as T, We should consider both the Range of T, and the tn,, the Range of T is as bigger as better, the tn is smaller as better.
when we choose the T. We could apply the space as F[tn + 1][X]...[Z] instead of F[X]...[T]...[Z].
Then we can use the formula F[t % (tn + 1)][x]..[z] = [(t-ti) % (tn + 1)][x]...[z]
2. coding skill:
    1. Be careful about the base case. which normally is F[0][Y][Z], F[X][0][Z], ....
    2. For F[x][y][z], we should give it a proper initial value, if try get max of something, than #include <limits>, using std::numeric_limits<Number_Type>:: min().
    3. using `F[x][y][z] = max(F[x][y][z], some value in G)` if more clear than if (some value in G > F[x][y][z]) {F[x][y][z] = some value in G}. In C++, using reference value is even more clear.
3. pitfalls:
    1. f[x,y,z], x, y, z should be the length of X, Y. because it's from 0 to X.size(), so should initialize F as (F[X.size() + 1, Y.size() +1, ...]), and when iterate the funcition.
    ```C++
    for (int i = 1; i <= X.size(); i++) {
        for (int j = 1; j <= Y.size(); j++) {
            ...
            if (X[i - 1] == Y[j - 1]) // remember that i, j presents the size(), not the index; the current index should be size - 1;
            ...
        }
    } 
    ```

