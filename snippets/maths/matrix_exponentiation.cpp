const long long MOD = 1e9 + 7;
using Matrix = vector<vector<long long>>;

Matrix multiply(const Matrix &A, const Matrix &B, long long m = MOD) {
    int n = A.size();
    Matrix result(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] = (result[i][j] + A[i][k] * B[k][j]) % m;
            }
        }
    }
    return result;
}

Matrix matrixExpo(Matrix A, long long power, long long m = MOD) {
    int n = A.size();
    Matrix result(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) result[i][i] = 1;
    while (power > 0) {
        if (power & 1) {
            result = multiply(result, A, m);
        }
        A = multiply(A, A, m);
        power >>= 1;
    }
    return result;
}
