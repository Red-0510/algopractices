// Radix Sort
// complexity:O(d*(n+k));d is no of digits ;n is number of elements to sort; k is number of possible values a digit can take i.e 10
// basic principle: it sorts the least significant digit of all the numbers and then proceeds further to sort the most dignificant digit 
// requirements: needs same amount of digits in all numbers
//              needs to use a stable sort in between (stable sort means that it maintains the respective order of equal elements as in which comes first)
//              stable sort egs:insertion sort, merge sort, counting sort 
//              nonstable sorts: heapsort, quicksort
//pseudocode:
// for i=1 to d:
//     use stable sort to sort the array based on the ith digit