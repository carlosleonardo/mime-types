#include <iostream>
#include <filesystem>
#include <string>
#include <magic.h>
#include <fmt/format.h>

class MagicType
{
    magic_t magic;
    int opcao;
    void load_magic();

public:
    explicit MagicType(int opcao = MAGIC_MIME_TYPE);
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
    fmt::print("{}\n", "Destrutor chamado");
    if (magic != nullptr)
        magic_close(magic);
}

std::string MagicType::get_type(const std::filesystem::path &path)
{
    return magic_file(magic, path.string().c_str());
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
        std::cout << magic.get_type(argv[1]) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (...)
    {
        std::cerr << "Erro desconhecido" << std::endl;
    }
    return 0;
}
