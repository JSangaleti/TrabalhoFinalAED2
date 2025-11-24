#ifndef INDEXER_HPP
#define INDEXER_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include "text_processor.hpp"
#include "index.hpp"

class Indexer
{
private:
    TextProcessor processor; // responsável pelo preocessamento do texto: transforma o texto em lista de palavras úteis
    Index index;             // índice invertivo (a estrutura de dados principal)

public:
    Indexer() = default;

    // processa um único arquivo
    void indexFile(const std::filesystem::path &file_path);

    // processa todos os arquivos .txt dentro de um diretório
    void indexDirectory(const std::filesystem::path &dir_path);

    // acesso ao índice para salvamento, consultas, etc
    Index &getIndex();
};

#endif // INDEXER_HPP