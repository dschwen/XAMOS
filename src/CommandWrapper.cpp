#include <stdio.h>
#include <string.h>
#include <sstream>

#include "CommandWrapper.h"

using std::stringstream;

CommandWrapper::CommandWrapper(Game* g_, AMOS_System* am_)
{
	g=g_;
	am = am_;
}

/*CommandWrapper::CommandWrapper(Game* g_)
{
	g=g_;
}*/


Mytype* CommandWrapper::runfunction(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	// For executing "Print" etc. :
	switch(ret->instflag)
	{
	case 1: return m_double(ret, mytokens, myvalues, offset, realret, mytemps);
	case 2: return m_print(ret, mytokens, myvalues, offset, realret, mytemps);
	case 3: return m_say(ret, mytokens, myvalues, offset, realret, mytemps);
	case 4: return m_instr(ret, mytokens, myvalues, offset, realret, mytemps);
	case 5: return m_substring(ret, mytokens, myvalues, offset, realret, mytemps);


	// Added - from jAMOS:
	case 6:  return m_screenopen(ret, mytokens, myvalues, offset, realret, mytemps);
	case 7:  return m_screendisplay(ret, mytokens, myvalues, offset, realret, mytemps);
	case 8:  return m_screenoffset(ret, mytokens, myvalues, offset, realret, mytemps);
	case 9:  return m_screenclose(ret, mytokens, myvalues, offset, realret, mytemps);
	case 10: return m_screenclone(ret, mytokens, myvalues, offset, realret, mytemps);
	case 11: return m_screen(ret, mytokens, myvalues, offset, realret, mytemps);
	case 12: return m_doublebuffer(ret, mytokens, myvalues, offset, realret, mytemps);
	case 13: return m_dualplayfield(ret, mytokens, myvalues, offset, realret, mytemps);
	case 14: return m_dualpriority(ret, mytokens, myvalues, offset, realret, mytemps);
	case 15: return m_loadiff(ret, mytokens, myvalues, offset, realret, mytemps);
	case 16: return m_load(ret, mytokens, myvalues, offset, realret, mytemps);
	case 17: return m_erase(ret, mytokens, myvalues, offset, realret, mytemps);
	case 18: return m_hideon(ret, mytokens, myvalues, offset, realret, mytemps);
	case 19: return m_updateevery(ret, mytokens, myvalues, offset, realret, mytemps);
	case 20: return m_flashoff(ret, mytokens, myvalues, offset, realret, mytemps);
	case 21: return m_flash(ret, mytokens, myvalues, offset, realret, mytemps);
	case 22: return m_setrainbow(ret, mytokens, myvalues, offset, realret, mytemps);
	case 23: return m_rainbowdel(ret, mytokens, myvalues, offset, realret, mytemps);
	case 24: return m_rainbow(ret, mytokens, myvalues, offset, realret, mytemps);
	case 25: return m_boboff(ret, mytokens, myvalues, offset, realret, mytemps);
	case 26: return m_bob(ret, mytokens, myvalues, offset, realret, mytemps);
	case 27: return m_setbob(ret, mytokens, myvalues, offset, realret, mytemps);
	case 28: return m_spriteoff(ret, mytokens, myvalues, offset, realret, mytemps);
	case 29: return m_sprite(ret, mytokens, myvalues, offset, realret, mytemps);
	case 30: return m_setspritebuffer(ret, mytokens, myvalues, offset, realret, mytemps);
	case 31: return m_setreg(ret, mytokens, myvalues, offset, realret, mytemps);
	case 32: return m_unpack(ret, mytokens, myvalues, offset, realret, mytemps);
	case 33: return m_channeltosprite(ret, mytokens, myvalues, offset, realret, mytemps);
	case 34: return m_channeltobob(ret, mytokens, myvalues, offset, realret, mytemps);
	case 35: return m_channeltoscreenoffset(ret, mytokens, myvalues, offset, realret, mytemps);
	case 36: return m_channeltoscreensize(ret, mytokens, myvalues, offset, realret, mytemps);
	case 37: return m_channeltorainbow(ret, mytokens, myvalues, offset, realret, mytemps);
	case 38: return m_channeltoscreendisplay(ret, mytokens, myvalues, offset, realret, mytemps);
	case 39: return m_bell(ret, mytokens, myvalues, offset, realret, mytemps);
	case 40: return m_xmouse(ret, mytokens, myvalues, offset, realret, mytemps);
	case 41: return m_ymouse(ret, mytokens, myvalues, offset, realret, mytemps);
	case 42: return m_mousekey(ret, mytokens, myvalues, offset, realret, mytemps);
	case 43: return m_xscreen(ret, mytokens, myvalues, offset, realret, mytemps);
	case 44: return m_yscreen(ret, mytokens, myvalues, offset, realret, mytemps);
	case 45: return m_xhard(ret, mytokens, myvalues, offset, realret, mytemps);
	case 46: return m_yhard(ret, mytokens, myvalues, offset, realret, mytemps);
	case 47: return m_joy(ret, mytokens, myvalues, offset, realret, mytemps);
	case 48: return m_jleft(ret, mytokens, myvalues, offset, realret, mytemps);
	case 49: return m_jright(ret, mytokens, myvalues, offset, realret, mytemps);
	case 50: return m_jup(ret, mytokens, myvalues, offset, realret, mytemps);
	case 51: return m_jdown(ret, mytokens, myvalues, offset, realret, mytemps);
	case 52: return m_fire(ret, mytokens, myvalues, offset, realret, mytemps);
	case 53: return m_xsprite(ret, mytokens, myvalues, offset, realret, mytemps);
	case 54: return m_ysprite(ret, mytokens, myvalues, offset, realret, mytemps);
	case 55: return m_isprite(ret, mytokens, myvalues, offset, realret, mytemps);
	case 56: return m_xbob(ret, mytokens, myvalues, offset, realret, mytemps);
	case 57: return m_ybob(ret, mytokens, myvalues, offset, realret, mytemps);
	case 58: return m_ibob(ret, mytokens, myvalues, offset, realret, mytemps);
	case 59: return m_pastebob(ret, mytokens, myvalues, offset, realret, mytemps);
	case 60: return m_plot(ret, mytokens, myvalues, offset, realret, mytemps);
	case 61: return m_ink(ret, mytokens, myvalues, offset, realret, mytemps);
	case 62: return m_draw(ret, mytokens, myvalues, offset, realret, mytemps);
	case 63: return m_bar(ret, mytokens, myvalues, offset, realret, mytemps);
	case 64: return m_box(ret, mytokens, myvalues, offset, realret, mytemps);
	case 65: return m_circle(ret, mytokens, myvalues, offset, realret, mytemps);
	case 66: return m_ellipse(ret, mytokens, myvalues, offset, realret, mytemps);
	case 67: return m_rnd(ret, mytokens, myvalues, offset, realret, mytemps);
	case 68: return m_hrev(ret, mytokens, myvalues, offset, realret, mytemps);
	case 69: return m_vrev(ret, mytokens, myvalues, offset, realret, mytemps);
	case 70: return m_rev(ret, mytokens, myvalues, offset, realret, mytemps);
	case 71: return m_rain(ret, mytokens, myvalues, offset, realret, mytemps);
	case 72: return m_degree(ret, mytokens, myvalues, offset, realret, mytemps);
	case 73: return m_radian(ret, mytokens, myvalues, offset, realret, mytemps);
	case 74: return m_sin(ret, mytokens, myvalues, offset, realret, mytemps);
	case 75: return m_cos(ret, mytokens, myvalues, offset, realret, mytemps);
	case 76: return m_tan(ret, mytokens, myvalues, offset, realret, mytemps);
	case 77: return m_asin(ret, mytokens, myvalues, offset, realret, mytemps);
	case 78: return m_acos(ret, mytokens, myvalues, offset, realret, mytemps);
	case 79: return m_atan(ret, mytokens, myvalues, offset, realret, mytemps);
	case 80: return m_pi(ret, mytokens, myvalues, offset, realret, mytemps);
	case 81: return m_left(ret, mytokens, myvalues, offset, realret, mytemps);
	case 82: return m_right(ret, mytokens, myvalues, offset, realret, mytemps);
	case 83: return m_mid(ret, mytokens, myvalues, offset, realret, mytemps);
	case 84: return m_len(ret, mytokens, myvalues, offset, realret, mytemps);
	case 85: return m_upper(ret, mytokens, myvalues, offset, realret, mytemps);
	case 86: return m_lower(ret, mytokens, myvalues, offset, realret, mytemps);
	case 87: return m_string(ret, mytokens, myvalues, offset, realret, mytemps);
	case 88: return m_repeat(ret, mytokens, myvalues, offset, realret, mytemps);
	case 89: return m_space(ret, mytokens, myvalues, offset, realret, mytemps);
	case 90: return m_flip(ret, mytokens, myvalues, offset, realret, mytemps);
	case 91: return m_val(ret, mytokens, myvalues, offset, realret, mytemps);
	case 92: return m_str(ret, mytokens, myvalues, offset, realret, mytemps);
	case 93: return m_asc(ret, mytokens, myvalues, offset, realret, mytemps);
	case 94: return m_chr(ret, mytokens, myvalues, offset, realret, mytemps);
	case 95: return m_boom(ret, mytokens, myvalues, offset, realret, mytemps);
	case 96: return m_shoot(ret, mytokens, myvalues, offset, realret, mytemps);
	case 97: return m_paramstring(ret, mytokens, myvalues, offset, realret, mytemps);
	case 98: return m_paramfloat(ret, mytokens, myvalues, offset, realret, mytemps);
	case 99: return m_param(ret, mytokens, myvalues, offset, realret, mytemps);

	case 100: return m_getarrayvalue(ret, mytokens, myvalues, offset, realret, mytemps);

	case 101: return m_bobcol(ret, mytokens, myvalues, offset, realret, mytemps);
	case 102: return m_spritecol(ret, mytokens, myvalues, offset, realret, mytemps);
	case 103: return m_spritebobcol(ret, mytokens, myvalues, offset, realret, mytemps);
	case 104: return m_bobspritecol(ret, mytokens, myvalues, offset, realret, mytemps);
	case 105: return m_col(ret, mytokens, myvalues, offset, realret, mytemps);
	case 106: return m_text(ret, mytokens, myvalues, offset, realret, mytemps);
	case 107: return m_textlength(ret, mytokens, myvalues, offset, realret, mytemps);
	case 108: return m_pasteicon(ret, mytokens, myvalues, offset, realret, mytemps);
	case 109: return m_hotspot(ret, mytokens, myvalues, offset, realret, mytemps);
	case 110: return m_paper(ret, mytokens, myvalues, offset, realret, mytemps);

	// From 3Dlicious! (another project):
	/*
	case 6: return m_take(ret, mytokens, myvalues, offset, realret, mytemps);
	case 7: return m_rotate(ret, mytokens, myvalues, offset, realret, mytemps);
	case 8: return m_move(ret, mytokens, myvalues, offset, realret, mytemps);
	case 9: return m_setnode(ret, mytokens, myvalues, offset, realret, mytemps);
	case 10: return m_selectusewith(ret, mytokens, myvalues, offset, realret, mytemps);
	case 11: return m_usewithme(ret, mytokens, myvalues, offset, realret, mytemps);
	case 12: return m_setothernode(ret, mytokens, myvalues, offset, realret, mytemps);
	case 13: return m_kill(ret, mytokens, myvalues, offset, realret, mytemps);
	case 14: return m_createinventoryobject(ret, mytokens, myvalues, offset, realret, mytemps);
	case 15: return m_createActiveObject(ret, mytokens, myvalues, offset, realret, mytemps);
	case 16: return m_usewith(ret, mytokens, myvalues, offset, realret, mytemps);
	case 17: return m_scale(ret, mytokens, myvalues, offset, realret, mytemps);
	case 18: return m_sound(ret, mytokens, myvalues, offset, realret, mytemps);
	case 19: return m_drop(ret, mytokens, myvalues, offset, realret, mytemps);
	*/


	// TODO: Special functions (temporary numbers given - fix this!)
	/*case 20: return m_paramstring(ret, mytokens, myvalues, offset, realret, mytemps);
	case 21: return m_paramfloat(ret, mytokens, myvalues, offset, realret, mytemps);
	case 22: return m_param(ret, mytokens, myvalues, offset, realret, mytemps);*/


	// TODO: Special functions (jAMOS numbers given - fix this!)
	//case 97: return m_paramstring(ret, mytokens, myvalues, offset, realret, mytemps);
	//case 98: return m_paramfloat(ret, mytokens, myvalues, offset, realret, mytemps);
	//case 99: return m_param(ret, mytokens, myvalues, offset, realret, mytemps);

	// Special function:
	// Should work:
	//case 100: return m_getarrayvalue(ret, mytokens, myvalues, offset, realret, mytemps);


	default: return m_dummyfunction(ret, mytokens, myvalues, offset, realret, mytemps);
	}
}

