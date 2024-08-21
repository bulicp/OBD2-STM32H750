#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>


// A queue to send the data from a task to GUI
extern "C" {
	osMessageQueueId_t mid_MODELMsgQueue;                // message queue
}

OBDQueueElement_t OBD2Data;

Model::Model() : modelListener(0)
{
	// create a message queue:
	mid_MODELMsgQueue = osMessageQueueNew(10, sizeof(OBDQueueElement_t), NULL);
	if (mid_MODELMsgQueue == NULL) {
		// Message Queue object not created, handle failure
	}
}

void Model::tick()
{
	// check if a new message has arrived - do not wait for it, just check :
	if (osMessageQueueGet(mid_MODELMsgQueue, &OBD2Data, NULL, 0U) == osOK)   // wait for message
	{
		// process data
		//modelListener->setNewSpeed(OBD2Data.uwData);
		modelListener->setNewOBD2Data(&OBD2Data);
		modelListener->setNewGaugeData(&OBD2Data);
	}
}

void Model::saveSpeed(uint32_t speed)
{
	savedSpeed = speed;
}

void Model::saveRPM(uint32_t rpm)
{
	savedRPM = rpm;
}

void Model::saveAmbientTemp(uint32_t temp)
{
	savedAmbientTemp = temp;
}

void Model::saveCoolantTemp(uint32_t temp)
{
	savedCoolantTemp = temp;
}

uint32_t Model::getSavedSpeed()
{
	return savedSpeed;
}

uint32_t Model::getSavedRPM()
{
	return savedRPM;
}

uint32_t Model::getSavedAmbientTemp()
{
	return savedAmbientTemp;
}

uint32_t Model::getSavedCoolantTemp()
{
	return savedCoolantTemp;
}
