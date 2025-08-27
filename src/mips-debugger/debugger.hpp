#pragma once

#include "interpreter.hpp"
#include "machine_state.hpp"
#include "assembler.hpp"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <memory>
#include <QString>
#include <QTextEdit>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QFile>
#include <QMessageBox>
#include <fstream>
#include <QCheckBox>

class DebuggerWindow : public QWidget {
    Q_OBJECT

private slots:
    void on_step_clicked();
    void command_entered();
    void change_reg_display(int current_state);

private:
    QPushButton* step_button;
    QLabel* pc_label;

    void update_ui();

    std::unique_ptr<MachineState> machine_state;
    std::unique_ptr<Interpreter> interpreter;

    QGroupBox* assembly_group;
    QGroupBox* state_group;

    QLineEdit* command_input;
    QPushButton* command_button;
    QTextEdit* output_console;

    std::array<QLabel*, 32> register_value_labels;

    std::unordered_map<QString, uint8_t> reg_name_index;

    void populate_register_map();

    QTextEdit* assembly_view;

    void load_and_assemble_file(const QString& filepath);

    QCheckBox* reg_display_option;
    bool display_decimal = false;

public:
    explicit DebuggerWindow(const QString& assembly_file, QWidget* parent = nullptr);
};
