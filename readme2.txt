Type "make" to make all 3 files

run with "./program2 filex.txt filey.txt output.txt"

Data structures used: 2d array to store subproblem results

Complexity: Recursively computes subproblems, breaking into two subproblems each taking O(max(m,n)) time.
Complexity should be O(max(m,n) * 2^max(m,n)), where m and n are length of the input strings. 
