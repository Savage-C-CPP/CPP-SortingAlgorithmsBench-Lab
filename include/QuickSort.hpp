#include <vector>

/*
    Best: O(N log N)
    Avg: O(N log N)
    Worst: O(N^2)
*/

template <typename T, class Comparator>
void quick_sort(std::vector<T> &arr, Comparator cmp)
{
    if (arr.size() < 2)
        return;

    else
    {
        size_t ix = 0;
        T pivot = arr[ix];
        std::vector<T> less, greater;

        for (size_t i = 1; i < arr.size(); ++i)
        {
            if (cmp(arr[i], pivot))
                less.push_back(arr[i]);
            if (cmp(pivot, arr[i]))
                greater.push_back(arr[i]);
        }

        less = quick_sort(less, cmp);
        greater = quick_sort(greater, cmp);

        arr.clear();
        for (typename std::vector<T>::iterator it = less.begin(); it != less.end(); ++it)
            arr.push_back(*it);
        arr.push_back(pivot);
        for (typename std::vector<T>::iterator it = greater.begin(); it != greater.end(); ++it)
            arr.push_back(*it);
    }
};