// Special functions:
Mytype* CommandWrapper::m_paramstring(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	realret->t = 1;
	realret->s = myvalues->myparamstring;

	return realret;
}
Mytype* CommandWrapper::m_paramfloat(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	realret->t = 0;
	realret->d = myvalues->myparamfloat;

	return realret;
}
Mytype* CommandWrapper::m_param(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	realret->t = 0;
	realret->d = myvalues->myparamfloat;
	//realret->d = myvalues->myparamint; // Uses float/double by default - TODO - allow AMOS behaviour!

	return realret;
}

// Special function:
/*
Mytype* CommandWrapper::m_getarrayvalue(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	vector<int> arraydims(ret->numargs-2);
	for (int dim=0; dim<ret->numargs-2; dim++)
		arraydims.push_back((int)getarg(ret->args[offset+dim], ret->argtypes[offset+dim], myvalues, mytemps));

	//printf("Debug: Number of params: %d\n", arraydims.size());
	//for (int p=0; p<arraydims.size(); p++) printf("%d\n, arraydims[p]);

	Mytype* actualret = myvalues->myarrays[(int)ret->args[ret->numargs-1]].get(arraydims);

	realret->t = actualret->t;
	realret->d = actualret->d;
	realret->s = actualret->s;

	return realret;
}
*/
Mytype* CommandWrapper::m_getarrayvalue(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	// Using array instead of vector for speed:
	int* arraydims = new int[ret->numargs-1];
	arraydims[0] = ret->numargs-2;
	for (int dim=0; dim<ret->numargs-2; dim++)
		arraydims[dim+1] = ((int)getarg(ret->args[offset+dim], ret->argtypes[offset+dim], myvalues, mytemps));

	//printf("Debug: Number of params: %d\n", arraydims.size());
	//for (int p=0; p<arraydims.size(); p++) printf("%d\n, arraydims[p]);

	Mytype* actualret = myvalues->myarrays[(int)ret->args[ret->numargs-1]].get(arraydims);

	delete[] arraydims;

	realret->t = actualret->t;
	realret->d = actualret->d;
	realret->s = actualret->s;

	return realret;
}


