/********************
*
*    FileWriter.hpp
*    Created by:   Matt Kaufman
*    
*    Class for writing simulation data to a file for use in plotting via Python.
*
*********************/

#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>





class FileWriter
{
public:
    int lines;
    std::string filename;
    std::string separator;
    std::ofstream output_stream;


    ~FileWriter();
    FileWriter(std::string filename);
    FileWriter(std::string filename, std::string header);
    FileWriter(std::string filename, std::string header, std::string separator);

    void AddLine(int value);
    void AddLine(float value);
    void AddLine(double value);
    void AddLine(sf::Vector2f value);
    void AddLine(int value1, int value2);
    void AddLine(float value1, float value2);
    void AddLine(double value1, double value2);
    void AddLine(sf::Vector2f value1, sf::Vector2f value2);
    void AddLine(int value1, int value2, int value3);
    void AddLine(float value1, float value2, float value3);
    void AddLine(double value1, double value2, double value3);
    void AddLine(sf::Vector2f value1, sf::Vector2f value2, sf::Vector2f value3);

    void AddLine(int value1, float value2);
    void AddLine(int value1, float value2, float value3);
    void AddLine(int value1, float value2, float value3, float value4);



private:
    /* Overloaded << for printing File information */
    friend std::ostream& operator<<(std::ostream& os, const FileWriter& filewriter)
    {
        os << std::endl << std::endl;
        os << "File \"" << filewriter.filename << "\":" << std::endl;
        os << "------"; for (int i = 0; i < filewriter.filename.length()+2; i++) os << "-"; os << std::endl;
        os << "   > Lines: " << filewriter.lines << std::endl << std::endl;
        os << "   > Separator: " << filewriter.separator << std::endl;
        os << std::endl << std::endl;
        return os;
    }
};




FileWriter::~FileWriter()
{
    output_stream.close();
    // std::cout << std::endl 
    // << "File \"" << filename << "\" closed." << std::endl
    // << "   > Total number of lines: " << lines << std::endl
    // << std::endl << std::endl;
}


FileWriter::FileWriter(std::string filename)
{
    this->filename = filename;
    this->separator = ";";
    this->output_stream.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    this->lines = 0;
}


FileWriter::FileWriter(std::string filename, std::string header)
{
    this->filename = filename;
    this->separator = ";";
    this->output_stream.open(filename);
    // If the header string does not contain a newline, add one
    if (header.find("\n") == std::string::npos) header += "\n";
    this->output_stream << header;
    this->lines = 0;    // Does not count the header as a line
}


FileWriter::FileWriter(std::string filename, std::string header, std::string separator)
{
    this->filename = filename;
    this->separator = separator;
    this->output_stream.open(filename);
    // If the header string does not contain a newline, add one
    if (header.find("\n") == std::string::npos) header += "\n";
    this->output_stream << header;
    this->lines = 0;    // Does not count the header as a line
}







void FileWriter::AddLine(int value)
{
    this->output_stream << value << "\n";
    this->lines++;
}
void FileWriter::AddLine(float value)
{
    this->output_stream << value << "\n";
    this->lines++;
}
void FileWriter::AddLine(double value)
{
    this->output_stream << value << "\n";
    this->lines++;
}
void FileWriter::AddLine(sf::Vector2f value)
{
    this->output_stream << value.x << "," << value.y << "\n";
    this->lines++;
}


void FileWriter::AddLine(int value1, int value2)
{
    this->output_stream << value1 << separator << value2 << "\n";
    this->lines++;
}
void FileWriter::AddLine(float value1, float value2)
{
    this->output_stream << value1 << separator << value2 << "\n";
    this->lines++;
}
void FileWriter::AddLine(double value1, double value2)
{
    this->output_stream << value1 << separator << value2 << "\n";
    this->lines++;
}
void FileWriter::AddLine(sf::Vector2f value1, sf::Vector2f value2)
{
    this->output_stream << value1.x << "," << value1.y << separator << value2.x << "," << value2.y << "\n";
    this->lines++;
}


void FileWriter::AddLine(int value1, int value2, int value3)
{
    this->output_stream << value1 << separator << value2 << separator << value3 << "\n";
    this->lines++;
}
void FileWriter::AddLine(float value1, float value2, float value3)
{
    this->output_stream << value1 << separator << value2 << separator << value3 << "\n";
    this->lines++;
}
void FileWriter::AddLine(double value1, double value2, double value3)
{
    this->output_stream << value1 << separator << value2 << separator << value3 << "\n";
    this->lines++;
}
void FileWriter::AddLine(sf::Vector2f value1, sf::Vector2f value2, sf::Vector2f value3)
{
    this->output_stream << value1.x << "," << value1.y << separator << value2.x << "," << value2.y << separator << value3.x << "," << value3.y << "\n";
    this->lines++;
}






void FileWriter::AddLine(int value1, float value2)
{
    this->output_stream << value1 << separator << value2 << "\n";
    this->lines++;
}

void FileWriter::AddLine(int value1, float value2, float value3)
{
    this->output_stream << value1 << separator << value2 << separator << value3 << "\n";
    this->lines++;
}

void FileWriter::AddLine(int value1, float value2, float value3, float value4)
{
    this->output_stream << value1 << separator << value2 << separator << value3 << separator << value4 << "\n";
    this->lines++;
}