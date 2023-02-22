#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <ctime>

constexpr size_t ARGUMENTS_IN_LINE = 5;

struct Args
{
    std::string inputFile;
    std::string oututFile;
    std::string searchingSubstring;
    std::string replaceString;
};

bool InitializeOfFileStreams(std::ifstream& inputFile, std::ofstream& outputFile, const std::string& inputPath, const std::string& outputPath);
std::optional<Args> ParsingArgs(int argc, char** argv);
std::string ReplaceSubstringWithString(const std::string& tempString, const std::string& searchingSubstring, const std::string& replaceString);
void WriteReplacedString(std::ifstream& inputFile, std::ofstream& outputFile, std::string& searchingSubstring, std::string& replaceString);

int main(int argc, char** argv)
{
    clock_t start_time = clock();

    std::optional<Args> args = ParsingArgs(argc, argv);
    if (args == std::nullopt)
    {
        std::cout << "Invalid counts of parameters. Sample: replace.exe <input file> <output file> <search string> <replace string>";
        return 0;
    }
    
    std::ifstream inputStream;
    std::ofstream outputStream;
    if (!InitializeOfFileStreams(inputStream, outputStream, args.value().inputFile, args.value().oututFile))
    { 
        return 1; 
     }

    WriteReplacedString(inputStream, outputStream, args.value().searchingSubstring, args.value().replaceString);

    std::cout << "Time execution is " << float(clock() - start_time) / 1000 << " sec" << std::endl;
    return 0;
}

bool InitializeOfFileStreams(std::ifstream& inputFile, std::ofstream& outputFile, const std::string& inputPath, const std::string& outputPath)
{
    inputFile.open(inputPath);
    outputFile.open(outputPath);

    if (!inputFile.is_open())
    {
        std::cout << "Something went wrong with input file...\n";
        return false;
    }

    if (!outputFile.is_open())
    {
        std::cout << "Something went wrong with output file...\n";
        return false;
    }

    return true;
}

std::optional<Args> ParsingArgs(int argc, char** argv)
{
    if (argc != ARGUMENTS_IN_LINE)
    {
        return std::nullopt;
    }

    Args parsedArgs = { argv[1], argv[2], argv[3], argv[4] };

    return parsedArgs;
} 

void WriteReplacedString(std::ifstream& inputFile, std::ofstream& outputFile, std::string& searchingSubstring, std::string& replaceString)
{
    std::string str;
    while (std::getline(inputFile, str))
    {
        outputFile << ReplaceSubstringWithString(str, searchingSubstring, replaceString) << "\n";
    }
}

std::string ReplaceSubstringWithString(const std::string& str, const std::string& searchingSubstring, const std::string& replaceString)
{
    std::string resultString = "";

    size_t posString = 0;

    while (posString < str.length())
    {
        size_t foundPosString = str.find(searchingSubstring, posString);
        resultString.append(str, posString, foundPosString - posString); 

        if (foundPosString == std::string::npos) 
        {
            break;
        }
        resultString.append(replaceString);
        posString = foundPosString + searchingSubstring.length();
    }
    return resultString;
}
