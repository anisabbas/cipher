#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class vigenere_cipher {
    // Vigenere cipher class with methods to encrypt and decrypt messages
    public:
        string key;
        string text;
    public:
        string encryprt(){
            // Encrypts the text using the key
            string ciphertext = "";
            int i, j, k, l, m, n, o;
            int key_length = key.length();
            int text_length = text.length();
            for(i = 0; i < text_length; i++)
            {
                if (isalpha(text[i]))
                {
                    if (isupper(text[i]))
                    {
                        j = text[i] - 65;
                        k = key[i % key_length] - 65;
                        l = (j + k) % 26;
                        ciphertext += l + 65;
                    }
                    else if(islower(text[i]))
                    {
                        m = text[i] - 97;
                        n = key[i % key_length] - 97;
                        o = (m + n) % 26;
                        ciphertext += o + 97;
                    }
                }
                else if(text[i] >= 32 && text[i] <= 64){
                    j = text[i] - 32;
                    k = key[i % key_length] - 32;
                    l = (j + k) % 32;
                    ciphertext += l + 32;
                }
                else{
                    ciphertext += text[i];
                }
            }
            return ciphertext;
        }
        string decrypt(){
            // Decrypts the text using the key
            string plaintext = "";
            int i, j, k, l, m, n, o;
            int key_length = key.length();
            int text_length = text.length();
            for(i = 0; i < text_length; i++)
            {
                if (isalpha(text[i]))
                {
                    if (isupper(text[i]))
                    {
                        j = text[i] - 65;
                        k = key[i % key_length] - 65;
                        l = (j - k) % 26;
                        if (l < 0)
                        {
                            l += 26;
                        }
                        plaintext += l + 65;
                    }
                    else if(islower(text[i]))
                    {
                        m = text[i] - 97;
                        n = key[i % key_length] - 97;
                        o = (m - n) % 26;
                        if (o < 0)
                        {
                            o += 26;
                        }
                        plaintext += o + 97;
                    }
                }
                else if(text[i] >= 32 && text[i] <= 64){
                    j = text[i] - 32;
                    k = key[i % key_length] - 32;
                    l = (j - k) % 32;
                    if (l < 0)
                    {
                        l += 32;
                    }
                    plaintext += l + 32;
                }
                else{
                    plaintext += text[i];
                }
            }
            return plaintext;
        }
};

string read_from_file(string filename){
    string text = "";
    ifstream file;
    file.open(filename);
    if(file.is_open()){
        while(!file.eof()){
            string line;
            getline(file, line);
            text += line;
        }
    }
    file.close();
    return text;
}

void write_to_file(string filename, string text){
    ofstream file;
    file.open(filename);
    if(file.is_open()){
        file << text;
    }
    file.close();
}

int main(int argc, char const *argv[])
{
    if (argc != 5)
    {
        cout << "Usage: ./file <encrypt/decrypt> <key_file> <input_file> <output_file>" << endl;
        return 0;
    }
    string mode = argv[1];
    string key_file = argv[2];
    string input_file = argv[3];
    string output_file = argv[4];
    string key = read_from_file(key_file);
    string text = read_from_file(input_file);
    vigenere_cipher cipher;
    cipher.key = key;
    cipher.text = text;
    if (mode == "encrypt")
    {
        string ciphertext = cipher.encryprt();
        write_to_file(output_file, ciphertext);
    }
    else if (mode == "decrypt")
    {
        string plaintext = cipher.decrypt();
        write_to_file(output_file, plaintext);
    }
    else
    {
        cout << "Usage: ./file <encrypt/decrypt> <key_file> <input_file> <output_file>" << endl;
    }
}
