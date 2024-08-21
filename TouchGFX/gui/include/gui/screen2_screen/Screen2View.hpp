#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void updateSpeed(uint32_t uwSpeed);
    void updateRPMs(uint32_t uwRPMs);
    void updateCoolantTemp(uint32_t uwCoolTemp);
    void updateAmbientAirTemp(uint32_t uwAmbientAirTemp);

    uint32_t uwCurrentSpeed;
    uint32_t uwCurrentRPMs;
    uint32_t uwCurrentCoolTemp;


    // Declaring callback handler for the click in the background image:
    void backgroundClickHandler(const Image& image, const ClickEvent& event);
    void gaugeClickHandler(const Gauge& gauge, const ClickEvent& event);

protected:
    // Declaring callback type of image and clickEvent:
    Callback<Screen2View, const Image&, const ClickEvent&> backgroundClickedCallback;
    // Declaring callback type of gauge and clickEvent:
    Callback<Screen2View, const Gauge&, const ClickEvent&> gaugeClickedCallback;
};

#endif // SCREEN2VIEW_HPP
