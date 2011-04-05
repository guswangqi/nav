/*
* Author: Jarryd Hall
* Purpose: Logic for controlling which navigation system is in use. 
* Interface: 
*
* Function: Switch between functions. Manual input, Auto-pilot(gps/ad-hoc)
*           User input: Transform user input to an angle, pass it along
*           Auto-Pilot GPS: Create connection to gps/ start gps parser
*           Auto-Pilot ad-hoc: Parse TMX File
*
* User controls: see movementCommands.h file
*
*/

#include <stdio.h>
#include "NavigationSystem.h"
#include "TMXParser.c"
#include "Tilemap.c"
#include "movementCommands.h"

// Determine if the gps system is used together with the indoor system
void setNavigationSystem(char* navigationSystem)
{
	if (strcmp("gps", navigationSystem) == 0)
	{
		setupGPSSystem;
		printf("gps system started\n");
	}
	else if ((strcmp("indoor", navigationSystem) == 0))
	{
		setupIndoorNavigationSystem;
		printf("indoor navigation system started\n");
	}
	else
		fprintf(stderr, "Incorrect system selected\n");
}

void setupGPSSystem()
{
	// TODO: start connection to gps
	// TODO: start parser
	// TODO: fetch data from gps data structure
}

void setupIndoorNavigationSystem()
{
	world = NULL;
	// TODO: Set the return of the parsed doc to the new representation

	char *doc = "secondYearSquare.xml";
	parseDoc(doc, world);
	
	// TODO: Open the return struct and set the representation fields to the fields\
	//       of the returned parsed struct. Init the 3DWorld
	// TODO: Add functions in TMXParser to return the needed struct
	
}

// functions for handling the manual user input
void manualMovementCommand(char *_command)
{
	// TODO: notify the path calculation to stop creating movement orders.
	sendMovementCommand();
}

// receive data about the movement from movement group
void receiveOrder(movementPerformed *movement)
{
	// send the movement data to the positioning system
}