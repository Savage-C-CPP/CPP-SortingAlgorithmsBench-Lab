#include <vector>
using namespace std;

template <typename T, class Comparator>
void merge_vectors(vector<T> &a, vector<T> &b, size_t left, size_t middle, size_t right, Comparator cmp)
{
    int l = left;
    int r = middle + 1;

    for (int i = left; i <= right; i++)
    {
        if (r > right || (l <= middle && cmp(a[l], a[r])))
        {
            b[i] = a[l++];
        }
        else if (l > middle || (r <= right && cmp(a[r], a[l])))
        {
            b[i] = a[r++];
        }
    }

    for (int i = left; i <= right; i++)
    {
        a[i] = b[i];
    }
}
template <typename T, class Comparator>
void natural_merge_sort(vector<T> &a, Comparator cmp)
{
    vector<T> b(a.size(), 0);
    int left = 0;
    int right = a.size() - 1;
    bool sorted = false;
    int l = 0;
    int r = right;

    do
    {
        sorted = true;
        left = 0;

        while (left < right)
        {
            l = left;
            while (l < right && cmp(a[l], a[l + 1]))
                l++;

            r = l + 1;
            while (r == right - 1 || r < right && cmp(a[r], a[r + 1]))
                r++;

            if (r <= right)
            {
                merge_vectors(a, b, left, l, r, cmp);
                sorted = false;
            }
            left = r + 1;
        }
    } while (!sorted);
}
