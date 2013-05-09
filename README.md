#getoption

A c++ platform-independent class to display multiple-choice questions. 

##Modes
The class has 4 modes of operation at the moment. These are: 
- Windows (auto-selected at compile time): 
 - Graphical (Using WINAPI) - #define GRAPHICAL before initialiasation to use 
 - Text - The default on Windows. Simple command-line interface 
- Linux (alternatively not Windows - again auto-selected): 
 - Graphical (Using gtk+ 3.2 or higher - might work with lower) - #define GRAPHICAL   before initialiasation to use 
 - Text - The default on Linux. Simple command-line interface 
		
##Features
- Ability to control (only in graphical mode so far):
 - Window class name (WINAPI - seemed like a good idea)
 - Window Title
 - Window height/width
 - Background colour
 - Button colour
 - Font used (including size)
- Easy to use - you define the content function, it does the rest
- No difference in usage between platforms
- Keyboard buttons "1","2" etc can be used instead of clicks in graphical mode (single-digit only)
- Demo program now included!

##Usage
1. If you want to, define graphical

    ```#define GRAPHICAL```
2. Include the class file
3. Declare (and define if you want) your "driver" function to match this template:
    
    ```dialog driver(int,int);```

	The return type is a struct defined in the file, and the 2 arguments are, in order, the status you told it to report (0 on startup) and the number of the button clicked (top=1).
4. Initialise the class
    
    ```getoption option("*class_name*","*window_name*",*width*,*height*,*background_r*,*background_g*,*background_b*,*button_r*,*button_g*,*button_b*,*font_size(pt)*,"*font_name*",*driver_function*);```
		
5. Define the main function (I want this in the class - any ideas, email me):
    
    ```(HASH)if (defined (__WIN32__) || (_MSC_VER)) && (defined GRAPHICAL)```
	
    ```int WINAPI WinMain(HINSTANCE inst, HINSTANCE p_inst, LPSTR arg, int nfs) { option.main(inst,p_inst,arg,nfs); }```

    ```(HASH)else```

    ```int main(int argc,char *argv[]) { option.main(argc,argv); }```

    ```(HASH)endif```

Just copy + paste these lines in for now.

##Contact
If you have any requests for future releases, feel free to email plpub2@gmail.com 

##Copyright
This class is Copyright (C) 2013  Peter Lotts. 
It is released under the GNU General Public Licence version 3. 

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
GNU General Public License for more details. 