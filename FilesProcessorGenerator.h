#ifndef FILESPROCESSORGENERATOR_H
#define FILESPROCESSORGENERATOR_H

#include <memory>

#include "FilesProcessor.h"

class FilesProcessorGenerator
{
public:
    FilesProcessorGenerator() = delete;
    
    static std::unique_ptr<FilesProcessorInterface> generateFilesProcessor();
};

#endif // FILESPROCESSORGENERATOR_H
