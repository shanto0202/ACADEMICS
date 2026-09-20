/*
Proof:

(i) A perfect binary tree of height h has 2^(h+1) - 1 nodes.

In a perfect binary tree, every level is completely full.

Level 0 has 1 node      = 2^0
Level 1 has 2 nodes     = 2^1
Level 2 has 4 nodes     = 2^2
...
Level h has 2^h nodes

Total nodes,
n = 2^0 + 2^1 + 2^2 + ... + 2^h

This is a geometric series.

n = 2^(h+1) - 1

Hence proved.

--------------------------------------------------

(ii) The average depth of a node is Θ(ln n).

In a perfect binary tree:

Number of nodes at depth i = 2^i

So total depth of all nodes:

S = 0*2^0 + 1*2^1 + 2*2^2 + ... + h*2^h

Average depth,

Avg = S / n

Now, most nodes are near the last level.
The height of the tree is h.

From part (i),

n = 2^(h+1) - 1

So,

n + 1 = 2^(h+1)

Taking log on both sides,

h + 1 = log2(n + 1)

h = log2(n + 1) - 1

Therefore,

h = Θ(log n)

Since log base does not matter in asymptotic notation,

log2 n = Θ(ln n)

Average depth is proportional to height h.

Therefore,

Average depth = Θ(h) = Θ(log n) = Θ(ln n)

Hence proved.
*/