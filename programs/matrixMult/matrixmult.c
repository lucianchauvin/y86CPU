int main()
{
    //read in dimensions of matrix
    //initialize initialize dimensions of matrices
    int m[2][2] = {{1,2},{3,4}};
    int n[2][2] = {{5,6},{7,8}};
    int nm[2][2];

    nm[0][0] = m[0][0]*n[0][0] + m[0][1]*n[1][0];
    nm[0][1] = m[0][0]*n[0][1] + m[0][1]*n[1][1];
    nm[1][0] = m[1][0]*n[0][0] + m[1][1]*n[1][0];
    nm[1][1] = m[1][0]*n[0][1] + m[1][1]*n[1][1];
    
    return 0;
}

