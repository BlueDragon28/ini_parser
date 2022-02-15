/*
MIT License

Copyright (c) 2022 Erwan Saclier de la Bâtie

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef INI_PARSER_H_
#define INI_PARSER_H_

#include <string>
#include <vector>

/*
This class is used to open a ini file
and parsing it. It's goal is to offer
a very simple way to open ini files.
*/
class ini_parser
{
public:
    /*
    Creating an instance of the ini_parser
    class and opening a ini file passing using
    the iniFile parameters. The isFile param is
    indicating if the iniFile param is a file path
    or the file data.
    */
    ini_parser();
    ini_parser(const char* iniFile, bool isFile = true);
    ini_parser(const std::string& iniFile, bool isFile = true);

    /*
    Return the ini file path or data.
    */
    const std::string& iniFile() const;

    /*
    Return if the data passed by the users is a
    file path or a file data.
    */
    bool isFile() const;

    /*
    Return if the ini data has been parsed properly.
    */
    bool isParsed() const;

    /*
    Return the value of the parameters (parameters)
    of the section (section).
    */
    const char* getValue(const char* section, const char* parameters, bool* isExist = nullptr) const;
    const std::string& getValue(const std::string& section, const std::string& parameters, bool* isExist = nullptr) const;

    /*
    Set the ini file path or data and parse it.
    */
    void setIniFile(const char* iniFile, bool isFile);
    void setIniFile(const std::string& iniFile, bool isFile);

protected:
    /*
    Check whether to parse has a file
    or has a data.
    */
    void parse();
    /*
    Parse has a file.
    */
    void parseFile();
    /*
    Parse as a data. (the data 
    of a ini file have been passed into the parameters iniFile
    of the constructor).
    */
    void parseData();
    
    /*
    Parse a single line of the ini data.
    */
    virtual void parseLine(const std::string& line, std::string& currentSection);

    /*
    Set the value (value) of the parameters (parameters)
    of the section (section) in the parsed list.
    */
    void setValue(const char* section, const char* parameters, const char* value);
    void setValue(const std::string& section, const std::string& parameters, const std::string& value);

    /*
    Remove the parameters (parameters) of the section (section)
    of the parsed list.
    */
    void removeParameters(const char* section, const char* parameters);
    void removeParameters(const std::string& section, const std::string& parameters);

    /*
    Remove the section (section) of the parsed list.
    */
    void removeSection(const char* section);
    void removeSection(const std::string& section);

    /*
    Indicate that the parsing has been successfull.
    */
    void parsingSuccess();

    /*
    Remove the first and last spaces of a string.
    */
    static void removeSpaces(std::string& value);
    /*
    Remove only the first space of a string.
    */
    static void removeFirstSpaces(std::string& value);

private:
    /*
    A structure storing a parameters and
    it's value. The name variable is the
    name of the parameters and the value
    is the value of the parameters.
    Ex : name=value.
    */
    struct Parameter
    {
        /*
        The name of the parameters.
        */
        std::string name;
        /*
        The value fo the parameters.
        */
        std::string value;
    };

    /*
    A structure storing all the parameters
    and the values of a section.
    */
    struct Section
    {
        /*
        The name of the section.
        */
        std::string name;
        /*
        All the parameters of the section.
        */
        std::vector<Parameter> params;
    };

    /*
    The ini file path or data.
    */
    std::string m_iniFile;
    /*
    If the m_iniFile parameters is
    a filePath or a file data.
    */
    bool m_isFile;
    /*
    All the sections of the ini file.
    */
    std::vector<Section> m_sections;
    /*
    If the ini have been parsed properly.
    */
    bool m_isParsed;

    // Empty string
    static const std::string m_nullString;
};

#endif // INI_PARSER_H_