#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include <vector>

unsigned NW_method( const std::vector<std::vector<unsigned>> &cost
                    , const unsigned row
                    , const unsigned col
                    , const std::vector<unsigned> &offer_given
                    , const std::vector<unsigned> &demand_given)
{
    std::vector<unsigned> offer;
    std::vector<unsigned> demand;    
    std::copy(demand_given.cbegin(), demand_given.cend(),  std::back_inserter(demand));
    std::copy(offer_given.cbegin(), offer_given.cend(),  std::back_inserter(offer));
    std::vector<unsigned> selected_cost;
    std::vector<unsigned> final_demand;
    
    unsigned i = 0;
    unsigned j = 0;

    while (i < row && j < col) {
        // Take the north-west element first
        selected_cost.push_back(cost[i][j]);
        if (offer[i] == demand[j]) {
            final_demand.push_back(offer[i]);
            i++; j++;
        }
        else if (offer[i] > demand[j]) {
            final_demand.push_back(demand[j]);
            offer[i] -= demand[j];
            j++;
        }
        else if (offer[i] < demand[j]) {
            final_demand.push_back(offer[i]);
            demand[j] -= offer[i];
            i++;
        }
    }

    return std::inner_product(selected_cost.cbegin(), selected_cost.cend(), final_demand.cbegin(), 0); 
}

#endif
