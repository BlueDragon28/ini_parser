# About

Ini_parser is a little C++ library to open and parse .ini config file. The library support a flexible syntax. You can add space at the beginning or add spaces before and after the `=`. All the lignes starting with `#` are ignores. It's also possible to add a comment after a parameter line.

# Compilation

To compile the ini_parser library, you need a C++11 compliant compiler, [CMake](https://cmake.org/) and [git](https://git-scm.com/).

By default CMake will compile the library in static. To compile the dynamic library enable the option `BUILD_SHARED_LIBS`.

## Options

- `BUILD_STATIC_LIBS` (enabled by default) : build the static library, the library is named `libini_parser_static.a` (or `ini_parser_static.lib` on Windows).
- `BUILD_SHARED_LIBS` (disabled by default) : build the shared library, the library is named `libini_parser.so` (or `ini_parser.lib` on Windows).

# How to use

Include the library header into your project
``` C++
#include <ini_parser.h>
```
Create the `ini_parser` object with the path to the .ini file.
```C++
ini_parser parser("Path/To/IniFile.ini");
```
Use the method `getValue` to get a value from the ini file.
``` C++
std::string value = parser.getValue("Section", "Parameters");
```

## Methods prototype

There is 3 constructors in the class. One default contructor and 2 override constructor.
``` C++
ini_parser();
ini_parser(const char* iniFile, bool isFile = true);
ini_parser(const std::string& iniFile, bool isFile = true);
```
If you want to pass the data of a `.ini` file and not the file path, set the `isFile` parameter to false.

To check is the file has been parsed used the `isParsed` method :
``` C++
bool isParsed() const;
```

To get the value of a parameter of a section, use the `getValue` method :
``` C++
const char* getValue(const char* section, const char* parameters, bool* isExist = nullptr) const;
const std::string& getValue(const std::string& section, const std::string& parameters, bool* isExist = nullptr) const;
```
Pass a bool pointer in the `isExist` parameters to know if the parameters or the section exist.

To open a new file without recreating a new object, use the `setIniFile` method :
``` C++
void setIniFile(const char* iniFile, bool isFile);
void setIniFile(const std::string& iniFile, bool isFile);
```

## Use for a regular **.conf** file

The library can also be used for regular **.conf** file that do not have any sections. The parameters of this file are attached to a section with an empty name string. To retrieve this parameters, there is an override of **getValue** :

``` C++
const char* getValue(const char* parameters, bool* isExist = nullptr) const;
const std::string& getValue(const std::string& parameters, bool* isExist = nullptr) const;
```

# Syntax

The library support a flexible `.ini` file syntax, here an exemple of what possible :

``` INI
# A Comment

# Param not attached to any sections.
MyParam = My Value

[Section1]
Param1=Value1

  Param2 = Value2  # Another comment
```

# License

The library is licensed under the MIT license. Check the [license](https://github.com/Erwan28250/ini_parser/blob/development/LICENSE) file.