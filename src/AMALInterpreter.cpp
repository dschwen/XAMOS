///////////////////////////////////////////////////////////
// AMOS AMAL -> C++ Interpreter
// By Stephen Harvey-Brooks - Mequa Innovations
///////////////////////////////////////////////////////////

#include "AMALInterpreter.h"


// The following functions form the AMAL Interpreter:

// Constructor function:
AMALInterpreter::AMALInterpreter(AMOS_System* AMi)
{
	AM = AMi;
}

void AMALInterpreter::interpret()
{
	int FF;
	double TempX;
	double TempY;

	//cout << "Running interpret()\n";

	switch ( AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][0] )
	{
	case 0:
		// Pause

		AM->PROGPOINTER[AM->CHAN]++;
		AM->PAUSED=true;

		// cout << "Pause found!!!\n";

		break;
	case 1:
		// For

		// c=0 -> global(d)=b
		// c=1 -> local(d)=b
		FETCHARGUMENTS(2);
		if ( AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]==0 )
		{
			AM->myGLOBAL[AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][4]]=AM->ARG[AM->CHAN][2];
		}
		else if ( AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]==1 )
		{
			AM->LOCAL[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][4]]=AM->ARG[AM->CHAN][2];
		}
		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 2:
		// Next

		// Memorise the current line number:
		AM->OLDPROGPOINTER=AM->PROGPOINTER[AM->CHAN];
		// Find LINE number of matching 'for':
		FF=AM->INSTRLINENUM[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]];

		// Skip back to the 'for' to get the parameters:
		AM->PROGPOINTER[AM->CHAN]=FF;
		FETCHARGUMENTS(1);

		// Check the index register's value:
		switch ( AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3] )
		{
		case 0:
			// Global index (RA->RZ)
			// Is the index less than the target value?
			if ( AM->myGLOBAL[AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][4]]<AM->ARG[AM->CHAN][1] )
			{
				// As for Pause:
				AM->PAUSED=true;
				// Add 1 to the index:
				AM->myGLOBAL[AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][4]]++;
				// Jump straight after the 'for':
				AM->PROGPOINTER[AM->CHAN]++;
			}
			else
			{
				// Index has reached target, so continue after the 'Next':
				AM->PROGPOINTER[AM->CHAN]=AM->OLDPROGPOINTER+1;
			}
			break;
		case 1:
			// Local index (R0->R9)
			// Is the index less than the target value?
			if ( AM->LOCAL[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][4]]<AM->ARG[AM->CHAN][1] )
			{
				// As for Pause:
				AM->PAUSED=true;
				// Add 1 to the index:
				AM->LOCAL[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][4]]++;
				// Jump straight after the 'for':
				AM->PROGPOINTER[AM->CHAN]++;
			}
			else
			{
				// Index has reached target, so continue after the 'Next':
				AM->PROGPOINTER[AM->CHAN]=AM->OLDPROGPOINTER+1;
			}
		}

		break;
	case 3:
		// Let
		// b=0 -> global(c)=a
		// b=1 -> local(c)=a
		// b=2 -> special(c)=a

		//cout << "Let found!!!\n";

		FETCHARGUMENTS(1);
		if ( AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][2]==0 )
		{
			AM->myGLOBAL[AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]]=AM->ARG[AM->CHAN][1];
		}
		else if ( AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][2]==1 )
		{
			AM->LOCAL[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]]=AM->ARG[AM->CHAN][1];
		}
		else if ( AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][2]==2 )
		{
			AM->SPECIAL[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]]=AM->ARG[AM->CHAN][1];
		}
		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 4:
		// Jump (Goto)

		if ( AM->LABELS[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][1]]==0 )
		{
			AM->PROGPOINTER[AM->CHAN]=0;
		}
		else
		{
			AM->PROGPOINTER[AM->CHAN]=AM->INSTRLINENUM[AM->CHAN][AM->LABELS[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][1]]-1]+1;
		}

		break;
	case 5:
		// If ...

		FETCHARGUMENTS(1);
		if ( (AM->ARG[AM->CHAN][1]) != 0 )
		{
			// If Test is true, run next line (Jump L/Direct L/eXit):
			AM->PROGPOINTER[AM->CHAN]++;
		}
		else
		{
			// If Test is not true, skip the next line:
			AM->PROGPOINTER[AM->CHAN]+=2;
		}

		break;
	case 6:
		// Move (initialize)

		FETCHARGUMENTS(3);
		AM->SPECIAL[AM->CHAN][3]=AM->ARG[AM->CHAN][1]; AM->SPECIAL[AM->CHAN][4]=AM->ARG[AM->CHAN][2];
		AM->SPECIAL[AM->CHAN][5]=AM->ARG[AM->CHAN][3];
		if ( AM->SPECIAL[AM->CHAN][5]==0 ) { AM->SPECIAL[AM->CHAN][5]=1; } // Fix this...
		// Counter:
		AM->SPECIAL[AM->CHAN][6]=1;
		// Record positions for X and Y...
		//AM->SPECIAL[AM->CHAN][7]=AM->SPECIAL[AM->CHAN][0]; AM->SPECIAL[AM->CHAN][8]=AM->SPECIAL[AM->CHAN][1];

		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 7:
		// Move (run)

		// Interpolate the position:
		TempX=(((AM->SPECIAL[AM->CHAN][6]-1)*AM->SPECIAL[AM->CHAN][3])/AM->SPECIAL[AM->CHAN][5]);
		TempY=(((AM->SPECIAL[AM->CHAN][6]-1)*AM->SPECIAL[AM->CHAN][4])/AM->SPECIAL[AM->CHAN][5]);
		AM->SPECIAL[AM->CHAN][0]+=((AM->SPECIAL[AM->CHAN][6]*AM->SPECIAL[AM->CHAN][3])/AM->SPECIAL[AM->CHAN][5])-TempX;
		AM->SPECIAL[AM->CHAN][1]+=((AM->SPECIAL[AM->CHAN][6]*AM->SPECIAL[AM->CHAN][4])/AM->SPECIAL[AM->CHAN][5])-TempY;

		// As for Pause:
		AM->PAUSED=true;

		if ( AM->SPECIAL[AM->CHAN][6]<AM->SPECIAL[AM->CHAN][5] )
		{
			AM->SPECIAL[AM->CHAN][6]++; // Increase the Counter...
			// Don't move to next instruction yet...
		}
		else
		{
			AM->PROGPOINTER[AM->CHAN]++; // End of Move...
		}

		break;
	case 8:
		// Direct
		// As for Jump...

		AM->RUNNINGAUTOTEST[AM->CHAN]=false; // Leave Autotest...
		if ( AM->LABELS[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][1]]==0 )
		{
			AM->PROGPOINTER[AM->CHAN]=0;
		}
		else
		{
			AM->PROGPOINTER[AM->CHAN]=AM->INSTRLINENUM[AM->CHAN][AM->LABELS[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][1]]-1]+1;
		}

		break;
	case 9:
		// End
		// Skip to end of program:
		AM->PROGPOINTER[AM->CHAN]=AM->NUMLINES[AM->CHAN];

		break;
	case 10:
		// eXit
		// Re-enter the main program again, at the original departure point:
		AM->RUNNINGAUTOTEST[AM->CHAN]=false; // Leave Autotest...
		if ( AM->MAINPROGDEPPOINT[AM->CHAN]>=0 )
		{
			AM->PROGPOINTER[AM->CHAN]=AM->MAINPROGDEPPOINT[AM->CHAN];
		}
		else
		{
			// Jump to end of Autotest:
			AM->PROGPOINTER[AM->CHAN]=AM->INSTRLINENUM[AM->CHAN][AM->COMMAND[AM->CHAN][AM->AUTOTESTSTART[AM->CHAN]][1]-1]+2; // +1+1
		}

		break;
	case 11:
		// On
		// Re-enter the main program again, after the original departure point:
		AM->RUNNINGAUTOTEST[AM->CHAN]=false; // Leave Autotest...
		if ( AM->MAINPROGDEPPOINT[AM->CHAN]>=0 )
		{
			AM->PROGPOINTER[AM->CHAN]=AM->MAINPROGDEPPOINT[AM->CHAN]+1;
		}
		else
		{
			// Jump to end of Autotest:
			AM->PROGPOINTER[AM->CHAN]=AM->INSTRLINENUM[AM->CHAN][AM->COMMAND[AM->CHAN][AM->AUTOTESTSTART[AM->CHAN]][1]-1]+1+1;
		}

		break;
	case 12:
		// Wait
		// As for Pause, but don't move to next instruction:
		AM->PAUSED=true;

		break;
	case 13:
		// Anim (initialization)
		FETCHARGUMENTS(AM->NUMARGS[AM->CHAN][AM->PROGPOINTER[AM->CHAN]]);

		// Current frame number (0 = no animation)
		AM->SPECIAL[AM->CHAN][10]=1;
		// Number of frames (i.e. brackets)
		AM->SPECIAL[AM->CHAN][11]=(AM->NUMARGS[AM->CHAN][AM->PROGPOINTER[AM->CHAN]]-1)/2;
		// Timer for current frame (VBLs)...
		AM->SPECIAL[AM->CHAN][12]=1;

		// Copy the arguments into the special registers...
		for ( int T=1; T<= AM->NUMARGS[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])]; T++ )
		{
			AM->SPECIAL[AM->CHAN][T+12]=AM->ARG[AM->CHAN][T];
		}

		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 15:
		// PLay
		// TO DO....
		FETCHARGUMENTS(1);
		AM->amalPLay(AM->CHAN, AM->ARG[AM->CHAN][1]);
		AM->PROGPOINTER[AM->CHAN]++;

		// AMAL Operators:

		break;
	case 16:
		// Add +
		// temp(c)=a+b

		FETCHARGUMENTS(2);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]]=AM->ARG[AM->CHAN][1]+AM->ARG[AM->CHAN][2];
		AM->PROGPOINTER[AM->CHAN]++;
		break;
	case 17:
		// Subtract -
		// temp(c)=a-b

		FETCHARGUMENTS(2);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]]=AM->ARG[AM->CHAN][1]-AM->ARG[AM->CHAN][2];
		AM->PROGPOINTER[AM->CHAN]++;
		break;
	case 18:
		// Multiply *
		// temp(c)=a*b

		FETCHARGUMENTS(2);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]]=AM->ARG[AM->CHAN][1]*AM->ARG[AM->CHAN][2];
		AM->PROGPOINTER[AM->CHAN]++;
		break;
	case 19:
		// Divide /
		// temp(c)=a/b

		FETCHARGUMENTS(2);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]]=AM->ARG[AM->CHAN][1]/AM->ARG[AM->CHAN][2];
		AM->PROGPOINTER[AM->CHAN]++;
		break;
	case 20:
		// Equals =
		// temp(c)=a=b

		FETCHARGUMENTS(2);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]]=AM->booltoint(AM->ARG[AM->CHAN][1]==AM->ARG[AM->CHAN][2]);
		AM->PROGPOINTER[AM->CHAN]++;
		break;
	case 21:
		// Greater than >
		// temp(c)=a>b

		FETCHARGUMENTS(2);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]]=AM->booltoint(AM->ARG[AM->CHAN][1]>AM->ARG[AM->CHAN][2]);
		AM->PROGPOINTER[AM->CHAN]++;
		break;
	case 22:
		// Less than <
		// temp(c)=a<b

		FETCHARGUMENTS(2);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]]=AM->booltoint(AM->ARG[AM->CHAN][1]<AM->ARG[AM->CHAN][2]);
		AM->PROGPOINTER[AM->CHAN]++;
		break;
	case 23:
		// Not equal <>
		// temp(c)=a<>b

		FETCHARGUMENTS(2);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]]=AM->booltoint(AM->ARG[AM->CHAN][1]!=AM->ARG[AM->CHAN][2]);
		AM->PROGPOINTER[AM->CHAN]++;
		break;
	case 24:
		// And &
		// temp(c)=a AND b

		FETCHARGUMENTS(2);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]]=(AM->ARG[AM->CHAN][1] & AM->ARG[AM->CHAN][2]);
		AM->PROGPOINTER[AM->CHAN]++;
		break;
	case 25:
		// Or |
		// temp(c)=a OR b

		FETCHARGUMENTS(2);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]]=(AM->ARG[AM->CHAN][1] | AM->ARG[AM->CHAN][2]);
		AM->PROGPOINTER[AM->CHAN]++;
		break;


		// AMAL Functions:

	case 26:
		// XMouse
		// temp(a)=XMouse

		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][1]]=AM->xMouse();
		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 27:
		// YMouse
		// temp(a)=YMouse

		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][1]]=AM->yMouse();
		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 28:
		// J0
		// temp(a)=J0

		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][1]]=AM->joy(0);
		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 29:
		// J1
		// temp(a)=J1

		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][1]]=AM->joy(1);
		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 30:
		// K1
		// temp(a)=K1

		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][1]]=AM->booltoint((AM->mouseKey() & 1) != 0);
		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 31:
		// K2
		// temp(a)=K2

		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][1]]=AM->booltoint((AM->mouseKey() & 2) != 0);
		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 32:
		// XScreen()
		// temp(c)=XScreen(a,b)

		FETCHARGUMENTS(2);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]]=AM->xScreen(AM->ARG[AM->CHAN][1],AM->ARG[AM->CHAN][2]);
		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 33:
		// YScreen()
		// temp(c)=YScreen(a,b)

		FETCHARGUMENTS(2);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]]=AM->yScreen(AM->ARG[AM->CHAN][1],AM->ARG[AM->CHAN][2]);
		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 34:
		// XHard()
		// temp(c)=XHard(a,b)

		FETCHARGUMENTS(2);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]]=AM->xHard(AM->ARG[AM->CHAN][1],AM->ARG[AM->CHAN][2]);
		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 35:
		// YHard
		// temp(c)=YHard(a,b)

		FETCHARGUMENTS(2);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][3]]=AM->yHard(AM->ARG[AM->CHAN][1],AM->ARG[AM->CHAN][2]);
		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 36:
		// BobCol
		// temp(d)=BobCol(a,b,c)

		FETCHARGUMENTS(3);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][4]]=AM->bobCol(AM->ARG[AM->CHAN][1],AM->ARG[AM->CHAN][2] , AM->ARG[AM->CHAN][3]);
		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 37:
		// SpriteCol
		// temp(d)=SpriteCol(a,b,c)

		FETCHARGUMENTS(3);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][4]]=AM->spriteCol(AM->ARG[AM->CHAN][1],AM->ARG[AM->CHAN][2] , AM->ARG[AM->CHAN][3]);
		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 38:
		// VUmeter
		// temp(b)=VUmeter(a)

		FETCHARGUMENTS(1);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][2]]=AM->vumeter(AM->ARG[AM->CHAN][1]);
		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 39:
		// Col
		// temp(b)=Col(a)

		FETCHARGUMENTS(1);
		AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][2]]=AM->col(AM->ARG[AM->CHAN][1]);
		AM->PROGPOINTER[AM->CHAN]++;

		break;
	case 40:
		// Zandom
		// temp(b)=Zandom(a)

		if (AM->ARGTYPE[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1] >= 0)
		{
			FETCHARGUMENTS(1);

			//cout << "Z arg type: " << AM->ARGTYPE[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][1] << "\n";
			//cout << "Zandom out! " << AM->ARG[AM->CHAN][1];

			AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][2]]=AM->amalZnd(AM->ARG[AM->CHAN][1]);
		}
		else
		{
			//cout << "Empty Zandom out! \n";

			AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][2]]=AM->amalZnd(); //AM->rnd(65535)-32767;
		}
		AM->PROGPOINTER[AM->CHAN]++;
		break;


		// Other instructions:


	case 41:
		// AUtotest(
		// Argument 1 = instruction number for ')'

		// Record the start position of the Autotest
		AM->AUTOTESTSTART[AM->CHAN]=AM->PROGPOINTER[AM->CHAN];
		// Skip to end of Autotest:
		AM->PROGPOINTER[AM->CHAN]=AM->INSTRLINENUM[AM->CHAN][AM->COMMAND[AM->CHAN][AM->AUTOTESTSTART[AM->CHAN]][1]-1]+1+1;

		break;
	case 42:
		// ")" (End of Autotest)
		// As for eXit:

		// Re-enter the main program again, at the original departure point:
		AM->RUNNINGAUTOTEST[AM->CHAN]=false; // Leave Autotest...
		if ( AM->MAINPROGDEPPOINT[AM->CHAN]>=0 )
		{
			AM->PROGPOINTER[AM->CHAN]=AM->MAINPROGDEPPOINT[AM->CHAN];
		}
		else
		{
			// Jump to end of Autotest (next instruction in this case):
			AM->PROGPOINTER[AM->CHAN]++;
		}

		break;
	default:
		// Skip...
		AM->PROGPOINTER[AM->CHAN]++;
	}
}

