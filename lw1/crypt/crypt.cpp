#include <iostream>
#include <array>
#include <string>
#include <fstream>
#include <algorithm>

enum class Mode
{
    CRYPT,
    DECRYPT,
    UNKNOWN
};

struct ProgrammArgs
{
    std::string inputFile;
    std::string outputFile;
    char key = 0;
    Mode mode = Mode::UNKNOWN;
};

constexpr int MIN_KEY = 0;
constexpr int MAX_KEY = 255;
constexpr int BYTE = 8;
const std::array <size_t, BYTE> MASK = { 2, 3, 4, 6, 7, 0, 1, 5 };

bool ParseArgs(const int argc, char** argv, ProgrammArgs& args);
Mode InitializeMode(const std::string& mode);
int ParseKey(const std::string& key);
bool InitializeFiles(std::ifstream& input, std::ofstream& output, const std::string& inputPath, const std::string& outputPath);
void Encrypt(std::istream& input, std::ostream& output, char key);
void Decrypt(std::istream& input, std::ostream& output, char key);

int main(int argc, char** argv)
{
    ProgrammArgs args;
    if (!ParseArgs(argc, argv, args))
    {
        return 1;
    }

    std::ifstream input;
    std::ofstream output;
    if (!InitializeFiles(input, output, args.inputFile, args.outputFile))
    {
        return 1;
    }

    if (args.mode == Mode::CRYPT)
    {
        Encrypt(input, output, args.key);
    }
    else if (args.mode == Mode::DECRYPT)
    {
        Decrypt(input, output, args.key);
    }

    return 0;
}

bool ParseArgs(const int argc, char** argv, ProgrammArgs& args)
{
    if (argc != 5)
    {
        std::cout << "Invalid count of argumins. Using sample: crypt.exe <mode> <input file> <output file> <key>\n";
        return false;
    }

    args.mode = InitializeMode(argv[1]);
    if (args.mode == Mode::UNKNOWN)
    {
        return false;
    }

    args.inputFile = argv[2];
    args.outputFile = argv[3];

    auto key = ParseKey(argv[4]);
    if (key == -1)
    {
        return false;
    }
    args.key = (char)key;

    return true;
}

Mode InitializeMode(const std::string& mode)
{
    if (mode == "CRYPT")
    {
        return Mode::CRYPT;
    }
    else if (mode == "DECRYPT")
    {
        return Mode::DECRYPT;
    }
    else
    {
        std::cout << "Invalid value of mode. Mode must be CRYPT or DECRYPT\n";
        return Mode::UNKNOWN;
    }
}

bool InitializeFiles(std::ifstream& input, std::ofstream& output, const std::string& inputPath, const std::string& outputPath)
{
    input.open(inputPath, std::ios::in | std::ios::binary);
    if (!input.is_open())
    {
        std::cout << "Something went wrong with input file...\n";
        return false;
    }

    output.open(outputPath, std::ios::out | std::ios::binary);
    if (!output.is_open())
    {
        std::cout << "Something went wrong with output file...\n";
        return false;
    }
    return true;
}

int ParseKey(const std::string& key)
{
    short value;

    if (!std::all_of(key.begin(), key.end(), ::isdigit))
    {
        std::cout << "Invalid key\n";
        return -1;
    }
    value = std::stoi(key);

    if (value < MIN_KEY || value > MAX_KEY)
    {
        std::cout << "Key out of range. The domain is [" << MIN_KEY << " ; " << MAX_KEY << "]\n";
        return -1;
    }

    return value;
}



char EncryptByte(char byte, char key)
{
    byte ^= key;

    char result = 0;
    for (size_t sourcePos = 0; sourcePos < BYTE; ++sourcePos)
    {
        result |= (char)((byte >> sourcePos) & 1) << MASK[sourcePos];
    }

    return result;
}

char DecryptByte(char byte, char key)
{
    char result = 0;
    for (size_t sourcePos = 0; sourcePos < BYTE; ++sourcePos)
    {
        result |= (char)((byte >> MASK[sourcePos]) & 1) << sourcePos;
    }

    result ^= key;

    return result;
}

void Encrypt(std::istream& input, std::ostream& output, char key)
{
    char byte;
    while (input.read(&byte, sizeof(byte)))
    {
        char encryptedByte = EncryptByte(byte, key);
        output.write(&encryptedByte, sizeof(byte));
    }
}

void Decrypt(std::istream& input, std::ostream& output, char key)
{
    char byte;
    while (input.read(&byte, sizeof(byte)))
    {
        char decryptedByte = DecryptByte(byte, key);
        output.write(&decryptedByte, sizeof(byte));
    }

}