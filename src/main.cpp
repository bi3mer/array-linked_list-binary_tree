#include <algorithm>
#include <chrono>
#include <fstream>
#include <functional>
#include <numeric>
#include <print>
#include <random>
#include <vector>
#include "array.hpp"
#include "bst.hpp"
#include "doubly_linked_list.hpp"
#include "linear_interface.hpp"
#include "linked_list.hpp"
#include "linked_list_tail.hpp"
#include "sorted_array.hpp"
#include "sorted_interface.hpp"

using Clock = std::chrono::steady_clock;
using Ms = std::chrono::duration<double, std::milli>;
using Fn = std::function<double()>;

static constexpr int TRIALS = 7;

static double bench(auto fn)
{
    auto start = Clock::now();
    fn();
    return std::chrono::duration_cast<Ms>(Clock::now() - start).count();
}

static double median(std::vector<double> v)
{
    std::sort(v.begin(), v.end());
    return v[v.size() / 2];
}

static void populate(LinearInterface& ds, const std::vector<int>& vals)
{
    for (int v : vals)
    {
        ds.insert(v);
    }
}

static void populate(SortedInterface& ds, const std::vector<int>& vals)
{
    for (int v : vals)
    {
        ds.insert(v);
    }
}

// Runs each fn TRIALS times in shuffled order, returns median per fn.
static std::vector<double> run_trials(std::mt19937& rng, std::vector<Fn> fns)
{
    int k = static_cast<int>(fns.size());
    std::vector<std::vector<double>> times(k, std::vector<double>(TRIALS));
    std::vector<int> order(k);
    std::iota(order.begin(), order.end(), 0);
    for (int t = 0; t < TRIALS; ++t)
    {
        std::shuffle(order.begin(), order.end(), rng);
        for (int idx : order)
        {
            times[idx][t] = fns[idx]();
        }
    }
    std::vector<double> result(k);
    for (int i = 0; i < k; ++i)
    {
        result[i] = median(times[i]);
    }
    return result;
}

