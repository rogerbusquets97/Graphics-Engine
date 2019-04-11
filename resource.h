#ifndef RESOURCE_H
#define RESOURCE_H


class Resource
{
public:
    Resource(){}
    virtual ~Resource(){}

    virtual void update(){}
    virtual void cleanup(){}
};

#endif // RESOURCE_H
