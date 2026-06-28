#!/bin/bash

# Script para executar scrum_gui fora do ambiente snap
# Remove variáveis de snap que causam conflitos

# Limpar variáveis de snap
unset SNAP
unset SNAP_NAME
unset SNAP_VERSION
unset SNAP_REVISION
unset SNAP_ARCH
unset SNAP_LIBRARY_PATH
unset SNAP_COOKIE
unset SNAP_USER_COMMON
unset SNAP_USER_DATA
unset SNAP_REAL_HOME

# Limpar LD_LIBRARY_PATH de snap se tiver
if [[ $LD_LIBRARY_PATH == *"snap"* ]]; then
    LD_LIBRARY_PATH=$(echo $LD_LIBRARY_PATH | tr ':' '\n' | grep -v snap | tr '\n' ':' | sed 's/:$//')
    export LD_LIBRARY_PATH
fi

# Executar a aplicação
exec /home/felipe/trabalho-tp1/scrum_gui "$@"
