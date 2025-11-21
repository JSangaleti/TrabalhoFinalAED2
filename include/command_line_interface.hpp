#ifndef COMMAND_LINE_INTERFACE_HPP
#define COMMAND_LINE_INTERFACE_HPP

#include "../include/indexer.hpp"
#include "../include/serializer.hpp"
#include "../include/query_processor.hpp"
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

class CommandLineInterface
{
public:
    CommandLineInterface(int argc, char **argv);

    // Executa a ação solicitada
    void run();

private:
    std::vector<std::string> args;

    // Helpers
    bool hasFlag(const std::string &flag) const;
    std::string getArgumentAfter(const std::string &flag) const;
    std::vector<std::string> getWordsAfter(const std::string &flag) const;

    void showHelp() const;
};

#endif