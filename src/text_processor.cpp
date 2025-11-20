#include "../include/text_processor.hpp"
#include <fstream>
#include <sstream>
#include <cctype>

TextProcessor::TextProcessor(const std::string &stopwordsPath){
    loadStopwords(stopwordsPath); // carregando as stopwords
}

void TextProcessor::loadStopwords(const std::string &path){
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Erro ao abir stopwords: " + path);

    std::string word;
    while (file >> word) { 
        stopwords.insert(word);
    }
    file.close();
}

std::string TextProcessor::normalize(const std::string &text) {
    std::string result;
    result.reserve(text.size());

    for (size_t i = 0; i < text.size(); ) {
        unsigned char c = text[i];

        // ASCII normal (1 byte)
        if (c < 128) {
            if (std::isalnum(c))
                result += std::tolower(c);
            else
                result += ' ';
            i++;
        }
        // UTF-8 multibyte (acentos e cedilha)
        else {
            // Copia o byte atual e o próximo (UTF-8 até 2 bytes)
            // sem alterar. Mantemos o caractere.
            
            // Detectar sequência UTF-8 (simplificada)
            if ((c & 0xE0) == 0xC0) { 
                // caractere de 2 bytes (á, é, ó, ã, ç...)
                if (i + 1 < text.size()) {
                    result += text[i];
                    result += text[i+1];
                    i += 2;
                } else {
                    // byte inválido → ignora
                    i++;
                }
            }
            else {
                // Outros casos (3 e 4 bytes)
                // copiar byte e avançar 1 (simples e seguro)
                result += text[i];
                i++;
            }
        }
    }

    return result;
}


std::vector<std::string> TextProcessor::tokenize(const std::string &text) {
    std::vector<std::string> tokens;
    std::stringstream ss(text); // pego a string e transformo em um "fluxo", igual a um arquivo de texto
    std::string word;

    while (ss >> word) // lendo palavra por palavra (pegando caracteres até o espaço) e coloco na string word
        tokens.push_back(word); // adicionando a palavra ao final de tokens

    return tokens;
}

bool TextProcessor::isStopword(const std::string &word) const {
    return stopwords.count(word) > 0; // se a palavra é encontrada, então returna true. Do contrário, false
}

std::vector<std::string> TextProcessor::processText(const std::string &text){
    std::string clean = normalize(text); // "limpando" o texto, para devolver apenas letras e números, com tudo em minúsculo
    auto tokens = tokenize(clean); // transformando o texto em um vetor de palavras, separando pelos espaços

    std::vector<std::string> result;

    for (const auto &word : tokens) { // verificando palavra por palavra que está em tokens
        if (!isStopword(word)) // se a palavra não está no stopwords...
            result.push_back(word); // então ela é adicionada ao final de result
    }

    return result; // retorna o vetor com as palavras úteis
}