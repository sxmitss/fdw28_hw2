#include <iostream>
#include <cstring>
#include <bitset>
#include <cmath>
#include <iomanip>

using uint32 = uint32_t;
using uint64 = uint64_t;

std::string ieee(double d) {
    uint64 u;
    std::memcpy(&u, &d, 8);
    uint32 upper = u >> 32;
    std::bitset<32> bs(upper);
    std::string s = bs.to_string();
    return s.substr(0,1) + " " + s.substr(1,8) + " " + s.substr(9,23);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "usage: ./fp_overflow_checker loop_bound loop_counter\n"
                     "loop_bound is a positive floating-point value\n"
                     "loop_counter is a positive floating-point value\n";
        return 1;
    }
    double bound = std::stod(argv[1]);
    double step  = std::stod(argv[2]);
    if (bound <= 0 || step <= 0) return 1;

    std::cout << "Loop bound: " << ieee(bound) << '\\n';
    std::cout << "Loop counter: " << ieee(step) << '\\n';

    double ulp = std::nextafter(bound, INFINITY) - bound;
    if (step > ulp) {
        double threshold = std::nextafter(bound, INFINITY);
        std::cout << "Warning: Possible overflow!  Overflow threshold: "
                  << std::scientific << threshold << ' ' << ieee(threshold) << '\\n';
    } else {
        std::cout << "There is no overflow!\\n";
    }
    return 0;
}
