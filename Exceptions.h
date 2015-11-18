//
// Created by Kamil on 11/5/15.
//

#include "DimensionalityMismatchEx.h"
#include "OutOfBoundEx.h"
#include "RemoveFromEmptyEx.h"

#ifndef UCD_CSCI2312_PA2_EXCEPTIONS_H
#define UCD_CSCI2312_PA2_EXCEPTIONS_H

namespace Clustering {
    class Exceptions {

    public:
        DimensionalityMismatchEx dimEx;
        OutOfBoundEx outBound;
        RemoveFromEmptyEx rmEmptyEx;

    private:


    };

}
#endif //UCD_CSCI2312_PA2_EXCEPTIONS_H
