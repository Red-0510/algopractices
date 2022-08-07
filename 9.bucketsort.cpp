// Bucket sort
// complexity:O(n) assumes uniform random distribution of values over the interval [0,1)
// basic principle: it splits the elements into n arrays(bucket) so that numbers fall in range 0 to 1 
//                     then it sorts the individual buckets and merges their results
// pseudocode:
//     BUCKET_SORT(A):
//     n=A.length
//     B[0...n-1] be new array 
//     for i=0 to n-1:
//         make B[i] an empty list(bucket)
//     for i=1 to n:
//         insert A[i] into list b[int(n*A[i])]
//     for i=0 to n-1:
//         sort list B[i] with insertion sort/or other fast sorting algorith for lesser inputs
//     merge the results of individual lists B[0],B[1],...B[n-1] in order 