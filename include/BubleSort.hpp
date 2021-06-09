#include <vector>

/*
    Best: O(N)
    Avg: O(N^2)
    Worst: O(N^2)
*/

template <typename T, class Comparator>
std::vector<T> buble_sort(std::vector<T> arr, Comparator cmp)
{
    if (arr.size() < 2)
        return arr;
    typename std::vector<T>::iterator cur, next, last;
    last = arr.end();
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (cur = arr.begin(), next = cur, ++next; next != last; ++cur, ++next)
        {
            if (cmp(*next, *cur))
            {
                auto t = *cur;
                *cur = *next;
                *next = t;
                sorted = false;
            }
        }
        --last;
    }
    return arr;
}
