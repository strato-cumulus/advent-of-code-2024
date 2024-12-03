#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

enum mul_state {
    ST_NONE, ST_M, ST_U, ST_L, ST_PO, ST_N1, ST_CM, ST_N2, ST_PC 
};

int main(int argc, char **argv)
{
    std::fstream in("example_input_2");
    char c;

    std::string l_do("do()");
    std::string l_dont("don't()");
    int l_pos = 0;
    
    mul_state mul_s = ST_NONE;
    std::stringstream s_n;
    int n1, n2;
    long long int total = 0;
    bool mul_enabled = true;

    while ( in >> c ) {
        if (mul_enabled) {
            switch(mul_s) {
            case ST_NONE:
                if ( c == 'm') mul_s = ST_M;
                else mul_s = ST_NONE;
            break;
            case ST_M:
                if (c == 'u') mul_s = ST_U;
                else mul_s = ST_NONE;
            break;
            case ST_U:
                if (c == 'l') mul_s = ST_L;
                else mul_s = ST_NONE;
            break;
            case ST_L:
                if (c == '(') mul_s = ST_PO;
                else mul_s = ST_NONE;
            break;
            case ST_PO:
            case ST_N1:
                if (c >= '0' && c <= '9') {
                    mul_s = ST_N1;
                    s_n << c;
                }
                else {
                    if (c == ',' && mul_s == ST_N1) {
                        s_n >> n1;
                        mul_s = ST_CM;
                    }
                    else {
                        mul_s = ST_NONE;
                    }
                    s_n.str(std::string());
                    s_n.clear();
                }
            break;
            case ST_CM:
            case ST_N2:
                if (c >= '0' && c <= '9') {
                    mul_s = ST_N2;
                    s_n << c;
                }
                else {
                    if (c == ')' && mul_s == ST_N2) {
                        s_n >> n2;
                        total += n1 * n2;
                    }
                    mul_s = ST_NONE;
                    s_n.str(std::string());
                    s_n.clear();
                }
            break;
            }
        }
        if ( c == l_do[l_pos] ) {
            l_pos += 1;
            if ( l_pos == l_do.size() ) {
                l_pos = 0;
                mul_enabled = true;
            }
        }
        if (c == l_dont[l_pos] ) {
            l_pos += 1;
            if ( l_pos == l_dont.size() ) {
                l_pos = 0;
                mul_enabled = false;
            }
        }
    }
    std::cout << total << std::endl;
}

