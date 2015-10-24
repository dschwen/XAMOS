#include "AMALEnvGen.h"

AMALEnvGen::AMALEnvGen(AMOS_System* AMi)
{
	AM = AMi;

	// Initialise arrays here: (39)
	string commandstr[] = {"screen open", "screen display", "screen offset", "screen close",
    		"screen clone", "screen", "double buffer", "dual playfield", "dual priority", "load iff", "load",
    		"erase", "hide on", "update every", "flash off", "flash", "set rainbow", "rainbow del", "rainbow",
    		"bob off", "bob", "set bob", "sprite off", "sprite", "set sprite buffer", "set reg", "unpack",
    		"channel to sprite", "channel to bob", "channel to screen offset", "channel to screen size",
    		"channel to rainbow", "if screen", "if not screen", "if bank", "if not bank", "if reg", "channel to screen display", "bell"};

	// TODO - javaCommandStr[]
	string cppCommandstr[] = {"AM.screenOpen", "AM.screenDisplay", "AM.screenOffset",
	    	"AM.screenClose", "AM.screenClone", "AM.screen", "AM.doubleBuffer", "AM.dualPlayfield",
   	 	"AM.dualPriority", "AM.loadIff", "AM.load", "AM.erase", "AM.hideOn", "AM.updateEvery", "AM.flashOff",
  	  	"AM.flash", "AM.setRainbow", "AM.rainbowDel", "AM.rainbow", "AM.bobOff", "AM.bob", "AM.setBob",
  	  	"AM.spriteOff", "AM.sprite", "AM.setSpriteBuffer", "AM.setReg", "AM.unpack", "AM.channelToSprite",
	    	"AM.channelToBob", "AM.channelToScreenOffset", "AM.channelToScreenSize", "AM.channelToRainbow",
	    	"AM.isScreen", "AM.isNotScreen", "AM.isBank", "AM.isNotBank", "AM.isReg", "AM.channelToScreenDisplay", "AM.bell"};

	// TODO - cppCommandStr[]
	string javaCommandstr[] = {"AM->screenOpen", "AM->screenDisplay", "AM->screenOffset",
	    	"AM->screenClose", "AM->screenClone", "AM->screen", "AM->doubleBuffer", "AM->dualPlayfield",
   	 	"AM->dualPriority", "AM->loadIff", "AM->load", "AM->erase", "AM->hideOn", "AM->updateEvery", "AM->flashOff",
  	  	"AM->flash", "AM->setRainbow", "AM->rainbowDel", "AM->rainbow", "AM->bobOff", "AM->bob", "AM->setBob",
  	  	"AM->spriteOff", "AM->sprite", "AM->setSpriteBuffer", "AM->setReg", "AM->unpack", "AM->channelToSprite",
	    	"AM->channelToBob", "AM->channelToScreenOffset", "AM->channelToScreenSize", "AM->channelToRainbow",
	    	"AM->isScreen", "AM->isNotScreen", "AM->isBank", "AM->isNotBank", "AM->isReg", "AM->channelToScreenDisplay", "AM->bell"};

	commandlength = 39;


	command.clear();
	javaCommand.clear();
	cppCommand.clear();
	for (int n=0; n<commandlength; n++)
	{
		command.push_back(commandstr[n]);
		javaCommand.push_back(javaCommandstr[n]);
		cppCommand.push_back(cppCommandstr[n]);
	}

}

int AMALEnvGen::checkcommand(string inputline)
{
		for (int c=0; c<commandlength; c++)
			if (inputline.length() >= command[c].length())
				if (AM->lower(inputline.substr(0, command[c].length())) == command[c])
					return c;
		return -1;
}

Mytype AMALEnvGen::parsearg(string input) // Object???
{
	Mytype out;
	out.t = 0;

	//cout << "DEBUG: AMALEnvGen: Running =parsearg(" << input << ")";
	//int intarg = 0;
	string stringarg = "";

	if ((input == "")) // || (input.length()<2))
	{
		out.d=0;
		//return out; // Removed - C++ // was return 0 in Java
	}
	else if (input.length() < 2)
	{
		out.d = AM->val(input);
	}
	else if ((input.length()>=2) && (input[0] == '\"') && (input[input.length()-1] == '\"'))
	{
		out.t=1;
		out.s=input.substr(1, input.length() - 2); // was -1 (Java) // was -2
	}
	else if (AM->lower(input) == "lowres")
		out.d=0;
	else if (AM->lower(input) == "hires")
		out.d=0x8000;
	else if (AM->lower(input) == "laced")
		out.d=4;
	else if (AM->lower(input) == "hires+laced")
		out.d=0x8004;
	else if (AM->lower(input) == "laced+hires")
		out.d=0x8004;
	else
		out.d = AM->val(input);

	//out.d=-1; // Removed - C++

	return out;
}

