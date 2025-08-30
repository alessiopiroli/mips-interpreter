#include "debugger.hpp"

#include <QApplication>


int main(int argc, char* argv[]) {
    QApplication debugger_app(argc, argv);

    if (argc != 2) {
        QMessageBox::critical(nullptr, "ERROR", "Correct usage: ./src/mips-debugger/mips-debugger <filename.asm>");
        return 1;
    } else {
        DebuggerWindow debugger_window(argv[1]);
        debugger_window.show();

        return debugger_app.exec();
    }
}

