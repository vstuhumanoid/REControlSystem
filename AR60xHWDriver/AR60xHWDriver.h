#ifndef AR60XHWDRIVER_H
#define AR60XHWDRIVER_H

#include "RobotDescription/AR60xDescription.h"
#include "RobotDescription/JSONSerializer.h"

#include <string>

class AR60xHWDriver
{
    AR60xDescription * desc;
public:
    AR60xHWDriver();
    void saveDesc(std::string fileName);
    void generateDesc(std::string fileName);
};

#endif // AR60XHWDRIVER_H
