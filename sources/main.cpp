#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>

#include "Comparator.hpp"
#include "BinaryInsertionSort.hpp"
#include "ShellSort.hpp"
#include "KnuthShellSort.hpp"
#include "NaturalMergeSort.hpp"

#include "BinarySearchTree.hpp"
#include "RedBlackTree.hpp"

using namespace std;

template <typename T, typename F, class Comparator>
void BenchmarkAlgorithm(ofstream &, vector<T>, F, Comparator, const string &, size_t);
template <typename T>
void BenchmarkBST(ofstream &, vector<T> &);
template <typename T>
void BenchmarkRBT(ofstream &, vector<T> &);

int main(int argc, char **argv)
{
    typedef int DT;

    string origin_data = "../../../data/not_sorted/";
    string sorted_data = "../../../data/sorted/";

    ifstream itestnums(origin_data + "test_numbers.txt");
    vector<DT> vtestnums{istream_iterator<DT>{itestnums}, {}};
    ofstream otestnums(sorted_data + "test_numbers.txt");

    ofstream of15k(sorted_data + "15k.txt");
    ofstream of15kA(sorted_data + "15kA.txt");
    ofstream of15kD(sorted_data + "15kD.txt");
    vector<DT> v15k(vtestnums.begin(), vtestnums.begin() + 15000);
    vector<DT> v15kA(v15k);
    sort(v15kA.begin(), v15kA.end());
    vector<DT> v15kD(v15kA);
    reverse(v15kD.begin(), v15kD.end());

    ofstream of40k(sorted_data + "40k.txt");
    ofstream of40kA(sorted_data + "40kA.txt");
    ofstream of40kD(sorted_data + "40kD.txt");
    vector<DT> v40k(vtestnums.begin(), vtestnums.begin() + 40000);
    vector<DT> v40kA(v40k);
    sort(v40kA.begin(), v40kA.end());
    vector<DT> v40kD(v40kA);
    reverse(v40kD.begin(), v40kD.end());

    ofstream of80k(sorted_data + "80k.txt");
    ofstream of80kA(sorted_data + "80kA.txt");
    ofstream of80kD(sorted_data + "80kD.txt");
    vector<DT> v80k(vtestnums.begin(), vtestnums.begin() + 80000);
    vector<DT> v80kA(v80k);
    sort(v80kA.begin(), v80kA.end());
    vector<DT> v80kD(v80kA);
    reverse(v80kD.begin(), v80kD.end());

    ofstream of150k(sorted_data + "150k.txt");
    ofstream of150kA(sorted_data + "150kA.txt");
    ofstream of150kD(sorted_data + "150kD.txt");
    vector<DT> v150k(vtestnums.begin(), vtestnums.begin() + 150000);
    vector<DT> v150kA(v150k);
    sort(v150kA.begin(), v150kA.end());
    vector<DT> v150kD(v150kA);
    reverse(v150kD.begin(), v150kD.end());

    enum Sorts
    {
        BinaryInsertion = 1,
        NaturalMerge,
        Shell3,
        Shell2,
        BST,
        RBT
    };
    enum Sizes
    {
        n15k = 1,
        n40k,
        n80k,
        n150k
    };

    int N, algorithm;
    cout << "Выберите алгоритм\n";
    cout << "1. Бинарные вставки\n";
    cout << "2. Естественные слияния\n";
    cout << "3. Шелл-Кнут (H(k-1) = 3H(k+1))\n";
    cout << "4. Шелл-Кнут (H(k-1) = 2H(k+1))\n";
    cout << "5. Бинарное Дерево Поиска\n";
    cout << "6. Красно-Черное дерево\n";
    cin >> algorithm;

    if (algorithm != 5 && algorithm != 6)
    {
        cout << "Выберите длину массива\n";
        cout << "1. 15k\n";
        cout << "2. 40k\n";
        cout << "3. 80k\n";
        cout << "4. 150k\n";
        cin >> N;
    }

    ofstream *of, *ofA, *ofD;
    vector<DT> *v, *vA, *vD;
    switch (N)
    {
    case Sizes::n15k:
        of = &of15k;
        ofA = &of15kD;
        ofD = &of15kA;
        v = &v15k;
        vA = &v15kA;
        vD = &v15kD;
        break;

    case Sizes::n40k:
        of = &of40k;
        ofA = &of40kA;
        ofD = &of40kD;
        v = &v40k;
        vA = &v40kA;
        vD = &v40kD;
        break;

    case Sizes::n80k:
        of = &of80k;
        ofA = &of80kA;
        ofD = &of80kD;
        v = &v80k;
        vA = &v80kA;
        vD = &v80kD;
        break;

    case Sizes::n150k:
        of = &of150k;
        ofA = &of150kA;
        ofD = &of150kD;
        v = &v150k;
        vA = &v150kA;
        vD = &v150kD;
        break;

    default:
        break;
    }
    size_t additional_mem;
    switch (algorithm)
    {
    // Сортируем последовательности по убыванию. исходные последовательности могут быть неупорядоченны, по возрастанию или по убыванию
    case Sorts::BinaryInsertion: // Доп память sizeof(DT) + sizeof(size_t) * 4
        additional_mem = sizeof(DT) + sizeof(size_t) * 5;
        BenchmarkAlgorithm(*of, *v, bin_insertion_sort<DT, G<DT>>, G<DT>(), "Бинартыми вставками. Неупорядоченный", additional_mem);
        BenchmarkAlgorithm(*ofA, *vA, bin_insertion_sort<DT, G<DT>>, G<DT>(), "Бинарными вставками. По возрастанию", additional_mem);
        BenchmarkAlgorithm(*ofD, *vD, bin_insertion_sort<DT, G<DT>>, G<DT>(), "Бинарными вставками. По убыванию", additional_mem);
        break;

    case Sorts::NaturalMerge: // Доп память O(N)
        additional_mem = sizeof(DT) * vtestnums.size() + sizeof(size_t);
        BenchmarkAlgorithm(*of, *v, natural_merge_sort<DT, GE<DT>>, GE<DT>(), "Естественные слияния. Неупорядоченный", additional_mem);
        BenchmarkAlgorithm(*ofA, *vA, natural_merge_sort<DT, GE<DT>>, GE<DT>(), "Естественные слияния. По возрастанию", additional_mem);
        BenchmarkAlgorithm(*ofD, *vD, natural_merge_sort<DT, GE<DT>>, GE<DT>(), "Естественные слияния. По убыванию", additional_mem);
        break;

    case Sorts::Shell3: // Доп память  sizeof(DT) + sizeof(size_t) * 5
        additional_mem = sizeof(DT) + sizeof(size_t) * 5;
        BenchmarkAlgorithm(*of, *v, knuth_shell_sort<DT, G<DT>>, G<DT>(), "Шелл-Кнут (3). Неупорядоченный", additional_mem);
        BenchmarkAlgorithm(*ofA, *vA, knuth_shell_sort<DT, G<DT>>, G<DT>(), "Шелл-Кнут (3). По возрастанию", additional_mem);
        BenchmarkAlgorithm(*ofD, *vD, knuth_shell_sort<DT, G<DT>>, G<DT>(), "Шелл-Кнут (3). По убыванию", additional_mem);
        break;

    case Sorts::Shell2: // Доп память sizeof(DT) + sizeof(size_t) * 5
        additional_mem = sizeof(DT) + sizeof(size_t) * 5;
        BenchmarkAlgorithm(*of, *v, knuth_shell_sort<DT, G<DT>, 2>, G<DT>(), "Шелл-Кнут (2). Неупорядоченный", additional_mem);
        BenchmarkAlgorithm(*ofA, *vA, knuth_shell_sort<DT, G<DT>, 2>, G<DT>(), "Шелл-Кнут (2). По возрастанию", additional_mem);
        BenchmarkAlgorithm(*ofD, *vD, knuth_shell_sort<DT, G<DT>, 2>, G<DT>(), "Шелл-Кнут (2). По убыванию", additional_mem);
        break;

    case Sorts::BST:
        BenchmarkBST(otestnums, vtestnums);
        break;

    case Sorts::RBT:
        BenchmarkRBT(otestnums, vtestnums);
        break;
    }

    exit(EXIT_SUCCESS);
}