void AMALEnvGen::processline(string input)
{
	// Note: Empty lines are already tested for earlier.

	// Strip any spaces or tabs:
	while (input.substr(0, 1)==" ") // || input.substr(0, 1)=="")
		input = input.substr(1, input.length()-1);

	// Ignore comments (TO DO - convert to save to Java)		
	if (input.substr(0, 1)=="'" || AM->lower(input.substr(0, 3))=="rem")
		return;

	int commandnum = checkcommand(input);
	// cout << "checkcommand result: " << commandnum << " - " << command[commandnum];

	string lineargs = "";
	if (commandnum >= 0)
		if (input.length() > command[commandnum].length())
			lineargs = input.substr(command[commandnum].length(), input.length() - command[commandnum].length());

	// Strip any spaces or tabs:
	if (lineargs.length() > 0)
		while ((lineargs.length() > 0) && (lineargs.substr(0, 1) == " ")) // || lineargs.substr(0, 1) == "")
			lineargs = lineargs.substr(1, lineargs.length() - 1);
		
	//if (lineargs.length() > 0)
	//	cout << "arguments line: " << lineargs;

	// Split them up by comma, maximum 10:
	//string linearg[] = new string[10]; // CPP uses vector instead...
	vector<string> linearg;
	int numargs = 0;

	// Check number of commas
	string argchop = lineargs;
	int comma;
	comma = argchop.find(',', 0);
	while (comma >= 0)
	{
		linearg.push_back(argchop.substr(0, comma));
		if ((argchop.length() - comma - 1) > 0)
			argchop = argchop.substr(comma + 1, argchop.length() - comma - 1);
		else
			argchop == "";

		//cout << "Debug: argchop = " << argchop;
		numargs++;

		if (argchop != "")
			comma = argchop.find(',', 0);
		else
			comma = -1;
	}
	linearg.push_back(argchop);
	numargs++;

	if (lineargs == "")
	{
		numargs = 0;
	}
	else
	{
		// Strip any initial spaces off arguments here:
		for (int a=0; a < numargs; a++)
			if (linearg[a].length() > 0)
				while ((linearg[a].length() > 0) && (linearg[a][0] == ' '))
					linearg[a]=linearg[a].substr(1, linearg[a].length() - 1);

		// Strip any trailing spaces:
		for (int a=0; a < numargs; a++)
			if (linearg[a].length() > 0)
				while ((linearg[a].length() > 0) && (linearg[a][linearg[a].length() - 1] == ' '))
					linearg[a]=linearg[a].substr(0, linearg[a].length() - 1);
	}

	// Create the new vector for the line:
	vector<Mytype> newline; // = new vector<Mytype>();

	Mytype newentry;
	newentry.t = 0;
	newentry.d = commandnum;

	newline.push_back(newentry);

	// Check and convert argument types here:
	for (int c=0; c<numargs; c++)
		newline.push_back(parsearg(linearg[c]));

	// Insert the new line into the envScript vector:
	envScript.push_back(newline);
}

// TODO:
void AMALEnvGen::processcode(string input)
{
	// TO DO: Need to remove comments intelligently first to allow for : in comment...

	string input2;
	//input2 = input.replaceAll(":", "\n");

	// Added - character replace routine:
	for (unsigned int n=0; n<input.length(); n++)
		if (input[n] == ':')
			input[n] = '\n';

	vector<string> lines;
	//lines = input2.split("\\r?\\n");

	// Added - string split routine:
	char* split;
	string split2;
	split = strtok((char*)input.c_str(), "\n");
	while (split != NULL)
	{
		// For DOS/Windows format "\r\n" endline, remove the trailing \r:
		int len = strlen(split);
		if (split[len - 1] == '\r')
			split[len - 1] = (char)0;

		split2 = string(split);
		lines.push_back(split2);
		split = strtok(NULL, "\n");
	}

	for (unsigned int a=0; a<envScript.size(); a++)
		envScript[a].clear();

	envScript.clear();

	for (unsigned int a=0; a<lines.size(); a++)
	{
		if(!(lines[a] == ""))
			processline(lines[a]);
	}
}

