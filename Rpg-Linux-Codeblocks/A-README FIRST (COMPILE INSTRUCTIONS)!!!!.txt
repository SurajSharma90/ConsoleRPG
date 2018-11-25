This is the version that works with Code::Blocks and other IDE's as well as for Linux!
Go into the linux_example folder and read the instructions to understand what's what.
To compile this program, type: "bash compile.sh" from this directory or type: "make main".
To clean the solution, type: "make clean" from this directory.
To open the project in Code::Blocks open the Rpg.cbp file.

Rules for coding in Code::Blocks:
Make sure to follow these rules:
To get code to work on code::blocks and linux:
- Do not use std::to_string, instead include sstream and use the std::stringstream type.
- Do not use the keyword nullptr, use NULL.
- Do not use enums like this: enums::ENUM, instead use ENUM key directly.
- When passing strings as parameters to ifstream and ofstream objects, make sure to use; filename.c_str()
- Do not use #pragma once, instead use: 
#ifndef FILENAME_H
#define FILENAME_H

//code ...

#endif