// TODO - move these - copied from Interpreter:
string CommandWrapper::floattostring(double value) // was char*
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << value;
	return ss.str();
}
double CommandWrapper::getarg(double arg, int argtype, ActiveObject *myvalues, Mytype* mytemps)
{
	switch(argtype)
	{
	case 0:
		return arg;
	case 1:
		// Var name (string): mytokens->myvarnames[arg]
		return myvalues->myvars[(int)arg].d;
	case 3:
		return 0; // string: mytokens->mystrings[arg] - fix types!
	case 5:
		return mytemps[(int)arg].d; // Make sure initialised!
	default:
		return 0;
	}
}
char* CommandWrapper::getarg2(double arg, int argtype, ActiveObject *myvalues, TheTokens* mytokens, Mytype* mytemps)
{
	switch(argtype)
	{
	case 0:
		return (char*)(floattostring(arg).c_str());
	case 1:
		// Var name (string): mytokens->myvarnames[arg]
		// Convert number if appropriate:
		if (myvalues->myvars[(int)arg].t == 0)
			return (char*)(floattostring(myvalues->myvars[(int)arg].d).c_str());
		else
			return (char*)((myvalues->myvars[(int)arg].s).c_str());
	case 3:
		return (char*)(mytokens->mystrings[(int)arg].c_str());
	case 5:
		return (char*)((mytemps[(int)arg].s).c_str()); // Make sure initialised!
	default:
		return 0;
	}
}
int CommandWrapper::isnumber(double arg, int argtype, ActiveObject *myvalues, Mytype* mytemps)
{
	switch(argtype)
	{
	case -1:
		return 1;
	case 0:
		return 1;
	case 1: // Variable name - to do:
		// Var name (string): mytokens->myvarnames[arg]
		return myvalues->myvars[(int)arg].t == 0;
	case 3:
		return 0;
	case 5:
		return (mytemps[(int)arg].t) == 0; // Make sure initialised!
	default:
		return 0;
	}
}


