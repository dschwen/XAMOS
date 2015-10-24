// Translated AMAL scripts:

#include "AmalPrograms.h"

// This part initialises the class:
AmalPrograms::AmalPrograms(AMOS_System* AMi)
{
	AM = AMi;
	forrepeat = false;
}

int AmalPrograms::runAmal(int program, int channel)
{
	switch (program)
	{
	case 1: amal1(channel); return 0;
	case 2: amal2(channel); return 0;
	case 3: amal3(channel); return 0;
	case 4: amal4(channel); return 0;
	case 5: amal5(channel); return 0;
	case 6: amal6(channel); return 0;
	case 7: amal7(channel); return 0;
	case 8: amal8(channel); return 0;
	case 9: amal9(channel); return 0;
	case 10: amal10(channel); return 0;
	case 11: amal11(channel); return 0;
	case 12: amal12(channel); return 0;
	default: return -1;
	}
	//return -1;
}

int AmalPrograms::numPrograms()
{
	return 12;
}

// Environment Generator:
void AmalPrograms::environment()
{
	AM->bobOff();
	AM->spriteOff();
	AM->rainbowDel();
	AM->screen(0);
	AM->screenOpen(0, 720, 576, 16777216, 0x8004);
	AM->loadIff("resources/starfield.jpg", 0);
	AM->load("resources/sprites", 1);
	AM->bell();
}

// And here are your converted AMAL programs:
void AmalPrograms::amal1(int CHAN)
{
		while(AM->PROGNOTFINISHED[CHAN] && !AM->PAUSED) switch(AM->PROGPOINTER[CHAN])
		{
		case 0:
			AM->amalSetX(CHAN, 10);
		case 1:
			AM->amalSetY(CHAN, 10);
		case 2:
			AM->amalSetA(CHAN, (AM->rnd(1) * 2));
		case 5:
			AM->amalSetA(CHAN, (AM->SPECIAL[CHAN][2] + 6));
		case 7:
			AM->amalSetLocal(CHAN, 0, AM->rnd(120));
		case 9:
			// For R0-R9 (local)
			if (forrepeat) {
				forrepeat = false;
				if ( AM->amalGetLocal(CHAN, 1) < AM->LOCAL[CHAN][0] ) {
					AM->amalIncLocal(CHAN, 1);
					AM->amalPause(CHAN, 10);
				} else
					AM->amalJump(CHAN, 11);
				break;
			} else
				AM->amalSetLocal(CHAN, 1, 0);
		case 10:
			// Next
			forrepeat = true;
			AM->amalJump(CHAN, 9);
			break;
		case 11:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 12:
			AM->amalMoveRun(CHAN, 12, 13);
			break;
		case 13:
			AM->amalMoveInit(CHAN, 280, -200, 20);
		case 14:
			AM->amalMoveRun(CHAN, 14, 15);
			break;
		case 15:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 16:
			AM->amalMoveRun(CHAN, 16, 17);
			break;
		case 17:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 18:
			AM->amalMoveRun(CHAN, 18, 19);
			break;
		case 19:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 20:
			AM->amalMoveRun(CHAN, 20, 21);
			break;
		case 21:
			AM->amalMoveInit(CHAN, 0, -400, 20);
		case 22:
			AM->amalMoveRun(CHAN, 22, 23);
			break;
		case 23:
			AM->amalMoveInit(CHAN, 280, 0, 20);
		case 24:
			AM->amalMoveRun(CHAN, 24, 25);
			break;
		case 25:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 26:
			AM->amalMoveRun(CHAN, 26, 27);
			break;
		case 27:
			AM->amalMoveInit(CHAN, 0, -200, 20);
		case 28:
			AM->amalMoveRun(CHAN, 28, 29);
			break;
		case 29:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 30:
			AM->amalMoveRun(CHAN, 30, 31);
			break;
		case 31:
			// Jump (Goto) Label 7
			AM->amalJump(CHAN, 11);
			break;
		}
		if (AM->PROGPOINTER[CHAN] >= 32)
			AM->amalEnd(CHAN);
}

