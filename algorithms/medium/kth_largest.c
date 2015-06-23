void quicksort(int* arr, int l, int r) {
    if (l >= r) {
        return;
    }
    int i, j = l, t;
    for (i = l + 1; i <= r; i++) {
        if (arr[i] > arr[l]) {
            j += 1;
            t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    t = arr[l];
    arr[l] = arr[j];
    arr[j] = t;
    quicksort(arr, l, j - 1);
    quicksort(arr, j + 1, r);
}
int findKthLargest(int* nums, int numsSize, int k) {
    quicksort(nums, 0, numsSize - 1);
    return nums[k - 1];
}