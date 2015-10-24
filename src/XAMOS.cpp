/////////////////////////////////////////////////////////////////
// XAMOS - AMOS BASIC reimplemented!                           //
// (C) 2012 Mequa Innovations                                  //
/////////////////////////////////////////////////////////////////

#include "XAMOS.h"

int XAMOS::initGame(int argc, char* args[])
{
	runonly = 0;
	ntsc = 0;

	mthis = this;
	wrapper = new GameEngineWrapper(); //(this);
	am = new AMOS_System(); //(this);
	am->wrapper = wrapper;
	wrapper->AM = am;

	return startGame(argc, args);
}

string XAMOS::lower(string t1) { string t2=t1; std::transform(t2.begin(), t2.end(), t2.begin(), ::tolower); return t2; }

string XAMOS::processargs(int argc, char* args[])
{
	bool uselauncher;
	string filename;

	uselauncher=false;

	// OpenGL disabled by default for now (still experimental):
	wrapper->useopengl=false;
	wrapper->usenpot=false;

	filename="";

	for (int arg=1; arg<argc; arg++)
	{
		string strarg = string(args[arg]);
		
		// Set flags as appropriate:
		if (lower(strarg) == "-launcher")
			uselauncher = true;
		else if (lower(strarg) == "-useopengl")
			wrapper->useopengl = true;
		else if (lower(strarg) == "-usenpot")
			wrapper->usenpot = true;
		else if (filename == "")
			filename = strarg;
	}

	if (uselauncher)
		filename = consolelauncher();
	else if (filename == "")
		filename = "example/Default.xamos";

	if (filename == "")
	{
		wrapper->clean_up();
		exit(0);
	}

	return filename;
}