template <typename T, typename F, class Comparator>
void BenchmarkAlgorithm(ofstream &of, vector<T> v, F sort, Comparator cmp,  const string &comment, size_t additional_mem)
{
    auto t1 = chrono::high_resolution_clock::now();
    sort(v, cmp);
    auto sorted = v;
    auto t2 = chrono::high_resolution_clock::now();
    auto ms_int = chrono::duration_cast<chrono::milliseconds>(t2 - t1);

    stringstream ss;
    ss << ms_int.count() << "ms";
    string duration = {ss.str()};
    ss.str(string());

    size_t width = 24;

    ss << left << string(width * 2 + 3, '_') << "\n";
    ss << left << setw(width / 2) << "|" << comment << "\n";
    ss << left << string(width * 2 + 3, '-') << "\n";

    ss << left << setw(width) << "| Элементов             " << setfill(' ') << "| " << setw(width) << v.size() << "|\n";
    ss << left << setw(width) << "| Время работы          " << setfill(' ') << "| " << setw(width) << duration << "|\n";
    ss << left << setw(width) << "| Доп. памяти           " << setfill(' ') << "| " << setw(width) << additional_mem << "|\n";
    ss << left << setw(width) << "| Тип сравнения         " << setfill(' ') << "| " << setw(width) << Comparator::type << "|\n";
    ss << left << setw(width) << "| К-во сравнений        " << setfill(' ') << "| " << setw(width) << Comparator::amount_of_comparisons << "|\n";
    ss << left << string(width * 2 + 3, '-') << "\n";
    ss << "\n";

    cout << ss.str();

    ss << "Отсортированный массив:\n\n";
    for (const auto item : sorted)
    {
        ss << item << '\n';
    }

    of << ss.str();
    of.close();

    Comparator::amount_of_comparisons = 0;
}

