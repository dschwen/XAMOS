/////////////////////////////////////////////////////////////////
// XAMAL - AMOS Animation Language reimplemented in C++!       //
// By Stephen Harvey-Brooks - (C) 2012 Mequa Innovations       //
/////////////////////////////////////////////////////////////////

#include "AMALDebugTest.h"
#include "AMALCompiler.h"

// Constructor function:
AMALDebugTest::AMALDebugTest()
{
	AM = NULL;
}
AMALDebugTest::AMALDebugTest(AMOS_System* AMi)
{
	AM = AMi;
}

int AMALDebugTest::mymain(int argc, char* args[])
{
    	//string filename = "AMAL.amal";
        string filename = "XAMOS/OldDefault.jamal";
        vector<string> AMALCode; // = new String[256];
	//for (int n=0; n<256; n++)
	//	AMALCode.push_back("");

	//AMALCode = loadfile(filename, AMALCode);
        AMALCode = loadfile(filename);
        
        AM = new AMOS_System(); // new AMOS_System(NULL);
        
        int numchannels = 0;

        // Write stripped output to file (TODO):
        //FileOutputStream ffout;
        PrintStream* fout;
	//try {
	
	// TODO:
	//ffout = new FileOutputStream("AMAL_stripped.amal");
        //fout = new PrintStream(ffout);
	fout = new PrintStream();
        for (unsigned int channel = 1; (channel < AMALCode.size()) && !(AMALCode[channel]==""); channel++)
        {
        	if (channel > 1)
        		fout->println("");

        	fout->println("AMAL Channel " + AM->stri(channel));
        	AM->amal(channel, AMALCode[channel]);

        	// Write stripped output to file:
        	fout->println(AM->tokest);
        	numchannels++;
        }

	// TODO:
        //fout->close();

	//catch (Exception e)
        //{
        //    cout << "Error: " << e.getMessage();
        //}

        if (numchannels > 0)
        {
		// TODO:
		//AM->amalcompiler->AmalCompile(fout, 1, numchannels); // System.out
        	AM->amalcompiler->AmalCompile(1, numchannels, true); // Added - true for C++, false for Java
        	//AM->amalcompiler->DEBUG(); // TODO!

        	// Write to file - TODO:
        	//FileOutputStream ffout;
        	//PrintStream fout;
        	//try {

		// TODO:
        	//ffout = new FileOutputStream("AMALout.java");
        	//fout = new PrintStream(ffout);
		//fout = new PrintStream();

		// TODO:
		//AM->amalcompiler->AmalCompile(fout, 1, numchannels);
        	AM->amalcompiler->AmalCompile(1, numchannels, true); // added - true for C++, false for Java

		// TODO:
        	//fout->close();

        	//catch (Exception e)
        	//{
        	//    cout << "Error: " << e.getMessage();
        	//}
	}

	// Added:
	return 0;
}

vector <string> AMALDebugTest::loadfile(string filename)
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

