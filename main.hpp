#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>

unsigned NW_method( const std::vector<std::vector<unsigned>> &cost
                    , const unsigned row
                    , const unsigned col
                    , const std::vector<unsigned> &offer_given
                    , const std::vector<unsigned> &demand_given)
{
    // Necessary initializations
    std::vector<unsigned> offer;
    std::vector<unsigned> demand;    
    std::copy(demand_given.cbegin(), demand_given.cend(),  std::back_inserter(demand));
    std::copy(offer_given.cbegin(), offer_given.cend(),  std::back_inserter(offer));
    std::vector<unsigned> selected_cost;
    std::vector<unsigned> final_demand;
    unsigned i = 0, j = 0;
   
    while (i < row && j < col) {
        // Take the north-west element first
        selected_cost.push_back(cost[i][j]);
        if (offer[i] == demand[j]) {
            final_demand.push_back(offer[i]);
            // Do not take into consideration columns and rows
            // where offer and demand are depleted
            i++; j++;
        }
        else if (offer[i] > demand[j]) {
            final_demand.push_back(demand[j]);
            offer[i] -= demand[j];
            // Do not take into consideration columns 
            // where demand is depleted
            j++;
        }
        else if (offer[i] < demand[j]) {
            final_demand.push_back(offer[i]);
            demand[j] -= offer[i];
            // Do not take into consideration rows
            // where offer is depleted
            i++;
        }
    }

    return std::inner_product(selected_cost.cbegin(), selected_cost.cend(), final_demand.cbegin(), 0); 
}

// Input: matrix, number od rows and columns
// Output: array where a single element is an element from the given matrix and its position
std::vector<std::tuple<unsigned, unsigned, unsigned>> matrix2array
(const std::vector<std::vector<unsigned>> &matrix
, const unsigned row
, const unsigned col)
{
    std::vector<std::tuple<unsigned, unsigned, unsigned>> array;
    for (unsigned i = 0; i < row; ++i) {
        for (unsigned j = 0; j < col; ++j) {
            array.push_back(std::make_tuple(matrix[i][j], i, j));
        }
    }
    return array;
}

unsigned min_method( const std::vector<std::vector<unsigned>> &cost
                    , const unsigned row
                    , const unsigned col
                    , const std::vector<unsigned> &offer_given
                    , const std::vector<unsigned> &demand_given)
{
    // Necessary initializations
    std::vector<unsigned> offer;
    std::vector<unsigned> demand;    
    std::copy(demand_given.cbegin(), demand_given.cend(),  std::back_inserter(demand));
    std::copy(offer_given.cbegin(), offer_given.cend(),  std::back_inserter(offer));
    std::vector<unsigned> selected_cost;
    std::vector<unsigned> final_demand;
    unsigned i = 0;
    unsigned j = 0;
    
    auto cost_array = matrix2array(cost, row, col);
    // Thus, minimum element is always at the position 0
    std::sort(cost_array.begin(), cost_array.end());

    while (cost_array.size()) {
        // Extract minimum element
        unsigned min_element = std::get<0>(cost_array[0]);
        i = std::get<1>(cost_array[0]);
        j = std::get<2>(cost_array[0]);

        // Minimum element is always in the end result
        selected_cost.push_back(min_element);
        cost_array.erase(cost_array.cbegin());

        if (offer[i] == demand[j]) {
            // Do not take into consideration columns and rows
            // where offer and demand are depleted
            final_demand.push_back(offer[i]);
            cost_array.erase(
                std::remove_if(cost_array.begin(), cost_array.end(),
                [i, j] (auto cost) { return (std::get<1>(cost) == i) or (std::get<2>(cost) == j); }), 
                cost_array.end()
            );
        }
        else if (offer[i] > demand[j]) {
            // Do not take into consideration columns
            // where demand is depleted
            final_demand.push_back(demand[j]);
            offer[i] -= demand[j];
            cost_array.erase(
                std::remove_if(cost_array.begin(), cost_array.end(),
                [i, j] (auto cost) { return std::get<2>(cost) == j; }), 
                cost_array.end()
            );
        }
        else if (offer[i] < demand[j]) {
            // Do not take into consideration rows
            // where offer is depleted
            final_demand.push_back(offer[i]);
            demand[j] -= offer[i];
            cost_array.erase(
                std::remove_if(cost_array.begin(), cost_array.end(),
                [i, j] (auto cost) { return std::get<1>(cost) == i; }), 
                cost_array.end()
            );
        }
    }
    
    return std::inner_product(selected_cost.cbegin(), selected_cost.cend(), final_demand.cbegin(), 0);    
}

void print_vector(const std::vector<unsigned>& vector, const unsigned size)
{
    for(unsigned i = 0 ; i < size; ++i) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

void print_matrix( const std::vector<std::vector<unsigned>> &cost
                   , const unsigned row
                   , const unsigned col)
{
    std::cout << "Given cost matrix:" << std::endl;
    for(unsigned i = 0 ; i < row ; ++i) {
        print_vector(cost[i], col);
    }
}

#endif
