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
    scan_matrix(cost, row, col);
    print_matrix(cost, row, col);
    std::vector<unsigned> offer;        // {2, 6, 7};
    std::vector<unsigned> demand;       // {3, 3, 4, 5};
    offer.resize(row);
    demand.resize(col);
    scan_vector(offer, row);
    scan_vector(demand, col);
    std::cout << "Offer: " << std::endl;
    print_vector(offer, row);
    std::cout << "Demand: " << std::endl;
    print_vector(demand, col);

    if (std::accumulate(offer.cbegin(), offer.cend(), 0) == std::accumulate(demand.cbegin(), demand.cend(), 0)) {
        std::cout << "Problem is saturated." << std::endl;
    }
    
    std::cout << "North-west method: " << NW_method(cost, row, col, offer, demand) << std::endl;
    std::cout << "Minimum method: " << min_method(cost, row, col, offer, demand) << std::endl;
    std::cout << "Fogel's method: " << fogels_method(cost, row, col, offer, demand) << std::endl;
    
    return 0;
}

