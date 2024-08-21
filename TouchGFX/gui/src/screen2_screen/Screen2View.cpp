#include <gui/screen2_screen/Screen2View.hpp>

Screen2View::Screen2View():
	// Initialization list:
	// In constructor for callback, bind to this view object and bind which function to handle the event.
	backgroundClickedCallback(this, &Screen2View::backgroundClickHandler),
	gaugeClickedCallback(this, &Screen2View::gaugeClickHandler)

{
}



void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
    // Add the callback to background image
    image1.setClickAction(backgroundClickedCallback);
    // Add the callback to gauges:
    gaugeRPM.setClickAction(gaugeClickedCallback);
    gaugeSpeed.setClickAction(gaugeClickedCallback);

    // Display last saved data:
    boxProgressTemp.setValue(presenter->getSavedCoolantTemp());
    gaugeRPM.setValue(presenter->getSavedRPM());
    gaugeSpeed.setValue(presenter->getSavedSpeed());

    Unicode::snprintf(textSpeedBuffer, TEXTSPEED_SIZE, "%d", presenter->getSavedSpeed());
    Unicode::snprintf(textAmbientTempBuffer, TEXTAMBIENTTEMP_SIZE, "%d", presenter->getSavedAmbientTemp());

}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();

    // Save the displayed data upon exiting the screen:
    presenter->saveSpeed(gaugeRPM.getValue());
    presenter->saveRPM(gaugeSpeed.getValue());
    presenter->saveRPM(boxProgressTemp.getValue());

}


void Screen2View::backgroundClickHandler(const Image& image, const ClickEvent& event)
{
    if (&image == &image1)
    {
        //Implement what should happen when 'image' is touched/clicked here.
    	//Go to Screen1 with screen transition towards East
    	application().gotoScreen1ScreenCoverTransitionEast();
    }
}

void Screen2View::gaugeClickHandler(const Gauge& gauge, const ClickEvent& event)
{
    if (&gauge == &gaugeSpeed)
    {
        //Implement what should happen when 'gauge' is touched/clicked here.
    	//Go to Screen1 with screen transition towards East
    	application().gotoScreen1ScreenCoverTransitionEast();
    }
    else if (&gauge == &gaugeRPM)
    {
        //Implement what should happen when 'gauge' is touched/clicked here.
        //Go to Screen1 with screen transition towards East
        application().gotoScreen1ScreenCoverTransitionEast();
    }
}



// update SPEED gauge:
void Screen2View::updateSpeed(uint32_t uwSpeed)
{
	// update speed gauge:
	gaugeSpeed.setValue(uwSpeed);
	// update speed text:
	Unicode::snprintf(textSpeedBuffer, TEXTSPEED_SIZE, "%d", uwSpeed);
	textSpeed.resizeHeightToCurrentText();
	textSpeed.invalidate();
}

// update RPM gauge:
void Screen2View::updateRPMs(uint32_t uwRPMs)
{
	gaugeRPM.setValue(uwRPMs);
}

void Screen2View::updateCoolantTemp(uint32_t uwCoolTemp)
{
	boxProgressTemp.setValue(uwCoolTemp);
	presenter->saveCoolantTemp(uwCoolTemp);
}

void Screen2View::updateAmbientAirTemp(uint32_t uwAmbientAirTemp)
{
	Unicode::snprintf(textAmbientTempBuffer, TEXTAMBIENTTEMP_SIZE, "%d", uwAmbientAirTemp);
	textAmbientTemp.resizeHeightToCurrentText();
	textAmbientTemp.invalidate();
	presenter->saveAmbientTemp(uwAmbientAirTemp);
}
