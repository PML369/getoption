/*
 getoption-v2.cpp - class to present multi-choice interaction to a user
 Copyright (C) 2013  Peter Lotts

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <vector>
#include <string>
#include <sstream>

#if defined (__WIN32__) || (_MSC_VER)
	#if defined GRAPHICAL
		#include <Windows.h>
	#else
		#include <iostream>
		#include <conio.h>
	#endif
#else
	#if defined GRAPHICAL
		#include <gtk/gtk.h>
		#include <functional>
		#include <algorithm>
	#else
		#include <iostream>
		#include <cstdlib>
		#include <stdio.h>
		#include <termios.h>
	#endif
#endif

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

#if (defined (__WIN32__) || (_MSC_VER)) && (defined GRAPHICAL)
#define MAIN_MACRO(name) int WINAPI WinMain(HINSTANCE inst, HINSTANCE p_inst, LPSTR arg, int nfs) { return name.main(inst, p_inst, arg, nfs); }
#else
#define MAIN_MACRO(name) int main(int argc, char *argv[]) { return name.main(argc, argv); }
#endif

struct rgb_col { int r; int g; int b; };
struct dialog
{
	tstring title;
	int status_1st_opt;
	int status_other_opt;
	bool timer;
	std::vector<tstring> buttons;
};

class getoption
{
	public:
		getoption(std::string class_name, std::string window_name, int width, int height, int bg_colour_r, int bg_colour_g, int bg_colour_b, int button_colour_r, int button_colour_g, int button_colour_b, int font_size_pt, tstring font_name, dialog (*driver)(int, int));
		static tstring String(double Val);

		#if defined (__WIN32__) || (_MSC_VER)
			#if defined GRAPHICAL
				int WINAPI main(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil);
			#else
				int main(int argc,char *argv[]);
			#endif
		#else
			#if defined GRAPHICAL
				int main(int argc,char *argv[]);
			#else
				int main(int argc,char *argv[]);
			#endif
		#endif
	private:
		static	std::string	_class_name;
		static	std::string	_windowname;
		static	int		_windowwidth;
		static	int		_windowheight;
		static	rgb_col	_backgroundcol;
		static	rgb_col	_buttoncol;
		static	int		_fontsize; // pt
		static	tstring	_fontname;
		static	dialog	_data;
		static	dialog	_tmp;
		static	dialog (*_driver)(int, int);

		#if defined (__WIN32__) || (_MSC_VER)
			#if defined GRAPHICAL
				static	LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
				static	void draw_buttons(HWND);

				static	HINSTANCE _g_hInst;
				static	HWND _hwnd;
				static	HFONT _font;
				static	HDC _hdc;
				static	HBRUSH _buttonbrush;

				static	tstring _top_text;
				static	int _top_text_x;
				static	int _top_text_y;
				static	int _top_text_xfar;
				static	int _top_text_yfar;

				static	int _globalstatus;
				static	int _globalstatusfirstopt;
				static	std::vector<HWND> _hwndbutton;
			#else
				
			#endif
		#else
			#if defined GRAPHICAL
				/* GtkWidget is the storage type for widgets */
				static	GtkWidget	*_window;
				static	GtkWidget	*_button;
				static	GtkWidget	*_box1;
				static	GtkWidget	*_buttonlabel;
				static	std::vector<GtkWidget *> _buttons;
				static	GtkWidget	*_label;
				static	int			_globalstatus;
				static	int			_globalstatusfirstopt;
				static	GdkColor	_bgcol;
				static	GdkColor	_buttcol;

				struct IsWindow : public std::binary_function< GtkWidget *, GtkWidget *, bool >
				{
					bool operator () ( GtkWidget *totest, GtkWidget *against ) const
						{
							return totest == against;
						}
				};

				static void click( GtkWidget *widget, gpointer data );
				static void newdata(int clicked_button);
				static gint key_press_cb(GtkWidget *widget, GdkEventKey *kevent, gpointer data);
				static gboolean delete_event( GtkWidget *widget, GdkEvent  *event, gpointer   data );
				static void destroy( GtkWidget *widget, gpointer   data );
			#else
				char getch(void);
			#endif
		#endif
};

