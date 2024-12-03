#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

inline bool predicate(const std::vector<int> & report) {
    for ( auto r_it = report.begin(); r_it != report.end() - 2; ++r_it ) {
        auto diff1 = *r_it - *( r_it + 1 );
        auto diff2 = *( r_it + 1 ) - *( r_it + 2 );
        if ( ! diff1 
            || (diff1 < 0) != (diff2 < 0)
            || ( std::abs(diff1) < 1 )
            || ( std::abs(diff1) > 3 )
            || ( std::abs(diff2) < 1 )
            || ( std::abs(diff2) > 3 )
        ) {
            return false;
        }
    }
    return true;
}

int main (int argc, char **argv)
{
    std::fstream input("example_input");
    std::string s_buffer;
    int i_buffer;

    std::vector<int> report;
    report.reserve(8);

    int good = 0;

    while ( std::getline(input, s_buffer) ) {
        std::istringstream is(s_buffer);

        report.clear();

        while ( is >> i_buffer ) {
            report.push_back(i_buffer);
        }

        if ( predicate(report) ) {
            good += 1;
        }
    }
    std::cout << good << std::endl;
}