int XAMOS::startGame(int argc, char* args[])
{
	// On Win32 only - enable Command Prompt with SDL:
	wrapper->initsimpleconsole();

	string textline;
	//vector <string> textline;

	string filename;
	//cout << "Debug: initGame()" << endl;
	filename = processargs(argc, args);

	// Load the file here:
	textline = loadfiletotext(filename);
	////textline = loadfiletotext_old(filename);

	dumprawcode(textline); // Debug - dump raw code here

	// Removed - check for SDL - use stub methods if not enabled:
	//#ifdef USESDL
	wrapper->initsdlstuff();

	wrapper->initsdlaudio();
	//#endif

	numprograms = 0;

	am->translatedamalprograms = new AmalPrograms(am);

	// TO DO: Load Blank.jamos instead of Default.jamos if no resources found:
	//String filename = "amos/Blank.jamos";
	string runonlyfilename = "example/RunOnly.xamos";
	//string filename = "jamos/Default.jamos";

	// Added for jAMOS:
	editingamos = true;

	//vector<string> AMALCode; // = new String[256];

	// TODO - CPP:
	//bool usefile = false;

	// Removed - CPP:
	//AMALCode.push_back(""); AMALCode.push_back("Move 100,100,25;");

	//AMALCode.push_back("");

	// TODO - CPP:
	// First check if a RunOnly.jamos file is present, and if so load and disable the editor:
	//try {
	//AMALCode = loadfile(usefile, filename, AMALCode); //, mthis.getResourceAsStream(runonlyfilename));
	//runonly = true;
	//} catch (Exception e) { }

	AMALCode.clear();

	if (!runonly)
	{
		//try {

		//AMALCode = loadfiletotext_old(filename); //, mthis.getResourceAsStream(filename));
		AMALCode = loadfile(true, filename, AMALCode);

		//} catch (Exception e) { cout << "Error loading file " << filename << endl; }
	}

	// Removed - C++:
	//if (AMALCode.empty()) // == NULL)
	//	cout << "Error loading code string!" << endl;

	//cout << "DEBUG: Successfully loaded file " << filename << ", AMALCode.size() == " << am->stri(AMALCode.size()) << endl;

	numprograms = 0;
	inputstring = "";

	//if (AMALCode != null)
	for (unsigned int channel = 1; (channel < AMALCode.size()); channel++)
	{
		// C++ - test removed!
		//if (!(AMALCode[channel] == ""))
		//{
			//cout << "Attempting to initialise AMAL Channel " << am->stri(channel) << endl;
			am->amal(channel, AMALCode[channel]);
			inputstring += AMALCode[channel] + '\n';
		//}
		numprograms++;
	}
	//numprograms = AMALCode.size() - 1; // removed

	//setsplash(); // removed in C++

	//int t=0;
	//if (t == 0);
	////	AM->amalcompiler->AmalCompile(1, numprograms);

	wrapper->initspritesandbobs();

	// TODO - Pause here?

	// Moved:
	// Load the files:
	if( wrapper->load_files() == false )
	{
		return 1;
	}

	// Debug:
	// Initialise the screen here (TODO) - moved:
	wrapper->initScreen();

	// Set the default AMAL Environment Generator code - removed:
	//environmentCode = defaultEnvGenString();

	// Add some sprites:
	// New - because of EnvGen, only add sprites we need
	// TO DO - improve this:

	//cout << "DEBUG: numprograms = " << am->stri(numprograms) << endl;
	for (int pp = 1; pp <= numprograms; pp++)
	{
		//cout << "DEBUG: AMALCode[" << am->stri(pp) << "] == \"" << string(AMALCode[pp]) << "\"" << endl;
		////cout << "DEBUG - am->sprite(" << am->stri(pp) << ", (720)/2 - 30, (576)/2 - 40, 1)" << endl;

		// TODO - fix this!
		// New: Only create sprite if doesn't already exist:
		if (1) // 1 // TRUE
			am->sprite(pp, (720)/2 - 30, (576)/2 - 40, 1);

		////cout << "DEBUG - am->amalOn(" << am->stri(pp) << ")" << endl;
		am->amalOn(pp);
	}
	// AM->amalOn(); // To fix!
	for (int pp = 1; pp <= numprograms; pp++)
		am->channelToSprite(pp, pp);

	// Added: Reset the screen position (TO DO)
	am->screenDisplay(0,0,0);
	am->screenOffset(0,0,0);

	// Lex the environment string:
	// Debug - if environment buffer is null:
	//if (environmentCode == "")
	//	cout << "Empty AMAL environment string!" << endl;
	am->envGen->processcode(environmentCode); // moved

	//cout << "DEBUG: Testing EnvGen:" << endl << environmentCode << endl;
	// Interpret and run the environment string (MOVED):
	am->envGen->interpretEnvGen();
	//cout << "DEBUG: Tested EnvGen" << endl;

	// MequaScript: Tokenise the instructions:
	//am->parser->lexString(amosCode); // moved
	////demoinit(textline);


	//// Create editor window here:
	//if (!runonly)
	//	createtextpane();

	// Dump the tokens here (to console and/or file):
	demodump();

	cout << endl;

	// Added - display compiled AMAL channels here and debug info:
  	am->amalcompiler->AmalCompile(1, numprograms, true); // Added: true for C++, false for Java

	// TODO: AMAL compiler debug crashes!
       	//am->amalcompiler->DEBUG();

	cout << endl << "Now running the program:" << endl;

	// Run the XAMOS program here:
	wrapper->demotest();

        // Clean up
        wrapper->clean_up();

	return 0;
}
void XAMOS::demodump()
{
	// Once tokenisation is complete - dump the output:
	am->dumper->dumpoutput(&am->g->mytokens);

	// Dump alternative output to file (needs debugging):
	am->dumper->dumpoutputtofile(&am->g->mytokens, "dump.txt");
}

