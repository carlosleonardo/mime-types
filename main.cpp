#include <iostream>
#include <filesystem>
#include <magic.h>
#include <fmt/format.h>

class MagicType
{
    magic_t magic;
    int opcao;
    void load_magic();

public:
    explicit MagicType(int opcao = MAGIC_MIME);
    void inicializa();
    std::string get_type(const std::filesystem::path &path);

    ~MagicType();
};

MagicType::MagicType(int opcao) : opcao(opcao)
{
}

void MagicType::inicializa()
{
    magic = magic_open(opcao);
    if (magic == nullptr)
    {
        throw std::runtime_error("Erro ao inicializar o magic");
    }
    load_magic();
}

void MagicType::load_magic()
{
    if (magic_load(magic, nullptr) != 0)
    {
        throw std::runtime_error("Erro ao carregar o magic");
    }
}

MagicType::~MagicType()
{
    if (magic != nullptr)
        magic_close(magic);
}

std::string MagicType::get_type(const std::filesystem::path &path)
{
    return magic_file(magic, path.c_str());
}

int main(int argc, const char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Uso: " << argv[0] << " <arquivo>" << std::endl;
        return 1;
    }
    MagicType magic;
    try
    {
        magic.inicializa();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
