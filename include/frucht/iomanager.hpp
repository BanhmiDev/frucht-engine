#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <string>
#include <vector>

namespace Frucht {

class IOManager
{
public:
    static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
};

}

#endif // IOMANAGER_H
