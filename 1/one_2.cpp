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

    auto l_it = left.begin(), r_it = right.begin();
    int sim_score = 0;
    int cur_number = 0;
    int cur_repetitions = 0;

    while ( l_it != left.end() && r_it != right.end() ) {

        if ( *l_it < *r_it ) {
            l_it++;
        }
        else if ( *r_it < *l_it ) {
            r_it++;
        }
        else {
            cur_number = *l_it;
            cur_repetitions += 1;
            r_it++;
            continue;
        }
        sim_score += cur_number * cur_repetitions;
        cur_number = 0;
        cur_repetitions = 0;
    }

    std::cout << sim_score << std::endl;
}
