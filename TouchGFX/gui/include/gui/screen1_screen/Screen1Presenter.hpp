#ifndef SCREEN1PRESENTER_HPP
#define SCREEN1PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include "stm32h7xx_hal.h"
#include "obd2.h"

using namespace touchgfx;

class Screen1View;

class Screen1Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen1Presenter(Screen1View& v);

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

    virtual ~Screen1Presenter() {};

    void setNewSpeed(uint32_t uwSpeed);	// OBSOLETE - do not use!!

    // Methods to transfer OBD2 data from Model -> Presenter -> View:
    void setNewOBD2Data(OBDQueueElement_t* pOBD2Data);
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
    Screen1Presenter();

    Screen1View& view;
};

#endif // SCREEN1PRESENTER_HPP
