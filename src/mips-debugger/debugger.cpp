#include "debugger.hpp"

DebuggerWindow::DebuggerWindow(const QString& assembly_file, QWidget* parent) : QWidget(parent) {
    setWindowTitle("MIPS Debugger");
    resize(1200, 800);

    assembly_group = new QGroupBox("Assembly");
    state_group = new QGroupBox("State");
    pc_label = new QLabel("PC: 0x00000000");
    step_button = new QPushButton("Step");

    assembly_view = new QTextEdit();
    assembly_view->setReadOnly(true);


    command_input = new QLineEdit();
    const QString placeholder_text = "Enter command: (e.g., reg $name, mem8/mem16/mem32 address)";
    command_input->setPlaceholderText(placeholder_text);
    command_button = new QPushButton("Submit");

    output_console = new QTextEdit();
    output_console->setReadOnly(true);

    auto* pc_control_layout = new QHBoxLayout();
    pc_control_layout->addWidget(pc_label);
    pc_control_layout->addWidget(step_button);
    pc_control_layout->addStretch();

    auto* register_grid_layout = new QGridLayout();
    const char* register_names[] = {
        "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
        "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
        "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
        "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$s8", "$ra"
    };

    for (size_t i = 0; i < 32; ++i) {
       int row = i / 4;
        int col = i % 4;

        auto* register_frame = new QFrame();
        register_frame->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

        auto* name_label = new QLabel(register_names[i]);

        register_value_labels[i] = new QLabel("0x00000000");

        auto* inner_layout = new QHBoxLayout();
        inner_layout->addWidget(name_label);
        inner_layout->addWidget(register_value_labels[i]);
        register_frame->setLayout(inner_layout); 
        register_grid_layout->addWidget(register_frame, row, col);
    }

    auto* state_layout = new QVBoxLayout();
    state_layout->addLayout(pc_control_layout);
    state_layout->addLayout(register_grid_layout);
    state_group->setLayout(state_layout);

    auto* assembly_layout = new QVBoxLayout();
    assembly_layout->addWidget(assembly_view);
    assembly_group->setLayout(assembly_layout);

    auto* top_panels_layout = new QHBoxLayout();
    top_panels_layout->addWidget(assembly_group);
    top_panels_layout->addWidget(state_group);
    top_panels_layout->setStretch(0, 1);
    top_panels_layout->setStretch(1, 2);

    auto* command_label = new QLabel("Command:");
    
    auto* command_layout = new QHBoxLayout();
    command_layout->addWidget(command_label);
    command_layout->addWidget(command_input);
    command_layout->addWidget(command_button);

    auto* main_layout = new QVBoxLayout();
    main_layout->addLayout(top_panels_layout);
    main_layout->addLayout(command_layout);
    main_layout->addWidget(output_console);

    setLayout(main_layout);

    machine_state = std::make_unique<MachineState>(1024 * 1024 * 4);
    interpreter = std::make_unique<Interpreter>(*machine_state);

    populate_register_map();

    connect(step_button, &QPushButton::clicked, this, &DebuggerWindow::on_step_clicked);
    connect(command_button, &QPushButton::clicked, this, &DebuggerWindow::command_entered);
    connect(command_input, &QLineEdit::returnPressed, this, &DebuggerWindow::command_entered);
    
    load_and_assemble_file(assembly_file);
    update_ui();
}

void DebuggerWindow::load_and_assemble_file(const QString& filepath) {
    // 1. Read the .asm file to display its text content in the GUI
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not open file: " + filepath);
        return;
    }
    QTextStream in(&file);
    assembly_view->setText(in.readAll());
    file.close();

    // 2. Assemble the file using your Assembler class
    std::ifstream input_file_stream(filepath.toStdString());
    Assembler assembler;
    std::stringstream binary_stream;

    try {
        assembler.process(input_file_stream, binary_stream, false);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Assembly Error", e.what());
        return;
    }

    // 3. Load the resulting machine code into the machine's memory
    std::string binary_string = binary_stream.str();
    std::vector<uint8_t> machine_code(binary_string.begin(), binary_string.end());

    for (size_t i = 0; i < machine_code.size(); ++i) {
        machine_state->write_byte(i, machine_code[i]);
    }

    // 4. Find the 'main' label from the symbol table and set the PC
    const auto& symbol_table = assembler.get_symbol_table();
    if (!symbol_table.count("main")) {
        QMessageBox::critical(this, "Error", "'main' label not found in assembly file.");
        return;
    }
    
    machine_state->set_pc(symbol_table.at("main"));
    interpreter->start();
}

