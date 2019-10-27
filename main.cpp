#include <iostream>
#include <vector>
#include <numeric>

#include "main.hpp"

int main() {
    // Cost matrix
    unsigned row; // = 3;
    unsigned col; // = 4;
    scanf("%u", &row);
    scanf("%u", &col);

    std::vector< std::vector<unsigned>> cost;
    /*{   {20, 11, 15, 13},
        {17, 14,12, 13},
        {15, 12, 18, 18},
    };*/
    unsigned i, j;
    cost.resize(row);
    for(i = 0; i < row; ++i) {
        cost[i].resize(col);
    }

    for(i = 0 ; i < row ; ++i) {
        for(j = 0 ; j < col ; ++j) {
            scanf("%u", &cost[i][j]);
        }
    }

    std::cout << "Given cost matrix:" << std::endl;
    for(i = 0 ; i < row ; ++i) {
        for(j = 0 ; j < col ; ++j) {
            std::cout << cost[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::vector<unsigned> offer;        // {2, 6, 7};
    std::vector<unsigned> demand;       // {3, 3, 4, 5};
    offer.resize(row);
    demand.resize(col);
    
    for(i = 0 ; i < col; ++i) {
        scanf("%u", &demand[i]);
    }
    for(i = 0 ; i < row; ++i) {
        scanf("%u", &offer[i]);
    }

    if (std::accumulate(offer.cbegin(), offer.cend(), 0) == std::accumulate(demand.cbegin(), demand.cend(), 0)) {
        std::cout << "Problem is saturated." << std::endl;
    }
    
    std::cout << NW_method(cost, row, col, offer, demand) << std::endl;
    
    return 0;
}

