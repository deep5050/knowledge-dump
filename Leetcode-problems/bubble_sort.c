
void bubble(int *arr, int size)
{
    int flag = 0;
    while (!flag)
    {
        int swapped = 0;
        for (int i = 0; i < size - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped)
            flag = 1;
    }
}
