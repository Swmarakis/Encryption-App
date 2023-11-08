#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Box.H>
#include <string>
#include <iostream>
#include <fstream>

#define MAX_BUFFER_SIZE 1024

std::string xor_encrypt_decrypt(const std::string &data, const std::string &key) {
    std::string result = data;
    size_t key_len = key.length();

    for (size_t i = 0; i < data.length(); i++) {
        result[i] = data[i] ^ key[i % key_len];
    }

    return result;
}

void encrypt_file(const std::string &input_file, const std::string &output_file, const std::string &password) {
    std::ifstream input(input_file, std::ios::binary);
    std::ofstream output(output_file, std::ios::binary);
    if (!input || !output) {
        std::cout << "Error opening files.\n";
        return;
    }

    char buffer[MAX_BUFFER_SIZE];
    size_t read_bytes;

    while (input.read(buffer, sizeof(buffer)), (read_bytes = input.gcount()) > 0) {
        std::string encrypted_data(buffer, read_bytes);
        std::string encrypted_buffer = xor_encrypt_decrypt(encrypted_data, password);
        output.write(encrypted_buffer.c_str(), encrypted_buffer.length());
    }
}

void decrypt_file(const std::string &input_file, const std::string &output_file, const std::string &password) {
    // Decryption is just the reverse process of encryption
    encrypt_file(input_file, output_file, password);
}

void encrypt_callback(Fl_Widget* widget, void* data) {
    Fl_File_Chooser *chooser = new Fl_File_Chooser("", "", Fl_File_Chooser::SINGLE, "Select File");
    chooser->show();
    while (chooser->shown()) {
        Fl::wait();
    }

    if (chooser->value() == nullptr) {
        return;
    }

    std::string input_file = chooser->value();
    const std::string output_file = "encrypted_file";

    Fl_Secret_Input *password_input = static_cast<Fl_Secret_Input*>(data);
    const std::string password = password_input->value();

    encrypt_file(input_file, output_file, password);
    std::cout << "File encrypted successfully!\n";
}

void decrypt_callback(Fl_Widget* widget, void* data) {
    Fl_File_Chooser *chooser = new Fl_File_Chooser("", "", Fl_File_Chooser::SINGLE, "Select File");
    chooser->show();
    while (chooser->shown()) {
        Fl::wait();
    }

    if (chooser->value() == nullptr) {
        return;
    }

    std::string input_file = chooser->value();
    const std::string output_file = "decrypted_file";

    Fl_Secret_Input *password_input = static_cast<Fl_Secret_Input*>(data);
    const std::string password = password_input->value();

    decrypt_file(input_file, output_file, password);
    std::cout << "File decrypted successfully!\n";
}

int main() {
    // Create the FLTK GUI window
    Fl_Double_Window window(370, 170, "File Encryption/Decryption APP");
    Fl_Box *label = new Fl_Box(150,10,100,30, "Som SoftwareTM");
    label -> box(FL_NO_BOX);
    label -> labelfont(FL_BOLD);
    label -> labelsize(18);
   
    Fl_Secret_Input password_input(105, 80, 230, 25, "Password:");
    password_input.labeltype(FL_NORMAL_LABEL);

    Fl_Button encrypt_button(30, 125, 100, 25, "Encrypt");
    encrypt_button.labeltype(FL_NORMAL_LABEL);
    encrypt_button.callback(encrypt_callback, &password_input);

    Fl_Button decrypt_button(230, 125, 100, 25, "Decrypt");
    decrypt_button.labeltype(FL_NORMAL_LABEL);
    decrypt_button.callback(decrypt_callback, &password_input);

    // Show the window
    window.end();
    window.show();

    // Run the FLTK event loop
    return Fl::run();
}

