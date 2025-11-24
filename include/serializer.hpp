#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <string>
#include <fstream>
#include <stdexcept>
#include "index.hpp"

class Serializer
{
public:
    // salva o índice inteiro em formato binário
    static void save(const Index &index, const std::string &filename);

    // carrga o índice inteiro em um arquivo binário
    static void load(Index &index, const std::string &filename);
};

#endif // SERIALIZER_HPP