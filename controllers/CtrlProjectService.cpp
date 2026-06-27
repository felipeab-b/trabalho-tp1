#include "CtrlProjectService.hpp"

// 1. CRIAR PROJETO
void CntrServicoProjeto::criarProjeto(Code code, Name name, Date beginning, Date ending, Email scrumMaster) {
    // Verifica se já existe um projeto com este código (chave primária)
    for (const auto& projeto : containerProjetos) {
        if (projeto.getCode().get() == code.get()) {
            throw std::invalid_argument("Erro: Ja existe um projeto cadastrado com este codigo.");
        }
    }

    // Instancia a classe usando o construtor da Entidade
    Project novoProjeto(code);
    
    // Seta os atributos restantes
    novoProjeto.setName(name);
    novoProjeto.setBeginning(beginning);
    novoProjeto.setEnding(ending);
    
    // IMPORTANTE: O projeto precisa armazenar o Scrum Master associado a ele.
    // Descomente e ajuste a linha abaixo conforme o que você codou no project.hpp
    // novoProjeto.setScrumMaster(scrumMaster); 

    // Guarda no nosso contêiner em memória
    containerProjetos.push_back(novoProjeto);
}

// 2. LER PROJETO
Project CntrServicoProjeto::lerProjeto(Code code) const {
    for (const auto& projeto : containerProjetos) {
        if (projeto.getCode().get() == code.get()) {
            return projeto;
        }
    }
    throw std::invalid_argument("Erro: Projeto nao encontrado no sistema.");
}

// 3. ATUALIZAR PROJETO
void CntrServicoProjeto::atualizarProjeto(Code code, Name name, Date beginning, Date ending) {
    for (auto& projeto : containerProjetos) {
        if (projeto.getCode().get() == code.get()) {
            // A chave primária está blindada, atualizamos o resto
            projeto.setName(name);
            projeto.setBeginning(beginning);
            projeto.setEnding(ending);
            return; 
        }
    }
    throw std::invalid_argument("Erro: Nao foi possivel atualizar. Projeto nao encontrado.");
}

// 4. EXCLUIR PROJETO
void CntrServicoProjeto::excluirProjeto(Code code) {
    for (auto it = containerProjetos.begin(); it != containerProjetos.end(); ++it) {
        if (it->getCode().get() == code.get()) {
            // Nota: O TP1 diz que a exclusão não pode gerar inconsistência.
            // Numa versão final, você precisaria checar se o projeto tem planos de sprint 
            // antes de dar o erase aqui. Mas para o CRUD base, é isso:
            containerProjetos.erase(it); 
            return; 
        }
    }
    throw std::invalid_argument("Erro: Nao foi possivel excluir. Projeto nao encontrado.");
}

// 5. LISTAR PROJETOS DE PESSOA
std::vector<Code> CntrServicoProjeto::listarProjetosDePessoa(Email person) const {
    std::vector<Code> projetosDaPessoa;
    
    for (const auto& projeto : containerProjetos) {
        // Para listar os projetos dessa pessoa, temos que verificar se ela é o Scrum Master.
        // Descomente e ajuste conforme o nome do seu getter:
        // if (projeto.getScrumMaster().get() == person.get()) {
        //     projetosDaPessoa.push_back(projeto.getCode());
        // }
    }
    
    return projetosDaPessoa;
}