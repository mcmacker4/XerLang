#include "Util.h"

#include <iostream>

namespace Xer { namespace Util {

    long BinSearchCharRange(
            const std::vector<char> &vec,
            char t, long l, long r) {
        if(r < l) return -1;
        auto m = (l + r) / 2;
        if(vec[m] < t) return BinSearchCharRange(vec, t, m + 1, r);
        if(vec[m] > t) return BinSearchCharRange(vec, t, l, m - 1);
        return m;
    }

    long BinSearchChar(const std::vector<char> &vec, char el) {
        return BinSearchCharRange(vec, el, 0, vec.size() - 1);
    }

}}