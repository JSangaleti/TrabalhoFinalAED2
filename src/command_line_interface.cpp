#include "../include/command_line_interface.hpp"

namespace fs = std::filesystem;

CommandLineInterface::CommandLineInterface(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        args.push_back(argv[i]);
    }
}

bool CommandLineInterface::hasFlag(const std::string &flag) const
{
    return std::find(args.begin(), args.end(), flag) != args.end();
}

std::string CommandLineInterface::getArgumentAfter(const std::string &flag) const
{
    auto it = std::find(args.begin(), args.end(), flag);
    if (it != args.end() && ++it != args.end())
        return *it;
    return "";
}

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

void CommandLineInterface::showHelp() const
{
    std::cout << "\nUso do programa:\n\n"
              << "  --index <pasta> --output <arquivo>    Indexa diretório e salva índice\n"
              << "  --load <arquivo> --search <palavras>  Carrega índice e busca palavras\n"
              << "\nExemplos:\n"
              << "  ./programa --index ./files --output ./data/index.bin\n"
              << "  ./programa --load ./data/index.bin --search gato cachorro\n\n";
}

void CommandLineInterface::run()
{

    // exibir ajuda
    if (hasFlag("--help") && args.size() == 1)
    {
        showHelp();
        return;
    }

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

    // se não der em nenhuma opção
    showHelp();
}