#include <stdio.h>

int main()
{
    
    int n; 
    scanf("%d",&n);
    
    //initialize array
    int arr[n];
    //read in input 
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int ok = 1;
    
    for(int i = 0; i < n; i++) {
        int opposite_idx = n - i - 1;
        int lo = arr[i];
        int hi = arr[opposite_idx];
        if(hi != lo) {
            ok = 0;
        }
    }
    
    //optional printing
    printf("%d\n",ok);
    
    return 0;
}

/*
samples inputs: 

5
1 2 3 2 1

expected output:
1

5
1 2 3 1 2

expected output:
0
*/
