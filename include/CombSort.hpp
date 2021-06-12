#include <vector>

/*
    Best: O(N log N)
    AVG: O(N log N)?
    Worst: O(N^2)
*/

template <typename T, class Comparator>
void comb_sort(std::vector<T> &arr, Comparator cmp)
{
    if (arr.size() < 2)
        return;

    size_t step = arr.size() - 1;
    float k = 1.2473309;
    while (step > 1)
    {
        for (size_t i = 0; i + step < arr.size() - 1; ++i)
        {
            if (cmp(arr.at(i + step), arr.at(i)))
            {
                auto t = arr.at(i + step);
                arr[i + step] = arr[i];
                arr[i] = t;
            }
        }
        step /= k;
    }

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
}
