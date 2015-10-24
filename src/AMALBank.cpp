///////////////////////////////////////////////////////////
// AMOS AMAL -> Load AMAL ABK Banks
// By Stephen Harvey-Brooks - Mequa Innovations
///////////////////////////////////////////////////////////

#include "AMALBank.h"

// TODO - not working yet!
// Load AMOS .abk AMAL banks files directly:
AMALBank::AMALBank(AMOS_System* AMi)
{
	AM = AMi;
}

int AMALBank::loadabk(string f)
{
	// TODO:
	//string file = System.getProperty("user.dir") + "\\" + f;
	string file = f;

	char c = 1;
	int ambk = 0;
	int banknumber = 0;
	long banklength = 0;
	int flag = 0;
	string namebank = "";

	long stringsstart = 0;
	int numprogs = 0;

	// TODO:
	//FileInputStream* fileinputstream = new FileInputStream(file);
	//DataInputStream* datainputstream = new DataInputStream(fileinputstream);

	if ((char)readByte() == 'A')
		if ((char)readByte() == 'm')
			if ((char)readByte() == 'B')
				if ((char)readByte() == 'k')
					ambk = 1;

	if (ambk == 1)
		cout << ("AMOS bank detected!");
	else
		return -1;

	banknumber = readWord();
	//banknumber = (banknumber << 8) | (int)readUnsignedByte();
	cout << "banknumber = " << AM->stri(banknumber);

	flag = readWord();
	//flag = (flag * 256) + (int)readUnsignedByte();
	cout << "flag = " << AM->stri(flag);

	banklength = readLong();
	//banklength = (banklength << 8) | readByte();
	//banklength = (banklength << 8) | readByte();
	//banklength = (banklength << 8) | readByte();
	//banklength = banklength - 8;
	cout << "banklength = " << AM->stri(banklength);
	// TODO - hex to string output:
	cout << "banklength = 0x" << AM->stri(banklength); // Long.toHexString(banklength);

	namebank = "";
	for (int a=0; a<8; a++)
		namebank = namebank + (char)readUnsignedByte();
	cout << "namebank = " << namebank;

	if (namebank == ("Amal    "))
		cout << ("AMAL bank detected!");
	else
		return -1;

	stringsstart = readLong();
	//stringsstart = (stringsstart << 8) | (int)readByte();
	//stringsstart = (stringsstart << 8) | (int)readByte();
	//stringsstart = (stringsstart << 8) | (int)readByte();
	cout << "stringsstart = " << AM->stri(stringsstart);
	// TODO - hex to string output:
	cout << "stringsstart = 0x" << AM->stri(stringsstart); // << Long.toHexString(stringsstart);

	for (long temp=0; temp<stringsstart; temp++)
		c = (char)readUnsignedByte();

	numprogs = readWord();
	cout << "numprogs = " << AM->stri(numprogs);
	// TODO - hex to string output:
	cout << "numprogs = 0x" << AM->stri(numprogs); // << Long.toHexString(numprogs);

	c = 1;
	while (c >= 0)
	{
		//int ii;
		c = (char)readUnsignedByte();

		if (c>31 && c<128)
		{
			if (c == '~')
				cout << "\n";
			else
				cout << "" + c;
		}
		else
			cout << " #" << (AM->stri((int)0 + c) + "# ");
	}
	cout << "\n";

	// TODO:
	//datainputstream.close();
	//fileinputstream.close();

	return 0+(int)c;
}

// Note: These are private:

// TODO:
//int AMALBank::readUnsignedByte(DataInputStream d)
unsigned int AMALBank::readUnsignedByte()
{
	return 0;
}

//int AMALBank::readByte(DataInputStream d)
int AMALBank::readByte()
{
	int b1 = readUnsignedByte();
	return b1;
}

//int AMALBank::readWord(DataInputStream d)
int AMALBank::readWord()
{
	int b1 = readUnsignedByte();
	int b2 = readUnsignedByte();
	cout << "readWord: " + AM->stri(b1) + " " + AM->stri(b2);
	return (b1 << 8) + b2;
}

//int AMALBank::readLong(DataInputStream d)
long AMALBank::readLong()
{
	long l1 = readWord();
	long l2 = readWord();
	cout << "readLong: " + AM->stri(l1) + " " + AM->stri(l2);
	return (l1 << 16) + l2;
}