void AMALEnvGen::dump()
{
	vector<Mytype> newline;

	for (unsigned int a=0; a<envScript.size(); a++)
	{
		// Type safety needs fixing!
		newline = ((vector<Mytype>)(envScript[a]));

		cout << "checkcommand result: " << AM->str(newline[0].d) << " - " << command[(int)newline[1].d];
		if (newline.size() > 1)
			cout << "Number of arguments: " << (newline.size() - 1);
		for (unsigned int c=1; c<=(newline.size() - 1); c++)
			if (newline[c].t == 0)
				cout << "Argument #" << c << ": *" << AM->stri(newline[c].d) << "*";
			else
				cout << "Argument #" << c << ": *" << newline[c].s << "*";
	}
}

string AMALEnvGen::outputCPP()
{
	string output = "void environment()\n{\n";
	vector<Mytype> line;

	for (unsigned int a=0; a<envScript.size(); a++)
	{
		// Type safety fixed here:
		line = (vector<Mytype>) envScript[a];

		// Exclude special cases: 37 = channelToScreenDisplay, 38=Bell (added):
		if ((line[0].d >= 32) && (line[0].d != 37) && (line[0].d != 38))
			output += "	if (";
		else
			output += "	";

		output += cppCommand[(int)line[0].d] + "(";

		// To do - support string output below:
		for (unsigned int c=1; c <=(line.size() - 1); c++)
		{
			// If using Load Iff or Load, allow strings:
			if ((((line[0].d == 9)
					|| (line[0].d == 10))
					&& (c == 1))
			// For Set Rainbow strings:
					|| ((line[0].d == 16 )
						&& ((c == 4) || (c == 5) || (c == 6))) )
				output += "\"" + line[c].s + "\"";
			else
				//if (line[c] != NULL)
				output += AM->stri(line[c].d);

			if ( c <= (line.size() - 2))
				output += ", ";
		}

		// Exclude special case: 37 = channelToScreenDisplay:
		if ((line[0].d >= 32) && (line[0].d < 37))
			output += "))\n	";
		else
			output += ");\n";
	}

	output += "}\n";
	return output;
}

string AMALEnvGen::outputJava()
{
	string output = "	public void environment()\n	{\n";
	vector<Mytype> line;

	for (unsigned int a=0; a<envScript.size(); a++)
	{
		// Type safety fixed here:
		line = (vector<Mytype>) envScript[a];

		// Exclude special cases: 37 = channelToScreenDisplay, 38=Bell (added):
		if ((line[0].d >= 32) && (line[0].d != 37) && (line[0].d != 38))
			output += "		if (";
		else
			output += "		";

		output += javaCommand[(int)line[0].d] + "(";

		// To do - support string output below:
		for (unsigned int c=1; c <=(line.size() - 1); c++)
		{
			// If using Load Iff or Load, allow strings:
			if ((((line[0].d == 9)
					|| (line[0].d == 10))
					&& (c == 1))
			// For Set Rainbow strings:
					|| ((line[0].d == 16 )
						&& ((c == 4) || (c == 5) || (c == 6))) )
				output += "\"" + line[c].s + "\"";
			else
				//if (line[c] != NULL)
				output += AM->stri(line[c].d);

			if ( c <= (line.size() - 2))
				output += ", ";
		}

		// Exclude special case: 37 = channelToScreenDisplay:
		if ((line[0].d >= 32) && (line[0].d < 37))
			output += "))\n	";
		else
			output += ");\n";
	}

	output += "	}\n";
	return output;
}