// User-defined functions...
Mytype* CommandWrapper::m_dummyfunction(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	return realret;
}
Mytype* CommandWrapper::m_double(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	if (ret->numargs == 0)
	{
		//realret->d = -1; // error (-1, now 0)...
		return realret;
	}
	// First arg only
	double arg = getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	realret->d = arg * 2;
	return realret;
}
Mytype* CommandWrapper::m_print(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	for (int n=offset; n<ret->numargs; n++)
	{
		if (isnumber(ret->args[n], ret->argtypes[n], myvalues, mytemps))
			printf("%s\n", floattostring(getarg(ret->args[n], ret->argtypes[n], myvalues, mytemps)).c_str());
		else
			printf("%s\n", getarg2(ret->args[n], ret->argtypes[n], myvalues, mytokens, mytemps)); //, ret->argtypes[n]);
	}
	return realret;
}
Mytype* CommandWrapper::m_say(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	/*for (int n=offset; n<ret->numargs; n++)
    {
        if (isnumber(ret->args[n], ret->argtypes[n], myvalues, mytemps))
            setcaption(floattostring(getarg(ret->args[n], ret->argtypes[n], myvalues, mytemps)).c_str());
        else
            setcaption(getarg2(ret->args[n], ret->argtypes[n], myvalues, mytokens, mytemps)); //, ret->argtypes[n]);
    }*/
	return realret;
}

Mytype* CommandWrapper::m_instr(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	realret->t = 0;
	realret->d = (strstr(getarg2(ret->args[offset], ret->argtypes[offset], myvalues, mytokens, mytemps),
			getarg2(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytokens, mytemps)) != 0);
	return realret;
}

Mytype* CommandWrapper::m_substring(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	realret->t = 1;
	realret->s = getarg2(ret->args[offset], ret->argtypes[offset], myvalues, mytokens, mytemps);
	realret->s = realret->s.substr((int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps),
			(int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps));
	return realret;
}



