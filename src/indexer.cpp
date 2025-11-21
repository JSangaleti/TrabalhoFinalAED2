#include "../include/indexer.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

int nextDocumentID = 0;

void Indexer::indexFile(const std::filesystem::path &file_path){
    std::ifstream file(file_path);
    if(!file.is_open()){
        throw std::runtime_error("Erro ao abrir arquivo: " + file_path.string());
    }

    // Lê todo o arquivo 
    std::stringstream buffer; // criando um espaço na memória para receber minha string
    buffer << file.rdbuf(); // passando o bloco (tudo q tá no arquivo) para meu bloquinho na memória. Detalhe: COPIA TUDO do arquivo para o buffer
    std::string content = buffer.str(); // transformando meu buffer em string

    // Processa o texto transformando em um vetor de palavras
    std::vector<std::string> words = processor.processText(content);

    // Nome do documento (id)
    int doc_id = index.registerDocument(file_path.filename().string());

    // Indexa palavra por palavra 
    for(const auto &w : words) {
        index.addWord(w, doc_id);
    }
}

void Indexer::indexDirectory(const std::filesystem::path &dir_path) {
    for (const auto &entry : std::filesystem::recursive_directory_iterator(dir_path)) { // percorre TODOS os arquivos dentro da pasta, inclusive as subpastas 
        if(entry.is_regular_file() && entry.path().extension() == ".txt") { // retorna true apenas se for um arquivo .txt
            indexFile(entry.path()); // aqui lê o texto, normaliza, tokeniza, indexa palavra por palavra
        }
    }
}

Index& Indexer::getIndex() {
    return index;
}

/***
string ReadFile(const fs::path &file_path)
{
    /*
    essa função lê o conteúdo dos arquivos. ela recebe valores do tipo fs::path,
    que é um tipo meio esquisito, mas não precisa se preocupar com isso. afinal,
    essa função só é utilizada dentro do laço de repetição que lista recursivamente
    os arquivos
    
    ifstream file((file_path));
    if (!file.is_open())
        throw runtime_error("Erro ao abrir o arquivo: " + file_path.string());

    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    /*
    TODO
    tratamento do texto
    dos arquivos individualmente
   

    return buffer.str();
}

***/