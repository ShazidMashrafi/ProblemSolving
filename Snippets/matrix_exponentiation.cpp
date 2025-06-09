Matrix multiply(const Matrix &A, const Matrix &B) {
    int n = A.size(); Matrix result(n, vector<long long>(n, 0)); 
    for (int i = 0; i < n; ++i) { for (int j = 0; j < n; ++j) { for (int k = 0; k < n; ++k) { 
    result[i][j] = (result[i][j] + A[i][k] * B[k][j]) % mod; } } } return result;} 
Matrix matrixExpo(Matrix A, long long power) { int n = A.size(); Matrix result(n, vector<long long>(n, 0)); 
    for (int i = 0; i < n; ++i) result[i][i] = 1; while (power > 0) { if (power % 2 == 1) { 
    result = multiply(result, A); } A = multiply(A, A); power /= 2; } return result; } 
