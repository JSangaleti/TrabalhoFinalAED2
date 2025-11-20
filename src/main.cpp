#include "../include/main.hpp"
//#include "../include/index.hpp"
#include "../include/text_processor.hpp"

using namespace std;

namespace fs = filesystem;

string ReadFile(const fs::path &file_path)
{
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
    */

    return buffer.str();
}

void TestTextProcessor() {
    TextProcessor tp("./files/stopwords.txt");

    std::string texto = "O Gato está COMENDO no telhado! E o cachorro está comendo também.";

    auto palavras = tp.processText(texto);

    cout << "Palavras processadas:" << endl;
    for (const auto &p : palavras)
        cout << p << " ";
    cout << endl;
}


int main(/*int argc, char const *argv[]*/)
{
    fs::path dir_path = "./files/";
    vector<string> texts; // vetor dos textos

    for (const auto &entry : fs::recursive_directory_iterator(dir_path))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".txt")
        {
            /*  TODO
            scriptar aqui para que, para não colocar todos os textos num
            vetor e depois tratá-los todos, o que utilizaria muita memória,
            ir indexando e fechando os arquivos um de cada vez

            !!  está sendo utilizado um vetor apenas para fins de teste !!

            */

            texts.push_back(ReadFile(entry.path()));
        }
    }

    // apenas para testes
    for (int i = 0; i < texts.size(); i++)
    {
        cout << texts[i] << endl;
    }
    TestTextProcessor();
    return 0;
}
