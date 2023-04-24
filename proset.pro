QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

HEADERS       = mainwindow.h \
                menu.h

SOURCES       = main.cpp \
                mainwindow.cpp \
                menu.cpp

FORMS         = mainwindow.ui \
                menu.ui

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/touch/fingerpaint
INSTALLS += target