void AmalPrograms::amal2(int CHAN)
{
		while(AM->PROGNOTFINISHED[CHAN] && !AM->PAUSED) switch(AM->PROGPOINTER[CHAN])
		{
		case 0:
			AM->amalSetX(CHAN, 10);
		case 1:
			AM->amalSetY(CHAN, 10);
		case 2:
			AM->amalSetA(CHAN, (AM->rnd(1) * 2));
		case 5:
			AM->amalSetA(CHAN, (AM->SPECIAL[CHAN][2] + 6));
		case 7:
			AM->amalSetLocal(CHAN, 0, AM->rnd(120));
		case 9:
			// For R0-R9 (local)
			if (forrepeat) {
				forrepeat = false;
				if ( AM->amalGetLocal(CHAN, 1) < AM->LOCAL[CHAN][0] ) {
					AM->amalIncLocal(CHAN, 1);
					AM->amalPause(CHAN, 10);
				} else
					AM->amalJump(CHAN, 11);
				break;
			} else
				AM->amalSetLocal(CHAN, 1, 0);
		case 10:
			// Next
			forrepeat = true;
			AM->amalJump(CHAN, 9);
			break;
		case 11:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 12:
			AM->amalMoveRun(CHAN, 12, 13);
			break;
		case 13:
			AM->amalMoveInit(CHAN, 280, -200, 20);
		case 14:
			AM->amalMoveRun(CHAN, 14, 15);
			break;
		case 15:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 16:
			AM->amalMoveRun(CHAN, 16, 17);
			break;
		case 17:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 18:
			AM->amalMoveRun(CHAN, 18, 19);
			break;
		case 19:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 20:
			AM->amalMoveRun(CHAN, 20, 21);
			break;
		case 21:
			AM->amalMoveInit(CHAN, 0, -400, 20);
		case 22:
			AM->amalMoveRun(CHAN, 22, 23);
			break;
		case 23:
			AM->amalMoveInit(CHAN, 280, 0, 20);
		case 24:
			AM->amalMoveRun(CHAN, 24, 25);
			break;
		case 25:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 26:
			AM->amalMoveRun(CHAN, 26, 27);
			break;
		case 27:
			AM->amalMoveInit(CHAN, 0, -200, 20);
		case 28:
			AM->amalMoveRun(CHAN, 28, 29);
			break;
		case 29:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 30:
			AM->amalMoveRun(CHAN, 30, 31);
			break;
		case 31:
			// Jump (Goto) Label 7
			AM->amalJump(CHAN, 11);
			break;
		}
		if (AM->PROGPOINTER[CHAN] >= 32)
			AM->amalEnd(CHAN);
}

void AmalPrograms::amal3(int CHAN)
{
		while(AM->PROGNOTFINISHED[CHAN] && !AM->PAUSED) switch(AM->PROGPOINTER[CHAN])
		{
		case 0:
			AM->amalSetX(CHAN, 10);
		case 1:
			AM->amalSetY(CHAN, 10);
		case 2:
			AM->amalSetA(CHAN, (AM->rnd(1) * 2));
		case 5:
			AM->amalSetA(CHAN, (AM->SPECIAL[CHAN][2] + 6));
		case 7:
			AM->amalSetLocal(CHAN, 0, AM->rnd(120));
		case 9:
			// For R0-R9 (local)
			if (forrepeat) {
				forrepeat = false;
				if ( AM->amalGetLocal(CHAN, 1) < AM->LOCAL[CHAN][0] ) {
					AM->amalIncLocal(CHAN, 1);
					AM->amalPause(CHAN, 10);
				} else
					AM->amalJump(CHAN, 11);
				break;
			} else
				AM->amalSetLocal(CHAN, 1, 0);
		case 10:
			// Next
			forrepeat = true;
			AM->amalJump(CHAN, 9);
			break;
		case 11:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 12:
			AM->amalMoveRun(CHAN, 12, 13);
			break;
		case 13:
			AM->amalMoveInit(CHAN, 280, -200, 20);
		case 14:
			AM->amalMoveRun(CHAN, 14, 15);
			break;
		case 15:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 16:
			AM->amalMoveRun(CHAN, 16, 17);
			break;
		case 17:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 18:
			AM->amalMoveRun(CHAN, 18, 19);
			break;
		case 19:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 20:
			AM->amalMoveRun(CHAN, 20, 21);
			break;
		case 21:
			AM->amalMoveInit(CHAN, 0, -400, 20);
		case 22:
			AM->amalMoveRun(CHAN, 22, 23);
			break;
		case 23:
			AM->amalMoveInit(CHAN, 280, 0, 20);
		case 24:
			AM->amalMoveRun(CHAN, 24, 25);
			break;
		case 25:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 26:
			AM->amalMoveRun(CHAN, 26, 27);
			break;
		case 27:
			AM->amalMoveInit(CHAN, 0, -200, 20);
		case 28:
			AM->amalMoveRun(CHAN, 28, 29);
			break;
		case 29:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 30:
			AM->amalMoveRun(CHAN, 30, 31);
			break;
		case 31:
			// Jump (Goto) Label 7
			AM->amalJump(CHAN, 11);
			break;
		}
		if (AM->PROGPOINTER[CHAN] >= 32)
			AM->amalEnd(CHAN);
}

