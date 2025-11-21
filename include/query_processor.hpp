#ifndef QUERY_PROCESSOR_HPP
#define QUERY_PROCESSOR_HPP

#include "index.hpp"
#include <string>
#include <vector>
#include <algorithm>

class QueryProcessor {
public:
    // Recebe referência ao índice já carregado
    QueryProcessor(const Index &idx);

    // Busca simples: retorna nomes dos arquivos que contém a palavra
    std::vector<std::string> searchWord(const std::string &word) const;

    // Busca múltipla: interseção (AND)
    std::vector<std::string> searchAND(const std::vector<std::string> &words) const;

private:
    const Index &index;

    // interseção entre duas listas de documentos
    std::vector<int> intersect(const std::vector<int> &a, const std::vector<int> &b) const;
};

#endif
