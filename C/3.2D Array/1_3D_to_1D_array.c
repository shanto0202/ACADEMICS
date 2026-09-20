#include <stdio.h>
// For 3D array A[l][m][n], element A[i][j][k] maps to:
// 1D_index = i * (m * n) + j * n + k
int main()
{
    int l = 3, m = 4, n = 5; // Dimensions
    int i = 1, j = 2, k = 3; // Indices
    int index_1D = i * (m * n) + j * n + k;// Formula for 3D to 1D conversion
    printf("3D Array dimensions: %d x %d x %d\n", l, m, n);
    printf("Element A[%d][%d][%d] maps to 1D index: %d\n", i, j, k, index_1D);
    // Verification with actual arrays
    int arr_3D[3][4][5];
    int arr_1D[3 * 4 * 5];
    // Fill both arrays with same pattern
    for (int x = 0; x < l; x++)
    {
        for (int y = 0; y < m; y++)
        {
            for (int z = 0; z < n; z++)
            {
                int value = x * 100 + y * 10 + z;
                arr_3D[x][y][z] = value;
                arr_1D[x * (m * n) + y * n + z] = value;
            }
        }
    }
    printf("\nVerification:");
    printf("\n3D array A[%d][%d][%d] = %d", i, j, k, arr_3D[i][j][k]);
    printf("\n1D array at index %d = %d", index_1D, arr_1D[index_1D]);

    return 0;
}