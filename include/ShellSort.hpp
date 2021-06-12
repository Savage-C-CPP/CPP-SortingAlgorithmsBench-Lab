#include <vector>
#include <cmath>

/*
    Best: O(N log^2 N)
    AVG: O(N^2)
    Worst: O(N^2)
*/

/**
 * @brief Shell sort with Shell's intervals sequence: h(t) = N / 2, h(t - 1) = h(t) / 2, ..., h1 = 1, h0 = 0
 * 
 * @tparam T Data type of collection
 * @tparam Comparator Function that compares two elements and returns true or false
 * @param arr Origin collection
 * @param cmp Comparator
 * @return std::vector<T> Sorted collection
 */
template <typename T, class Comparator>
void shell_sort(std::vector<T> &arr, Comparator cmp)
{
    size_t step = arr.size() / 2;
    T buf;
    while (step != 0)
    {
        for (size_t i = 0; i < arr.size(); ++i)
        {
            buf = arr[i];
            while (i >= step && cmp(buf, arr[i - step]))
            {
                arr[i] = arr[i - step];
                i -= step;
            }
            arr[i] = buf;
        }
        step /= 2;
    }
}