void AmalPrograms::amal4(int CHAN)
{
		while(AM->PROGNOTFINISHED[CHAN] && !AM->PAUSED) switch(AM->PROGPOINTER[CHAN])
		{
		case 0:
			AM->amalSetX(CHAN, 10);
		case 1:
			AM->amalSetY(CHAN, 10);
		case 2:
			AM->amalSetA(CHAN, (AM->rnd(1) * 2));
		case 5:
			AM->amalSetA(CHAN, (AM->SPECIAL[CHAN][2] + 6));
		case 7:
			AM->amalSetLocal(CHAN, 0, AM->rnd(120));
		case 9:
			// For R0-R9 (local)
			if (forrepeat) {
				forrepeat = false;
				if ( AM->amalGetLocal(CHAN, 1) < AM->LOCAL[CHAN][0] ) {
					AM->amalIncLocal(CHAN, 1);
					AM->amalPause(CHAN, 10);
				} else
					AM->amalJump(CHAN, 11);
				break;
			} else
				AM->amalSetLocal(CHAN, 1, 0);
		case 10:
			// Next
			forrepeat = true;
			AM->amalJump(CHAN, 9);
			break;
		case 11:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 12:
			AM->amalMoveRun(CHAN, 12, 13);
			break;
		case 13:
			AM->amalMoveInit(CHAN, 280, -200, 20);
		case 14:
			AM->amalMoveRun(CHAN, 14, 15);
			break;
		case 15:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 16:
			AM->amalMoveRun(CHAN, 16, 17);
			break;
		case 17:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 18:
			AM->amalMoveRun(CHAN, 18, 19);
			break;
		case 19:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 20:
			AM->amalMoveRun(CHAN, 20, 21);
			break;
		case 21:
			AM->amalMoveInit(CHAN, 0, -400, 20);
		case 22:
			AM->amalMoveRun(CHAN, 22, 23);
			break;
		case 23:
			AM->amalMoveInit(CHAN, 280, 0, 20);
		case 24:
			AM->amalMoveRun(CHAN, 24, 25);
			break;
		case 25:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 26:
			AM->amalMoveRun(CHAN, 26, 27);
			break;
		case 27:
			AM->amalMoveInit(CHAN, 0, -200, 20);
		case 28:
			AM->amalMoveRun(CHAN, 28, 29);
			break;
		case 29:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 30:
			AM->amalMoveRun(CHAN, 30, 31);
			break;
		case 31:
			// Jump (Goto) Label 7
			AM->amalJump(CHAN, 11);
			break;
		}
		if (AM->PROGPOINTER[CHAN] >= 32)
			AM->amalEnd(CHAN);
}

