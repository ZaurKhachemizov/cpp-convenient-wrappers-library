#pragma once

//==============================================================================================================================
#include <iostream>
#include <sstream>
#include <array>
#include <vector>
#include <catch2/catch.hpp>


#ifdef WIN32

//==============================================================================================================================
FILE *popen (const char *command, const char *flags)
{
    return _popen(command, flags);
}


//==============================================================================================================================
int pclose (FILE *fd)
{
    return _pclose(fd);
}

#endif


//==============================================================================================================================
std::string next_valuable_line(std::vector<std::string> const &lines, size_t &startIndex)
{
    for (; startIndex < lines.size(); ++startIndex)
        if (!lines[startIndex].empty())
            return lines[startIndex++];

    return std::string();
}


//==============================================================================================================================
bool lines_equal(std::vector<std::string> const &left, std::vector<std::string> const &right)
{
    size_t leftIndex  = 0;
    size_t rightIndex = 0;

    do
    {
        std::string leftLine  = next_valuable_line(left,  leftIndex);
        std::string rightLine = next_valuable_line(right, rightIndex);

        if (leftLine != rightLine)
            return false;
    }
    while (leftIndex < left.size() && rightIndex < right.size());

    return true;
}


//==============================================================================================================================
std::vector<std::string> read_lines(std::iostream &lines)
{
    std::vector<std::string> result;

    while (!lines.eof())
    {
        std::string line;
        getline(lines, line);

        result.push_back(line);
    }

    return result;
}


//==============================================================================================================================
std::vector<std::string> read_command(std::string const &command)
{
    static size_t const BUFFER_SIZE = 128;

    std::vector<std::string>                 result;
    std::array<char, BUFFER_SIZE>            buffer;
    std::stringstream                        lines;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);

    if (pipe)
    {
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
            lines << buffer.data();

        result = read_lines(lines);
    }

    return result;
}


//==============================================================================================================================
std::vector<std::string> read_file(std::string const &filePath)
{
    std::vector<std::string> result;
    std::fstream             file(filePath.c_str(), std::fstream::in);

    if (file.is_open())
        result = read_lines(file);

    return result;
}


//==============================================================================================================================
void do_app_test(std::string const &appName)
{
    auto commandOutput  = read_command(std::string(appName) + ".exe");
    auto expectedResult = read_file   (std::string(appName) + ".txt");

    REQUIRE(lines_equal(commandOutput, expectedResult));
}
