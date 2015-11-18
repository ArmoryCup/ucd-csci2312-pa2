//
// Created by kamil on 11/6/15.
//

#include <string>
#ifndef UCD_CSCI2312_PA2_OUTOFBOUNDEX_H
#define UCD_CSCI2312_PA2_OUTOFBOUNDEX_H

namespace Clustering {
    class OutOfBoundEx {

    private:
        std::string name;
        unsigned int data;

    public:
        OutOfBoundEx(const std::string s) { name = s;}
        OutOfBoundEx(const std::string s, const unsigned int i) { name = s, data = i;}

        std::string getName() const { return name; }

        friend std::ostream &operator<<(std::ostream &, const OutOfBoundEx &err);
    };
}
#endif //UCD_CSCI2312_PA2_OUTOFBOUNDEX_H
