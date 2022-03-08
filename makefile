all:
	gcc 1-Two-Sum.c -o 1
	gcc 9-Palindrome-Number.c -o 9
	gcc 13-Roman-to-Integer.c -o 13
	gcc 14-Longest-Common-Prefix.c -o 14
	gcc 20-Valid-Parentheses.c -o 20
	gcc 21-Merge-Two-Sorted-Lists.c -o 21
	gcc 26-Remove-Duplicates-from-Sorted-Array.c -o 26
	gcc 27-Remove-Element.c -o 27
	gcc 28-Implement-strStr().c -o 28
	gcc 35-Search-Insert-Position.c -o 35
	gcc 45-Jump-Game-II_byBFS.c -o 45BFS
	gcc 45-Jump-Game-II_byDP.c -o 45DP
	gcc 45-Jump-Game-II_byGreedy.c -o 45Greedy
	gcc 53-Maximum-Subarray.c -o 53
	gcc 55-Jump-Game.c -o 55
	gcc 58-Length-of-Last-Word.c -o 58
	gcc 66-Plus-One.c -o 66
	gcc 67-Add-Binary.c -o 67
	gcc 69-Sqrt(x).c -o 69
	gcc 70-Climbing-Stairs.c -o 70
	gcc 82-Remove-Duplicates-from-Sorted-List-II.c -o 82
	gcc 83-Remove-Duplicates-from-Sorted-List.c -o 83
	gcc 88-Merge-Sorted-Array.c -o 88
	gcc 94-Binary-Tree-Inorder-Traversal.c -o 94
	gcc 100-Same-Tree.c -o 100
	gcc 101-Symmetric-Tree.c -o 101
	gcc 102-Binary-Tree-Level-Order-Traversal.c -o 102
	gcc 104-Maximum-Depth-of-Binary-Tree.c -o 104
	gcc 108-Convert-Sorted-Array-to-Binary-Search-Tree.c -o 108
	gcc 110-Balanced-Binary-Tree.c -o 110
	gcc 111-Minimum-Depth-of-Binary-Tree.c -o 111
	gcc 112-Path-Sum.c -o 112
	gcc 118-Pascals-Triangle.c -o 118
	gcc 119-Pascals-Triangle-II.c -o 119
	gcc 125-Valid-Palindrome.c -o 125
	gcc 136-Single-Number.c -o 136
	gcc 139-Word-Break.c -o 139
	gcc 141-Linked-List-Cycle.c -o 141
	gcc 144-Binary-Tree-Preorder-Traversal.c -o 144
	gcc 145-Binary-Tree-Postorder-Traversal.c -o 145
	gcc 152-Maximum-Product-Subarray.c -o 152
	gcc 155-Min-Stack.c -o 155
	gcc 160-Intersection-of-Two-Linked-Lists.c -o 160
	gcc 168-Excel-Sheet-Column-Title.c -o 168
	gcc 169-Majority-Element.c -o 169
	gcc 171-Excel-Sheet-Column-Number.c -o 171
	gcc 190-Reverse-Bits.c -o 190
	gcc 191-Number-of-1-Bits.c -o 191
	gcc 198-House-Robber.c -o 198
	gcc 202-Happy-Number.c -o 202
	gcc 203-Remove-Linked-List-Elements.c -o 203
	gcc 205-Isomorphic-Strings.c -o 205
	gcc 206-Reverse-Linked-List.c -o 206
	gcc 213-House-Robber-II.c -o 213
	gcc 217-Contains-Duplicate_byQuickSort.c -o 217
	gcc 219-Contains-Duplicate-II_byRadixSort.c -o 219
	gcc 220-Contains-Duplicate-III_byRadixSort.c -o 220
	gcc 225-Implement-Stack-using-Queues.c -o 225
	gcc 429-N-ary-Tree-Level-Order-Traversal.c -o 429
	gcc 509-Fibonacci-Number.c -o 509
	gcc 538-Convert-BST-to-Greater-Tree.c -o 538
	gcc 589-N-ary-Tree-Preorder-Traversal.c -o 589
	gcc 590-N-ary-Tree-Postorder-Traversal.c -o 590
	gcc 637-Average-of-Levels-in-Binary-Tree.c -o 637
	gcc 653-Two-Sum-IV-Input-is-a-BST.c -o 653
	gcc 740-Delete-and-Earn_byQuickSort.c -o 740
	gcc 746-Min-Cost-Climbing-Stairs.c -o 746
	gcc 918-Maximum-Sum-Circular-Subarray.c -o 918
	gcc 1014-Best-Sightseeing-Pair.c -o 1014
	gcc 1030-Matrix-Cells-in-Distance-Order.c -o 1030
	gcc 1137-N-th-Tribonacci-Number.c -o 1137
	gcc 1464-Maximum-Product-of-Two-Elements-in-an-Array_byRadixSort.c -o 1464
	gcc 1567-Maximum-Length-of-Subarray-With-Positive-Product.c -o 1576
	gcc 1878-Get-Biggest-Three-Rhombus-Sums-in-a-Grid.c -o 1878
clean:
	rm -f *.exe