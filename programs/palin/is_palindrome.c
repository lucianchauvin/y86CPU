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
    int i = n - 1;
    int lo = 0;
    
    while(i >= 0) {
        if(arr[lo] != arr[i]) ok = 0;
        lo++;
        i--;
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
