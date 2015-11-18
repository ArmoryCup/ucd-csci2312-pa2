//
// Created by kamil on 11/6/15.
//

#include <ostream>
#include "OutOfBoundEx.h"

namespace Clustering {
    std::ostream &operator<<(std::ostream &os, const OutOfBoundEx &err) {
        os << "in " << err.getName() << ": " << err.data << " is out of range";
        return os;
    }
}

