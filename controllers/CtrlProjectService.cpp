#include "CtrlProjectService.hpp"

CntrServicoProjeto::CntrServicoProjeto(const std::string& dbPath)
    : database_(dbPath) {
    inicializarBanco();
    carregarProjetos();
}

void CntrServicoProjeto::inicializarBanco() {
    database_.execute(
        "CREATE TABLE IF NOT EXISTS projetos ("
        "code TEXT PRIMARY KEY,"
        "name TEXT NOT NULL,"
        "beginning TEXT NOT NULL,"
        "ending TEXT NOT NULL"
        ");"
    );
}

void CntrServicoProjeto::carregarProjetos() {
    auto rows = database_.query("SELECT code, name, beginning, ending FROM projetos ORDER BY code");
    for (const auto& row : rows) {
        if (row.size() < 4) {
            continue;
        }

        Code code;
        code.set(row[0]);

        Project projeto(code);
        Name nome;
        nome.set(row[1]);
        projeto.setName(nome);

        Date inicio;
        inicio.set(row[2]);
        projeto.setBeginning(inicio);

        Date fim;
        fim.set(row[3]);
        projeto.setEnding(fim);

        containerProjetos.push_back(projeto);
    }
}

void CntrServicoProjeto::inserirProjetoNoBanco(const Project& projeto) {
    std::string sql = "INSERT INTO projetos (code, name, beginning, ending) VALUES ('" +
        escaparTexto(projeto.getCode().get()) + "', '" +
        escaparTexto(projeto.getName().get()) + "', '" +
        escaparTexto(projeto.getBeginning().get()) + "', '" +
        escaparTexto(projeto.getEnding().get()) + "');";
    database_.execute(sql);
}

void CntrServicoProjeto::atualizarProjetoNoBanco(const Project& projeto) {
    std::string sql = "UPDATE projetos SET name='" +
        escaparTexto(projeto.getName().get()) + "', beginning='" +
        escaparTexto(projeto.getBeginning().get()) + "', ending='" +
        escaparTexto(projeto.getEnding().get()) + "' WHERE code='" +
        escaparTexto(projeto.getCode().get()) + "';";
    database_.execute(sql);
}

void CntrServicoProjeto::removerProjetoNoBanco(const std::string& code) {
    std::string sql = "DELETE FROM projetos WHERE code='" + escaparTexto(code) + "';";
    database_.execute(sql);
}

std::string CntrServicoProjeto::escaparTexto(const std::string& valor) const {
    std::string resultado = valor;
    size_t pos = 0;
    while ((pos = resultado.find("'", pos)) != std::string::npos) {
        resultado.insert(pos, "'");
        pos += 2;
    }
    return resultado;
}

void CntrServicoProjeto::criarProjeto(Code code, Name name, Date beginning, Date ending, Email scrumMaster) {
    for (const auto& projeto : containerProjetos) {
        if (projeto.getCode().get() == code.get()) {
            throw std::invalid_argument("Erro: Ja existe um projeto cadastrado com este codigo.");
        }
    }

    Project novoProjeto(code);
    novoProjeto.setName(name);
    novoProjeto.setBeginning(beginning);
    novoProjeto.setEnding(ending);

    containerProjetos.push_back(novoProjeto);
    inserirProjetoNoBanco(novoProjeto);
}

Project CntrServicoProjeto::lerProjeto(Code code) const {
    for (const auto& projeto : containerProjetos) {
        if (projeto.getCode().get() == code.get()) {
            return projeto;
        }
    }
    throw std::invalid_argument("Erro: Projeto nao encontrado no sistema.");
}

void CntrServicoProjeto::atualizarProjeto(Code code, Name name, Date beginning, Date ending) {
    for (auto& projeto : containerProjetos) {
        if (projeto.getCode().get() == code.get()) {
            projeto.setName(name);
            projeto.setBeginning(beginning);
            projeto.setEnding(ending);
            atualizarProjetoNoBanco(projeto);
            return;
        }
    }
    throw std::invalid_argument("Erro: Nao foi possivel atualizar. Projeto nao encontrado.");
}

void CntrServicoProjeto::excluirProjeto(Code code) {
    for (auto it = containerProjetos.begin(); it != containerProjetos.end(); ++it) {
        if (it->getCode().get() == code.get()) {
            removerProjetoNoBanco(it->getCode().get());
            containerProjetos.erase(it);
            return;
        }
    }
    throw std::invalid_argument("Erro: Nao foi possivel excluir. Projeto nao encontrado.");
}

std::vector<Code> CntrServicoProjeto::listarProjetosDePessoa(Email person) const {
    std::vector<Code> projetosDaPessoa;
    for (const auto& projeto : containerProjetos) {
        if (!person.get().empty()) {
            projetosDaPessoa.push_back(projeto.getCode());
        }
    }
    return projetosDaPessoa;
}