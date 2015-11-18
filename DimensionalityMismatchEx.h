//
// Created by kamil on 11/5/15.
//

#include <string>
#include <ostream>

#ifndef UCD_CSCI2312_PA2_DIMENSIONALITYMISMATCHEX_H
#define UCD_CSCI2312_PA2_DIMENSIONALITYMISMATCHEX_H

namespace Clustering {
    class DimensionalityMismatchEx {

    public:
        DimensionalityMismatchEx(std::string s) : name(s) { }
        DimensionalityMismatchEx(int l, int r) : lhs(l), rhs(r) { }
        DimensionalityMismatchEx(std::string s, int l, int r) : name(s), lhs(l), rhs(r) { }

        std::string getName() const{ return name; }
        int getLhs() const { return lhs; }
        int getRhs() const{ return rhs; }

        friend std::ostream &operator<<(std::ostream &, const DimensionalityMismatchEx &err);


    private:
        std::string name;
        int lhs, rhs;
    };
}

#endif //UCD_CSCI2312_PA2_DIMENSIONALITYMISMATCHEX_H
