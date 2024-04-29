#include <stdio.h>

int main()
{
    //read in length of input
    int n; 
    scanf("%d",&n);
    
    //initialize array
    int arr[n];
    //read in input 
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    
    //run some sort O(n^2) sort. names are hard. 
    for(int i = 0; i < n; i++) {
        for(int j = 1; j < n; j++) {
            if(arr[j-1] > arr[j]) {
                int t = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = t;
            }
        }
    }
    
    //optional printing for debugging
    
    for(int i = 0; i < n; i++) {
        printf("%d ",arr[i]);
    }
    printf("\n");
    
    return 0;
}
/*
sample input:

5
7 5 6 8 1

*/