#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View()
// Initialization list:
// In constructor for callback, bind to this view object and bind which function to handle the event.
: backgroundClickedCallback(this, &Screen1View::backgroundClickHandler)
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    Unicode::snprintf(textSpeedBuffer, TEXTSPEED_SIZE, "%d", presenter->getSavedSpeed());
    Unicode::snprintf(textRPMsBuffer, TEXTRPMS_SIZE, "%d", presenter->getSavedRPM());
    Unicode::snprintf(textAmbientTempBuffer, TEXTAMBIENTTEMP_SIZE, "%d", presenter->getSavedAmbientTemp());
    Unicode::snprintf(textCoolTempBuffer, TEXTCOOLTEMP_SIZE, "%d", presenter->getSavedCoolantTemp());
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}



void Screen1View::backgroundClickHandler(const Image& image, const ClickEvent& event)
{
    if (&image == &image1)
    {
        //Implement what should happen when 'image' is touched/clicked here.
    	//Go to Screen1 with screen transition towards East
    	application().gotoScreen1ScreenCoverTransitionEast();
    }
}



// update speed:
void Screen1View::updateSpeed(uint32_t uwSpeed)
{
	Unicode::snprintf(textSpeedBuffer, TEXTSPEED_SIZE, "%d", uwSpeed);
	textSpeed.resizeHeightToCurrentText();
	textSpeed.invalidate();
	presenter->saveSpeed(uwSpeed);
}

// update RPMs:
void Screen1View::updateRPMs(uint32_t uwRPMs)
{
	Unicode::snprintf(textRPMsBuffer, TEXTRPMS_SIZE, "%d", uwRPMs);
	textRPMs.resizeHeightToCurrentText();
	textRPMs.invalidate();
	presenter->saveRPM(uwRPMs);
}

// update Engine Loads:
void Screen1View::updateEngineLoad(float fEngLoad)
{
	Unicode::snprintfFloat(textEngLoadBuffer, TEXTENGLOAD_SIZE, "%3.1f", fEngLoad);
	textEngLoad.resizeHeightToCurrentText();
	textEngLoad.invalidate();
}

void Screen1View::updateCoolantTemp(uint32_t uwCoolTemp)
{
	Unicode::snprintf(textCoolTempBuffer, TEXTCOOLTEMP_SIZE, "%d", uwCoolTemp);
	textCoolTemp.resizeHeightToCurrentText();
	textCoolTemp.invalidate();
	presenter->saveCoolantTemp(uwCoolTemp);
}

void Screen1View::updateIntakeAirTemp(uint32_t uwIntakeAirTemp)
{
	Unicode::snprintf(textIntakeTempBuffer, TEXTINTAKETEMP_SIZE, "%d", uwIntakeAirTemp);
	textIntakeTemp.resizeHeightToCurrentText();
	textIntakeTemp.invalidate();
}

void Screen1View::updateAmbientAirTemp(uint32_t uwAmbientAirTemp)
{
	Unicode::snprintf(textAmbientTempBuffer, TEXTAMBIENTTEMP_SIZE, "%d", uwAmbientAirTemp);
	textAmbientTemp.resizeHeightToCurrentText();
	textAmbientTemp.invalidate();
	presenter->saveAmbientTemp(uwAmbientAirTemp);
}

void Screen1View::updateMAFRate(float fMAFRate)
{
	Unicode::snprintfFloat(textMAFrateBuffer, TEXTMAFRATE_SIZE, "%3.1f", fMAFRate);
	textMAFrate.resizeHeightToCurrentText();
	textMAFrate.invalidate();
}

void Screen1View::updateManifoldPressure(uint32_t uwManifoldPress)
{
	Unicode::snprintf(textManifoldPressBuffer, TEXTMANIFOLDPRESS_SIZE, "%d", uwManifoldPress);
	textManifoldPress.resizeHeightToCurrentText();
	textManifoldPress.invalidate();
}

void Screen1View::updateFuelPressure(uint32_t uwFuelPress)
{
	Unicode::snprintf(textFuelPressBuffer, TEXTFUELPRESS_SIZE, "%d", uwFuelPress);
	textFuelPress.resizeHeightToCurrentText();
	textFuelPress.invalidate();
}

void Screen1View::updateCatalystTemp(float fval)
{
	Unicode::snprintfFloat(textCatalystTempBuffer, TEXTCATALYSTTEMP_SIZE, "%3.1f", fval);
	textCatalystTemp.resizeHeightToCurrentText();
	textCatalystTemp.invalidate();
}

void Screen1View::updateAbsBaroPressure(uint32_t uwval)
{
	Unicode::snprintf(textBaroPressBuffer, TEXTBAROPRESS_SIZE, "%d", uwval);
	textBaroPress.resizeHeightToCurrentText();
	textBaroPress.invalidate();
}

void Screen1View::updateOxySensor1(uint32_t uwval, float fval)
{
	Unicode::snprintf(textOXYSensor1Buffer1, TEXTOXYSENSOR1BUFFER1_SIZE, "%d", "%3.1f", uwval, fval);
	textOXYSensor1.resizeHeightToCurrentText();
	textOXYSensor1.invalidate();
}


