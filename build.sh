#!/bin/bash

# Script para compilar e executar o Sistema Scrum

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Função para imprimir mensagens
print_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERRO]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[AVISO]${NC} $1"
}

# Verificar se está no diretório correto
if [ ! -f "scrum.pro" ]; then
    print_error "arquivo scrum.pro não encontrado. Execute este script do diretório raiz do projeto."
    exit 1
fi

# Menu de opções
echo ""
echo "╔════════════════════════════════════════╗"
echo "║  Sistema de Gerenciamento Scrum       ║"
echo "║  Compilador de Projeto                ║"
echo "╚════════════════════════════════════════╝"
echo ""
echo "Escolha uma opção:"
echo "1) Compilar GUI (Qt5)"
echo "2) Executar GUI"
echo "3) Compilar e Executar GUI"
echo "4) Compilar Console"
echo "5) Executar Console"
echo "6) Compilar e Executar Console"
echo "7) Limpar arquivos compilados"
echo "8) Sair"
echo ""
read -p "Opção [1-8]: " opcao

case $opcao in
    1)
        print_info "Compilando versão Qt5..."
        qmake scrum.pro
        if [ $? -ne 0 ]; then
            print_error "Falha ao gerar Makefile com qmake"
            exit 1
        fi
        make
        if [ $? -eq 0 ]; then
            print_info "Compilação concluída com sucesso!"
            ls -lh scrum_gui
        else
            print_error "Falha na compilação"
            exit 1
        fi
        ;;
    2)
        if [ ! -f "scrum_gui" ]; then
            print_error "Executável scrum_gui não encontrado. Compile primeiro com a opção 1."
            exit 1
        fi
        print_info "Executando GUI..."
        ./scrum_gui
        ;;
    3)
        print_info "Compilando versão Qt5..."
        qmake scrum.pro
        make
        if [ $? -eq 0 ]; then
            print_info "Compilação concluída com sucesso! Iniciando aplicação..."
            sleep 1
            ./scrum_gui
        else
            print_error "Falha na compilação"
            exit 1
        fi
        ;;
    4)
        print_info "Compilando versão Console..."
        g++ -std=c++17 -Wall -Wextra -I. main.cpp \
            controllers/CtrlPersonService.cpp \
            controllers/CtrlProjectService.cpp \
            controllers/CtrlSprintPlanService.cpp \
            controllers/CtrlUserStoryService.cpp \
            presentation/console_presentation.cpp \
            entidades/person.cpp \
            entidades/project.cpp \
            entidades/sprintplan.cpp \
            entidades/userstory.cpp \
            dominios/dominios.cpp \
            dominios/derivados/*.cpp \
            database/sqlite_connection.cpp \
            -lsqlite3 -o scrum_app
        if [ $? -eq 0 ]; then
            print_info "Compilação concluída com sucesso!"
            ls -lh scrum_app
        else
            print_error "Falha na compilação"
            exit 1
        fi
        ;;
    5)
        if [ ! -f "scrum_app" ]; then
            print_error "Executável scrum_app não encontrado. Compile primeiro com a opção 4."
            exit 1
        fi
        print_info "Executando Console..."
        ./scrum_app
        ;;
    6)
        print_info "Compilando versão Console..."
        g++ -std=c++17 -Wall -Wextra -I. main.cpp \
            controllers/CtrlPersonService.cpp \
            controllers/CtrlProjectService.cpp \
            controllers/CtrlSprintPlanService.cpp \
            controllers/CtrlUserStoryService.cpp \
            presentation/console_presentation.cpp \
            entidades/person.cpp \
            entidades/project.cpp \
            entidades/sprintplan.cpp \
            entidades/userstory.cpp \
            dominios/dominios.cpp \
            dominios/derivados/*.cpp \
            database/sqlite_connection.cpp \
            -lsqlite3 -o scrum_app
        if [ $? -eq 0 ]; then
            print_info "Compilação concluída com sucesso! Iniciando aplicação..."
            sleep 1
            ./scrum_app
        else
            print_error "Falha na compilação"
            exit 1
        fi
        ;;
    7)
        print_warning "Removendo arquivos compilados..."
        # Limpar com make
        if [ -f "Makefile" ]; then
            make distclean 2>/dev/null || make clean 2>/dev/null
        fi
        # Remover manualmente qualquer arquivo restante
        rm -f scrum_gui scrum_app
        rm -f *.o *.a *.so
        rm -f moc_*.cpp moc_*.o
        rm -f qrc_*.cpp qrc_*.o
        rm -f Makefile* .qmake.stash
        print_info "Arquivos removidos. Diretório limpo!"
        ;;
    8)
        print_info "Encerrando..."
        exit 0
        ;;
    *)
        print_error "Opção inválida!"
        exit 1
        ;;
esac
