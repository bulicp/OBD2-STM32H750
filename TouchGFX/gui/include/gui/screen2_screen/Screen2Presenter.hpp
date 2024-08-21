#ifndef SCREEN2PRESENTER_HPP
#define SCREEN2PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include "stm32h7xx_hal.h"
#include "obd2.h"

using namespace touchgfx;

class Screen2View;

class Screen2Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen2Presenter(Screen2View& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~Screen2Presenter() {};

    // Methods to transfer OBD2 data from Model -> Presenter -> View:
    void setNewGaugeData(OBDQueueElement_t* pOBD2Data);
    uint32_t getSavedSpeed();
    uint32_t getSavedRPM();
    uint32_t getSavedAmbientTemp();
    uint32_t getSavedCoolantTemp();

    // methods to transfer data from View -> Preseter -> Model:
    void saveSpeed(uint32_t uwSpeed);
    void saveRPM(uint32_t uwRPM);
    void saveAmbientTemp(uint32_t temp);
    void saveCoolantTemp(uint32_t temp);

private:
    Screen2Presenter();

    Screen2View& view;
};

#endif // SCREEN2PRESENTER_HPP
