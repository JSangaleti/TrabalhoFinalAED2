#include "../include/serializer.hpp"

// função auxiliar para salvar strings
// formato = (tamanho) + (bytes)

static void writeString(std::ofstream &out, const std::string &s)
{
    size_t len = s.size();
    out.write(reinterpret_cast<const char *>(&len), sizeof(size_t)); // salva tamanho
    out.write(s.data(), len);                                        // salva bytes
}

// função auxiliar para ler strings

static std::string readString(std::ifstream &in)
{
    size_t len;
    in.read(reinterpret_cast<char *>(&len), sizeof(size_t)); // lê tamanho
    std::string s(len, '\0');                                // aloca espaço
    in.read(&s[0], len);                                     // lê bytes
    return s;
}

// salvar
void Serializer::save(const Index &index, const std::string &filename)
{
    std::ofstream out(filename, std::ios::binary);
    if (!out.is_open())
        throw std::runtime_error("Erro ao abrir arquivo para salvar.");

    // 1) salvar idToFileName
    const auto &names = index.getIdToFileName();
    size_t nameCount = names.size();
    out.write(reinterpret_cast<const char *>(&nameCount), sizeof(size_t));

    for (const auto &name : names)
    {
        writeString(out, name);
    }

    // 2) salvar fileNameToId
    const auto &mapNameToId = index.getFileNameToId();
    size_t mapCount = mapNameToId.size();
    out.write(reinterpret_cast<const char *>(&mapCount), sizeof(size_t));

    for (const auto &p : mapNameToId)
    {
        writeString(out, p.first);
        out.write(reinterpret_cast<const char *>(&p.second), sizeof(int));
    }

    // 3) salvar invertedIndex
    const auto &inv = index.getInvertedIndex();
    size_t invSize = inv.size();
    out.write(reinterpret_cast<const char *>(&invSize), sizeof(size_t));

    for (const auto &pair : inv)
    {
        writeString(out, pair.first); // palavra

        size_t vecSize = pair.second.size();
        out.write(reinterpret_cast<const char *>(&vecSize), sizeof(size_t));

        for (int id : pair.second)
        {
            out.write(reinterpret_cast<const char *>(&id), sizeof(int));
        }
    }
}

void Serializer::load(Index &index, const std::string &filename)
{

    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open())
        throw std::runtime_error("Erro ao abrir arquivo para carregar.");

    // limpa tudo antes
    index.invertedIndex.clear();
    index.fileNameToId.clear();
    index.idToFileName.clear();

    // 1) carregar idToFileName
    size_t nameCount;
    in.read(reinterpret_cast<char *>(&nameCount), sizeof(size_t));
    index.getIdToFileNameRef().resize(nameCount);

    for (size_t i = 0; i < nameCount; i++)
    {
        index.getIdToFileNameRef()[i] = readString(in);
    }

    // 2) carregar fileNameToId
    size_t mapCount;
    in.read(reinterpret_cast<char *>(&mapCount), sizeof(size_t));

    for (size_t i = 0; i < mapCount; i++)
    {
        std::string name = readString(in);
        int id;
        in.read(reinterpret_cast<char *>(&id), sizeof(int));
        index.getFileNameToIdRef()[name] = id;
    }

    // 3) carregar invertedIndex
    size_t invSize;
    in.read(reinterpret_cast<char *>(&invSize), sizeof(size_t));

    for (size_t i = 0; i < invSize; ++i)
    {
        std::string word = readString(in);

        size_t vecSize;
        in.read(reinterpret_cast<char *>(&vecSize), sizeof(size_t));

        std::vector<int> docs(vecSize);
        for (size_t j = 0; j < vecSize; ++j)
        {
            in.read(reinterpret_cast<char *>(&docs[j]), sizeof(int));
        }

        index.invertedIndex[word] = docs;
    }
}
