#ifndef COMMANDWRAPPER_H
#define COMMANDWRAPPER_H

#include "Game.h"
#include "ActiveObject.h"
#include "Mytype.h"
#include "TheTokens.h"
#include "TokeniserReturn.h"
#include "AMOS_System.h"

class AMOS_System;

class CommandWrapper
{
public:
	// Added init method:
	Game* g;

	// Added from jAMOS:
	AMOS_System* am;

	CommandWrapper(Game* g_, AMOS_System* am_);
	//CommandWrapper(Game* g_);

	// TODO - move these - copied from Interpreter:
	string floattostring(double value);
	double getarg(double arg, int argtype, ActiveObject *myvalues, Mytype* mytemps);
	char* getarg2(double arg, int argtype, ActiveObject *myvalues, TheTokens* mytokens, Mytype* mytemps);
	int isnumber(double arg, int argtype, ActiveObject *myvalues, Mytype* mytemps);

	Mytype *runfunction(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);

	// Special functions:
	Mytype* m_paramstring(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_paramfloat(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_param(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_getarrayvalue(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);


	// User-defined functions:
	Mytype* m_dummyfunction(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_double(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_print(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_say(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_instr(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_substring(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);

	// jAMOS ported functions:
	Mytype* m_screenopen(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_screendisplay(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_screenoffset(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_screenclose(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_screenclone(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_screen(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_doublebuffer(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_dualplayfield(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_dualpriority(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_loadiff(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_load(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_erase(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_hideon(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_updateevery(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_flashoff(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_flash(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_setrainbow(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_rainbowdel(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_rainbow(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_boboff(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_bob(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_setbob(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_spriteoff(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_sprite(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_setspritebuffer(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_setreg(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_unpack(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_channeltosprite(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_channeltobob(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_channeltoscreenoffset(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_channeltoscreensize(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_channeltorainbow(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_channeltoscreendisplay(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_bell(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_xmouse(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_ymouse(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_mousekey(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_xscreen(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_yscreen(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_xhard(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_yhard(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_joy(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_jleft(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_jright(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_jup(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_jdown(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_fire(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_xsprite(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_ysprite(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_isprite(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_xbob(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_ybob(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_ibob(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_pastebob(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_plot(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_ink(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_draw(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_bar(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_box(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_circle(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_ellipse(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_rnd(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_hrev(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_vrev(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_rev(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_rain(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_degree(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_radian(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_sin(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_cos(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_tan(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_asin(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_acos(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_atan(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_pi(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_left(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_right(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_mid(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_len(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_upper(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_lower(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_string(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_repeat(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_space(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_flip(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_val(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_str(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_asc(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_chr(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_boom(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_shoot(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_bobcol(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_spritecol(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_spritebobcol(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_bobspritecol(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_col(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_text(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_textlength(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_pasteicon(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_hotspot(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_paper(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);

	// 3Dlicious! functions:
	Mytype* m_take(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_rotate(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_move(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_scale(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_setnode(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_selectusewith(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_usewith(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_setothernode(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_kill(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_createinventoryobject(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_createActiveObject(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_usewithme(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_sound(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
	Mytype* m_drop(TokeniserReturn* ret, TheTokens* mytokens, ActiveObject *myvalues, int offset, Mytype *realret, Mytype* mytemps);
};
#endif
