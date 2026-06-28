#!/bin/bash
# Script para limpeza rápida de arquivos compilados

echo "🧹 Limpando arquivos compilados e temporários..."

# Remover arquivos .o
rm -f *.o
echo "  ✓ Removidos arquivos .o"

# Remover arquivos MOC
rm -f moc_*.cpp moc_*.o
echo "  ✓ Removidos arquivos moc_*"

# Remover arquivos RCC
rm -f qrc_*.cpp qrc_*.o
echo "  ✓ Removidos arquivos qrc_*"

# Remover Makefiles
rm -f Makefile Makefile.* .qmake.stash
echo "  ✓ Removidos Makefiles"

# Remover bibliotecas antigas se existirem
rm -f *.a *.so *.so.*
echo "  ✓ Removidas bibliotecas antigas"

echo ""
echo "✅ Limpeza concluída!"
echo ""
echo "📁 Arquivos mantidos:"
ls -lh scrum_gui scrum_app 2>/dev/null | awk '{print "   " $9 " (" $5 ")"}'

echo ""
echo "Para compilar novamente:"
echo "  $ ./build.sh  (opção 3 para GUI)"
echo "  ou"
echo "  $ qmake scrum.pro && make"
