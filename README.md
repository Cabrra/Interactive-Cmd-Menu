Menu Manager Project
====================

Contained in the Project1Resources folder on the server you will find a collection of .mnu files which you will use to load the various options/submenus available to the player. The main.mnu file is always be the first menu loaded and presented to the user. Each menu file contains the name of the menu, the number of options, and the options themselves.  

A menu file looks something like this:  

DS Test Menu  
6  
MENU "Start" "play.mnu"  
MENU "Options" "opt.mnu"  
MENU "Help" "help.mnu"  
OPTION "CMD Test Project"  
OPTION "Full Sail"  
OPTION "Game Design and Development"  

The first line of the file contains the title of the menu. In this example “DS Test Menu” is the title.
The second line of the file contains the number of items that will be loaded from the file for this menu. In this example, we will load 6 items from the file. The remaining lines in the file will contain the menu items, one per line. The first tag is either the keyword OPTION or MENU. The second tag is the name of that item. The third tag is only found on MENU items. It contains the name of the submenu file to load next.

## Controls

+ Up/Down arrow keys: 								move the cursor
+ Enter:												make a selection
+ Exit option added at the bottom of every menu:		Selecting takes you back to previous menu
+ SLList class:										keeps track of the previous menus.
+ The Cursor starts at the top of each submenu
+ Selecting exit from the main menu exits the program
+ The cursor exhibits wraparound behavior.
+ The title is displayed on the top of each menu.
+ Main.mnu is the only file hardcoded. All other filenames are loaded from this file and the submenu files dynamically.

## Prerequisites

This project is based on some custom data structures implemented on one of my [repos](https://github.com/Cabrra/Data-Structures).

## Built With

* [Visual Studio](https://visualstudio.microsoft.com/)	- C++ development
* Run with Windows CMD

## Contributing

Please read [CONTRIBUTING.md](https://github.com/Cabrra/Contributing-template/blob/master/Contributing-template.md) for details on the code of conduct, and the process for submitting pull requests to me.

## Authors

* **Jagoba "Jake" Marcos** - [Cabrra](https://github.com/Cabrra)

## License

This project is licensed under the MIT license - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* Full Sail University - Game Development Department
* Rodney Stoeffler