void AMALInterpreter::FETCHARGUMENTS(int P1)
{
	for ( int PARNUM = 1; PARNUM <= P1; PARNUM++ )
	{
		switch ( AM->ARGTYPE[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])][PARNUM] )
		{
		case 0:
			// for constant values:
			AM->ARG[AM->CHAN][PARNUM]=AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][PARNUM];
			break;
		case 1:
			// for Global/External variables (RA-RZ, #0-25):
			AM->ARG[AM->CHAN][PARNUM]=AM->myGLOBAL[AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][PARNUM]];
			break;
		case 2:
			// for Local/Internal variables (R0-R9):
			AM->ARG[AM->CHAN][PARNUM]=AM->LOCAL[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][PARNUM]];
			break;
		case 3:
			// for Special registers (X,Y,A)
			AM->ARG[AM->CHAN][PARNUM]=AM->SPECIAL[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][PARNUM]];
			break;
		case 4:
			// for Temporary values:
			AM->ARG[AM->CHAN][PARNUM]=AM->TEMP[AM->CHAN][AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][PARNUM]];
		}
	}
}

// Debug:
void AMALInterpreter::DEBUG()
{
	cout << "(" << AM->PROGPOINTER[AM->CHAN] << ")  " << AM->commandlist[AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][0]] + "\n";
	if ( AM->NUMARGS[AM->CHAN][AM->PROGPOINTER[AM->CHAN]]>0 )
	{
		for ( int TT=1; TT<= AM->NUMARGS[AM->CHAN][AM->PROGPOINTER[AM->CHAN]]; TT++ )
		{
			cout << AM->argtypename[AM->ARGTYPE[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][TT]] << AM->COMMAND[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][TT];
			if ( TT<AM->NUMARGS[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])] )
				cout << ", ";
		}
	}
	cout << "\n";
	if ( AM->NUMSTRINGS[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])]>0 )
	{
		cout << "Strings:\n\n";
		for ( int TT=0; TT<= AM->NUMSTRINGS[AM->CHAN][AM->PROGPOINTER[AM->CHAN]]-1; TT++ )
		{
			cout << AM->strin[AM->CHAN][AM->PROGPOINTER[AM->CHAN]][TT];
			if ( TT<AM->NUMARGS[AM->CHAN][(AM->PROGPOINTER[AM->CHAN])] )
				cout << ", ";
		}
	}
	cout << "\n";
	//AM->WaitKey();
}

