#include <frucht/iomanager.hpp>
#include <fstream>

namespace Frucht {

bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
{
    std::ifstream file(filePath, std::ios::binary);
    if (file.fail()) {
        perror(filePath.c_str());
        return false;
    }
    
    // Seek to end
    file.seekg(0, std::ios::end);
    
    // How many bytes have past
    int fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Reduce file size by header bytes?
    fileSize -= file.tellg();

    // Edit buffer
    buffer.resize(fileSize);
    file.read((char *)&(buffer[0]), fileSize);
    file.close();

    return true;
}

}
