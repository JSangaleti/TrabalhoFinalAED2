#include "../include/index.hpp"

Index::Index() {}

void Index::addWord(const std::string &word, int documentId)
{
    auto &list = invertedIndex[word];

    // garante que não haja IDs repetidos
    if (std::find(list.begin(), list.end(), documentId) == list.end())
    {                               // se não encontrou...
        list.push_back(documentId); // adiciona ao final do vetor
    }
}

std::vector<int> Index::getDocuments(const std::string &word) const
{
    if (invertedIndex.count(word) == 0) // a palavra não foi encontrada
        return {};
    return invertedIndex.at(word); // retorno a lista de IDs (doocumentos) vinculada à palavra
}

int Index::registerDocument(const std::string &fileName)
{
    if (fileNameToId.count(fileName) > 0) // se já tenho um ID vinculado ao dado fileName, então retorno o ID
        return fileNameToId[fileName];

    int id = idToFileName.size();
    idToFileName.push_back(fileName); // adiciono ao fim da lista
    fileNameToId[fileName] = id;      // atribuo o ID (como é o último elemento adicionado, corresponde ao size da lista)

    return id;
}

std::string Index::getFileName(int id) const
{
    if (id < 0 || id >= (int)idToFileName.size()) // está fora do intervalo de IDs existentes
        return "";
    return idToFileName[id];
}

const std::unordered_map<std::string, std::vector<int>> &Index::getInvertedIndex() const
{
    return invertedIndex;
}