void XAMOS::demoinit(vector<string> textline)
{
	am->parser->inittokens(&am->g->mytokens, 0, "Master");

	// Load the instruction and function names:
	am->parser->initinstructions();
	// Tokenise the instructions:
	am->parser->evaluateinstructions(textline);

	// For each brain, initialise an object (in myvalues[n]), and set its brain number to the object number (only in this demo):
	for (unsigned int n=0; n<am->g->mytokens.size(); n++)
	{
		ActiveObject *temp = new ActiveObject();
		temp->ObjectBrain = n;
		am->g->ActiveObjects.push_back(temp);
	}

	// Now initialise the variables of each object:
	for (unsigned int n=0; n<am->g->mytokens.size(); n++)
		am->interpreter->initvalues(&am->g->mytokens, n);
}

void XAMOS::dumprawcode(string textline)
{
	// Display raw code:
	cout << "- The raw code:" << endl;
	cout << textline << endl;
	cout << endl << endl;
}

void XAMOS::dumprawcode_old(vector<string> textline)
{
	// Display raw code:
	cout << "- The raw code:" << endl;
	for (unsigned int n=0; n<textline.size(); n++)
		cout << textline[n] << endl;
	cout << endl << endl;
}

// Create default AMAL Environment Generator string here:
string XAMOS::defaultEnvGenString()
{
	//string out = "";
	//return out;

	// Added: Create default Environment string: 
	string out;

	// TODO - debug issues with default environment string.
#if 1
	out = "' AMAL Environment Generator\n";
	out += "Bob Off : Sprite Off : Rainbow Del\nScreen 0\n";
	out += "Screen Open 0,720,576,16777216,Hires+Laced\n";
	out += "Load \"resources/sprites\", 1\n";
	out += "Load Iff \"resources/back.jpg\", 0\n";
	return out;
#else
	out = "' AMAL Environment Generator\n";
	return out;
#endif
}

string XAMOS::loadfiletotext(string filename)
{
	string textline = "";
	// File open:
	FILE *fp;
	char* fgetstr;
	char filstr[505]; //char* filstr = new char[505];
	filstr[0] = 0;

	// D:/
	if ((fp=fopen(filename.c_str(), "r")) == NULL)
		exit(1);
	fgetstr=fgets(filstr, 500, fp);

	while(!feof(fp) && !(fgetstr == NULL))
	{
		// Kill any new lines:
		if (filstr[strlen(filstr)-1] == '\n')
			filstr[strlen(filstr)-1] = 0;
		if (filstr[strlen(filstr)-1] == '\r')
			filstr[strlen(filstr)-1] = 0;
		// Copy the string to the vector:
		textline += string(filstr) + '\n';
		fgetstr=fgets(filstr, 500, fp);
	}

	return textline;
}
vector <string> XAMOS::loadfiletotext_old(string filename)
{
	vector <string> textline;
	// File open:
	FILE *fp;
	char* fgetstr;
	char filstr[505]; //char* filstr = new char[505];
	filstr[0] = 0;

	// D:/
	if ((fp=fopen(filename.c_str(), "r")) == NULL)
		exit(1);
	fgetstr=fgets(filstr, 500, fp);

	while(!feof(fp) && !(fgetstr == NULL))
	{
		// Kill any new lines:
		if (filstr[strlen(filstr)-1] == '\n')
			filstr[strlen(filstr)-1] = 0;
		if (filstr[strlen(filstr)-1] == '\r')
			filstr[strlen(filstr)-1] = 0;
		// Copy the string to the vector:
		textline.push_back(string(filstr));
		fgetstr=fgets(filstr, 500, fp);
	}

	return textline;
}

