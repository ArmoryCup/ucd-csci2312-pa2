//
// Created by yushi on 11/9/15.
//

#include "RemoveFromEmptyEx.h"

namespace Clustering{


    std::ostream &operator<<(std::ostream &os, const RemoveFromEmptyEx &err){

        os << "Cluster has no points. Exception is thrown from " << err.m_name;
    }
}