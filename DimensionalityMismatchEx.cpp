//
// Created by yushi on 11/5/15.
//

#include "DimensionalityMismatchEx.h"
namespace Clustering {


    std::ostream &operator<<(std::ostream &ostream, const DimensionalityMismatchEx &err) {

        ostream << " in " << err.name << ": lhs.dim = " << err.lhs << ", rhs.dim = " << err.rhs;
        return ostream;
    }
}