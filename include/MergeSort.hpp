#include <vector>

/*
    Best: O(N log N)
    AVG: O(N log N)?
    Worst: O(N^2)
*/
template <typename T, class Comparator>
std::vector<T> merge(std::vector<T> left, std::vector<T> right);

/**
 * @brief Merge sort algorithm. Sorting half of colection recursively.
 * 
 * @tparam T Data type
 * @tparam Comparator Function that compares two T elements. Returns true or false
 * @param arr Origin collection
 * @param cmp Comparator function
 * @return std::vector<T> Sorted collection
 */
template <typename T, class Comparator>
std::vector<T> merge_sort(std::vector<T> &arr, Comparator cmp)
{
    if (arr.size() < 2)
        return;

    size_t mid = arr.size() / 2;

    std::vector<T> left, right;

    for (size_t i = 0; i < mid; ++i)
        left.push_back(arr[i]);
    for (size_t i = mid; i < arr.size(); ++i)
        right.push_back(arr[i]);

    left = merge_sort(left, cmp);
    right = merge_sort(right, cmp);

    arr = merge(left, right, cmp);
}

/**
 * @brief Merges right collectoin to the end of the left collection.
 * 
 * @tparam T Data type
 * @param left 
 * @param right 
 * @return std::vector<T> Merged collectoin
 */
template <typename T, class Comparator>
std::vector<T> merge(std::vector<T> left, std::vector<T> right, Comparator cmp)
{
    size_t l_size = left.size(), r_size = right.size();
    size_t l_ix = 0;
    size_t r_ix = 0;

    std::vector<T> arr;

    while (l_ix < l_size && r_ix < r_size)
        if (cmp(left[l_ix], right[r_ix]))
            arr.push_back(left[l_ix++]);

        else
            arr.push_back(right[r_ix++]);

    while (l_ix < l_size)
        arr.push_back(left[l_ix++]);

    while (r_ix < r_size)
        arr.push_back(right[r_ix++]);

    return arr;
}