void AmalPrograms::amal5(int CHAN)
{
		while(AM->PROGNOTFINISHED[CHAN] && !AM->PAUSED) switch(AM->PROGPOINTER[CHAN])
		{
		case 0:
			AM->amalSetX(CHAN, 10);
		case 1:
			AM->amalSetY(CHAN, 10);
		case 2:
			AM->amalSetA(CHAN, (AM->rnd(1) * 2));
		case 5:
			AM->amalSetA(CHAN, (AM->SPECIAL[CHAN][2] + 6));
		case 7:
			AM->amalSetLocal(CHAN, 0, AM->rnd(120));
		case 9:
			// For R0-R9 (local)
			if (forrepeat) {
				forrepeat = false;
				if ( AM->amalGetLocal(CHAN, 1) < AM->LOCAL[CHAN][0] ) {
					AM->amalIncLocal(CHAN, 1);
					AM->amalPause(CHAN, 10);
				} else
					AM->amalJump(CHAN, 11);
				break;
			} else
				AM->amalSetLocal(CHAN, 1, 0);
		case 10:
			// Next
			forrepeat = true;
			AM->amalJump(CHAN, 9);
			break;
		case 11:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 12:
			AM->amalMoveRun(CHAN, 12, 13);
			break;
		case 13:
			AM->amalMoveInit(CHAN, 280, -200, 20);
		case 14:
			AM->amalMoveRun(CHAN, 14, 15);
			break;
		case 15:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 16:
			AM->amalMoveRun(CHAN, 16, 17);
			break;
		case 17:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 18:
			AM->amalMoveRun(CHAN, 18, 19);
			break;
		case 19:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 20:
			AM->amalMoveRun(CHAN, 20, 21);
			break;
		case 21:
			AM->amalMoveInit(CHAN, 0, -400, 20);
		case 22:
			AM->amalMoveRun(CHAN, 22, 23);
			break;
		case 23:
			AM->amalMoveInit(CHAN, 280, 0, 20);
		case 24:
			AM->amalMoveRun(CHAN, 24, 25);
			break;
		case 25:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 26:
			AM->amalMoveRun(CHAN, 26, 27);
			break;
		case 27:
			AM->amalMoveInit(CHAN, 0, -200, 20);
		case 28:
			AM->amalMoveRun(CHAN, 28, 29);
			break;
		case 29:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 30:
			AM->amalMoveRun(CHAN, 30, 31);
			break;
		case 31:
			// Jump (Goto) Label 7
			AM->amalJump(CHAN, 11);
			break;
		}
		if (AM->PROGPOINTER[CHAN] >= 32)
			AM->amalEnd(CHAN);
}

void AmalPrograms::amal6(int CHAN)
{
		while(AM->PROGNOTFINISHED[CHAN] && !AM->PAUSED) switch(AM->PROGPOINTER[CHAN])
		{
		case 0:
			AM->amalSetX(CHAN, 10);
		case 1:
			AM->amalSetY(CHAN, 10);
		case 2:
			AM->amalSetA(CHAN, (AM->rnd(1) * 2));
		case 5:
			AM->amalSetA(CHAN, (AM->SPECIAL[CHAN][2] + 6));
		case 7:
			AM->amalSetLocal(CHAN, 0, AM->rnd(120));
		case 9:
			// For R0-R9 (local)
			if (forrepeat) {
				forrepeat = false;
				if ( AM->amalGetLocal(CHAN, 1) < AM->LOCAL[CHAN][0] ) {
					AM->amalIncLocal(CHAN, 1);
					AM->amalPause(CHAN, 10);
				} else
					AM->amalJump(CHAN, 11);
				break;
			} else
				AM->amalSetLocal(CHAN, 1, 0);
		case 10:
			// Next
			forrepeat = true;
			AM->amalJump(CHAN, 9);
			break;
		case 11:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 12:
			AM->amalMoveRun(CHAN, 12, 13);
			break;
		case 13:
			AM->amalMoveInit(CHAN, 280, -200, 20);
		case 14:
			AM->amalMoveRun(CHAN, 14, 15);
			break;
		case 15:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 16:
			AM->amalMoveRun(CHAN, 16, 17);
			break;
		case 17:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 18:
			AM->amalMoveRun(CHAN, 18, 19);
			break;
		case 19:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 20:
			AM->amalMoveRun(CHAN, 20, 21);
			break;
		case 21:
			AM->amalMoveInit(CHAN, 0, -400, 20);
		case 22:
			AM->amalMoveRun(CHAN, 22, 23);
			break;
		case 23:
			AM->amalMoveInit(CHAN, 280, 0, 20);
		case 24:
			AM->amalMoveRun(CHAN, 24, 25);
			break;
		case 25:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 26:
			AM->amalMoveRun(CHAN, 26, 27);
			break;
		case 27:
			AM->amalMoveInit(CHAN, 0, -200, 20);
		case 28:
			AM->amalMoveRun(CHAN, 28, 29);
			break;
		case 29:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 30:
			AM->amalMoveRun(CHAN, 30, 31);
			break;
		case 31:
			// Jump (Goto) Label 7
			AM->amalJump(CHAN, 11);
			break;
		}
		if (AM->PROGPOINTER[CHAN] >= 32)
			AM->amalEnd(CHAN);
}

