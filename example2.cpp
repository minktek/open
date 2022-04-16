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
#include "example2.h"

using std::vector;
using std::cout;
using std::endl;
using Example::Triplet;

// now that we have non-dupliate i,j find k such that k = 0 - i - j
static bool Find_k(const int32_t data[], size_t data_size, int32_t i, int32_t j)
{
    for (uint32_t index = 0; index < data_size; ++index)
    {
        if ((j == data[index]) || (i == data[index]))
            continue;

        // first one wins - other k's with the same value get dropped anyway
        if (i + j + data[index] == 0)
            return (true);
    }
    return (false);
}

// add a triplet to a vector if and only if it is not already present
static void StoreNonDupValues(vector<Triplet>& values, int32_t i, int32_t j)
{
    Triplet new_triple;
    int32_t k = 0 - (i + j);

    // create a sorted triplet
    if (i > j)
    {
         if (k > i)
             new_triple.Init(j, i, k);
         else if (k > j)
             new_triple.Init(j, k, i);
         else
             new_triple.Init(k, j, i);
    }
    // rest are all cases where i < j
    else if (k < i)
    {
         new_triple.Init(k, i, j);
    }
    else if (k > j)
    {
        new_triple.Init(i, j, k);
    }
    else
    {
        new_triple.Init(i, k, j);
    }
    
    // now make sure it isn't already there
    for (const Triplet& t : values)
        if (new_triple == t)
            return;

    // not already present so add it
    values.push_back(new_triple);
}

int main(int /*argc*/, char* /*argv*/[])
{
    constexpr int32_t numbers[] = { 1, -18, -17, 1, 2, -17, 4, -18, 8, -10, 10 };
    std::vector<Triplet> triplets;

    // deduplicate the i's and j's and find k based on the request
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

    // show everything that was found
    if (triplets.size() == 0)
        cout << "Nothing found" << endl;
    else
        for (const Triplet& t : triplets)
            t.Print();

    return (0);
}

// Sample data:
//     single answer: "1,-18,-17,2,4,8,10"
//     multiple different answers: "-12,14,2,1,1,1,1,1,1,1,1,-1,0"
//     another example: 1,2,3,4,5,6,7,8,9,10
