#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include "stm32h7xx_hal.h"

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void updateSpeed(uint32_t uwSpeed);
    void updateRPMs(uint32_t uwRPMs);
    void updateEngineLoad(float fEngLoad);
    void updateCoolantTemp(uint32_t uwCoolTemp);
    void updateIntakeAirTemp(uint32_t uwIntakeAirTemp);
    void updateAmbientAirTemp(uint32_t uwAmbientAirTemp);
    void updateMAFRate(float fMAFRate);
    void updateManifoldPressure(uint32_t uwManifoldPress);
    void updateFuelPressure(uint32_t uwFuelPress);
    void updateCatalystTemp(float fval);
    void updateAbsBaroPressure(uint32_t uwval);
    void updateOxySensor1(uint32_t uwval, float fval);

    // Declaring callback handler for the click in the background image:
    void backgroundClickHandler(const Image& image, const ClickEvent& event);

protected:
    // Declaring callback type of image and clickEvent:
    Callback<Screen1View, const Image&, const ClickEvent&> backgroundClickedCallback;
};

#endif // SCREEN1VIEW_HPP
