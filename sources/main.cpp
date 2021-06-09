#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <chrono>
#include <iomanip>

#include "Comparator.hpp"
#include "QuickSort.hpp"
#include "SelectionSort.hpp"
#include "BubleSort.hpp"
#include "ShakerSort.hpp"
#include "CombSort.hpp"
#include "InsertionSort.hpp"
#include "BinaryInsertionSort.hpp"
#include "ShellSort.hpp"
#include "KnuthShellSort.hpp"
#include "MergeSort.hpp"
#include "NaturalMergeSort.hpp"

using namespace std;

template <typename T, typename F, class Comparator>
void BenchmarkAlgorithm(ofstream &of, const string &, vector<T>, F, Comparator);

int main(int argc, char **argv)
{
    typedef int DT;

    string origin_data = "../../../data/not_sorted/";
    string sorted_data = "../../../data/sorted/";

    ifstream if15k(origin_data + "15k.txt");
    ofstream of15k(sorted_data + "15k.txt");
    vector<DT> v15k{istream_iterator<DT>{if15k}, {}};

    ifstream if40k(origin_data + "40k.txt");
    ofstream of40k(sorted_data + "40k.txt");
    vector<DT> v40k{istream_iterator<DT>{if40k}, {}};

    ifstream f80k(origin_data + "80k.txt");
    ofstream of80k(sorted_data + "80k.txt");
    vector<DT> v80k{istream_iterator<DT>{f80k}, {}};

    ifstream f150k(origin_data + "150k.txt");
    ofstream of150k(sorted_data + "150k.txt");
    vector<DT> v150k{istream_iterator<DT>{f150k}, {}};

    // BenchmarkAlgorithm(of15k, "Selection sort", v15k, selection_sort<DT, G<DT>>, G<DT>());
    // BenchmarkAlgorithm(of15k, "Buble sort", v15k, buble_sort<DT, G<DT>>, G<DT>());
    // BenchmarkAlgorithm(of15k, "Comb sort", v15k, comb_sort<DT, G<DT>>, G<DT>());
    // // // BenchmarkAlgorithm(of15k, "Shaker sort", v15k, shaker_sort<DT, G<DT>>, G<DT>()); // BUG: double free or corrupt
    // BenchmarkAlgorithm(of15k, "Shaker sort", v15k, shaker_sort<DT, L<DT>>, L<DT>());
    // BenchmarkAlgorithm(of15k, "Insertion sort", v15k, insertion_sort<DT, G<DT>>, G<DT>());
    // BenchmarkAlgorithm(of15k, "Binary insertion sort", v15k, bin_insertion_sort<DT, G<DT>>, G<DT>());
    // BenchmarkAlgorithm(of15k, "Merge sort", v15k, merge_sort<DT, L<DT>>, L<DT>());
    // BenchmarkAlgorithm(of15k, "Natural Merge sort", v15k, natural_merge_sort<DT, LE<DT>>, LE<DT>()); // It must accept GE or LE comparators, not G or L
    // BenchmarkAlgorithm(of15k, "Shell sort", v15k, shell_sort<DT, G<DT>>, G<DT>());
    // BenchmarkAlgorithm(of15k, "Knuth's shell sort", v15k, knuth_shell_sort<DT, L<DT>>, L<DT>());
    // BenchmarkAlgorithm(of15k, "Quick sort", v15k, quick_sort<DT, G<DT>>, G<DT>());

    enum Sorts
    {
        Selection = 1,
        BinaryInsertion,
        NaturalMerge,
        Shell3,
        Shell2
    };
    enum Sizes
    {
        n15k = 1,
        n40k,
        n80k,
        n150k
    };

    int N, algorithm;
    cout << "Choose sorting algorithm\n";
    cout << "1. Selection sort\n";
    cout << "2. Binary insertion sort\n";
    cout << "3. Natural merge sort\n";
    cout << "4. Shell sort, Knuth's series (H(k-1) = 3H(k+1))\n";
    cout << "5. Shell sort, Knuth's series (H(k-1) = 2H(k+1))\n";
    cin >> algorithm;

    cout << "Choose lenght of data\n";
    cout << "1. 15k\n";
    cout << "2. 40k\n";
    cout << "3. 80k\n";
    cout << "4. 150k\n";
    cin >> N;

    ofstream *of;
    vector<DT> *v;
    switch (N)
    {
    case Sizes::n15k:
        of = &of15k;
        v = &v15k;
        break;

    case Sizes::n40k:
        of = &of40k;
        v = &v40k;
        break;

    case Sizes::n80k:
        of = &of80k;
        v = &v80k;
        break;

    case Sizes::n150k:
        of = &of150k;
        v = &v150k;
        break;

    default:
        break;
    }
    switch (algorithm)
    {
    case Sorts::Selection:
        BenchmarkAlgorithm(*of, "Selection sort", *v, selection_sort<DT, G<DT>>, G<DT>());
        break;

    case Sorts::BinaryInsertion:
        BenchmarkAlgorithm(*of, "Binary insertion sort", *v, bin_insertion_sort<DT, G<DT>>, G<DT>());
        break;

    case Sorts::NaturalMerge:
        BenchmarkAlgorithm(*of, "Natural merge sort", *v, natural_merge_sort<DT, GE<DT>>, GE<DT>());
        break;

    case Sorts::Shell3:
        BenchmarkAlgorithm(*of, "Shell sort, Knuth's series (3)", *v, knuth_shell_sort<DT, G<DT>>, G<DT>());
        break;

    case Sorts::Shell2:
        BenchmarkAlgorithm(*of, "Shell sort, Knuth's series (2)", *v, knuth_shell_sort<DT, G<DT>, 2>, G<DT>());
        break;
    }

    exit(EXIT_SUCCESS);
}

template <typename T, typename F, class Comparator>
void BenchmarkAlgorithm(ofstream &of, const string &comment, vector<T> v, F sort, Comparator cmp)
{
    auto t1 = chrono::high_resolution_clock::now();
    auto sorted = sort(v, cmp);
    auto t2 = chrono::high_resolution_clock::now();
    auto ms_int = chrono::duration_cast<chrono::milliseconds>(t2 - t1);

    stringstream ss;
    ss << ms_int.count() << "ms";
    string duration = {ss.str()};
    ss.str(string());

    size_t width = 24;

    ss << left << string(width * 2 + 3, '_') << "\n";
    ss << setw(width / 2) << "|" << setw(width + width / 2 + 2) << comment << "|\n";
    ss << left << string(width * 2 + 3, '-') << "\n";

    ss << left << setw(width) << "| Elements       " << setfill(' ') << "| " << setw(width) << v.size() << "|\n";
    ss << left << setw(width) << "| Execution time " << setfill(' ') << "| " << setw(width) << duration << "|\n";
    ss << left << setw(width) << "| Comparator type" << setfill(' ') << "| " << setw(width) << Comparator::type << "|\n";
    ss << left << setw(width) << "| Comparisons    " << setfill(' ') << "| " << setw(width) << Comparator::amount_of_comparisons << "|\n";
    ss << left << string(width * 2 + 3, '-') << "\n";
    ss << "\n";

    cout << ss.str();

    ss << "Sorted array:\n\n";
    for (const auto item : sorted)
    {
        ss << item << '\n';
    }

    of << ss.str();
    of.close();

    Comparator::amount_of_comparisons = 0;
}