void AmalPrograms::amal7(int CHAN)
{
		while(AM->PROGNOTFINISHED[CHAN] && !AM->PAUSED) switch(AM->PROGPOINTER[CHAN])
		{
		case 0:
			AM->amalSetX(CHAN, 10);
		case 1:
			AM->amalSetY(CHAN, 10);
		case 2:
			AM->amalSetA(CHAN, (AM->rnd(1) * 2));
		case 5:
			AM->amalSetA(CHAN, (AM->SPECIAL[CHAN][2] + 6));
		case 7:
			AM->amalSetLocal(CHAN, 0, AM->rnd(120));
		case 9:
			// For R0-R9 (local)
			if (forrepeat) {
				forrepeat = false;
				if ( AM->amalGetLocal(CHAN, 1) < AM->LOCAL[CHAN][0] ) {
					AM->amalIncLocal(CHAN, 1);
					AM->amalPause(CHAN, 10);
				} else
					AM->amalJump(CHAN, 11);
				break;
			} else
				AM->amalSetLocal(CHAN, 1, 0);
		case 10:
			// Next
			forrepeat = true;
			AM->amalJump(CHAN, 9);
			break;
		case 11:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 12:
			AM->amalMoveRun(CHAN, 12, 13);
			break;
		case 13:
			AM->amalMoveInit(CHAN, 280, -200, 20);
		case 14:
			AM->amalMoveRun(CHAN, 14, 15);
			break;
		case 15:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 16:
			AM->amalMoveRun(CHAN, 16, 17);
			break;
		case 17:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 18:
			AM->amalMoveRun(CHAN, 18, 19);
			break;
		case 19:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 20:
			AM->amalMoveRun(CHAN, 20, 21);
			break;
		case 21:
			AM->amalMoveInit(CHAN, 0, -400, 20);
		case 22:
			AM->amalMoveRun(CHAN, 22, 23);
			break;
		case 23:
			AM->amalMoveInit(CHAN, 280, 0, 20);
		case 24:
			AM->amalMoveRun(CHAN, 24, 25);
			break;
		case 25:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 26:
			AM->amalMoveRun(CHAN, 26, 27);
			break;
		case 27:
			AM->amalMoveInit(CHAN, 0, -200, 20);
		case 28:
			AM->amalMoveRun(CHAN, 28, 29);
			break;
		case 29:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 30:
			AM->amalMoveRun(CHAN, 30, 31);
			break;
		case 31:
			// Jump (Goto) Label 7
			AM->amalJump(CHAN, 11);
			break;
		}
		if (AM->PROGPOINTER[CHAN] >= 32)
			AM->amalEnd(CHAN);
}