// Initialise statics...
std::string	getoption::_class_name;
std::string	getoption::_windowname;
int			getoption::_windowwidth;
int			getoption::_windowheight;
rgb_col		getoption::_backgroundcol;
rgb_col		getoption::_buttoncol;
int			getoption::_fontsize; // pt
tstring		getoption::_fontname;
dialog		getoption::_data;
dialog		getoption::_tmp;
dialog	(*	getoption::_driver)(int, int);

#if defined (__WIN32__) || (_MSC_VER)
	#if defined GRAPHICAL
		HINSTANCE	getoption::_g_hInst;
		HWND		getoption::_hwnd;
		HFONT		getoption::_font;
		HDC			getoption::_hdc;
		HBRUSH		getoption::_buttonbrush;
		tstring		getoption::_top_text;
		int			getoption::_top_text_x;
		int			getoption::_top_text_y;
		int			getoption::_top_text_xfar;
		int			getoption::_top_text_yfar;
		int			getoption::_globalstatus;
		int			getoption::_globalstatusfirstopt;
		std::vector<HWND> getoption::_hwndbutton;
	#else
				
	#endif
#else
	#if defined GRAPHICAL
		/* GtkWidget is the storage type for widgets */
		GtkWidget	*getoption::_window;
		GtkWidget	*getoption::_button;
		GtkWidget	*getoption::_box1;
		GtkWidget	*getoption::_buttonlabel;
		std::vector<GtkWidget *> getoption::_buttons;
		GtkWidget	*getoption::_label;
		int			getoption::_globalstatus=0;
		int			getoption::_globalstatusfirstopt=0;
		GdkColor	getoption::_bgcol;
		GdkColor	getoption::_buttcol;
	#else
				
	#endif
#endif

tstring getoption::String ( double Val )
{
	std::ostringstream Stream;
	Stream << Val;
	return Stream.str();
}
getoption::getoption(std::string class_name, std::string window_name, int width, int height, int bg_colour_r, int bg_colour_g, int bg_colour_b, int button_colour_r, int button_colour_g, int button_colour_b, int font_size_pt, tstring font_name, dialog (*driver)(int, int))
{
	_class_name=class_name.c_str();
	_windowname=window_name.c_str();
	_windowwidth=width;
	_windowheight=height;
	_backgroundcol.r=bg_colour_r; _backgroundcol.g=bg_colour_g; _backgroundcol.b=bg_colour_b;
	_buttoncol.r=button_colour_r; _buttoncol.g=button_colour_g; _buttoncol.b=button_colour_b;
	_fontsize=font_size_pt;
	_fontname=font_name;
	_driver=driver;
}


