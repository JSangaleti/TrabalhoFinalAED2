#include "../include/command_line_interface.hpp"

namespace fs = std::filesystem;

// ======================================================================
// Construtor: guarda os argumentos recebidos
// ======================================================================
CommandLineInterface::CommandLineInterface(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        args.push_back(argv[i]);
    }
}

// ======================================================================
// Verifica se uma flag foi fornecida
// ======================================================================
bool CommandLineInterface::hasFlag(const std::string &flag) const
{
    return std::find(args.begin(), args.end(), flag) != args.end();
}

// ======================================================================
// Retorna o argumento que vem após a flag
// Ex: --index ./files
// ======================================================================
std::string CommandLineInterface::getArgumentAfter(const std::string &flag) const
{
    auto it = std::find(args.begin(), args.end(), flag);
    if (it != args.end() && ++it != args.end())
        return *it;
    return "";
}

// ======================================================================
// Coleta várias palavras após --search
// Ex: --search gato cachorro telhado
// ======================================================================
std::vector<std::string> CommandLineInterface::getWordsAfter(const std::string &flag) const
{
    std::vector<std::string> words;
    auto it = std::find(args.begin(), args.end(), flag);
    if (it == args.end())
        return words;

    ++it;
    while (it != args.end())
    {
        words.push_back(*it);
        ++it;
    }
    return words;
}

// ======================================================================
// Mostra ajuda
// ======================================================================
void CommandLineInterface::showHelp() const
{
    std::cout << "\nUso do programa:\n\n"
              << "  --index <pasta> --output <arquivo>    Indexa diretório e salva índice\n"
              << "  --load <arquivo> --search <palavras>  Carrega índice e busca palavras\n"
              << "\nExemplos:\n"
              << "  ./programa --index ./files --output ./data/index.bin\n"
              << "  ./programa --load ./data/index.bin --search gato cachorro\n\n";
}

// ======================================================================
// núcleo da CLI: decide o que fazer
// ======================================================================
void CommandLineInterface::run()
{

    // Exibir ajuda
    if (hasFlag("--help") && args.size() == 1)
    {
        showHelp();
        return;
    }

    // --------------------------------------------------------------
    // Caso 1: indexar diretório e salvar
    // --------------------------------------------------------------
    if (hasFlag("--index"))
    {
        std::string dir = getArgumentAfter("--index");
        std::string out = getArgumentAfter("--output");

        if (dir.empty() || out.empty())
        {
            std::cout << "Erro: falta --index <dir> ou --output <arquivo>\n";
            return;
        }

        Indexer indexer;
        indexer.indexDirectory(dir);

        Serializer::save(indexer.getIndex(), out);

        std::cout << "Índice salvo em: " << out << "\n";
        return;
    }

    // --------------------------------------------------------------
    // Caso 2: carregar índice e fazer busca
    // --------------------------------------------------------------
    if (hasFlag("--load") && hasFlag("--search"))
    {
        std::string file = getArgumentAfter("--load");
        auto words = getWordsAfter("--search");

        if (file.empty() || words.empty())
        {
            std::cout << "Erro: falta --load <arquivo> ou palavras após --search\n";
            return;
        }
        Index index;
        Serializer::load(index, file);

        QueryProcessor qp(index);

        auto result = qp.searchAND(words);

        std::cout << "\nArquivos encontrados:\n";
        for (auto &f : result)
            std::cout << "  " << f << "\n";

        return;
    }

    // Se nada bateu:
    showHelp();
}