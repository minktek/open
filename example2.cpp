// compile with: g++ -o ex2 -g -Wall -pedantic -Wextra -std=c++14 example2.cpp
// sample data at the bottom

// Request: Given an integer array nums, return all the triplets 
//          [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, 
//          and nums[i] + nums[j] + nums[k] == 0.

#include <libgen.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <vector>
#include <assert.h>

using std::vector;
using std::cout;
using std::endl;

typedef struct Triplet
{
    int32_t i;
    int32_t j;
    int32_t k;
} Triplet;

static void InitTriple(Triplet& t, int32_t i, int32_t j, int32_t k)
{
    assert(i < j);
    assert(j < k);
    t.i = i;
    t.j = j;
    t.k = k;
}

static bool Find_k(const int32_t data[], size_t data_size, int32_t i, int32_t j)
{
    for (uint32_t index = 0; index < data_size; ++index)
    {
        if ((j == data[index]) || (i == data[index]))
            continue;

        if (i + j + data[index] == 0)
            return (true);
    }
    return (false);
}

static void StoreNonDupValues(vector<Triplet>& values, int32_t i, int32_t j)
{
    Triplet new_triple;
    int32_t k = 0 - (i + j);

    // create a sorted triplet
    if (i > j)
    {
         if (k > i)
             InitTriple(new_triple, j, i, k);
         else if (k > j)
             InitTriple(new_triple, j, k, i);
         else
             InitTriple(new_triple, k, j, i);
    }
    // rest are all cases where i < j
    else if (k < i)
    {
         InitTriple(new_triple, k, i, j);
    }
    else if (k > j)
    {
        InitTriple(new_triple, i, j, k);
    }
    else
    {
        InitTriple(new_triple, i, k, j);
    }
    
    // now make sure it isn't already there
    for (const Triplet& t : values)
        if ((t.i == new_triple.i) && 
            (t.j == new_triple.j) && 
            (t.k == new_triple.k))
            // it already exists
            return;

    // not already present so add it
    values.push_back(new_triple);
}

static void PrintResults(const vector<Triplet>& values)
{
    for (const Triplet& t : values)
    {
        cout << "{ " << t.i << " , " << t.j << " , " << t.k << " }" << endl;
    }
}

int main(int /*argc*/, char* /*argv*/[])
{
    constexpr int32_t numbers[] = { 1, -18, -17, 1, 2, -17, 4, -18, 8, -10, 10 };
    std::vector<Triplet> triplets;

    for (int32_t i : numbers)
    {
        for (int32_t j : numbers)
        {
            if (i != j)
            {
                bool rc;

                rc = Find_k(numbers, sizeof(numbers)/sizeof(numbers[0]), i, j);
                if (rc == true)
                    StoreNonDupValues(triplets, i, j);
            }
        }
    }

    PrintResults(triplets);

    return (0);
}

// Sample data:
//     single answer: "1,-18,-17,2,4,8,10"
//     multiple different answers: "-12,14,2,1,1,1,1,1,1,1,1,-1,0"
//     another example: 1,2,3,4,5,6,7,8,9,10
