#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>


Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}

void Screen1Presenter::saveSpeed(uint32_t uwSpeed)
{
	model->saveSpeed(uwSpeed);
}

void Screen1Presenter::saveRPM(uint32_t uwRPM)
{
	model->saveRPM(uwRPM);
}

void Screen1Presenter::saveAmbientTemp(uint32_t temp)
{
	model->saveAmbientTemp(temp);
}

void Screen1Presenter::saveCoolantTemp(uint32_t temp)
{
	model->saveCoolantTemp(temp);
}



uint32_t Screen1Presenter::getSavedSpeed()
{
	return model->getSavedSpeed();
}

uint32_t Screen1Presenter::getSavedRPM()
{
	return model->getSavedRPM();
}

uint32_t Screen1Presenter::getSavedAmbientTemp()
{
	return model->getSavedAmbientTemp();
}

uint32_t Screen1Presenter::getSavedCoolantTemp()
{
	return model->getSavedCoolantTemp();
}


void Screen1Presenter::setNewSpeed(uint32_t uwSpeed)
{
	view.updateSpeed(uwSpeed);
}

void Screen1Presenter::setNewOBD2Data(OBDQueueElement_t* pOBD2Data)
{
	switch(pOBD2Data->pid){
		case OBD2_PID_VEHICLE_SPEED:
			view.updateSpeed(pOBD2Data->uwData);
			break;

		case OBD2_PID_ENGINE_SPEED:
			view.updateRPMs(pOBD2Data->uwData);
			break;

		case OBD2_PID_ENGINE_LOAD:
			view.updateEngineLoad(pOBD2Data->fData);
			break;

		case OBD2_PID_ENGINE_COOLANT_TEMP:
			view.updateCoolantTemp(pOBD2Data->uwData);
			break;

		case OBD2_PID_INTAKE_AIR_TEMP:
			view.updateIntakeAirTemp(pOBD2Data->uwData);
			break;

		case OBD2_PID_AMBIENT_AIR_TEMP:
			view.updateAmbientAirTemp(pOBD2Data->uwData);
			break;

		case OBD2_PID_MAF_FLOW_RATE:
			view.updateMAFRate(pOBD2Data->fData);
			break;

		case OBD2_PID_INTAKE_MANIFOLD_PRESSURE:
			view.updateManifoldPressure(pOBD2Data->uwData);
			break;

		case OBD2_PID_FUEL_PRESSURE:
			view.updateFuelPressure(pOBD2Data->uwData);
			break;

		case OBD2_PID_ABS_CATALYST_TEMP:
			view.updateCatalystTemp(pOBD2Data->fData);
			break;

		case OBD2_PID_ABS_BARO_PRESSURE:
			view.updateAbsBaroPressure(pOBD2Data->uwData);
			break;

		case OBD2_PID_OXY_SENSOR_1:
			view.updateOxySensor1(pOBD2Data->uwData, pOBD2Data->fData);
			break;

		default:
			break;
	}
}
