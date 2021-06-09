#include <vector>
#include <list>

/*
    Best: O(N log N)
    AVG: O(N log N)?
    Worst: O(N^2)
*/

/**
 * @brief Natural Merge sort algorithm by Von Neuman. Mergeing the longest two subsequences.
 * 
 * @tparam T Data type
 * @tparam Comparator Function that compares two T elements (Less or equal / Greater or equal !). Returns true or false
 * @param arr Origin collection
 * @param cmp Comparator function
 * @return std::vector<T> Sorted collection
 */
template <typename T, class Comparator>
std::vector<T> natural_merge_sort(std::vector<T> arr, Comparator cmp)
{
    if (arr.size() < 2)
        return arr;

    std::list<T> tape1, tape2;
    std::list<T> *cur_tape;

    while (true)
    {
        tape1.clear();
        tape2.clear();
        cur_tape = &tape1;
        for (size_t i = 0; i < arr.size(); ++i)
        {
            if (i == arr.size() - 1)
                cur_tape->push_back(arr[i]);

            else if (!cmp(arr[i], arr[i + 1]))
            {
                cur_tape->push_back(arr[i]);
                cur_tape = cur_tape == &tape1 ? &tape2 : &tape1;
            }
            else
                cur_tape->push_back(arr[i]);
        }
        arr.clear();

        // Sorted if one of tapes is empty
        if (tape1.empty())
        {
            arr = std::vector<T>{tape2.begin(), tape2.end()};
            break;
        }
        else if (tape2.empty())
        {
            arr = std::vector<T>{tape1.begin(), tape1.end()};
            break;
        }

        while (!tape1.empty() && !tape2.empty())
        {
            if (cmp(tape1.front(), tape2.front()))
            {
                arr.push_back(tape1.front());
                tape1.pop_front();
            }
            else
            {
                arr.push_back(tape2.front());
                tape2.pop_front();
            }
        }
        if (tape1.size() == 0 && tape2.size() != 0)
            arr.insert(arr.end(), tape2.begin(), tape2.end());
        else if (tape2.size() == 0 && tape1.size() != 0)
            arr.insert(arr.end(), tape1.begin(), tape1.end());
    }
    return arr;
}
