#ifndef TEXT_PROCESSOR_HPP
#define TEXT_PROCESSOR_HPP

#include <string>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <cctype>

class TextProcessor
{
public:
    TextProcessor(const std::string &stopwordsPath =
                      "./files/stopwords.txt");

    // processa o texto e retorna uma lista de palavras válidas
    std::vector<std::string> processText(const std::string &text);

private:
    std::unordered_set<std::string> stopwords;

    // abre o arquivo stopwords.txt e cada palavra lida é colocada num unordered_set
    void loadStopwords(const std::string &path);

    // remove a pontuação (substituindo por espaço) e transforma tudo em minúsculas. Sobra apenas letras e números.
    std::string normalize(const std::string &text);

    // divide por espaços (usando stringstream) e retorna um vetor de palavras
    std::vector<std::string> tokenize(const std::string &text);

    // retorna se a palavra está ou não no set
    bool isStopword(const std::string &word) const;
};
#endif // TEXT_PROCESSOR_HPP