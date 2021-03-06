// Demo program for getoption-v2.cpp
// Copyright (C) 2013  Peter Lotts
#define GRAPHICAL

#include "getoption-v2.cpp"

dialog d(int status, int button);
getoption option("demo","Getoption Demo Program",640,480,0,255,255,255,0,0,16,"Times New Roman",d);

MAIN_MACRO(option)

dialog d(int status, int button)
{
	dialog ret;

	if ((status == 1) && (button == 1))
	{
		ret.title="page 2";
		ret.status_1st_opt=0;
		ret.status_other_opt=0;
		ret.buttons.push_back("click me to return");
	}
	else
	{
		ret.title="Test";
		ret.status_other_opt=0;
		ret.status_1st_opt=1;
		ret.buttons.push_back("Button1");
		ret.buttons.push_back("Button2");
		ret.buttons.push_back("Button3");
	}
	
	return ret;
}