int AMALEnvGen::interpretEnvGen()
{
	vector<Mytype> line;
	//cout << "DEBUG: Running interpretEnvGen(): envScript.size() == " << AM->stri(envScript.size()) << endl;
	for (unsigned int a=0; a<envScript.size(); a++)
	{
		// Type safety needs fixing here:
		line = (vector<Mytype>)(envScript[a]);
		
		//cout << "DEBUG: interpretEnvGen() line=" << AM->stri(a) << ", command=" << AM->stri((int)line[0].d) << endl; // debug
		//cout << "DEBUG: line.size() == " << AM->stri(line.size()) << endl;		
		// Get args for each:
		switch ((int)line[0].d)
		{
			case 0:
				//cout << "DEBUG: Trying screenOpen(" 
				//<< AM->stri((int)line[1].d) << ", " << AM->stri((int)line[2].d) << ", "
				//<< AM->stri((int)line[3].d) << ", " << AM->stri((int)line[4].d) << ", "
				//<< AM->stri((int)line[5].d) <<  ") from EnvGen" << endl;

				AM->screenOpen(line[1].d, line[2].d, line[3].d, line[4].d, line[5].d);
				//cout << "DEBUG: Tried screenOpen from EnvGen" << endl;
			break;
			case 1:
				AM->screenDisplay(line[1].d, line[2].d, line[3].d);
			break;
			case 2:
				AM->screenOffset(line[1].d, line[2].d, line[3].d);
			break;
			case 3:
				AM->screenClose();
			break;
			case 4:
				AM->screenClone(line[1].d);
			break;
			case 5:
				AM->screen(line[1].d);
			break;
			case 6:
				AM->doubleBuffer();
			break;
			case 7:
				AM->dualPlayfield(line[1].d, line[2].d);
			break;
			case 8:
				AM->dualPriority(line[1].d, line[2].d);
			break;
			case 9:
				AM->loadIff(line[1].s, line[2].d);
			break;
			case 10:
				AM->load(line[1].s, line[2].d);
			break;
			case 11:
				AM->erase(line[1].d);
			break;
			case 12:
				AM->hideOn();
			break;
			case 13:
				AM->updateEvery(line[1].d);
			break;
			case 14:
				AM->flashOff();
			break;
			case 15:
				AM->flash(line[1].d, line[2].s);
			break;
			case 16:
				AM->setRainbow((int)line[1].d, (int)line[2].d, (int)line[3].d, line[4].s, line[5].s, line[6].s);
			break;
			case 17:
				AM->rainbowDel();
			break;
			case 18:
				AM->rainbow(line[1].d, line[2].d, line[3].d, line[4].d);
			break;
			case 19:
				AM->bobOff();
			break;
			case 20:
				AM->bob(line[1].d, line[2].d, line[3].d, line[4].d);
			break;
			case 21:
				AM->setBob(line[1].d, line[2].d, line[3].d, line[4].d);
			break;
			case 22:
				AM->spriteOff();
			break;
			case 23:
				AM->sprite(line[1].d, line[2].d, line[3].d, line[4].d);
			break;
			case 24:
				AM->setSpriteBuffer(line[1].d);
			break;
			case 25:
				AM->setReg(line[1].d, line[2].d);
			break;
			case 26:
				AM->unpack(line[1].d, line[2].d);
			break;
			case 27:
				AM->channelToSprite(line[1].d, line[2].d);
			break;
			case 28:
				AM->channelToBob(line[1].d, line[2].d);
			break;
			case 29:
				AM->channelToScreenOffset(line[1].d, line[2].d);
			break;
			case 30:
				AM->channelToScreenSize(line[1].d, line[2].d);
			break;
			case 31:
				AM->channelToRainbow(line[1].d, line[2].d);
			break;
			case 32:
				if (AM->isScreen(line[1].d))
					a++;
			break;
			case 33:
				if (AM->isNotScreen(line[1].d))
					a++;
			break;
			case 34:
				if (AM->isBank(line[1].d))
					a++;
			break;
			case 35:
				if (AM->isNotBank(line[1].d))
					a++;
			break;
			case 36:
				if (AM->isReg(line[1].d, line[2].d))
					a++;
			break;
			case 37:
				AM->channelToScreenDisplay(line[1].d, line[2].d);
			break;
			case 38:
				AM->bell();
			break;
			default:
			break;
		}
	}

	return 0;
}

void AMALEnvGen::mymain()
{
	//string input = "    Screen open   0 , 320  , 256   , 16   , hires         \n";
	//input += "Screen 0 : Double Buffer : Bob Off \n";
	//input += "If Reg 1, 0 : Screen 0";
	
	AMALEnvGen* envgen = new AMALEnvGen(new AMOS_System());
	
	string input = "bob 1,100,100,1 : bob 2,100,150,1 : bob 3,100,250,1";

	// Lex the environment string:
	envgen->processcode(input);

	// Now dump the vector contents:
	//dump();
	cout << envgen->outputJava() << endl;
}

