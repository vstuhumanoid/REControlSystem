#ifndef IPORTMASTER_H
#define IPORTMASTER_H

class IPortMaster
{
public:
    virtual ~IPortMaster(){ }
    virtual void Write(char* packet)=0;
    virtual void Read(char* packet)=0;
};

#endif // IPORTMASTER_H
