#include <fstream>
#include <iostream>
#include <sstream>

enum state {
    ST_NONE, ST_M, ST_U, ST_L, ST_PO, ST_N1, ST_CM, ST_N2, ST_PC 
};

int main(int argc, char **argv)
{
    std::fstream in("example_input");
    char c;
    state s = ST_NONE;
    std::stringstream s_n;
    int n1, n2;
    long long int total = 0;

    while ( in >> c ) {
        switch(s) {
        case ST_NONE:
            if ( c == 'm') s = ST_M;
            else s = ST_NONE;
        break;
        case ST_M:
            if (c == 'u') s = ST_U;
            else s = ST_NONE;
        break;
        case ST_U:
            if (c == 'l') s = ST_L;
            else s = ST_NONE;
        break;
        case ST_L:
            if (c == '(') s = ST_PO;
            else s = ST_NONE;
        break;
        case ST_PO:
        case ST_N1:
            if (c >= '0' && c <= '9') {
                s = ST_N1;
                s_n << c;
            }
            else {
                if (c == ',' && s == ST_N1) {
                    s_n >> n1;
                    s = ST_CM;
                }
                else {
                    s = ST_NONE;
                }
                s_n.str(std::string());
                s_n.clear();
            }
        break;
        case ST_CM:
        case ST_N2:
            if (c >= '0' && c <= '9') {
                s = ST_N2;
                s_n << c;
            }
            else {
                if (c == ')' && s == ST_N2) {
                    s_n >> n2;
                    total += n1 * n2;
                }
                s = ST_NONE;
                s_n.str(std::string());
                s_n.clear();
            }
        break;
        }
    }
    std::cout << total << std::endl;
}

