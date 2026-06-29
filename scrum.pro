QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Flags para melhorar compatibilidade com snap e threading
QMAKE_CXXFLAGS += -fPIC -Wl,-z,relro,-z,now
QMAKE_LFLAGS += -Wl,-rpath-link=/lib/x86_64-linux-gnu

TARGET = scrum_gui
TEMPLATE = app

SOURCES += \
    gui/main_gui.cpp \
    gui/MainWindow.cpp \
    gui/AuthWidget.cpp \
    gui/LoginWidget.cpp \
    gui/RegisterWidget.cpp \
    gui/PessoaWidget.cpp \
    gui/ProjetoWidget.cpp \
    gui/SprintWidget.cpp \
    gui/HistoriaWidget.cpp \
    presentation/console_presentation.cpp \
    controllers/CtrlPersonService.cpp \
    controllers/CtrlAuthService.cpp \
    controllers/CtrlProjectService.cpp \
    controllers/CtrlSprintPlanService.cpp \
    controllers/CtrlUserStoryService.cpp \
    entidades/person.cpp \
    entidades/project.cpp \
    entidades/sprintplan.cpp \
    entidades/userstory.cpp \
    dominios/dominios.cpp \
    dominios/derivados/code.cpp \
    dominios/derivados/date.cpp \
    dominios/derivados/email.cpp \
    dominios/derivados/name.cpp \
    dominios/derivados/password.cpp \
    dominios/derivados/priority.cpp \
    dominios/derivados/role.cpp \
    dominios/derivados/state.cpp \
    dominios/derivados/text.cpp \
    dominios/derivados/time.cpp \
    database/sqlite_connection.cpp

HEADERS += \
    gui/MainWindow.hpp \
    gui/AuthWidget.hpp \
    gui/LoginWidget.hpp \
    gui/RegisterWidget.hpp \
    gui/PessoaWidget.hpp \
    gui/ProjetoWidget.hpp \
    gui/SprintWidget.hpp \
    gui/HistoriaWidget.hpp \
    presentation/console_presentation.hpp \
    controllers/CtrlPersonService.hpp \
    controllers/CtrlAuthService.hpp \
    controllers/CtrlProjectService.hpp \
    controllers/CtrlSprintPlanService.hpp \
    controllers/CtrlUserStoryService.hpp \
    interfaces/IPersonService.hpp \
    interfaces/IProjectService.hpp \
    interfaces/ISprintPlanService.hpp \
    interfaces/IUserStoryService.hpp \
    database/sqlite_connection.hpp

INCLUDEPATH += . controllers interfaces dominios dominios/derivados entidades database

LIBS += -lsqlite3

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
