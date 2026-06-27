#include "CtrlPersonService.hpp"

// 1. CRIAR PESSOA
void CntrServicoPessoa::criarPessoa(Email email, Name name, Password password, Role role) {
    // Regra: Verifica se já existe alguém com esse email (chave primária)
    for (const auto& pessoa : containerPessoas) {
        if (pessoa.getEmail().get() == email.get()) {
            throw std::invalid_argument("Erro: Ja existe uma pessoa cadastrada com este email.");
        }
    }

    // Instancia a classe usando o construtor correto que você definiu
    Person novaPessoa(email);
    
    // Seta os atributos restantes usando os métodos reais da sua classe
    novaPessoa.setName(name);
    novaPessoa.setPassword(password);
    novaPessoa.setRole(role);

    // Guarda no nosso contêiner em memória
    containerPessoas.push_back(novaPessoa);
}

// 2. LER PESSOA
Person CntrServicoPessoa::lerPessoa(Email email) const {
    // Varre o vetor procurando o email exato
    for (const auto& pessoa : containerPessoas) {
        if (pessoa.getEmail().get() == email.get()) {
            return pessoa; // Achou! Devolve a pessoa
        }
    }
    
    throw std::invalid_argument("Erro: Pessoa nao encontrada no sistema.");
}

// 3. ATUALIZAR PESSOA
void CntrServicoPessoa::atualizarPessoa(Email email, Name name, Password password, Role role) {
    for (auto& pessoa : containerPessoas) {
        if (pessoa.getEmail().get() == email.get()) {
            // A chave primária (email) está blindada, atualizamos apenas os atributos permitidos
            pessoa.setName(name);
            pessoa.setPassword(password);
            pessoa.setRole(role);
            return; 
        }
    }
    
    throw std::invalid_argument("Erro: Nao foi possivel atualizar. Pessoa nao encontrada.");
}

// 4. EXCLUIR PESSOA
void CntrServicoPessoa::excluirPessoa(Email email) {
    for (auto it = containerPessoas.begin(); it != containerPessoas.end(); ++it) {
        if (it->getEmail().get() == email.get()) {
            containerPessoas.erase(it); 
            return; 
        }
    }
    
    throw std::invalid_argument("Erro: Nao foi possivel excluir. Pessoa nao encontrada.");
}
