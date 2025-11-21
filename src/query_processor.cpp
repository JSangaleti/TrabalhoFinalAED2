#include "../include/query_processor.hpp"


// Construtor — armazena referência ao Index
QueryProcessor::QueryProcessor(const Index &idx)
    : index(idx) {}

// Busca simples: retorna nomes dos arquivos onde a palavra aparece
std::vector<std::string> QueryProcessor::searchWord(const std::string &word) const {
    std::vector<std::string> results;

    // obtém IDs dos documentos que contêm a palavra
    std::vector<int> docs = index.getDocuments(word);

    // converte IDs → nomes de arquivo
    for (int id : docs) {
        results.push_back(index.getFileName(id));
    }

    return results;
}

// Busca múltipla com AND (interseção das listas)
// Exemplo: palavras { "gato", "cachorro" }
std::vector<std::string> QueryProcessor::searchAND(const std::vector<std::string> &words) const {
    if (words.empty())
        return {};

    // Pega a lista da primeira palavra
    std::vector<int> result = index.getDocuments(words[0]);

    // Para cada outra palavra: faz interseção
    for (size_t i = 1; i < words.size(); i++) {
        std::vector<int> docs = index.getDocuments(words[i]);
        result = intersect(result, docs);
    }

    // Converte IDs → nomes de arquivo
    std::vector<std::string> files;
    for (int id : result) {
        files.push_back(index.getFileName(id));
    }

    return files;
}

// Interseção entre duas listas ORDENADAS de documentos
std::vector<int> QueryProcessor::intersect(const std::vector<int> &a, const std::vector<int> &b) const 
{
    std::vector<int> result;
    size_t i = 0, j = 0;

    // Percorre as duas listas (aproveita o fato de serem ordenadas)
    while (i < a.size() && j < b.size()) {
        if (a[i] == b[j]) {
            result.push_back(a[i]);
            i++; 
            j++;
        }
        else if (a[i] < b[j]) {
            i++;
        }
        else {
            j++;
        }
    }

    return result;
}