// jAMOS-ported functions:
// Added - for jAMOS:
// TODO - need to add wrappers:
Mytype* CommandWrapper::m_screenopen(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int s=0, w=320, h=200, d=16, r=0;
	if ((offset) < ret->numargs)
		s = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		w = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		h = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);
	if ((offset+3) < ret->numargs)
		d = (int)getarg(ret->args[offset+3], ret->argtypes[offset+3], myvalues, mytemps);
	if ((offset+4) < ret->numargs)
		r = (int)getarg(ret->args[offset+4], ret->argtypes[offset+4], myvalues, mytemps);

	am->screenOpen(s, w, h, d, r);

	return realret;
}
Mytype* CommandWrapper::m_screendisplay(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int s=0, x=0, y=0;
	if ((offset) < ret->numargs)
		s = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		x = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		y = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);

	am->screenDisplay(s, x, y);

	return realret;
}
Mytype* CommandWrapper::m_screenoffset(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int s=0, x=0, y=0;
	if ((offset) < ret->numargs)
		s = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		x = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		y = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);

	am->screenOffset(s, x, y);

	return realret;
}
Mytype* CommandWrapper::m_screenclose(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	am->screenClose(); // TODO - more params
	return realret;
}
Mytype* CommandWrapper::m_screenclone(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int s=0;
	if ((offset) < ret->numargs)
		s = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	am->screenClone(s);

	return realret;
}
Mytype* CommandWrapper::m_screen(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int s=0;
	if ((offset) < ret->numargs)
		s = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	am->screen(s);

	return realret;
}
Mytype* CommandWrapper::m_doublebuffer(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	am->doubleBuffer();
	return realret;
}
Mytype* CommandWrapper::m_dualplayfield(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);

	am->dualPlayfield(a, b);

	return realret;
}
Mytype* CommandWrapper::m_dualpriority(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);

	am->dualPriority(a, b);

	return realret;
}
Mytype* CommandWrapper::m_loadiff(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	string a="";
	int b=0;
	if ((offset) < ret->numargs)
		a = getarg2(ret->args[offset], ret->argtypes[offset], myvalues, mytokens, mytemps);

	if ((offset+1) < ret->numargs)
	{
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
		am->loadIff(a, b);
	}
	else
	{
		am->loadIff(a);
	}

	return realret;
}
Mytype* CommandWrapper::m_load(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	string a="";
	int b=0;
	int scale=1; // Added - scale defaults to 1. Now can also: Load "filename",bank,scale
	if ((offset) < ret->numargs)
		a = getarg2(ret->args[offset], ret->argtypes[offset], myvalues, mytokens, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		scale = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);

	am->load(a, b, scale);
	return realret;
}
Mytype* CommandWrapper::m_erase(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	am->erase(a);
	return realret;
}
Mytype* CommandWrapper::m_hideon(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	am->hideOn();
	return realret;
}
Mytype* CommandWrapper::m_updateevery(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	am->updateEvery(a);
	return realret;
}
Mytype* CommandWrapper::m_flashoff(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	am->flashOff(); // TODO - more params
	return realret;
}
Mytype* CommandWrapper::m_flash(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	string b="";
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = getarg2(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytokens, mytemps);

	am->flash(a, b);
	return realret;
}
Mytype* CommandWrapper::m_setrainbow(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0;
	string d="", e="", f="";
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);
	if ((offset+3) < ret->numargs)
		d = getarg2(ret->args[offset+3], ret->argtypes[offset+3], myvalues, mytokens, mytemps);
	if ((offset+4) < ret->numargs)
		e = getarg2(ret->args[offset+4], ret->argtypes[offset+4], myvalues, mytokens, mytemps);
	if ((offset+5) < ret->numargs)
		f = getarg2(ret->args[offset+5], ret->argtypes[offset+5], myvalues, mytokens, mytemps);

	am->setRainbow(a, b, c, d, e, f);
	return realret;
}
Mytype* CommandWrapper::m_rainbowdel(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a;
	if ((offset) < ret->numargs)
	{
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
		am->rainbowDel(a);
	}
	else
	{
		am->rainbowDel();
	}

	return realret;
}
Mytype* CommandWrapper::m_rainbow(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0, d=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);
	if ((offset+3) < ret->numargs)
		d = (int)getarg(ret->args[offset+3], ret->argtypes[offset+3], myvalues, mytemps);

	am->rainbow(a, b, c, d);
	return realret;
}
Mytype* CommandWrapper::m_boboff(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	am->bobOff(); // TODO - more params
	return realret;
}
Mytype* CommandWrapper::m_bob(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0, d=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);
	if ((offset+3) < ret->numargs)
		d = (int)getarg(ret->args[offset+3], ret->argtypes[offset+3], myvalues, mytemps);

	am->bob(a, b, c, d);
	return realret;
}
Mytype* CommandWrapper::m_setbob(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0, d=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);
	if ((offset+3) < ret->numargs)
		d = (int)getarg(ret->args[offset+3], ret->argtypes[offset+3], myvalues, mytemps);

	am->setBob(a, b, c, d);
	return realret;
}
Mytype* CommandWrapper::m_spriteoff(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	am->spriteOff(); // TODO - more params
	return realret;
}
Mytype* CommandWrapper::m_sprite(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0, d=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);
	if ((offset+3) < ret->numargs)
		d = (int)getarg(ret->args[offset+3], ret->argtypes[offset+3], myvalues, mytemps);

	am->sprite(a, b, c, d);
	return realret;
}
Mytype* CommandWrapper::m_setspritebuffer(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	am->setSpriteBuffer(a);
	return realret;
}
Mytype* CommandWrapper::m_setreg(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);

	am->setReg(a, b);
	return realret;
}
Mytype* CommandWrapper::m_unpack(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);

	am->unpack(a, b);
	return realret;
}
Mytype* CommandWrapper::m_channeltosprite(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);

	am->channelToSprite(a, b);
	return realret;
}
Mytype* CommandWrapper::m_channeltobob(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);

	am->channelToBob(a, b);
	return realret;
}
Mytype* CommandWrapper::m_channeltoscreenoffset(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);

	am->channelToScreenOffset(a, b);
	return realret;
}
Mytype* CommandWrapper::m_channeltoscreensize(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);

	am->channelToScreenSize(a, b);
	return realret;
}
Mytype* CommandWrapper::m_channeltorainbow(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);

	am->channelToRainbow(a, b);
	return realret;
}
Mytype* CommandWrapper::m_channeltoscreendisplay(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);

	am->channelToScreenDisplay(a, b);
	return realret;
}
Mytype* CommandWrapper::m_bell(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	// TODO - more params:
	am->bell();
	return realret;
}
Mytype* CommandWrapper::m_xmouse(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	// TODO - more params
	realret->d = am->xMouse();
	return realret;
}
Mytype* CommandWrapper::m_ymouse(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	// TODO - more params
	realret->d = am->yMouse();
	return realret;
}
Mytype* CommandWrapper::m_mousekey(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	// TODO - more params
	realret->d = am->mouseKey();
	return realret;
}
Mytype* CommandWrapper::m_xscreen(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	if ((offset+1) < ret->numargs)
	{
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
		realret->d = am->xScreen(a, b);
	}
	else
	{
		realret->d = am->xScreen(a);
	}

	return realret;
}
Mytype* CommandWrapper::m_yscreen(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	if ((offset+1) < ret->numargs)
	{
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
		realret->d = am->yScreen(a, b);
	}
	else
	{
		realret->d = am->yScreen(a);
	}

	return realret;
}
Mytype* CommandWrapper::m_xhard(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	if ((offset+1) < ret->numargs)
	{
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
		realret->d = am->xHard(a, b);
	}
	else
	{
		realret->d = am->xHard(a);
	}

	return realret;
}
Mytype* CommandWrapper::m_yhard(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	if ((offset+1) < ret->numargs)
	{
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
		realret->d = am->yHard(a, b);
	}
	else
	{
		realret->d = am->yHard(a);
	}

	return realret;
}
Mytype* CommandWrapper::m_joy(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->joy(a);
	
	return realret;
}
Mytype* CommandWrapper::m_jleft(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->jleft(a);
	
	return realret;
}
Mytype* CommandWrapper::m_jright(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->jright(a);
	
	return realret;
}
Mytype* CommandWrapper::m_jup(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->jup(a);

	return realret;
}
Mytype* CommandWrapper::m_jdown(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->jdown(a);

	return realret;
}
Mytype* CommandWrapper::m_fire(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->fire(a);

	return realret;
}
Mytype* CommandWrapper::m_xsprite(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->xSprite(a);

	return realret;
}
Mytype* CommandWrapper::m_ysprite(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->ySprite(a);

	return realret;
}
Mytype* CommandWrapper::m_isprite(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->iSprite(a);

	return realret;
}
Mytype* CommandWrapper::m_xbob(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->xBob(a);

	return realret;
}
Mytype* CommandWrapper::m_ybob(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->yBob(a);

	return realret;
}
Mytype* CommandWrapper::m_ibob(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->iBob(a);

	return realret;
}
Mytype* CommandWrapper::m_pastebob(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);

	am->pastebob(a, b, c);
	return realret;
}
Mytype* CommandWrapper::m_plot(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);

	if ((offset+2) < ret->numargs)
	{
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);
		am->plot(a, b, c);
	}
	else
	{
		am->plot(a, b);
	}

	return realret;
}
Mytype* CommandWrapper::m_ink(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	
	am->ink(a);
	return realret;
}
Mytype* CommandWrapper::m_draw(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0, d=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);
	if ((offset+3) < ret->numargs)
		d = (int)getarg(ret->args[offset+3], ret->argtypes[offset+3], myvalues, mytemps);

	am->draw(a, b, c, d);
	return realret;
}
Mytype* CommandWrapper::m_bar(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0, d=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);
	if ((offset+3) < ret->numargs)
		d = (int)getarg(ret->args[offset+3], ret->argtypes[offset+3], myvalues, mytemps);

	am->bar(a, b, c, d);
	return realret;
}
Mytype* CommandWrapper::m_box(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0, d=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);
	if ((offset+3) < ret->numargs)
		d = (int)getarg(ret->args[offset+3], ret->argtypes[offset+3], myvalues, mytemps);

	am->box(a, b, c, d);
	return realret;
}
Mytype* CommandWrapper::m_circle(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);

	am->circle(a, b, c);
	return realret;
}
Mytype* CommandWrapper::m_ellipse(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0, d=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);
	if ((offset+3) < ret->numargs)
		d = (int)getarg(ret->args[offset+3], ret->argtypes[offset+3], myvalues, mytemps);

	am->ellipse(a, b, c, d);
	return realret;
}
Mytype* CommandWrapper::m_rnd(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->rnd(a);
	return realret;
}
Mytype* CommandWrapper::m_hrev(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->hrev(a);
	return realret;
}
Mytype* CommandWrapper::m_vrev(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->vrev(a);
	return realret;
}
Mytype* CommandWrapper::m_rev(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->rev(a);
	return realret;
}
Mytype* CommandWrapper::m_rain(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);

	am->rain(a, b, c);
	return realret;
}
Mytype* CommandWrapper::m_degree(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	am->degree();
	return realret;
}
Mytype* CommandWrapper::m_radian(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	am->radian();
	return realret;
}
Mytype* CommandWrapper::m_sin(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->_sin(a);
	return realret;
}
Mytype* CommandWrapper::m_cos(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->_cos(a);
	return realret;
}
Mytype* CommandWrapper::m_tan(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->_tan(a);
	return realret;
}
Mytype* CommandWrapper::m_asin(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->_asin(a);
	return realret;
}
Mytype* CommandWrapper::m_acos(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->_acos(a);
	return realret;
}
Mytype* CommandWrapper::m_atan(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->d = am->_atan(a);
	return realret;
}
Mytype* CommandWrapper::m_pi(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	realret->d = am->pi();
	return realret;
}
Mytype* CommandWrapper::m_left(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	string a="";
	int b=0;
	if ((offset) < ret->numargs)
		a = getarg2(ret->args[offset], ret->argtypes[offset], myvalues, mytokens, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);

	realret->t = 1;
	realret->s = am->left(a, b);
	return realret;
}
Mytype* CommandWrapper::m_right(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	string a="";
	int b=0;
	if ((offset) < ret->numargs)
		a = getarg2(ret->args[offset], ret->argtypes[offset], myvalues, mytokens, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);

	realret->t = 1;
	realret->s = am->right(a, b);
	return realret;
}
Mytype* CommandWrapper::m_mid(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	string a="";
	int b=0; int c=0;

	realret->t = 1;

	if ((offset) < ret->numargs)
		a = getarg2(ret->args[offset], ret->argtypes[offset], myvalues, mytokens, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);

	if ((offset+2) < ret->numargs)
	{
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);
		realret->s = am->mid(a, b, c);
	}
	else
	{		
		realret->s = am->mid(a, b);
	}
	return realret;
}
Mytype* CommandWrapper::m_len(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	string a="";
	if ((offset) < ret->numargs)
		a = getarg2(ret->args[offset], ret->argtypes[offset], myvalues, mytokens, mytemps);

	realret->d = am->len(a);
	return realret;
}
Mytype* CommandWrapper::m_upper(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	string a="";
	if ((offset) < ret->numargs)
		a = getarg2(ret->args[offset], ret->argtypes[offset], myvalues, mytokens, mytemps);

	realret->t = 1;
	realret->s = am->upper(a);
	return realret;
}
Mytype* CommandWrapper::m_lower(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	string a="";
	if ((offset) < ret->numargs)
		a = getarg2(ret->args[offset], ret->argtypes[offset], myvalues, mytokens, mytemps);

	realret->t = 1;
	realret->s = am->lower(a);
	return realret;
}
Mytype* CommandWrapper::m_string(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	string a="";
	int b=0;
	if ((offset) < ret->numargs)
		a = getarg2(ret->args[offset], ret->argtypes[offset], myvalues, mytokens, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);

	realret->t = 1;
	realret->s = am->_string(a, b);
	return realret;
}
Mytype* CommandWrapper::m_repeat(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	string a="";
	int b=0;
	if ((offset) < ret->numargs)
		a = getarg2(ret->args[offset], ret->argtypes[offset], myvalues, mytokens, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);

	realret->t = 1;
	realret->s = am->repeat(a, b);
	return realret;
}
Mytype* CommandWrapper::m_space(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;

	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->t = 1;
	realret->s = am->space(a);
	return realret;
}
Mytype* CommandWrapper::m_flip(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	string a="";

	if ((offset) < ret->numargs)
		a = getarg2(ret->args[offset], ret->argtypes[offset], myvalues, mytokens, mytemps);

	realret->t = 1;
	realret->s = am->flip(a);
	return realret;
}
Mytype* CommandWrapper::m_val(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	string a="";

	if ((offset) < ret->numargs)
		a = getarg2(ret->args[offset], ret->argtypes[offset], myvalues, mytokens, mytemps);

	realret->d = am->val(a);
	return realret;
}
Mytype* CommandWrapper::m_str(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;

	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->t = 1;
	realret->s = am->str(a);
	return realret;
}
Mytype* CommandWrapper::m_asc(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	string a="";
	if ((offset) < ret->numargs)
		a = getarg2(ret->args[offset], ret->argtypes[offset], myvalues, mytokens, mytemps);

	realret->d = am->asc(a);
	return realret;
}
Mytype* CommandWrapper::m_chr(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;

	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);

	realret->t = 1;
	realret->s = am->chr(a);
	return realret;
}
Mytype* CommandWrapper::m_boom(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	// TODO - more params:
	am->boom();
	return realret;
}
Mytype* CommandWrapper::m_shoot(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	// TODO - more params:
	am->shoot();
	return realret;
}

