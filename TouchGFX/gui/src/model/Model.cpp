#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <message_types.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

uint8_t values[sizeof(display_values)];
uint8_t settings_value[sizeof(settings_message)];
int currentScreenIndex;
int tpmsIdFr = 1;
int tpmsIdRr = 2;
int tpmsIdRl = 3;
int tpmsIdFl = 4;
bool manualErrorScreenChange = false;

extern "C"
{
	xQueueHandle messageQ;
	xQueueHandle settingsMessageQ;
}

Model::Model() : modelListener(0)
{
	messageQ = xQueueGenericCreate(1, sizeof(display_values), 0);
	settingsMessageQ = xQueueGenericCreate(1, sizeof(settings_message), 0);
}

void Model::tick()
{
	if(xQueueReceive(messageQ, &values , 0) == pdTRUE)
	{
		modelListener->setNewValue(values);
	}

	if(xQueueReceive(settingsMessageQ, &settings_value , 0) == pdTRUE)
	{
		modelListener->updateDisplaySettings(settings_value);
	}
}

void Model::saveCurrentScreenIndex(int cScreen)
{
	currentScreenIndex = cScreen;
}


int Model::getCurrentScreenIndex()
{
	return currentScreenIndex;
}

int Model::getTpmsIdFr()
{
	return tpmsIdFr;
}

int Model::getTpmsIdRr()
{
	return tpmsIdRr;
}

int Model::getTpmsIdRl()
{
	return tpmsIdRl;
}

int Model::getTpmsIdFl()
{
	return tpmsIdFl;
}


void Model::setTpmsIdFr(int newTpmsIdFr)
{
	tpmsIdFr = newTpmsIdFr;
}

void Model::setTpmsIdRr(int newTpmsIdRr)
{
	tpmsIdRr = newTpmsIdRr;
}

void Model::setTpmsIdRl(int newTpmsIdRl)
{
	tpmsIdRl = newTpmsIdRl;
}

void Model::setTpmsIdFl(int newTpmsIdFl)
{
	tpmsIdFl = newTpmsIdFl;
}


void Model::setManualErrorChangeScreen() {
	manualErrorScreenChange = true;
}

bool Model::getManualErrorChangeScreen() {
	return manualErrorScreenChange;
}