vector<string> XAMOS::loadfile(bool usefile, string filename, vector<string> AMALCode)
{
	// Debug:
	//cout << "Debug - starting loadfile()" << endl;

	// Load the file:
	string channelCode = "";
	string line = "";
	int channel = -2; // for jAMOS

	// Set the default AMAL Environment Generator code:
	environmentCode = defaultEnvGenString();

	// Added:
	AMALCode.clear();
	// Added for currently unused program/channel 0:
	//AMALCode.push_back("default amal program\n");

	// TODO - change window frame here...
	// TODO - choose between file and resource loading...

	// TODO - get file input here...
	vector <string> myfileinput = loadfiletotext_old(filename);
	int whichline = 0;

	// Updated to parse EnvGen strings from file:
	while(true)
	{
		if (whichline >= (int)myfileinput.size())
		{
			break;
		}
		else
		{
			//cout << "DEBUG! whichline == " << am->stri(whichline) << ", myfileinput.size() == " << am->stri((int)myfileinput.size()) << endl;
			line = myfileinput[whichline];
			//cout << "successfully loaded into line" << endl;
			whichline++;
		}

		//line=lnr->readLine(); // TODO
		//if (line == null) // TODO
		//	break; // TODO

		// Debug: Test for EnvGen switch:
			//if (line.length()>15)// && (line.substr(0, 16)) == "AMAL Environment")
		//	cout << "Debug: Environment? " << line.substr(0, 11) << endl;

		//cout << "DEBUG! line.length() == " << am->stri(line.length()) << endl;
		if (line.length()>13 && (line.substr(0, 13)) == "AMAL Channel ")
		{
			//cout << "DEBUG! AMAL Channel found! channel == " << am->stri(channel) << endl;
			if (channel >= 0)
			{
				while (AMALCode.size() < (unsigned int)channel)
					AMALCode.push_back("default amal program\n");

				if (AMALCode.size() == (unsigned int)channel)
					AMALCode.push_back(channelCode);
				else
					AMALCode[channel] = channelCode;
			}
			else if (channel == -2)
			{
				amosCode = channelCode;
			}
			else //if (channel == -1)
			{
				environmentCode = channelCode;
			}

			channel = am->val(line.substr(13, line.length() - 13));
			//cout << channelCode << endl;
			//cout << "AMAL Program = " << AM->stri(channel) << endl;
			channelCode = "";
		}
		// Added - load the EnvGen string from file if found:
		else if (line.length()>15 && (line.substr(0, 16)) == "AMAL Environment")
		{
			//cout << "DEBUG! AMAL Environment found" << endl;
			if (channel >= 0)
			{
				while (AMALCode.size() < (unsigned int)channel)
					AMALCode.push_back("default amal program\n");

				if (AMALCode.size() == (unsigned int)channel)
					AMALCode.push_back(channelCode);
				else
					AMALCode[channel] = channelCode;
			}
			else if (channel == -2)
			{
				amosCode = channelCode;
			}
			else
			{
				environmentCode = channelCode;
			}

			channel = -1; // -1 for EnvGen for now
			//cout << "Attempting to load EnvGen string from file!" << endl;
			channelCode = "";
		}
		else
		{
			//cout << "DEBUG! Adding new line to channelCode" << endl;
			channelCode += line + "\n";
			//channelCode += line + " ";
		}
	}

	// Added for jAMOS
	if (channel == -2)
	{
		amosCode = channelCode + '\n';
		//AMALCode.push_back("default amal program");
	}
	else if (channel == -1)
	{
		environmentCode = channelCode + '\n';
		//AMALCode.push_back("default amal program");
	}
	else
	{
		while (AMALCode.size() < (unsigned int)channel)
			AMALCode.push_back("default amal program\n");

		if (AMALCode.size() == (unsigned int)channel)
			AMALCode.push_back(channelCode);
		else
			AMALCode[channel] = channelCode;

		//AMALCode.push_back("");
	}

	// Lex the environment string:
	am->envGen->processcode(environmentCode);

	// MequaScript: Tokenise the instructions:
	am->parser->lexString(amosCode);

	// Close files here if appropriate...
	if (usefile)
	{

	}

	return AMALCode;
}

XAMOS::XAMOS()
{
}

int XAMOS::mymain(int argc, char *args[])
{
	return initGame(argc, args);
}

