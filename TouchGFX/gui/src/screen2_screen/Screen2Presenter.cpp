#include <gui/screen2_screen/Screen2View.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

Screen2Presenter::Screen2Presenter(Screen2View& v)
    : view(v)
{

}

void Screen2Presenter::activate()
{

}

void Screen2Presenter::deactivate()
{

}

void Screen2Presenter::saveSpeed(uint32_t uwSpeed)
{
	model->saveSpeed(uwSpeed);
}

void Screen2Presenter::saveRPM(uint32_t uwRPM)
{
	model->saveRPM(uwRPM);
}

void Screen2Presenter::saveAmbientTemp(uint32_t temp)
{
	model->saveAmbientTemp(temp);
}

void Screen2Presenter::saveCoolantTemp(uint32_t temp)
{
	model->saveCoolantTemp(temp);
}

uint32_t Screen2Presenter::getSavedSpeed()
{
	return model->getSavedSpeed();
}

uint32_t Screen2Presenter::getSavedRPM()
{
	return model->getSavedRPM();
}

uint32_t Screen2Presenter::getSavedAmbientTemp()
{
	return model->getSavedAmbientTemp();
}

uint32_t Screen2Presenter::getSavedCoolantTemp()
{
	return model->getSavedCoolantTemp();
}

void Screen2Presenter::setNewGaugeData(OBDQueueElement_t* pOBD2Data)
{
	switch(pOBD2Data->pid){
		case OBD2_PID_VEHICLE_SPEED:
			view.updateSpeed(pOBD2Data->uwData);
			break;

		case OBD2_PID_ENGINE_SPEED:
			view.updateRPMs(pOBD2Data->uwData);
			break;

		case OBD2_PID_ENGINE_COOLANT_TEMP:
			view.updateCoolantTemp(pOBD2Data->uwData);
			break;

		case OBD2_PID_AMBIENT_AIR_TEMP:
			view.updateAmbientAirTemp(pOBD2Data->uwData);
			break;

		default:
			break;
	}
}