#if defined (__WIN32__) || (_MSC_VER)
	#if defined GRAPHICAL 
		int WINAPI getoption::main(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
		{
			_buttonbrush=CreateSolidBrush(RGB(_buttoncol.r,_buttoncol.g,_buttoncol.b));

			MSG messages;            /* Here messages to the application are saved */
			WNDCLASSEX wincl;        /* Data structure for the windowclass */

			/* The Window structure */
			_g_hInst = hThisInstance;
			wincl.hInstance = hThisInstance;
			wincl.lpszClassName = _class_name.c_str();
			wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
			wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
			wincl.cbSize = sizeof (WNDCLASSEX);

			/* Use default icon and mouse-pointer */
			wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
			wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
			wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
			wincl.lpszMenuName = NULL;                 /* No menu */
			wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
			wincl.cbWndExtra = 0;                      /* structure or the window instance */
			/* Use Windows''s default color as the background of the window */
			wincl.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(_backgroundcol.r,_backgroundcol.g,_backgroundcol.b))/*(COLOR_BTNFACE+1)*/;

			/* Register the window class, and if it fails quit the program */
			if (!RegisterClassEx (&wincl))
				return 0;

			/* The class is registered, let's create the program*/
			_hwnd = CreateWindowEx (
		           0,                   /* Extended possibilites for variation */
				   _class_name.c_str(), /* Classname */
				   _windowname.c_str(), /* Title Text */
		           WS_OVERLAPPEDWINDOW, /* default window */
		           CW_USEDEFAULT,       /* Windows decides the position */
		           CW_USEDEFAULT,       /* where the window ends up on the screen */
				   _windowwidth,        /* The programs width */
		           _windowheight,       /* and height in pixels */
		           HWND_DESKTOP,        /* The window is a child-window to desktop */
		           NULL,                /* No menu */
		           hThisInstance,       /* Program Instance handler */
		           NULL                 /* No Window Creation data */
		           );

			//-----------------------------------------------------------------------------------------------------------------------------------
			// Other Execution

			_hdc = GetDC(NULL);
			long lfHeight = -MulDiv(_fontsize, GetDeviceCaps(_hdc, LOGPIXELSY), 72);
			ReleaseDC(NULL, _hdc);

			_font = CreateFont(lfHeight, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, _fontname.c_str());

			if(_font)
				{
					//DeleteObject(g_hfFont);
					//g_hfFont = font;
				}
			else
				{
				    MessageBox(_hwnd, "Font creation failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
				}

			//-----------------------------------------------------------------------------------------------------------------------------------

			/* Make the window visible on the screen */
			ShowWindow (_hwnd, SW_SHOW);
			UpdateWindow(_hwnd);

			/* Run the message loop. It will run until GetMessage() returns 0 */
		    while (GetMessage (&messages, NULL, 0, 0))
		    {
				if(!IsDialogMessage(_hwnd,&messages))
					{
						/* Translate virtual-key messages into character messages */
						TranslateMessage(&messages);
						/* Send message to WindowProcedure */
						DispatchMessage(&messages);
					}
		    }
			/* The program return-value is 0 - The value that PostQuitMessage() gave */
			return static_cast<int>(messages.wParam);
		}
		LRESULT CALLBACK getoption::WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)                 /* Handles all Windows Messages */
			{
				case WM_COMMAND:
				{
					if(((HWND)lParam) && (HIWORD(wParam) == BN_CLICKED))
					{
						int iMID;
						iMID = LOWORD(wParam);
						// A button was clicked
						if ((iMID >= 10) && (iMID < 130)) // One of our buttons was clicked - doesn't matter which one
						{
							int option=((iMID-10)/4)+1; // -10+1
							// Get new data
							if (option == 1) { _tmp=_driver(_globalstatusfirstopt,option); } else { _tmp=_driver(_globalstatus,option); }
							if (_tmp.buttons.size() != 0) { _data=_tmp; }
							
							draw_buttons(hwnd);

							_globalstatusfirstopt=_data.status_1st_opt;
							_globalstatus=_data.status_other_opt;
						}
					}
							
					if (LOWORD(wParam) == IDOK)
					{
						// enter pressed in an editbox (could be any - needs tracking)
					}
					break;
				}
				case WM_KEYDOWN:
				{
					unsigned int keynum=((unsigned int)wParam - 0x30);
					if (keynum <= _hwndbutton.size())
					{
						SendMessage(_hwndbutton[keynum-1],BM_CLICK,0,0);
					}
				}
				case WM_DRAWITEM:
				{
					LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
					if (std::find(_hwndbutton.begin(), _hwndbutton.end(), pDIS->hwndItem) != _hwndbutton.end())
					{
						RECT prc=pDIS->rcItem; // Rectangle is that of the button
						// Get text of text box
						int bufSize = 1024;
						LPTSTR szText = new TCHAR[bufSize];
						GetDlgItemText(hwnd, (int)wParam, szText, bufSize);
						// Fill button
						FillRect(pDIS->hDC,&prc,_buttonbrush);
						SetBkMode(pDIS->hDC,TRANSPARENT);
						// Select font
						HFONT hfOld = (HFONT)SelectObject(_hdc, _font);
						DrawText(pDIS->hDC, szText/*butttext.c_str()*/, -1, &prc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					}
					return TRUE;
				}
		        case WM_DESTROY:
				{
					PostQuitMessage (0);       /* send a WM_QUIT to Message Queue, to shut off program */
					break;
				}
		
		        case WM_CREATE:
				{
					/* fill window with intial objects.*/
					
					// Get new data
					_tmp=_driver(0,0); if (_tmp.buttons.size() != 0) { _data=_tmp; }

					draw_buttons(hwnd);

					_globalstatusfirstopt=_data.status_1st_opt;
					_globalstatus=_data.status_other_opt;
					break;
				}
				case WM_PAINT:
				{
					PAINTSTRUCT ps;
					_hdc = BeginPaint(hwnd, &ps);
		            if (_top_text != "")
					{
						SetBkMode( _hdc, TRANSPARENT );
						HFONT hfOld = (HFONT)SelectObject(_hdc, _font);
						RECT prc;
						prc.left=_top_text_x;   prc.top=_top_text_y;   prc.right=_top_text_xfar;   prc.bottom=_top_text_yfar;
						DrawText(_hdc, _top_text.c_str(), -1, &prc, DT_CENTER | DT_WORDBREAK);
					}
		            EndPaint(hwnd, &ps);
				}
		        default:                      /* messages that we will not process */
		            return DefWindowProc (hwnd, message, wParam, lParam);
		    }
		    return 0;
		}
		void getoption::draw_buttons(HWND parent)
		{
			// Destroy all current buttons
			for (unsigned int y=0; y < _hwndbutton.size(); y++)
			{
				DestroyWindow(_hwndbutton[y]);
			}
			_hwndbutton.clear();
			
			_top_text=_data.title;
			_top_text_x=25;
			_top_text_y=25;
			_top_text_xfar=_windowwidth-25;
			_top_text_yfar=65;
		
			InvalidateRect(parent, NULL, TRUE); //tells windows that the whole client area needs to be repainted
						
			for (unsigned int i=0; i < _data.buttons.size(); i++)
			{
				/*Keep this one, to keep the comments which are not on the copies.*/
				_hwndbutton.push_back(CreateWindowEx(0,		/* more or 'extended' styles */
					TEXT("BUTTON"),							/* GUI 'class' to create */
					_data.buttons.at(i).c_str(),			/* GUI caption */
					WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_OWNERDRAW,/* control styles separated by | */
					25,										/* LEFT POSITION (Position from left) */
					(80+(50*i)-10),						/* TOP POSITION  (Position from Top) */
					_windowwidth-60,						/* WIDTH OF CONTROL */
					40,										/* HEIGHT OF CONTROL */
					parent,									/* Parent window handle */
					(HMENU)10+i,								/* control's ID for WM_COMMAND */
					_g_hInst,								/* application instance */
					NULL));
				ShowWindow(_hwndbutton.at(i),SW_SHOW);
			}
		}
	#else
		#include <iostream>
		#include <conio.h>
		int getoption::main(int argc,char *argv[])
		{
			_tmp=_driver(0,0); if (_tmp.buttons.size() != 0) { _data=_tmp; }
			while (true)
			{
				std::cout << _data.title << std::endl;
				for (unsigned int i=0; i < _data.buttons.size(); i++)
				{
					std::cout << String(i+1) << " - " << _data.buttons.at(i) << std::endl;
				}
				int option=_getch()-48;
				if (option == 1) { _tmp=_driver(_data.status_1st_opt,option); } else { _tmp=_driver(_data.status_other_opt,option); }
				if (_tmp.buttons.size() != 0) { _data=_tmp; }
				system("CLS");
			}
			return 0;
		}
	#endif
