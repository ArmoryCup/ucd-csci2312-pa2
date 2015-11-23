#ifndef UCD_CSCI2312_PA2_REMOVEFROMEMPTYEX_H
#define UCD_CSCI2312_PA2_REMOVEFROMEMPTYEX_H

#include <string>
#include <ostream>
#include "Cluster.h"

namespace Clustering {
    class RemoveFromEmptyEx {
        std::string m_name;
//        LNodePtr m_emptyNode;

    public:
        RemoveFromEmptyEx(std::string s) : m_name(s) { }

//        friend std::ostream &operator<<(std::ostream &, const RemoveFromEmptyEx &err);

        const std::string &getName() const { return m_name; }

        friend std::ostream &operator<<(std::ostream &, const RemoveFromEmptyEx &err);
    };

}
#endif //UCD_CSCI2312_PA2_REMOVEFROMEMPTYEX_H
