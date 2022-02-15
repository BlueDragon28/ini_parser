#include "ini_parser.h"
#include <fstream>
#include <sstream>

const std::string ini_parser::m_nullString = std::string();

ini_parser::ini_parser() :
    m_isFile(false),
    m_isParsed(false)
{}

ini_parser::ini_parser(const char* iniFile, bool isFile) :
    m_iniFile(iniFile),
    m_isFile(isFile),
    m_isParsed(false)
{
    parse();
}

ini_parser::ini_parser(const std::string& iniFile, bool isFile) :
    m_iniFile(iniFile),
    m_isFile(isFile),
    m_isParsed(false)
{
    parse();
}

void ini_parser::parse()
{
    // Check if the m_iniFile is a file path or a file data.
    if (m_isFile)
        parseFile();
    else
        parseData();
}

void ini_parser::parseFile()
{
    // Parsing the m_iniFile file.
    if (m_iniFile.empty())
        return;
    
    // Opening the ini file.
    std::ifstream file(m_iniFile);
    if (file.is_open())
    {
        std::string currentSection;
        std::string line;

        while (std::getline(file, line))
            parseLine(line, currentSection);
    }

    parsingSuccess();
}

void ini_parser::parseData()
{
    // Parsing the m_iniFile as ini data.
    if (m_iniFile.empty())
        return;
    
    // Streaming the string.
    std::istringstream data(m_iniFile);
    std::string currentSection;
    std::string line;
    while (std::getline(data, line))
        parseLine(line, currentSection);
    
    parsingSuccess();
}

void ini_parser::parseLine(const std::string& line, std::string& currentSection)
{
    // Parsing a single line of a ini file.
    if (line.size() == 0)
        return;
    
    // Retrieve the section name.
    if (line.at(0) == '#')
        return;
    else if (line.at(0) == '[')
    {
        size_t pos = line.find_first_of(']');
        if (pos < line.size())
        {
            currentSection.clear();
            currentSection.append(
                std::next(line.cbegin(), 1),
                std::next(line.cbegin(), pos));
            removeSpaces(currentSection);
        }
    }
    // Retrieve the parameters and values
    else
    {
        /*
        Do not parse parameters if there are no attached
        to any sections.
        */
        if (currentSection.empty())
            return;

        size_t pos = line.find_first_of('=');
        if (pos < line.size() && pos > 0)
        {
            std::string paramName;
            std::string valueName;

            paramName.append(
                line.cbegin(),
                std::next(line.cbegin(), pos));
            
            if (pos+1 < line.size())
                valueName.append(
                    std::next(line.cbegin(), pos+1),
                    line.cend());
                
            removeSpaces(paramName);
            removeSpaces(valueName);
            
            setValue(currentSection, paramName, valueName);
        }
    }
}

void ini_parser::setValue(const char* section, const char* parameters, const char* value)
{
    setValue(std::string(section), std::string(parameters), std::string(value));
}

void ini_parser::setValue(const std::string& section, const std::string& parameters, const std::string& value)
{
    // Setting the value of the parameters of the section (section).
    Section* pSection = nullptr;

    // Find existing section.
    for (std::vector<Section>::iterator it = m_sections.begin();
         it != m_sections.end();
         it++)
    {
        if (it->name == section)
        {
            pSection = &(*it);
            break;
        }
    }

    // If no section found, create a new one.
    if (pSection == nullptr)
    {
        Section sec = {};
        sec.name = section;
        m_sections.push_back(sec);
        pSection = &m_sections.at(m_sections.size()-1);
    }

    Parameter *pParam = nullptr;
    // Find existing parameters
    /*for (size_t i = 0; i < pSection->params.size(); i++)
    {
        if (pSection->params.at(i).name == parameters)
        {
            pParam = &pSection->params.at(i);
            break;
        }
    }*/
    for (std::vector<Parameter>::iterator it = pSection->params.begin();
         it != pSection->params.end();
         it++)
    {
        if (it->name == parameters)
        {
            pParam = &(*it);
            break;
        }
    }

    // If no parameters found, create a new one.
    if (pParam == nullptr)
    {
        ini_parser::Parameter param = {};
        param.name = parameters;
        pSection->params.push_back(param);
        pParam = &pSection->params.at(pSection->params.size()-1);
    }

    // Set the value of the parameters.
    pParam->value = value;
}

