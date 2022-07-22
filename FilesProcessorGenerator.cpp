#include "FilesProcessorGenerator.h"

std::unique_ptr<FilesProcessorInterface> FilesProcessorGenerator::generateFilesProcessor()
{
    return std::make_unique<FilesProcessor>();
}