void AmalPrograms::amal8(int CHAN)
{
		while(AM->PROGNOTFINISHED[CHAN] && !AM->PAUSED) switch(AM->PROGPOINTER[CHAN])
		{
		case 0:
			AM->amalSetX(CHAN, 10);
		case 1:
			AM->amalSetY(CHAN, 10);
		case 2:
			AM->amalSetA(CHAN, (AM->rnd(1) * 2));
		case 5:
			AM->amalSetA(CHAN, (AM->SPECIAL[CHAN][2] + 6));
		case 7:
			AM->amalSetLocal(CHAN, 0, AM->rnd(120));
		case 9:
			// For R0-R9 (local)
			if (forrepeat) {
				forrepeat = false;
				if ( AM->amalGetLocal(CHAN, 1) < AM->LOCAL[CHAN][0] ) {
					AM->amalIncLocal(CHAN, 1);
					AM->amalPause(CHAN, 10);
				} else
					AM->amalJump(CHAN, 11);
				break;
			} else
				AM->amalSetLocal(CHAN, 1, 0);
		case 10:
			// Next
			forrepeat = true;
			AM->amalJump(CHAN, 9);
			break;
		case 11:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 12:
			AM->amalMoveRun(CHAN, 12, 13);
			break;
		case 13:
			AM->amalMoveInit(CHAN, 280, -200, 20);
		case 14:
			AM->amalMoveRun(CHAN, 14, 15);
			break;
		case 15:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 16:
			AM->amalMoveRun(CHAN, 16, 17);
			break;
		case 17:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 18:
			AM->amalMoveRun(CHAN, 18, 19);
			break;
		case 19:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 20:
			AM->amalMoveRun(CHAN, 20, 21);
			break;
		case 21:
			AM->amalMoveInit(CHAN, 0, -400, 20);
		case 22:
			AM->amalMoveRun(CHAN, 22, 23);
			break;
		case 23:
			AM->amalMoveInit(CHAN, 280, 0, 20);
		case 24:
			AM->amalMoveRun(CHAN, 24, 25);
			break;
		case 25:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 26:
			AM->amalMoveRun(CHAN, 26, 27);
			break;
		case 27:
			AM->amalMoveInit(CHAN, 0, -200, 20);
		case 28:
			AM->amalMoveRun(CHAN, 28, 29);
			break;
		case 29:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 30:
			AM->amalMoveRun(CHAN, 30, 31);
			break;
		case 31:
			// Jump (Goto) Label 7
			AM->amalJump(CHAN, 11);
			break;
		}
		if (AM->PROGPOINTER[CHAN] >= 32)
			AM->amalEnd(CHAN);
}

void AmalPrograms::amal9(int CHAN)
{
		while(AM->PROGNOTFINISHED[CHAN] && !AM->PAUSED) switch(AM->PROGPOINTER[CHAN])
		{
		case 0:
			AM->amalSetX(CHAN, 10);
		case 1:
			AM->amalSetY(CHAN, 10);
		case 2:
			AM->amalSetA(CHAN, (AM->rnd(1) * 2));
		case 5:
			AM->amalSetA(CHAN, (AM->SPECIAL[CHAN][2] + 6));
		case 7:
			AM->amalSetLocal(CHAN, 0, AM->rnd(120));
		case 9:
			// For R0-R9 (local)
			if (forrepeat) {
				forrepeat = false;
				if ( AM->amalGetLocal(CHAN, 1) < AM->LOCAL[CHAN][0] ) {
					AM->amalIncLocal(CHAN, 1);
					AM->amalPause(CHAN, 10);
				} else
					AM->amalJump(CHAN, 11);
				break;
			} else
				AM->amalSetLocal(CHAN, 1, 0);
		case 10:
			// Next
			forrepeat = true;
			AM->amalJump(CHAN, 9);
			break;
		case 11:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 12:
			AM->amalMoveRun(CHAN, 12, 13);
			break;
		case 13:
			AM->amalMoveInit(CHAN, 280, -200, 20);
		case 14:
			AM->amalMoveRun(CHAN, 14, 15);
			break;
		case 15:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 16:
			AM->amalMoveRun(CHAN, 16, 17);
			break;
		case 17:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 18:
			AM->amalMoveRun(CHAN, 18, 19);
			break;
		case 19:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 20:
			AM->amalMoveRun(CHAN, 20, 21);
			break;
		case 21:
			AM->amalMoveInit(CHAN, 0, -400, 20);
		case 22:
			AM->amalMoveRun(CHAN, 22, 23);
			break;
		case 23:
			AM->amalMoveInit(CHAN, 280, 0, 20);
		case 24:
			AM->amalMoveRun(CHAN, 24, 25);
			break;
		case 25:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 26:
			AM->amalMoveRun(CHAN, 26, 27);
			break;
		case 27:
			AM->amalMoveInit(CHAN, 0, -200, 20);
		case 28:
			AM->amalMoveRun(CHAN, 28, 29);
			break;
		case 29:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 30:
			AM->amalMoveRun(CHAN, 30, 31);
			break;
		case 31:
			// Jump (Goto) Label 7
			AM->amalJump(CHAN, 11);
			break;
		}
		if (AM->PROGPOINTER[CHAN] >= 32)
			AM->amalEnd(CHAN);
}