int main()
{
    std::mt19937 rng(std::random_device{}());

    std::ofstream csv("results.csv");
    csv << "N,operation,Array,SortedArray,LinkedList,LinkedListTail,DoublyLinkedList,BST\n";

    for (int n : {250, 500, 1000, 2000, 4000, 8000, 16000})
    {
        std::print("N={}...\n", n);

        std::uniform_int_distribution<int> val_dist(0, n * 2);
        std::vector<int> values(n);
        for (int& v : values)
        {
            v = val_dist(rng);
        }

        std::vector<std::size_t> shrink_indices(n);
        for (int i = 0; i < n; ++i)
        {
            shrink_indices[i] = static_cast<std::size_t>(
                std::uniform_int_distribution<int>(0, n - i - 1)(rng));
        }

        // insert_front: Array, LL, LLT, DLL
        {
            auto r = run_trials(rng, {
                [&]
                {
                    Array arr(n);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            arr.insert_front(values[i]);
                        }
                    });
                },
                [&]
                {
                    LinkedList ll;
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            ll.insert_front(values[i]);
                        }
                    });
                },
                [&]
                {
                    LinkedListTail llt;
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            llt.insert_front(values[i]);
                        }
                    });
                },
                [&]
                {
                    DoublyLinkedList dll;
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            dll.insert_front(values[i]);
                        }
                    });
                },
            });
            csv << n << ",insert_front,"
                << r[0] << ",," << r[1] << "," << r[2] << "," << r[3] << ",\n";
        }

        // insert_back: Array, LL, LLT, DLL
        {
            auto r = run_trials(rng, {
                [&]
                {
                    Array arr(n);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            arr.insert_back(values[i]);
                        }
                    });
                },
                [&]
                {
                    LinkedList ll;
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            ll.insert_back(values[i]);
                        }
                    });
                },
                [&]
                {
                    LinkedListTail llt;
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            llt.insert_back(values[i]);
                        }
                    });
                },
                [&]
                {
                    DoublyLinkedList dll;
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            dll.insert_back(values[i]);
                        }
                    });
                },
            });
            csv << n << ",insert_back,"
                << r[0] << ",," << r[1] << "," << r[2] << "," << r[3] << ",\n";
        }

        // insert_sorted: all
        {
            auto r = run_trials(rng, {
                [&]
                {
                    Array arr(n);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            arr.insert_sorted(values[i]);
                        }
                    });
                },
                [&]
                {
                    SortedArray sa(n);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            sa.insert(values[i]);
                        }
                    });
                },
                [&]
                {
                    LinkedList ll;
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            ll.insert_sorted(values[i]);
                        }
                    });
                },
                [&]
                {
                    LinkedListTail llt;
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            llt.insert_sorted(values[i]);
                        }
                    });
                },
                [&]
                {
                    DoublyLinkedList dll;
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            dll.insert_sorted(values[i]);
                        }
                    });
                },
                [&]
                {
                    BST bst;
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            bst.insert(values[i]);
                        }
                    });
                },
            });
            csv << n << ",insert_sorted,"
                << r[0] << "," << r[1] << "," << r[2] << ","
                << r[3] << "," << r[4] << "," << r[5] << "\n";
        }

        // remove_front: Array, LL, LLT, DLL
        {
            auto r = run_trials(rng, {
                [&]
                {
                    Array arr(n);
                    populate(arr, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            arr.remove_front();
                        }
                    });
                },
                [&]
                {
                    LinkedList ll;
                    populate(ll, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            ll.remove_front();
                        }
                    });
                },
                [&]
                {
                    LinkedListTail llt;
                    populate(llt, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            llt.remove_front();
                        }
                    });
                },
                [&]
                {
                    DoublyLinkedList dll;
                    populate(dll, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            dll.remove_front();
                        }
                    });
                },
            });
            csv << n << ",remove_front,"
                << r[0] << ",," << r[1] << "," << r[2] << "," << r[3] << ",\n";
        }

        // remove_back: Array, LL, LLT, DLL
        {
            auto r = run_trials(rng, {
                [&]
                {
                    Array arr(n);
                    populate(arr, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            arr.remove_back();
                        }
                    });
                },
                [&]
                {
                    LinkedList ll;
                    populate(ll, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            ll.remove_back();
                        }
                    });
                },
                [&]
                {
                    LinkedListTail llt;
                    populate(llt, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            llt.remove_back();
                        }
                    });
                },
                [&]
                {
                    DoublyLinkedList dll;
                    populate(dll, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            dll.remove_back();
                        }
                    });
                },
            });
            csv << n << ",remove_back,"
                << r[0] << ",," << r[1] << "," << r[2] << "," << r[3] << ",\n";
        }

        // remove_index: Array, LL, LLT, DLL
        {
            auto r = run_trials(rng, {
                [&]
                {
                    Array arr(n);
                    populate(arr, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            arr.remove_index(shrink_indices[i]);
                        }
                    });
                },
                [&]
                {
                    LinkedList ll;
                    populate(ll, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            ll.remove_index(shrink_indices[i]);
                        }
                    });
                },
                [&]
                {
                    LinkedListTail llt;
                    populate(llt, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            llt.remove_index(shrink_indices[i]);
                        }
                    });
                },
                [&]
                {
                    DoublyLinkedList dll;
                    populate(dll, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            dll.remove_index(shrink_indices[i]);
                        }
                    });
                },
            });
            csv << n << ",remove_index,"
                << r[0] << ",," << r[1] << "," << r[2] << "," << r[3] << ",\n";
        }

        // remove: all
        {
            auto r = run_trials(rng, {
                [&]
                {
                    Array arr(n);
                    populate(arr, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            arr.remove(values[i]);
                        }
                    });
                },
                [&]
                {
                    SortedArray sa(n);
                    populate(sa, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            sa.remove(values[i]);
                        }
                    });
                },
                [&]
                {
                    LinkedList ll;
                    populate(ll, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            ll.remove(values[i]);
                        }
                    });
                },
                [&]
                {
                    LinkedListTail llt;
                    populate(llt, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            llt.remove(values[i]);
                        }
                    });
                },
                [&]
                {
                    DoublyLinkedList dll;
                    populate(dll, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            dll.remove(values[i]);
                        }
                    });
                },
                [&]
                {
                    BST bst;
                    populate(bst, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            bst.remove(values[i]);
                        }
                    });
                },
            });
            csv << n << ",remove,"
                << r[0] << "," << r[1] << "," << r[2] << ","
                << r[3] << "," << r[4] << "," << r[5] << "\n";
        }

        // find: all
        {
            auto r = run_trials(rng, {
                [&]
                {
                    Array arr(n);
                    populate(arr, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            arr.find_element(values[i]);
                        }
                    });
                },
                [&]
                {
                    SortedArray sa(n);
                    populate(sa, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            sa.find_element(values[i]);
                        }
                    });
                },
                [&]
                {
                    LinkedList ll;
                    populate(ll, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            ll.find_element(values[i]);
                        }
                    });
                },
                [&]
                {
                    LinkedListTail llt;
                    populate(llt, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            llt.find_element(values[i]);
                        }
                    });
                },
                [&]
                {
                    DoublyLinkedList dll;
                    populate(dll, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            dll.find_element(values[i]);
                        }
                    });
                },
                [&]
                {
                    BST bst;
                    populate(bst, values);
                    return bench([&]
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            bst.find_element(values[i]);
                        }
                    });
                },
            });
            csv << n << ",find,"
                << r[0] << "," << r[1] << "," << r[2] << ","
                << r[3] << "," << r[4] << "," << r[5] << "\n";
        }
    }

    std::print("results written to results.csv\n");
    return 0;
}
