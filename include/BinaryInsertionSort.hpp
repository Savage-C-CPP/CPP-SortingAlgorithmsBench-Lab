#include <vector>

/*
    Best: O(N^2)
    AVG: O(N^2)
    Worst: O(N^2)
*/

template <typename T, class Comparator>
void bin_insertion_sort(std::vector<T> &arr, Comparator cmp)
{
    for (size_t i = 1; i < arr.size(); ++i)
    {
        T buf = arr[i];
        size_t low = 0, high = i, mid;
        while (low < high)
        {
            mid = low + (high - low) / 2;
            if (cmp(buf, arr[mid]))
                high = mid;
            else
                low = mid + 1;
        }
        for (size_t j = i; j >= low + 1; --j)
            arr[j] = arr[j - 1];
        arr[low] = buf;
    }
}