void AmalPrograms::amal10(int CHAN)
{
		while(AM->PROGNOTFINISHED[CHAN] && !AM->PAUSED) switch(AM->PROGPOINTER[CHAN])
		{
		case 0:
			AM->amalSetX(CHAN, 10);
		case 1:
			AM->amalSetY(CHAN, 10);
		case 2:
			AM->amalSetA(CHAN, (AM->rnd(1) * 2));
		case 5:
			AM->amalSetA(CHAN, (AM->SPECIAL[CHAN][2] + 6));
		case 7:
			AM->amalSetLocal(CHAN, 0, AM->rnd(120));
		case 9:
			// For R0-R9 (local)
			if (forrepeat) {
				forrepeat = false;
				if ( AM->amalGetLocal(CHAN, 1) < AM->LOCAL[CHAN][0] ) {
					AM->amalIncLocal(CHAN, 1);
					AM->amalPause(CHAN, 10);
				} else
					AM->amalJump(CHAN, 11);
				break;
			} else
				AM->amalSetLocal(CHAN, 1, 0);
		case 10:
			// Next
			forrepeat = true;
			AM->amalJump(CHAN, 9);
			break;
		case 11:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 12:
			AM->amalMoveRun(CHAN, 12, 13);
			break;
		case 13:
			AM->amalMoveInit(CHAN, 280, -200, 20);
		case 14:
			AM->amalMoveRun(CHAN, 14, 15);
			break;
		case 15:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 16:
			AM->amalMoveRun(CHAN, 16, 17);
			break;
		case 17:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 18:
			AM->amalMoveRun(CHAN, 18, 19);
			break;
		case 19:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 20:
			AM->amalMoveRun(CHAN, 20, 21);
			break;
		case 21:
			AM->amalMoveInit(CHAN, 0, -400, 20);
		case 22:
			AM->amalMoveRun(CHAN, 22, 23);
			break;
		case 23:
			AM->amalMoveInit(CHAN, 280, 0, 20);
		case 24:
			AM->amalMoveRun(CHAN, 24, 25);
			break;
		case 25:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 26:
			AM->amalMoveRun(CHAN, 26, 27);
			break;
		case 27:
			AM->amalMoveInit(CHAN, 0, -200, 20);
		case 28:
			AM->amalMoveRun(CHAN, 28, 29);
			break;
		case 29:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 30:
			AM->amalMoveRun(CHAN, 30, 31);
			break;
		case 31:
			// Jump (Goto) Label 7
			AM->amalJump(CHAN, 11);
			break;
		}
		if (AM->PROGPOINTER[CHAN] >= 32)
			AM->amalEnd(CHAN);
}

void AmalPrograms::amal11(int CHAN)
{
		while(AM->PROGNOTFINISHED[CHAN] && !AM->PAUSED) switch(AM->PROGPOINTER[CHAN])
		{
		case 0:
			AM->amalSetX(CHAN, 10);
		case 1:
			AM->amalSetY(CHAN, 10);
		case 2:
			AM->amalSetA(CHAN, (AM->rnd(1) * 2));
		case 5:
			AM->amalSetA(CHAN, (AM->SPECIAL[CHAN][2] + 6));
		case 7:
			AM->amalSetLocal(CHAN, 0, AM->rnd(120));
		case 9:
			// For R0-R9 (local)
			if (forrepeat) {
				forrepeat = false;
				if ( AM->amalGetLocal(CHAN, 1) < AM->LOCAL[CHAN][0] ) {
					AM->amalIncLocal(CHAN, 1);
					AM->amalPause(CHAN, 10);
				} else
					AM->amalJump(CHAN, 11);
				break;
			} else
				AM->amalSetLocal(CHAN, 1, 0);
		case 10:
			// Next
			forrepeat = true;
			AM->amalJump(CHAN, 9);
			break;
		case 11:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 12:
			AM->amalMoveRun(CHAN, 12, 13);
			break;
		case 13:
			AM->amalMoveInit(CHAN, 280, -200, 20);
		case 14:
			AM->amalMoveRun(CHAN, 14, 15);
			break;
		case 15:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 16:
			AM->amalMoveRun(CHAN, 16, 17);
			break;
		case 17:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 18:
			AM->amalMoveRun(CHAN, 18, 19);
			break;
		case 19:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 20:
			AM->amalMoveRun(CHAN, 20, 21);
			break;
		case 21:
			AM->amalMoveInit(CHAN, 0, -400, 20);
		case 22:
			AM->amalMoveRun(CHAN, 22, 23);
			break;
		case 23:
			AM->amalMoveInit(CHAN, 280, 0, 20);
		case 24:
			AM->amalMoveRun(CHAN, 24, 25);
			break;
		case 25:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 26:
			AM->amalMoveRun(CHAN, 26, 27);
			break;
		case 27:
			AM->amalMoveInit(CHAN, 0, -200, 20);
		case 28:
			AM->amalMoveRun(CHAN, 28, 29);
			break;
		case 29:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 30:
			AM->amalMoveRun(CHAN, 30, 31);
			break;
		case 31:
			// Jump (Goto) Label 7
			AM->amalJump(CHAN, 11);
			break;
		}
		if (AM->PROGPOINTER[CHAN] >= 32)
			AM->amalEnd(CHAN);
}

