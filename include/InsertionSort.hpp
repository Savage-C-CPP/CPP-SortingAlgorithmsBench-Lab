#include <vector>

/*
    Best: O(N)
    AVG: O(N^2)
    Worst: O(N^2)
*/

template <typename T, class Comparator>
std::vector<T> insertion_sort(std::vector<T> arr, Comparator cmp)
{
    for (size_t i = 1; i < arr.size(); ++i)
    {
        T buf = arr[i];
        bool inserted = false;
        size_t j = i;
        while (!inserted)
        {
            if (cmp(arr[j - 1], buf) || j == 0)
            {
                arr[j] = buf;
                inserted = true;
            }
            else
            {
                arr[j] = arr[j - 1];
                --j;
            }
        }
    }
    return arr;
}