void ini_parser::removeParameters(const char* section, const char* parameters)
{
    removeParameters(std::string(section), std::string(parameters));
}

void ini_parser::removeParameters(const std::string& section, const std::string& parameters)
{
    // Removing a parameters of a given section.
    Section* pSection = nullptr;

    // Find the section.
    for (std::vector<Section>::iterator it = m_sections.begin();
         it != m_sections.end();
         it++)
    {
        if (it->name == section)
        {
            pSection = &(*it);
            break;
        }
    }

    // Remove the parameters from the section.
    for (std::vector<Parameter>::const_iterator it = pSection->params.cbegin();
         it != pSection->params.cend();
         it++)
    {
        if (it->name == parameters)
        {
            pSection->params.erase(it);
            break;
        }
    }
}

void ini_parser::removeSection(const char* section)
{
    removeSection(std::string(section));
}

void ini_parser::removeSection(const std::string& section)
{
    // Removing a section.
    for (std::vector<Section>::const_iterator it = m_sections.cbegin();
         it != m_sections.cend();
         it++)
    {
        if (it->name == section)
        {
            m_sections.erase(it);
            break;
        }
    }
}

void ini_parser::parsingSuccess()
{
    m_isParsed = true;
}

void ini_parser::removeSpaces(std::string& value)
{
    // Removing the first and the last spaces from a string.
    // Removing the first spaces.
    while (value.size() > 0)
    {
        if (value.at(0) == ' ')
            value.erase(0, 1);
        else
            break;
    }

    // Removing the last spaces.
    for (std::string::const_reverse_iterator rit = value.crbegin();
         rit != value.crend();
         rit++)
    {
        if (*rit == ' ')
            value.erase((rit+1).base());
        else
            break;
    }
}

const std::string& ini_parser::iniFile() const
{
    return m_iniFile;
}

bool ini_parser::isFile() const
{
    return m_isFile;
}

bool ini_parser::isParsed() const
{
    return m_isParsed;
}

const char* ini_parser::getValue(const char* section, const char* parameters, bool* isExist) const
{
    return getValue(std::string(section), std::string(parameters), isExist).c_str();
}

const std::string& ini_parser::getValue(const std::string& section, const std::string& parameters, bool* isExist) const
{
    // Return the value of the parameters (parameters) of the section (section).
    // Find section.
    const Section* pSection = nullptr;
    for (std::vector<Section>::const_iterator it = m_sections.cbegin();
         it != m_sections.cend();
         it++)
    {
        if (it->name == section)
        {
            pSection = &(*it);
            break;
        }
    }

    if (pSection == nullptr)
        return m_nullString;
    
    // Find parameters
    const Parameter* pParameters = nullptr;
    for (std::vector<Parameter>::const_iterator it = pSection->params.cbegin();
         it != pSection->params.cend();
         it++)
    {
        if (it->name == parameters)
        {
            pParameters = &(*it);
            break;
        }
    }

    if (pParameters == nullptr)
        return m_nullString;
    else
        return pParameters->value;
}

void ini_parser::setIniFile(const char* iniFile, bool isFile)
{
    m_iniFile = iniFile;
    m_isFile = isFile;
    m_isParsed = false;
    m_sections.clear();
    parse();
}

void ini_parser::setIniFile(const std::string& iniFile, bool isFile)
{
    m_iniFile = iniFile;
    m_isFile = isFile;
    m_isParsed = false;
    m_sections.clear();
    parse();
}