#ifndef AR60XUDPPORTMASTER_H
#define AR60XUDPPORTMASTER_H

#include "IPortMaster.h"

class AR60xUDPPortMaster : public IPortMaster
{
public:
    AR60xUDPPortMaster();
    virtual void Write(char *packet);
    virtual void Read(char *packet);
};

#endif // AR60XUDPPORTMASTER_H
