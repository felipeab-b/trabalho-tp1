#include "../controllers/CtrlPersonService.hpp"
#include <cassert>
#include <cstdio>
#include <iostream>

int main() {
    std::remove("test_persons.db");

    {
        CntrServicoPessoa service("test_persons.db");

        Email email;
        email.set("ana@email.com");

        Name name;
        name.set("Ana Silva");

        Password password;
        password.set("a1B2c3");

        Role role;
        role.set("DESENVOLVEDOR");

        service.criarPessoa(email, name, password, role);

        Person recovered = service.lerPessoa(email);
        assert(recovered.getEmail().get() == "ana@email.com");
        assert(recovered.getName().get() == "Ana Silva");
    }

    {
        CntrServicoPessoa service("test_persons.db");

        Email email;
        email.set("ana@email.com");

        Person recovered = service.lerPessoa(email);
        assert(recovered.getName().get() == "Ana Silva");
    }

    std::cout << "person sqlite persistence ok" << std::endl;
    return 0;
}
