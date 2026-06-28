#ifndef CTRL_PERSON_SERVICE_HPP
#define CTRL_PERSON_SERVICE_HPP

#include "../interfaces/IPersonService.hpp"
#include "../database/sqlite_connection.hpp"
#include <vector>
#include <stdexcept>
#include <string>

class CntrServicoPessoa : public IPersonService {
private:
    std::vector<Person> containerPessoas;
    SQLiteConnection database_;

    void inicializarBanco();
    void carregarPessoas();
    void inserirPessoaNoBanco(const Person& pessoa);
    void atualizarPessoaNoBanco(const Person& pessoa);
    void removerPessoaNoBanco(const std::string& email);
    std::string escaparTexto(const std::string& valor) const;
    std::vector<Person> listarTodasAsPessoas() const override;

public:
    explicit CntrServicoPessoa(const std::string& dbPath = "scrum.db");

    void criarPessoa(Email email, Name name, Password password, Role role) override;
    Person lerPessoa(Email email) const override;
    void atualizarPessoa(Email email, Name name, Password password, Role role) override;
    void excluirPessoa(Email email) override;
};

#endif