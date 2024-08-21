#ifndef MODEL_HPP
#define MODEL_HPP

#include "stm32h7xx_hal.h"
#include "cmsis_os.h"
#include "obd2.h"

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    void saveSpeed(uint32_t speed);
    void saveRPM(uint32_t rpm);
    void saveAmbientTemp(uint32_t temp);
    void saveCoolantTemp(uint32_t temp);
    uint32_t getSavedSpeed();
    uint32_t getSavedRPM();
    uint32_t getSavedAmbientTemp();
    uint32_t getSavedCoolantTemp();



protected:
    ModelListener* modelListener;
    uint32_t savedSpeed;
    uint32_t savedRPM;
    uint32_t savedAmbientTemp;
    uint32_t savedCoolantTemp;
};

#endif // MODEL_HPP
