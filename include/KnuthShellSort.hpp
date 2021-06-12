#include <vector>
#include <cmath>

/*
    Best: O(N log^2 N)
    AVG: O(N^2)
    Worst: O(N^2)
*/

/**
 * @brief Shell sort with Knuth's intervals sequence: t = logh(3, N - 1); h0 = 0, h1 = 1, ..., h(t) = (h(t - 1) - 1) / 3
 * 
 * @tparam T Data type of collection
 * @tparam Comparator Function that compares two elements and returns true or false
 * @param arr Origin collection link
 * @param cmp Comparator
 */
template <typename T, class Comparator, int constanta = 3>
void knuth_shell_sort(std::vector<T> &arr, Comparator cmp)
{
    if (arr.size() < 2)
        return;

    size_t t = log(arr.size() - 1) / log(constanta);
    size_t h = 1;
    for (size_t i = 0; i < t; ++i)
        h = constanta * h + 1;

    T buf;
    while (h >= 1)
    {
        for (size_t i = h; i < arr.size(); ++i)
        {
            buf = arr[i];
            auto j = i;
            while (j > h - 1 && cmp(buf, arr[j - h]))
            {
                arr[j] = arr[j - h];
                j -= h;
            }
            arr[j] = buf;
        }
        h = (h - 1) / constanta;
    }
}
