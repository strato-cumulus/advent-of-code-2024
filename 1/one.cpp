#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

#define RESERVED_LEN 1000

int main(int argc, char **argv)
{
    std::vector<int> left, right;
    std::ifstream input("example_input", std::ios::in);

    left.reserve(RESERVED_LEN);
    right.reserve(RESERVED_LEN);

    int l, r;
    
    while ( input >> l >> r ) {
        left.push_back(l);
        right.push_back(r);
    }

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    std::transform(left.begin(), left.end(), right.begin(), left.begin(), [](const int & l, const int & r) {
        return std::abs(l - r);
    });

    int result = std::accumulate(left.begin(), left.end(), 0);

    std::cout << result << std::endl;
}
