#ifndef INDEX_HPP
#define INDEX_HPP

#include <unordered_map>
#include <vector>
#include <string>

class Index {
    public:
        Index();

        // Adiciona uma plavra associada a um arquivo (por ID)
        void addWord(const std::string &word, int documentId);

        // Obtém a lista de documentos que contém a palavra
        std::vector<int> getDocuments(const std::string &word) const;

        // Registra um arquivo novo e retorna seu ID
        int registerDocument(const std::string &fileName);

        // Obtém nome do arquivo a partid de seu ID
        std::string getFileName(int id) const;

    private: 
        // palavra -> lista de IDs de documentos
        std::unordered_map<std::string, std::vector<int>> invertedIndex;

        // documentoId-> nome do arquivo
        std::vector<std::string> idToFileName;

        // nome do arquivo -> id
        std::unordered_map<std::string, int> fileNameToId;

};

#endif