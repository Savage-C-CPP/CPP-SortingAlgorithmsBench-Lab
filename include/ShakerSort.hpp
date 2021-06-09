#include <vector>
/*
    Best: O(N)
    Avg: O(N^2)
    Worst: O(N^2)
*/

template <typename T, class Comparator>
std::vector<T> shaker_sort(std::vector<T> arr, Comparator cmp)
{
    if (arr.size() < 2)
        return arr;
    typename std::vector<T>::iterator first, cur, next, last;
    first = arr.begin();
    --first; // BUG: This causes "double free or corruption (out)" when use G<T> comparison
    last = arr.end();
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (cur = first, next = cur, ++next; next != last; ++cur, ++next)
        {
            if (cmp(*next, *cur))
            {
                auto t = *cur;
                *cur = *next;
                *next = t;
                sorted = false;
            }
        }
        if (sorted) break;
        --last;
        for (cur = last, next = cur, --next; next != first; --cur, --next)
        {
            if (!cmp(*next, *cur))
            {
                auto t = *cur;
                *cur = *next;
                *next = t;
                sorted = false;
            }
        }
        first++;
    }
    return arr;
};