template <typename T>
void BenchmarkBST(ofstream &of, vector<T> &v)
{
    std::random_device seeder;
    std::ranlux48 gen(seeder());
    std::uniform_int_distribution<int> rand_search_keys(10000000, 100000000);
    std::uniform_int_distribution<int> rand_ix(0, 199999);

    vector<T> keys;
    for (size_t i = 0; i < 50; ++i)
        keys.push_back(v[rand_ix(gen)]);
    for (size_t i = 0; i < 50; ++i)
        keys.push_back(rand_search_keys(gen));
    shuffle(keys.begin(), keys.end(), gen);

    StatementCounter::amount_of_calls = 0;
    auto t1 = chrono::high_resolution_clock::now();

    BinarySearchTree<T> tree;
    for (const auto i : v)
        tree.insert(i);

    auto t2 = chrono::high_resolution_clock::now();

    vector<T> sorted;
    ToSortedVector(sorted, tree.root);
    auto t3 = chrono::high_resolution_clock::now();

    double search_comps = 0;
    for (const auto key : keys)
    {
        if (tree.find(key) == BinarySearchTree<T>::nullnode)
            cout << "Ключ " << key << " не найден. Сравнений: " << __.obj_amount_of_calls << '\n';
        else
            cout << "Ключ " << key << " найден. Сравнений: " << __.obj_amount_of_calls << '\n';

        search_comps += __.obj_amount_of_calls;
        __.obj_amount_of_calls = 0;
    }
    auto t4 = chrono::high_resolution_clock::now();

    auto buildtime = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
    auto traverstime = chrono::duration_cast<chrono::milliseconds>(t3 - t2);
    auto searchtime = chrono::duration_cast<chrono::milliseconds>(t4 - t3);
    auto fulltime = chrono::duration_cast<chrono::milliseconds>(t4 - t1);

    stringstream ss;
    ss << buildtime.count() << "ms";
    string buildtime_str = {ss.str()};
    ss.str(string());

    ss << traverstime.count() << "ms";
    string traverstime_str = {ss.str()};
    ss.str(string());

    ss << searchtime.count() << "ms";
    string searchtime_str = {ss.str()};
    ss.str(string());

    ss << fulltime.count() << "ms";
    string fulltime_str = {ss.str()};
    ss.str(string());

    ss << Node<T>::counter << "bytes";
    string mem = {ss.str()};
    ss.str(string());

    size_t width = 24;

    ss << left << string(width * 2 + 4, '_') << "\n";
    ss << setw(width / 2) << "|" << setw(width + width / 2 + 3) << "Бинарное дерево поиска" << "\n";
    ss << left << string(width * 2 + 4, '-') << "\n";

    ss << left << setw(width) << "| Элементов              " << setfill(' ') << "| " << setw(width) << v.size() << "|\n";
    ss << left << setw(width) << "| Построение дерева      " << setfill(' ') << "| " << setw(width) << buildtime_str << "|\n";
    ss << left << setw(width) << "| Обход дерева           " << setfill(' ') << "| " << setw(width) << traverstime_str << "|\n";
    ss << left << setw(width) << "| Время поиска           " << setfill(' ') << "| " << setw(width) << searchtime_str << "|\n";
    ss << left << setw(width) << "| Общее время            " << setfill(' ') << "| " << setw(width) << fulltime_str << "|\n";
    ss << left << setw(width) << "| Всего сравнений        " << setfill(' ') << "| " << setw(width) << StatementCounter::amount_of_calls << "|\n";
    ss << left << setw(width) << "| Сравнений в поиске     " << setfill(' ') << "| " << setw(width) << search_comps << "|\n";
    ss << left << setw(width) << "| Ср. сравнений в поиске " << setfill(' ') << "| " << setw(width) << search_comps / 100.0 << "|\n";
    ss << left << setw(width) << "| Память                 " << setfill(' ') << "| " << setw(width) << mem << "|\n";
    ss << left << string(width * 2 + 4, '-') << "\n";
    ss << "\n";

    cout << ss.str();

    ss << "Sorted array:\n\n";
    for (const auto item : sorted)
    {
        ss << item << '\n';
    }

    of << ss.str();
    of.close();
    StatementCounter::amount_of_calls = 0;
}

