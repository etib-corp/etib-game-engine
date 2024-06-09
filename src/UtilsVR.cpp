/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** UtilsVR
*/

#include "UtilsVR.hpp"


EGE::UtilsVR::UtilsVR()
{
}

EGE::UtilsVR::~UtilsVR()
{
}


std::string EGE::UtilsVR::readAssetFile(const std::string& filename)
{
    AAssetManager *mgr = EGE::UtilsVR::app->activity->assetManager;
    AAsset *file = AAssetManager_open(mgr, filename.c_str(), AASSET_MODE_UNKNOWN);
    off_t fileLength = AAsset_getLength(file);
    char *buffer = (char *)malloc(fileLength + 1);
    AAsset_read(file, buffer, fileLength);
    buffer[fileLength] = '\0';
    AAsset_close(file);
    std::string fileContent(buffer);
    free(buffer);
    return fileContent;
}