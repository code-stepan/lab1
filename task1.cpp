#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class encoder {
private:
	char* key;
	unsigned int len;
public:
	encoder(unsigned char const* key, unsigned int len);
	~encoder();
	encoder(encoder const& ob);
	void encode(char const* ifile, char const* ofile, bool flag);
	void set_key(char const* key);
};

int main() {
    encoder ob((unsigned char const*)"key", 3);
    encoder ob2(ob);
    ob.set_key("new_key");
    ob2.encode("file.txt", "ofile.txt", 1);
	return 0;
}

encoder::encoder(unsigned char const* key, unsigned int len) {
	this->key = new char[len + 1];
	this->len = len;
    int i;
    for (i = 0; i < len; i++) {
        this->key[i] = key[i];
    }
    this->key[i] = '\0';
}

encoder::encoder(encoder const& ob) {
    len = ob.len;
    key = new char[len + 1];
    int i;
    for (i = 0; i < len; i++) {
        key[i] = ob.key[i];
    }
    key[i] = '\0';
}

encoder::~encoder() {
    delete key;
}

void encoder::encode(char const* ifile, char const* ofile, bool flag) {
    unsigned char S[256];
    int i = 0;
    for (i = 0; i < 256; i++)
        S[i] = i;

    int j = 0; 
    for (i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % len]) % 256;
        swap(S[i], S[j]);
    }

    ifstream ifi(ifile);
    ofstream ofi(ofile);

    char x;
    j = 0;
    i = 0;
    char temp = 0;
    while (ifi.read(&x, 1)) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        temp = S[(S[i] + S[j]) % 256] ^ x;
        ofi << temp;
    }
    ifi.close();
    ofi.close();
}

void encoder::set_key(char const* key) {
    delete this->key;
    this->len = strlen((char*)key);
    this->key = new char[this->len + 1];
    int i;
    for (i = 0; i < len; i++) {
        this->key[i] = key[i];
    }
    this->key[i] = '\0';
}