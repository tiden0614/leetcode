// compute the width of the biggest possible square of which the upper-left corner is (i, j)
// recursively use the result of the point (i+1, j+1)
// store the width information in an array of widths
int compute_width(char** matrix, int r, int c, int i, int j, int* widths) {
    // corner conditions
    if (i >= r || j >= c) return 0;
    int w_index = (j * r) + i;
    if (i == r - 1 || j == c - 1) {
        widths[w_index] = matrix[i][j] - '0';
        return matrix[i][j] - '0';
    }
    // if the width of this point has already been computed, return immediately
    if (widths[w_index] > -1) {
        return widths[w_index];
    }
    // compute the max possible width starting from point (i, j)
    int x;
    int w;
    // find continuous 1s in a row
    for (x = 0; i + x < r && matrix[i + x][j] == '1'; x++);
    for (w = 0; j + w < c && matrix[i][j + w] == '1'; w++);
    w = w < x? w : x;
    // if the max possible width is 0, there's no need to continue the computation
    if (w == 0) return 0;
    // recursively get the max possible width of the next point. i.e. (i+1, j+1)
    int next_w = compute_width(matrix, r, c, i + 1, j + 1, widths);
    if (w <= next_w) {
        widths[w_index] = w;
        return w;
    } else {
        widths[w_index] = next_w + 1;
        return next_w + 1;
    }
}

int maximalSquare(char** matrix, int matrixRowSize, int matrixColSize) {
    if (matrixRowSize <= 0 || matrixColSize <= 0) return 0;
    int max_width = 0;
    int l = matrixRowSize * matrixColSize;
    int* widths = (int *) malloc(l * sizeof(int));
    int i;
    int j;
    int w;
    for (i = 0; i < l; i++) {
        widths[i] = -1;
    }
    for (j = 0; j < matrixColSize; j++) {
        for (i = 0; i < matrixRowSize; i++) {
            w = compute_width(matrix, matrixRowSize, matrixColSize, i, j, widths);
            if (w > max_width) max_width = w;
        }
    }
    return max_width * max_width;
}