Mytype* CommandWrapper::m_bobcol(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	else
	{
		realret->d = am->bobCol(a);
		return realret;
	}

	if ((offset+2) < ret->numargs)
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);

	realret->d = am->bobCol(a, b, c);
	return realret;
}
Mytype* CommandWrapper::m_spritecol(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	else
	{
		realret->d = am->spriteCol(a);
		return realret;
	}

	if ((offset+2) < ret->numargs)
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);

	realret->d = am->spriteCol(a, b, c);
	return realret;
}
Mytype* CommandWrapper::m_spritebobcol(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	else
	{
		realret->d = am->spriteBobCol(a);
		return realret;
	}

	if ((offset+2) < ret->numargs)
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);

	realret->d = am->spriteBobCol(a, b, c);
	return realret;
}
Mytype* CommandWrapper::m_bobspritecol(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	else
	{
		realret->d = am->bobSpriteCol(a);
		return realret;
	}

	if ((offset+2) < ret->numargs)
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);

	realret->d = am->bobSpriteCol(a, b, c);
	return realret;
}
Mytype* CommandWrapper::m_col(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
	{
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
		realret->d = am->col(a);
	}
	else
	{
		realret->d = am->col(-1);
	}

	return realret;
}
Mytype* CommandWrapper::m_text(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int x=0;
	int y=0;
	string a="";

	realret->t = 1;

	if ((offset) < ret->numargs)
		x = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		y = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		a = getarg2(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytokens, mytemps);

	am->text(x, y, a);

	return realret;
}
Mytype* CommandWrapper::m_textlength(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	string a="";
	if ((offset) < ret->numargs)
		a = getarg2(ret->args[offset], ret->argtypes[offset], myvalues, mytokens, mytemps);

	realret->t = 0;
	realret->d = am->textlength(a);

	return realret;
}
Mytype* CommandWrapper::m_pasteicon(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);
	if ((offset+2) < ret->numargs)
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);

	am->pasteicon(a, b, c);
	return realret;
}

