#pragma once
#include <string>
#include <filesystem>

//#define RELEASE_VERSION

#ifdef RELEASE_VERSION
const std::string ASSETS_PATH = std::filesystem::current_path().string() + "\\Assets\\";
#else
const std::string ASSETS_PATH = std::filesystem::current_path().parent_path().string() + "\\Assets\\";
#endif


