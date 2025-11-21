#ifndef INDEX_HPP
#define INDEX_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

class Index
{
public:
    Index();

    // Apenas uma declaração é suficiente
    const std::unordered_map<std::string, std::vector<int>>& getInvertedIndex() const;

    // Adiciona uma palavra associada a um arquivo (por ID)
    void addWord(const std::string &word, int documentId);

    // Obtém a lista de documentos que contém a palavra
    std::vector<int> getDocuments(const std::string &word) const;

    // Registra um arquivo novo e retorna seu ID
    int registerDocument(const std::string &fileName);

    // Obtém nome do arquivo a partir de seu ID
    std::string getFileName(int id) const;

private:
    // palavra -> lista de IDs de documentos
    std::unordered_map<std::string, std::vector<int>> invertedIndex;

    // documentoId -> nome do arquivo
    std::vector<std::string> idToFileName;

    // nome do arquivo -> id
    std::unordered_map<std::string, int> fileNameToId;

    // Serializer é amigo (pode acessar private)
    friend class Serializer;

    // NÃO DECLARE getInvertedIndex() AQUI DE NOVO
    // Removido!
    
    const std::vector<std::string>& getIdToFileName() const {
        return idToFileName;
    }

    std::vector<std::string>& getIdToFileNameRef() {
        return idToFileName;
    }

    const std::unordered_map<std::string, int>& getFileNameToId() const {
        return fileNameToId;
    }

    std::unordered_map<std::string, int>& getFileNameToIdRef() {
        return fileNameToId;
    }
};




#endif