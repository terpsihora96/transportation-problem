#include <iostream>
#include <vector>

int main() {
    // Cost matrix
    unsigned row = 3;
    unsigned col = 4;
    
    unsigned cost[row][col]
    {   {20, 11, 15, 13},
        {17, 14,12, 13},
        {15, 12, 18, 18},
    };

    std::vector<unsigned> offer{2, 6, 7};
    std::vector<unsigned> demand{3, 3, 4, 5};
    
    if (std::accumulate(offer.cbegin(), offer.cend(), 0) == std::accumulate(demand.cbegin(), demand.cend(), 0)) {
        std::cout << "Problem je zasicen." << std::endl;
    }
    

    return 0;
}
