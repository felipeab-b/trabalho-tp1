#ifndef CNTRL_PERSON_SERVICE_HPP
#define CNTRL_PERSON_SERVICE_HPP

#include "IPersonService.hpp" // Puxa a interface que você já tem
#include <vector>             // A estrutura de dados exigida
#include <stdexcept>

// A classe herda (implementa) a interface IPersonService
class CntrServicoPessoa : public IPersonService {
private:
    // Nossa estrutura de dados em memória que vai guardar as pessoas
    std::vector<Person> containerPessoas; 

public:
    // O 'override' avisa o compilador que estamos implementando os métodos da interface
    void criarPessoa(Email email, Name name, Password password, Role role) override;
    Person lerPessoa(Email email) const override;
    void atualizarPessoa(Email email, Name name, Password password, Role role) override;
    void excluirPessoa(Email email) override;
};

#endif