Mytype* CommandWrapper::m_hotspot(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0, b=0, c=0;
	if ((offset) < ret->numargs)
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
	if ((offset+1) < ret->numargs)
		b = (int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps);

	if ((offset+2) < ret->numargs)
	{
		c = (int)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps);
		am->hotspot(a, b, c);
	}
	else
	{
		am->hotspot(a, b);
	}

	return realret;
}

Mytype* CommandWrapper::m_paper(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset,
		Mytype *realret, Mytype* mytemps)
{
	int a=0;
	if ((offset) < ret->numargs)
	{
		a = (int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps);
		am->paper(a);
	}

	return realret;
}

// From 3Dlicious! (another project) - removed in jAMOS:
// 3Dlicious! functions...
Mytype* CommandWrapper::m_take(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	//realret->t = 0;
	//realret->d = myvalues->take();
	return realret;
}

Mytype* CommandWrapper::m_rotate(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	//myvalues->rotate(getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps),
	//                                      getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps),
	//                                      getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps));
	return realret;
}

Mytype* CommandWrapper::m_move(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	//myvalues->move(getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps),
	//                                      getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps),
	//                                      getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps));
	return realret;
}

Mytype* CommandWrapper::m_scale(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	//myvalues->setscale(getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps),
	//                                      getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps),
	//                                     getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps));
	return realret;
}

