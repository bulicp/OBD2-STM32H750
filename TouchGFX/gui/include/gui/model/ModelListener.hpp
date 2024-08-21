#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include "obd2.h"


class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    virtual void setNewSpeed(unsigned int uwSpeed) {}
    virtual void setNewOBD2Data(OBDQueueElement_t* pOBD2Data) {}
    virtual void setNewGaugeData(OBDQueueElement_t* pOBD2Data) {}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
