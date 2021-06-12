#include <vector>

/*
    Best: O(N^2)
    AVG: O(N^2)
    Worst: O(N^2)
*/

template <typename T, class Comparator>
void selection_sort(std::vector<T> &arr, Comparator cmp)
{
    std::vector<T> result;
    typename std::vector<T>::iterator extremum_it;

    while (arr.size() > 0)
    {
        extremum_it = arr.begin();
        for (typename std::vector<T>::iterator it = arr.begin(); it != arr.end(); ++it)
        {
            if (cmp(*it, *extremum_it))
                extremum_it = it;
        }
        result.push_back(*extremum_it);
        arr.erase(extremum_it);
    }
    arr = result;
};