#else
	#if defined GRAPHICAL
		#include <gtk/gtk.h>
		#include <functional>
		#include <algorithm>

		void getoption::newdata(int clicked_button)
		{
			for (int i=0; i < _buttons.size(); i++)
			{
				gtk_widget_destroy(_buttons.at(i));
			}
			if (GTK_IS_WIDGET(_label)) { gtk_widget_destroy(_label); }
			_buttons.clear();

			if (clicked_button == 1) { _tmp=_driver(_globalstatusfirstopt,clicked_button); } else { _tmp=_driver(_globalstatus,clicked_button); }
			if (_tmp.buttons.size() != 0) { _data=_tmp; }

			_globalstatusfirstopt=_data.status_1st_opt;
			_globalstatus=_data.status_other_opt;

			_label=gtk_label_new(_data.title.c_str()); /* Create label */
			gtk_label_set_justify(GTK_LABEL(_label), GTK_JUSTIFY_CENTER); /* Centre it */
			gtk_widget_modify_font (_label, pango_font_description_from_string ((_fontname + " " + String(_fontsize)).c_str())); /* Set font + size */
			gtk_box_pack_start (GTK_BOX(_box1), _label, FALSE, FALSE, 5); /* Put it in the box */
			gtk_widget_show(_label); /* Show it */
    
			for (int i=0; i < _data.buttons.size(); i++)
			{
				/* Creates a new button with the desired label. */
				_buttons.push_back(gtk_button_new_with_label (_data.buttons.at(i).c_str()));
    
				/* When the button receives the "clicked" signal, it will call the function hello() passing it NULL as its argument.  The click()*/
				g_signal_connect (_buttons.at(i), "clicked", G_CALLBACK (click), NULL);
				gtk_widget_set_size_request(GTK_WIDGET(_buttons.at(i)),_windowwidth-60,40);
				gtk_widget_modify_bg (_buttons.at(i), GTK_STATE_NORMAL, &_buttcol);
				_buttonlabel=gtk_bin_get_child(GTK_BIN(_buttons.at(i)));
				gtk_widget_modify_font (_buttonlabel, pango_font_description_from_string ((_fontname + " " + String(_fontsize)).c_str()));
				gtk_box_pack_start (GTK_BOX(_box1), _buttons.at(i), FALSE, FALSE, 5); /* Instead of gtk_container_add, we pack this button into the invisible box.*/
				gtk_widget_show (_buttons.at(i)); /* The final step is to display this newly created button. */
			}
		}
		/* This is a callback function. */
		void getoption::click( GtkWidget *widget, gpointer data )
		{
			size_t index = std::distance(_buttons.begin(), std::find_if(_buttons.begin(), _buttons.end(), std::bind2nd( IsWindow(), widget)));
			if (index == _buttons.size()) { /* invalid */ }
    	
			//g_print (((std::string)"Hello World" + String(index) + (std::string)"\n").c_str());
			newdata(index + 1);
		}
		gint getoption::key_press_cb(GtkWidget *widget, GdkEventKey *kevent, gpointer data)
		{
			int key=(kevent->keyval)-48;
			if (key == 0) { key=10; }
			if (key <= _buttons.size())
			{
				g_signal_emit_by_name(G_OBJECT(_buttons.at(key-1)), "activate", NULL);
			}
			return TRUE;
		}
		gboolean getoption::delete_event( GtkWidget *widget, GdkEvent  *event, gpointer   data )
		{
			/* If you return FALSE in the "delete-event" signal handler, GTK will emit the "destroy" signal.
				* Returning TRUE means you don't want the window to be destroyed.
				* This is useful for popping up 'are you sure you want to quit?' type dialogs. */
			return FALSE;
		}
		/* Another callback */
		void getoption::destroy( GtkWidget *widget, gpointer   data )
		{
			gtk_main_quit ();
		}
		int getoption::main( int argc, char *argv[] )
		{
			_bgcol.red  =257*_backgroundcol.r; _bgcol.green  =257*_backgroundcol.g; _bgcol.blue  =257*_backgroundcol.b;
			_buttcol.red=257*_buttoncol.r;     _buttcol.green=257*_buttoncol.g;     _buttcol.blue=257*_buttoncol.b;

			gtk_init (&argc, &argv); /* This is called in all GTK applications. Arguments are parsed from the command line and are returned to the application. */

			_window = gtk_window_new (GTK_WINDOW_TOPLEVEL); /* create a new window */
			gtk_window_set_title (GTK_WINDOW (_window), _windowname.c_str()); /* Set title */
			gtk_widget_set_size_request(GTK_WIDGET(_window),_windowwidth,_windowheight);
			gtk_widget_modify_bg (_window, GTK_STATE_NORMAL, &_bgcol);
			gtk_container_set_border_width (GTK_CONTAINER (_window), 10); /* Sets the border width of the window. */
    
			/* When the window is given the "delete-event" signal (this is given
				* by the window manager, usually by the "close" option, or on the
				* titlebar), we ask it to call the delete_event () function
				* as defined above. The data passed to the callback
				* function is NULL and is ignored in the callback function. */
			g_signal_connect (_window, "delete-event", G_CALLBACK (delete_event), NULL);
    
			/* Here we connect the "destroy" event to a signal handler.  
				* This event occurs when we call gtk_widget_destroy() on the window,
				* or if we return FALSE in the "delete-event" callback. */
			g_signal_connect (_window, "destroy", G_CALLBACK (destroy), NULL);
			g_signal_connect(G_OBJECT(_window), "key_press_event", G_CALLBACK(key_press_cb), NULL); /* connect key presses to activate buttons */

			_box1 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0); /* We create a box to pack widgets into. The box is not really visible, it is just used as a tool to arrange widgets. */
			gtk_container_add (GTK_CONTAINER (_window), _box1); /* Put the box into the main window. */
    
			newdata(0);

			gtk_widget_show(_box1); /* Show the box */
			gtk_widget_show (_window); /* and the window */
    
			/* All GTK applications must have a gtk_main(). Control ends here
				* and waits for an event to occur (like a key press or mouse event). */
			gtk_main ();
			return 0;
		}
	#else
		#include <iostream>
		#include <cstdlib>

		#include <stdio.h>
		#include <termios.h>
		#include <unistd.h>

		char getoption::getch(void)
		{
			char buf = 0;
			struct termios old = {0};
			if (tcgetattr(0, &old) < 0)
				perror("tcsetattr()");
			old.c_lflag &= ~ICANON;
			old.c_lflag &= ~ECHO;
			old.c_cc[VMIN] = 1;
			old.c_cc[VTIME] = 0;
			if (tcsetattr(0, TCSANOW, &old) < 0)
				perror("tcsetattr ICANON");
			if (read(0, &buf, 1) < 0)
				perror ("read()");
			old.c_lflag |= ICANON;
			old.c_lflag |= ECHO;
			if (tcsetattr(0, TCSADRAIN, &old) < 0)
				perror ("tcsetattr ~ICANON");
			return (buf);
		}

		int getoption::main(int argc,char *argv[])
		{
			_tmp=_driver(0,0); if (_tmp.buttons.size() != 0) { _data=_tmp; }
			while (true)
			{
				std::cout << _data.title << std::endl;
				for (unsigned int i=0; i < _data.buttons.size(); i++)
				{
					std::cout << String(i+1) << " - " << _data.buttons.at(i) << std::endl;
				}
				int option=getch()-48;
				if (option == 1) { _tmp=_driver(_data.status_1st_opt,option); } else { _tmp=_driver(_data.status_other_opt,option); }
				if (_tmp.buttons.size() != 0) { _data=_tmp; }
				system("clear");
			}
			return 0;
		}
	#endif
#endif