// Added - console launcher:
string XAMOS::stri(int i) { std::ostringstream s; s << i; return s.str(); }
string XAMOS::consolelauncher()
{
	string filename = "example/Default.xamos";

	string example[] =
	{
		"example/Plotter.xamos",
		"example/Mandelbrot.xamos",
		"example/LoadAbk.xamos",
		"example/LoadAbk2.xamos",
		"example/PasteBob.xamos",
		"example/PasteBobAbk.xamos",
		"example/Drawing.xamos",
		"example/Rainbows.xamos",
		"example/Arrays.xamos",
		"example/EnvgenAndDatatypes.xamos",
		"example/MultiScreens.xamos",
		"example/Eater.xamos",
		"example/Brainf---.xamos",
		"example/XAMOSOut.xamos",
		"example/Default.xamos"
	};
	string tutorial[] =
	{
		"example/HelloWorld.xamos",
		"example/DynamicTypes.xamos",
		"example/HybridSyntax.xamos",
		"example/MoveSprite.xamos",
		"example/UseMouse.xamos",
		"example/UseGameControls.xamos",
		"example/Maths.xamos",
		"example/Procedures.xamos",
		"example/Procedures2.xamos",
		"example/MultiBrains.xamos",
		"example/Collision.xamos",
		"example/PasteIcon.xamos"
	};
	string amalexample[] =
	{
		"example/MultiChannelExample.xamal",
		"example/BouncyBalls.xamal",
		"example/MoreBouncyBalls.xamal",
		"example/OldDefault.xamal",
		"example/Mystery.xamal",
		"example/Shoot.xamal",
		"example/ScreenDragDemo.xamal",
		"example/ScreenScrollingDemo.xamal"
	};
	string amaltutorial[] =
	{
		"example/SimpleMove.xamal",
		"example/SimpleLoop.xamal",
		"example/SimpleFor.xamal",
		"example/SimpleLoopedMove.xamal",
		"example/SimpleLoopedFor.xamal",
		"example/SimpleAnimation.xamal",
		"example/Rotate.xamal",
		"example/Mouse.xamal",
		"example/MouseAutotest.xamal",
		"example/SimpleGameControl.xamal",
		"example/GameControl.xamal",
		"example/AI.xamal"
	};

	vector<string> allexamples;
	allexamples.push_back("");

	int examplenum = 1;

	cout << "Please type the example number below (anything else to quit) and press enter:" << endl << endl << "Example:" << endl;
	for (int n=0; n<15; n++)
	{
		cout << stri(examplenum) << " : " << example[n] << endl;
		allexamples.push_back(example[n]);
		examplenum++;
	}
	
	cout << endl << "Tutorial:" << endl;
	for (int n=0; n<12; n++)
	{
		cout << stri(examplenum) << " : " << tutorial[n] << endl;
		allexamples.push_back(tutorial[n]);
		examplenum++;
	}

	cout << endl << "AMAL Example:" << endl;
	for (int n=0; n<8; n++)
	{
		cout << stri(examplenum) << " : " << amalexample[n] << endl;
		allexamples.push_back(amalexample[n]);
		examplenum++;
	}
	
	cout << endl << "AMAL Tutorial:" << endl;
	for (int n=0; n<10; n++)
	{
		cout << stri(examplenum) << " : " << amaltutorial[n] << endl;
		allexamples.push_back(amaltutorial[n]);
		examplenum++;
	}

	cout << endl;
	cout << "> ";

	// Patch for AROS - clear the input stream from command line arguments (AROS bug):
	#ifdef __AROS__
	{
		int c;
		while (((c = getchar()) != EOF) && (c != '\n'));
	}
	#endif

	// Prompt here:
	unsigned int selected=0;
	cin >> selected;

	if (selected < allexamples.size())
		filename = allexamples[selected];
	else
		filename = "";
	
	//filename = allexamples[12]; // debug - default program

	return filename;
}

