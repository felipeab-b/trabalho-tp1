#include "CtrlPersonService.hpp"

CntrServicoPessoa::CntrServicoPessoa(const std::string& dbPath)
    : database_(dbPath) {
    inicializarBanco();
    carregarPessoas();
}

void CntrServicoPessoa::inicializarBanco() {
    database_.execute(
        "CREATE TABLE IF NOT EXISTS pessoas ("
        "email TEXT PRIMARY KEY,"
        "name TEXT NOT NULL,"
        "password TEXT NOT NULL,"
        "role TEXT NOT NULL"
        ");"
    );
}

void CntrServicoPessoa::carregarPessoas() {
    auto rows = database_.query("SELECT email, name, password, role FROM pessoas ORDER BY email");
    for (const auto& row : rows) {
        if (row.size() < 4) {
            continue;
        }

        Email email;
        email.set(row[0]);

        Person pessoa(email);
        Name nome;
        nome.set(row[1]);
        pessoa.setName(nome);

        Password senha;
        senha.set(row[2]);
        pessoa.setPassword(senha);

        Role papel;
        papel.set(row[3]);
        pessoa.setRole(papel);

        containerPessoas.push_back(pessoa);
    }
}

void CntrServicoPessoa::inserirPessoaNoBanco(const Person& pessoa) {
    std::string sql = "INSERT INTO pessoas (email, name, password, role) VALUES ('" +
        escaparTexto(pessoa.getEmail().get()) + "', '" +
        escaparTexto(pessoa.getName().get()) + "', '" +
        escaparTexto(pessoa.getPassword().get()) + "', '" +
        escaparTexto(pessoa.getRole().get()) + "');";
    database_.execute(sql);
}

void CntrServicoPessoa::atualizarPessoaNoBanco(const Person& pessoa) {
    std::string sql = "UPDATE pessoas SET name='" +
        escaparTexto(pessoa.getName().get()) + "', password='" +
        escaparTexto(pessoa.getPassword().get()) + "', role='" +
        escaparTexto(pessoa.getRole().get()) + "' WHERE email='" +
        escaparTexto(pessoa.getEmail().get()) + "';";
    database_.execute(sql);
}

void CntrServicoPessoa::removerPessoaNoBanco(const std::string& email) {
    std::string sql = "DELETE FROM pessoas WHERE email='" + escaparTexto(email) + "';";
    database_.execute(sql);
}

std::string CntrServicoPessoa::escaparTexto(const std::string& valor) const {
    std::string resultado = valor;
    size_t pos = 0;
    while ((pos = resultado.find("'", pos)) != std::string::npos) {
        resultado.insert(pos, "'");
        pos += 2;
    }
    return resultado;
}

void CntrServicoPessoa::criarPessoa(Email email, Name name, Password password, Role role) {
    for (const auto& pessoa : containerPessoas) {
        if (pessoa.getEmail().get() == email.get()) {
            throw std::invalid_argument("Erro: Ja existe uma pessoa cadastrada com este email.");
        }
    }

    Person novaPessoa(email);
    novaPessoa.setName(name);
    novaPessoa.setPassword(password);
    novaPessoa.setRole(role);

    containerPessoas.push_back(novaPessoa);
    inserirPessoaNoBanco(novaPessoa);
}

Person CntrServicoPessoa::lerPessoa(Email email) const {
    for (const auto& pessoa : containerPessoas) {
        if (pessoa.getEmail().get() == email.get()) {
            return pessoa;
        }
    }

    throw std::invalid_argument("Erro: Pessoa nao encontrada no sistema.");
}

void CntrServicoPessoa::atualizarPessoa(Email email, Name name, Password password, Role role) {
    for (auto& pessoa : containerPessoas) {
        if (pessoa.getEmail().get() == email.get()) {
            pessoa.setName(name);
            pessoa.setPassword(password);
            pessoa.setRole(role);
            atualizarPessoaNoBanco(pessoa);
            return;
        }
    }

    throw std::invalid_argument("Erro: Nao foi possivel atualizar. Pessoa nao encontrada.");
}

void CntrServicoPessoa::excluirPessoa(Email email) {
    for (auto it = containerPessoas.begin(); it != containerPessoas.end(); ++it) {
        if (it->getEmail().get() == email.get()) {
            removerPessoaNoBanco(it->getEmail().get());
            containerPessoas.erase(it);
            return;
        }
    }

    throw std::invalid_argument("Erro: Nao foi possivel excluir. Pessoa nao encontrada.");
}