template <typename T>
void BenchmarkRBT(ofstream &of, vector<T> &v)
{
    std::random_device seeder;
    std::ranlux48 gen(seeder());
    std::uniform_int_distribution<int> rand_search_keys(10000000, 100000000);
    std::uniform_int_distribution<int> rand_ix(0, 199999);

    vector<T> keys;
    for (size_t i = 0; i < 50; ++i)
        keys.push_back(v[rand_ix(gen)]);
    for (size_t i = 0; i < 50; ++i)
        keys.push_back(rand_search_keys(gen));
    shuffle(keys.begin(), keys.end(), gen);

    StatementCounter::amount_of_calls = 0;
    auto t1 = chrono::high_resolution_clock::now();

    RedBlackTree<T> tree;
    for (const auto i : v)
        tree.insert(i);

    auto t2 = chrono::high_resolution_clock::now();

    vector<T> sorted;
    ToSortedVector(sorted, tree.root);

    auto t3 = chrono::high_resolution_clock::now();

    double search_comps = 0;
    for (size_t i = 0; i < 100; ++i)
    {
        auto key = keys[i];
        if (tree.find(key) == RedBlackTree<T>::nullnode)
            cout << "Ключ " << key << " не найден. Сравнений: " << __.obj_amount_of_calls << '\n';
        else
            cout << "Ключ " << key << " найден. Сравнений: " << __.obj_amount_of_calls << '\n';

        search_comps += __.obj_amount_of_calls;
        __.obj_amount_of_calls = 0;
    }
    auto t4 = chrono::high_resolution_clock::now();

    auto buildtime = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
    auto traverstime = chrono::duration_cast<chrono::milliseconds>(t3 - t2);
    auto searchtime = chrono::duration_cast<chrono::milliseconds>(t4 - t3);
    auto fulltime = chrono::duration_cast<chrono::milliseconds>(t4 - t1);

    stringstream ss;
    ss << buildtime.count() << "ms";
    string buildtime_str = {ss.str()};
    ss.str(string());

    ss << traverstime.count() << "ms";
    string traverstime_str = {ss.str()};
    ss.str(string());

    ss << searchtime.count() << "ms";
    string searchtime_str = {ss.str()};
    ss.str(string());

    ss << fulltime.count() << "ms";
    string fulltime_str = {ss.str()};
    ss.str(string());

    ss << RBNode<T>::counter << "bytes";
    string mem = {ss.str()};
    ss.str(string());

    size_t width = 28;

    ss << left << string(width * 2 + 3, '_') << "\n";
    ss << setw(width / 2) << "|" << setw(width + width / 2 + 2) << "Красно-Черное дерево"
       << "\n";
    ss << left << string(width * 2 + 3, '-') << "\n";

    ss << left << setw(width) << "| Элементов                 " << setfill(' ') << "| " << setw(width) << v.size() << "|\n";
    ss << left << setw(width) << "| Построение дерева         " << setfill(' ') << "| " << setw(width) << buildtime_str << "|\n";
    ss << left << setw(width) << "| Время обхода              " << setfill(' ') << "| " << setw(width) << traverstime_str << "|\n";
    ss << left << setw(width) << "| Время поиска              " << setfill(' ') << "| " << setw(width) << traverstime_str << "|\n";
    ss << left << setw(width) << "| Общее время               " << setfill(' ') << "| " << setw(width) << fulltime_str << "|\n";
    ss << left << setw(width) << "| Всего сравнений           " << setfill(' ') << "| " << setw(width) << StatementCounter::amount_of_calls << "|\n";
    ss << left << setw(width) << "| Сравнений в поиске        " << setfill(' ') << "| " << setw(width) << search_comps << "|\n";
    ss << left << setw(width) << "| Ср. сравнений в поиске    " << setfill(' ') << "| " << setw(width) << search_comps / 100.0 << "|\n";
    ss << left << setw(width) << "| Память                    " << setfill(' ') << "| " << setw(width) << mem << "|\n";
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
    StatementCounter::amount_of_calls = 0;
}
