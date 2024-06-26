/*
** EPITECH PROJECT, 2024
** EGE
** File description:
** Utils
*/

#pragma once

#include <fstream>
#include <filesystem>
#include <exception>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "Error.hpp"


/**
 * @brief Utility class that provides various helper functions and exception classes.
 *
 * The `Utils` class is a utility class that provides various helper functions and exception classes
 * for common operations such as string manipulation, file handling, and command line argument validation.
 * It also includes exception classes for handling specific error conditions.
 */
/**
 * @file Utils.hpp
 * @brief Contains the declaration of the Utils class and its member functions.
 */

/**
 * @class Utils
 * @brief A utility class that provides various helper functions.
 */
class Utils {
    public:
        /**
         * @class IsDirectoryException
         * @brief Exception class thrown when attempting to parse a directory.
         * @extends EGE::Error
         */
        class IsDirectoryException : public EGE::Error {
            public:
                /**
                 * @brief Constructs an IsDirectoryException object with the given error message.
                 * @param msg The error message associated with the exception.
                 */
                IsDirectoryException(const std::string& msg) : Error(msg) {}
        };

        /**
         * @class FileNotFoundException
         * @brief Exception class for file not found errors.
         * @extends EGE::Error
         */
        class FileNotFoundException : public EGE::Error {
            public:
                /**
                 * @brief Constructs a FileNotFoundException object with the default error message.
                 * The default error message is "File not found".
                 * @param msg The error message associated with the exception.
                */
                FileNotFoundException(const std::string& msg = "File not found") : Error(msg) {};
        };

        /**
         * @class InvalidArgumentsException
         * @brief Exception class for invalid arguments.
         * @extends EGE::Error
         *
         * This exception is thrown when invalid arguments are provided.
         */
        class InvalidArgumentsException : public EGE::Error {
            public:
                /**
                 * @brief Constructs an InvalidArgumentsException object with the given error message.
                 * @param msg The error message associated with the exception.
                 */
                InvalidArgumentsException(const std::string& msg) : Error(msg) {}
        };

        /**
         * @brief Splits a string into a vector of substrings based on a delimiter.
         *
         * @param str The string to be split.
         * @return std::vector<std::string> A vector containing the substrings.
         */
        static std::vector<std::string> split(const std::string &str);

        /**
         * @brief Splits a string into a vector of substrings based on a separator character.
         *
         * @param str The string to be split.
         * @param sep The separator character.
         * @return std::vector<std::string> A vector containing the substrings.
         */
        static std::vector<std::string> split(const std::string &str, char sep);

        /**
         * @brief Retrieves the content of a file.
         *
         * @param filename The name of the file to read.
         * @return The content of the file as a string.
         */
        static std::string getFileContent(const std::string &filename);

        /**
         * @brief Writes content to a file.
         *
         * @param filename The name of the file to write to.
         * @param content The content to write to the file.
         * @param append If true, the content will be appended to the file. Otherwise, the file will be overwritten.
         * @throws std::exception if the file cannot be opened.
        */
        static void setFileContent(const std::string &filename, const std::string &content, bool append = false);

        /**
         * @brief Converts a vector of strings to a single string.
         *
         * @param container The vector of strings to be converted.
         * @return The concatenated string.
         */
        static std::string vectorToString(const std::vector<std::string> &container);

        /**
         * @brief Retrieves the files in a directory.
         *
         * @param directory The directory path.
         * @return std::vector<std::string> A vector containing the names of the files in the directory.
         */
        static std::vector<std::string> getDirectoryFiles(const std::string &directory);

        /**
         * @brief Retrieves the files in a directory with a specific extension.
         *
         * @param directory The directory path.
         * @param extension The file extension to filter by.
         * @return std::vector<std::string> A vector containing the names of the files with the specified extension in the directory.
         */
        static std::vector<std::string> getDirectoryFiles(const std::string &directory, const std::string &extension);

        /**
         * @brief Retrieves the subdirectories in a directory.
         *
         * @param directory The directory path.
         * @return std::vector<std::string> A vector containing the names of the subdirectories in the directory.
         */
        static std::vector<std::string> getDirectorySubDirectories(const std::string &directory);

        /**
         * @brief Retrieves the content of a directory (files and subdirectories).
         *
         * @param directory The directory path.
         * @return std::vector<std::string> A vector containing the names of the files and subdirectories in the directory.
         */
        static std::vector<std::string> getDirectoryContent(const std::string &directory);
};

