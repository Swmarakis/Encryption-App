File Encryption/Decryption App
Author

George Somarakis
Description

This is a simple file encryption and decryption application written in C++ using the FLTK library. The application uses a simple XOR encryption algorithm to encrypt and decrypt files.
How to Use

    Compile and run the program.
    Enter your password in the ‘Password’ field.
    Click on ‘Encrypt’ or ‘Decrypt’ button.
    A file chooser dialog will appear. Select the file you want to encrypt or decrypt.
    The encrypted file will be saved as ‘encrypted_file’ and the decrypted file will be saved as ‘decrypted_file’.

Dependencies

    FLTK library
    C++ Standard Library

Compilation

To compile the program, you need to have the FLTK library installed on your system. You can compile the program using g++:

g++ main.cpp -o app -lfltk

Disclaimer

This program uses a simple XOR encryption algorithm which is not secure for sensitive data. Use at your own risk.
License

This project is open source. Feel free to use, modify, and distribute the code.

