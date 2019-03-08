#include <stdio.h>
#include <stdlib.h>
#include "ComputerSystem.h"
#include "OperatingSystem.h"
#include "ComputerSystemBase.h"
#include "Processor.h"
#include "Messages.h"
#include "Asserts.h"

// Functions prototypes

// Array that contains basic data about all daemons
// and all user programs specified in the command line
PROGRAMS_DATA *programList[PROGRAMSMAXNUMBER];

// Powers on of the Computer System.
void ComputerSystem_PowerOn(int argc, char *argv[]) {

	// Load debug messages
	int nm=0;
	nm=Messages_Load_Messages(nm,TEACHER_MESSAGES_FILE);
	nm=Messages_Load_Messages(nm,STUDENT_MESSAGES_FILE);
	printf("%d Messages Loaded\n",nm);

	// Obtain a list of programs in the command line and debus sections
	int daemonsBaseIndex = ComputerSystem_ObtainProgramList(argc, argv);

	/*Ejercicio 2:
	Muestra la información del ejercicio 1, justo antes de la inicialización del sistema operativo
	en ComputerSystem_PowerOn()*/
	ComputerSystem_PrintProgramList();

	int na=Asserts_LoadAsserts();
	if (na==-1)
		// printf("Asserts file unavailable\n");
		ComputerSystem_DebugMessage(84,POWERON);
	else
		// printf("%d Asserts Loaded\n",na);
		ComputerSystem_DebugMessage(85,POWERON,na);

	// Request the OS to do the initial set of tasks. The last one will be
	// the processor allocation to the process with the highest priority
	OperatingSystem_Initialize(daemonsBaseIndex);
	
	// Tell the processor to begin its instruction cycle 
	Processor_InstructionCycleLoop();
	
}

// Powers off the CS (the C program ends)
void ComputerSystem_PowerOff() {
	// Show message in red colour: "END of the simulation\n" 
	ComputerSystem_DebugMessage(99,SHUTDOWN); 
	exit(0);
}

/////////////////////////////////////////////////////////
//  New functions below this line  //////////////////////

/*Ejercicio1 1:
Implementa una función ComputerSystem_PrintProgramList() que muestre en pantalla
los programas de usuario contenidos en el vector programsList.*/
void ComputerSystem_PrintProgramList() {
	int i;
	ComputerSystem_DebugMessage(101, INIT);
	for (i = 1; i < PROGRAMSMAXNUMBER; i++) {
		if (programList[i] != NULL) {

			char *name = programList[i]->executableName;
			unsigned int time = programList[i]->arrivalTime;

			ComputerSystem_DebugMessage(102, INIT, name, time);
		}
	}
}