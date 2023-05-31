/*
 ============================================================================
 Name        : Vehicle_Control_System.c
 Author      : Basel Dawoud
 Description : Embedded Diploma 74 Mini-Project1
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
enum{OFF,ON};	/* Replace these words with 0 and 1 to handle them easily */
struct sensor{	/* A global structure whose members represent the current vehicle state */
	char Engine_state;	/* ON/OFF */
	char AC;			/* ON/OFF */
	int Vehicle_Speed;
	float Room_Temperature;
	char Engine_Temperature_Controller_State;	/* ON/OFF */
	float Engine_Temperature;
};
struct sensor current ={ON,OFF,50,20,OFF,90};	/* Setting a global variable (instant) with struct sensor type with initial values to its members */
char selector=1;/* A global variable to select between the main list states */

/* Functions Declaration (Prototypes) */

void start();	/* Printing main list */
void Home();	/* Checking the main list states */
void state_a(); /* Relevant to turning the vehicle on */
/* we will assume that this is the sensor read value for each of the following functions */
void trLight(char light);
void roomTemp(float rtemp);
void engineTemp(float etemp);

void vehicle_speed();/* Checking the current vehicle speed */
void strPrint();	/* Display the current vehicle state(Printing the current structure members) */

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	while('c'!=selector) /*Checking the selector value every time*/
	{
		start();	/* Calling the start function to display the main list */
		Home();		/* Calling the Home function */
	};
	return EXIT_SUCCESS;
}

/* Functions Definitions */

void start()
{
	printf(" a. Turn on the vehicle engine\n b. Turn off the vehicle engine\n c. Quit the system\n");
	scanf(" %c",&selector);
	return;	/* Returning to call the Home function and checking the selector value entered above */
}
void Home()
{
	switch (selector)
	{
	case 'a':
		state_a();	/* Turning the vehicle on */
		break;
	case 'b':
		printf("\nVehicle engine is OFF..\n\n");
		break;	/* Back to main */
	case 'c':
		printf("\nQuitting the system");
		break;	/* Back to main and close the program where the selector holds the value 'c' */
	default:
		start();	/* If the selector entered false, go back to the start function */
	}
}
void state_a()
{
	char cond;
	printf("\nVehicle engine is ON..\n\n");
	printf(" a. Turn off the engine\n b. Set the traffic light color\n c. Set the room temperature (Temperature Sensor)\n d. Set the engine temperature (Engine Temperature Sensor)\n");
	scanf(" %c",&cond);
	switch (cond)	/* Checking the condition */
	{
	case 'a':
		selector='b'; /* To access case 'b' in Home function  */
	Home();	/* Calling the Home to turn the engine off */
		break;
	case 'b':
		char light;
		printf("Enter the traffic light: ");
		scanf(" %c",&light);
		trLight(light);	/* Calling the trLight function for the traffic light cases */
		break;
	case 'c':
		float temp;
		printf("Enter the required room temperature: ");
		scanf(" %f",&temp);
		roomTemp(temp);	/* Calling the roomTemp function for the room temperature cases */
		break;
	case 'd':
		float etemp;
		printf("Enter the required engine temperature: ");
		scanf(" %f",&etemp);
		engineTemp(etemp);
		break;
	}
	return;
}
void trLight(char light)	/* Setting the Vehicle_Speed member in current depending on light */
{
	if ('G'==light||'g'==light)
	{
		current.Vehicle_Speed=100;
	}
	else if('O'==light||'o'==light)
	{
		current.Vehicle_Speed=30;
	}
	else if('R'==light||'r'==light)
	{
		current.Vehicle_Speed=0;
	}
	vehicle_speed();	/* Calling the vehicle_speed function */
}
void roomTemp(float rtemp)	/* Setting the Room_Temperature member in current depending on room temperature */
{
	if (rtemp<10||rtemp>30)
	{
		current.AC= ON;	/* 1 */
		current.Room_Temperature= 20;
	}
	else
	{
		current.AC= OFF;	/* 0 */
	}
	vehicle_speed();	/* Calling the vehicle_speed function */
}
void engineTemp(float etemp)
{
	if (etemp<100||etemp>150)
	{
		current.Engine_Temperature_Controller_State= ON;
		current.Room_Temperature= 125;
	}
	else
	{
		current.Engine_Temperature_Controller_State= OFF;
	}
	vehicle_speed();	/* Calling the vehicle_speed function */
}
void vehicle_speed()	/* Checking whether the vehicle_speed is 30 or not */
{
	if (30==current.Vehicle_Speed)
	{
		if (!current.AC)	/* Turn ON AC if it was OFF */
		{
			current.AC= ON;
		}
		current.Room_Temperature= (current.Room_Temperature)*(5/4)+1;
		current.Engine_Temperature_Controller_State= ON;
		current.Engine_Temperature= (current.Room_Temperature)*(5/4)+1;
	}
	strPrint();	/* Calling the strPrint function */
}
void strPrint()	/* Displaying the sensor structure with recent values */
{
	if (current.Engine_Temperature)	/* if (ON)=> if (1) => The condition is true */
		printf("\n Engine is ON\n");
	else
		printf(" Engine Temperature is OFF\n");
	if (current.AC)	/* if (ON)=> if (1) => The condition is true */
		printf(" AC: ON\n");
	else
		printf(" AC: OFF\n");

	printf(" Vehicle Speed: %d Km/Hr\n",current.Vehicle_Speed);
	printf(" Room Temperature: %f C\n",current.Room_Temperature);
	if (current.Engine_Temperature_Controller_State)	/* if (ON)=> if (1) => The condition is true */
		printf(" Engine Temperature Controller is ON\n");
	else
		printf(" Engine Temperature Controller is OFF\n");
	printf(" Engine Temperature: %f C\n",current.Engine_Temperature);
	Home();	/* Calling the Home function to repeat the program system */
}
/* Thanks XD */