void DebuggerWindow::on_step_clicked() {
    if (interpreter->is_running()) {
        interpreter->step();
        update_ui();
    }
}

void DebuggerWindow::update_ui() {
    uint32_t pc = machine_state->get_pc();
    pc_label->setText(QString("PC: 0x%1").arg(pc, 8, 16, QChar('0')));

    for (int i = 0; i < 32; ++i) {
        uint32_t value = machine_state->get_register(i);
        QString value_text = QString("0x%1").arg(value, 8, 16, QChar('0'));
        register_value_labels[i]->setText(value_text);
    }
}

void DebuggerWindow::populate_register_map() {
    const char* registers_names[] = {
        "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
        "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
        "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
        "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$s8", "$ra"
    };

    for (uint8_t i = 0; i < 32; ++i) {
        reg_name_index[registers_names[i]] = i;
    }
}

void DebuggerWindow::command_entered() {
    QString command_text = command_input->text().trimmed();
    command_input->clear();

    if (command_text.isEmpty()) {
        return;
    }

    output_console->append("> " + command_text);

    QStringList parts_of_command = command_text.split(" ", Qt::SkipEmptyParts);
    const QString command = parts_of_command[0].toLower();

    if (command == "reg") {
        if (parts_of_command.size() != 2) {
            output_console->append("Invalid usage. Correct usage: reg <register name>");
            return;
        } else {
            const QString register_name = parts_of_command[1];

            if (reg_name_index.count(register_name)) {
                uint8_t register_index = reg_name_index.at(register_name);
                uint32_t register_value = machine_state->get_register(register_index);

                QString output_message = QString("Value of %1 is 0x%2.").arg(register_name).arg(register_value, 8, 16, QChar('0'));

                output_console->append(output_message);
            } else {
                output_console->append("Error: " + register_name + " is not a valid register name.");
            }
        }
    } else if ((command == "mem8") || (command == "mem16") || (command == "mem32")) {
        if (parts_of_command.size() != 2) {
            output_console->append("Invalid usage. Correct usage: " + command  + " <address>");
            return;
        } else {
            bool converted;
            uint32_t address = parts_of_command[1].toUInt(&converted, 0);

            if (!converted) {
                output_console->append("Error: invalid address format");
                return; 
            } else {
                try {
                    uint32_t memory_value;

                    if (command == "mem8") {
                        memory_value = machine_state->read_byte_unsigned(address);
                        output_console->append(QString("Value at 0x%1 is 0x%2")
                        .arg(address, 8, 16, QChar('0')).arg(memory_value, 2, 16, QChar('0')));
                    } else if (command == "mem16") {
                        memory_value = machine_state->read_half_word_unsigned(address);
                        output_console->append(QString("Value at 0x%1 is 0x%2")
                        .arg(address, 8, 16, QChar('0')).arg(memory_value, 4, 16, QChar('0')));
                    } else {
                        memory_value = machine_state->read_word(address);
                        output_console->append(QString("Value at 0x%1 is 0x%2")
                        .arg(address, 8, 16, QChar('0')).arg(memory_value, 8, 16, QChar('0')));
                    }
                } catch (const std::out_of_range& e) {
                    output_console->append("Error: Memory access out of bounds, address = " + parts_of_command[1]);
                }
            }
        }
    } else {
        output_console->append("Error: " + command + " is an unknown command");
    }
}