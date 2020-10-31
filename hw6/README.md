# Homework 6
## Hints
### Q1
- 可以通过构建 <from, to> 和 <to, from> 这样的两个图来快速寻找结点的出度与入度。
- 有 root 输入的情况下，输出会包含 node / tree / btree / graph，参见 `checkHasRoot()` 函数。
- 没有 root 输入的情况下，输出会包含 tree / btree / graph， 其中 graph 中可能还会有环的情况，参见 `checkNoRoot()` 函数。
- 使用 BFS 来探测所有的连通点。