Mytype* CommandWrapper::m_setnode(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	//myvalues->setNode((int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps));
	return realret;
}

Mytype* CommandWrapper::m_selectusewith(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	//myvalues->selectUseWith();
	return realret;
}

Mytype* CommandWrapper::m_usewith(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	realret->t = 0;
	realret->d = 0;
	/*
    // Was if (ret->numargs == 0)
    if (ret->argtypes[offset] != 1)
    {
         realret->d = myvalues->myvars[5].d;
    }
    else if ((ret->argtypes[offset] == 1) && (myvalues->myvars[5].d == 1))
    {
        // A variable is given as a parameter. First, get the variable name:
        string varname = g->mytokens[myvalues->ObjectBrain].myvarnames[(int)ret->args[offset]];

        // Find the number of the brain which matches the variable name:
        int brainnum = -1;
        for (unsigned int n=0; n<g->mytokens.size(); n++)
        {
            if (g->mytokens[n].name == varname)
            {
               brainnum = n;
               break;
            }
        }        

        if (brainnum>=0)
        {
            // OK, we've found a matching brain name.
            // Now we want to check if the object used with this has that brain name.
            // The ID of the object used with this is in id2.
            if (g->ActiveObjects[myvalues->id2]->ObjectBrain == brainnum)
            {
                // Match! The object used with is of the specified type.
                // Set the variable name to the object number:
                myvalues->myvars[(int)ret->args[offset]].d = (double)myvalues->id2;
                // Return true
                realret->d = 1;
            }
        }
    }*/

	return realret;
}

Mytype* CommandWrapper::m_setothernode(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	//ActiveObject* target = g->ActiveObjects[(int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps)];
	//target->setNode((int)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps));
	return realret;
}

Mytype* CommandWrapper::m_kill(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	//myvalues->dead = 1;
	return realret;
}

Mytype* CommandWrapper::m_createinventoryobject(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	/*createInventoryObject((int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps),
                          getarg2(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytokens, mytemps),
                          getarg2(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytokens, mytemps),
                          (int)getarg(ret->args[offset+3], ret->argtypes[offset+3], myvalues, mytemps),
                          (int)getarg(ret->args[offset+4], ret->argtypes[offset+4], myvalues, mytemps),
                          (int)getarg(ret->args[offset+5], ret->argtypes[offset+5], myvalues, mytemps),
                          getarg(ret->args[offset+6], ret->argtypes[offset+6], myvalues, mytemps),
                          getarg(ret->args[offset+7], ret->argtypes[offset+7], myvalues, mytemps),
                          getarg(ret->args[offset+8], ret->argtypes[offset+8], myvalues, mytemps),
                          (int)getarg(ret->args[offset+9], ret->argtypes[offset+9], myvalues, mytemps));*/
	//createInventoryObject(0, "Ball of Light", "A mysterious glowing orb", 1, 1, 0, 20, 20, 0, 0);
	//setcaption("Well, I tried!");

	return realret;
}

Mytype* CommandWrapper::m_createActiveObject(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	/*realret->t = 0;
    realret->d = createActiveObject((int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps),
                          getarg2(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytokens, mytemps),
                          getarg2(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytokens, mytemps),
                          (int)getarg(ret->args[offset+3], ret->argtypes[offset+3], myvalues, mytemps),
                          (int)getarg(ret->args[offset+4], ret->argtypes[offset+4], myvalues, mytemps),
                          (int)getarg(ret->args[offset+5], ret->argtypes[offset+5], myvalues, mytemps),
                          getarg(ret->args[offset+6], ret->argtypes[offset+6], myvalues, mytemps),
                          getarg(ret->args[offset+7], ret->argtypes[offset+7], myvalues, mytemps),
                          getarg(ret->args[offset+8], ret->argtypes[offset+8], myvalues, mytemps),
                          (int)getarg(ret->args[offset+9], ret->argtypes[offset+9], myvalues, mytemps),
                          (int)getarg(ret->args[offset+10], ret->argtypes[offset+10], myvalues, mytemps),
                          (int)getarg(ret->args[offset+11], ret->argtypes[offset+11], myvalues, mytemps),
                          (int)getarg(ret->args[offset+12], ret->argtypes[offset+12], myvalues, mytemps));*/
	//realret->d = createActiveObject(9, "Serena's Tinkerbell", "I hope she doesn't kill it!", 0, 6, 0, 0.6, 0.6, 0.6, 2, -1500, 0, -1780);
	return realret;
}

Mytype* CommandWrapper::m_usewithme(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	//ActiveObject* target = g->ActiveObjects[(int)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps)];
	//myvalues->reverseUseWith(target);
	return realret;
}

Mytype* CommandWrapper::m_sound(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	/*
#ifdef __useaudio
	if (!(g->irrKlang))
		return realret;

    for (int n=offset; n<ret->numargs; n++)
       irrklang::ISound* snd =
		   g->irrKlang->play2D(getarg2(ret->args[n], ret->argtypes[n], myvalues, mytokens, mytemps), false, false, true);
#endif*/
	return realret;
}

Mytype* CommandWrapper::m_drop(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps)
{
	//realret->t = 0;
	//realret->d = myvalues->drop((double)getarg(ret->args[offset], ret->argtypes[offset], myvalues, mytemps),
	//		                            (double)getarg(ret->args[offset+1], ret->argtypes[offset+1], myvalues, mytemps),
	//	                            (double)getarg(ret->args[offset+2], ret->argtypes[offset+2], myvalues, mytemps));
	return realret;
}