void AmalPrograms::amal12(int CHAN)
{
		while(AM->PROGNOTFINISHED[CHAN] && !AM->PAUSED) switch(AM->PROGPOINTER[CHAN])
		{
		case 0:
			AM->amalSetX(CHAN, 10);
		case 1:
			AM->amalSetY(CHAN, 10);
		case 2:
			AM->amalSetA(CHAN, (AM->rnd(1) * 2));
		case 5:
			AM->amalSetA(CHAN, (AM->SPECIAL[CHAN][2] + 6));
		case 7:
			AM->amalSetLocal(CHAN, 0, AM->rnd(120));
		case 9:
			// For R0-R9 (local)
			if (forrepeat) {
				forrepeat = false;
				if ( AM->amalGetLocal(CHAN, 1) < AM->LOCAL[CHAN][0] ) {
					AM->amalIncLocal(CHAN, 1);
					AM->amalPause(CHAN, 10);
				} else
					AM->amalJump(CHAN, 11);
				break;
			} else
				AM->amalSetLocal(CHAN, 1, 0);
		case 10:
			// Next
			forrepeat = true;
			AM->amalJump(CHAN, 9);
			break;
		case 11:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 12:
			AM->amalMoveRun(CHAN, 12, 13);
			break;
		case 13:
			AM->amalMoveInit(CHAN, 280, -200, 20);
		case 14:
			AM->amalMoveRun(CHAN, 14, 15);
			break;
		case 15:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 16:
			AM->amalMoveRun(CHAN, 16, 17);
			break;
		case 17:
			AM->amalMoveInit(CHAN, 280, 200, 20);
		case 18:
			AM->amalMoveRun(CHAN, 18, 19);
			break;
		case 19:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 20:
			AM->amalMoveRun(CHAN, 20, 21);
			break;
		case 21:
			AM->amalMoveInit(CHAN, 0, -400, 20);
		case 22:
			AM->amalMoveRun(CHAN, 22, 23);
			break;
		case 23:
			AM->amalMoveInit(CHAN, 280, 0, 20);
		case 24:
			AM->amalMoveRun(CHAN, 24, 25);
			break;
		case 25:
			AM->amalMoveInit(CHAN, -280, 200, 20);
		case 26:
			AM->amalMoveRun(CHAN, 26, 27);
			break;
		case 27:
			AM->amalMoveInit(CHAN, 0, -200, 20);
		case 28:
			AM->amalMoveRun(CHAN, 28, 29);
			break;
		case 29:
			AM->amalMoveInit(CHAN, -280, 0, 20);
		case 30:
			AM->amalMoveRun(CHAN, 30, 31);
			break;
		case 31:
			// Jump (Goto) Label 7
			AM->amalJump(CHAN, 11);
			break;
		}
		if (AM->PROGPOINTER[CHAN] >= 32)
			AM->amalEnd(CHAN);
}

