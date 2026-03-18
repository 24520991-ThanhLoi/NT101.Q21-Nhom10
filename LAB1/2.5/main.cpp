#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

/*
 * Chương trình mã hóa và giải mã bằng Vigenère Cipher
 * Vigenère là một mã hóa cổ điển sử dụng khóa để mã hóa từng ký tự
 * Công thức: C = (P + K) % 26, D = (C - K) % 26
 * P: plaintext, K: khóa, C: ciphertext, D: decrypted text
 */

// Hàm chuẩn hóa khóa: loại bỏ khoảng trắng và chuyển thành chữ hoa
string normalizeKey(string key) {
    string normalKey = "";
    for (char c : key) {
        // Chỉ lấy các ký tự chữ cái, bỏ qua khoảng trắng
        if (isalpha(c)) {
            normalKey += toupper(c);
        }
    }
    return normalKey;
}

// Hàm mã hóa văn bản bằng Vigenère cipher
string encrypt(string plaintext, string key) {
    key = normalizeKey(key); // Chuẩn hóa khóa
    
    if (key.empty()) {
        cout << "Lỗi: Khóa không được để trống hoặc không chứa ký tự chữ cái!\n";
        return "";
    }
    
    string ciphertext = "";
    int keyIndex = 0;
    
    // Lặp qua từng ký tự của plaintext
    for (int i = 0; i < plaintext.length(); i++) {
        char c = plaintext[i];
        
        if (isalpha(c)) {
            // Lấy giá trị khóa hiện tại (chu kỳ)
            char keyChar = key[keyIndex % key.length()];
            int keyValue = keyChar - 'A'; // Chuyển khóa thành số (0-25)
            
            if (isupper(c)) {
                // Mã hóa chữ hoa: (c - 'A' + keyValue) % 26 + 'A'
                ciphertext += (char)((c - 'A' + keyValue) % 26 + 'A');
            } else {
                // Mã hóa chữ thường: (c - 'a' + keyValue) % 26 + 'a'
                ciphertext += (char)((c - 'a' + keyValue) % 26 + 'a');
            }
            
            keyIndex++; // Chuyển sang ký tự tiếp theo của khóa
        } else {
            // Giữ lại khoảng trắng, dấu câu, số, v.v.
            ciphertext += c;
        }
    }
    
    return ciphertext;
}

// Hàm giải mã văn bản bằng Vigenère cipher
string decrypt(string ciphertext, string key) {
    key = normalizeKey(key); // Chuẩn hóa khóa
    if (key.empty()) {
        cout << "Lỗi: Khóa không được để trống hoặc không chứa ký tự chữ cái!\n";
        return "";
    }
    string plaintext = "";
    int keyIndex = 0;
    
    // Lặp qua từng ký tự của ciphertext
    for (int i = 0; i < ciphertext.length(); i++) {
        char c = ciphertext[i];
        
        if (isalpha(c)) {
            // Lấy giá trị khóa hiện tại (chu kỳ)
            char keyChar = key[keyIndex % key.length()];
            int keyValue = keyChar - 'A'; // Chuyển khóa thành số (0-25)
            
            if (isupper(c)) {
                // Giải mã chữ hoa: (c - 'A' - keyValue + 26) % 26 + 'A'
                // +26 để đảm bảo kết quả luôn dương
                plaintext += (char)((c - 'A' - keyValue + 26) % 26 + 'A');
            } else {
                // Giải mã chữ thường: (c - 'a' - keyValue + 26) % 26 + 'a'
                plaintext += (char)((c - 'a' - keyValue + 26) % 26 + 'a');
            }
            
            keyIndex++; // Chuyển sang ký tự tiếp theo của khóa
        } else {
            // Giữ lại khoảng trắng, dấu câu, số, v.v.
            plaintext += c;
        }
    }
    return plaintext;
}

// Hàm hiển thị menu
void displayMenu() {
    cout << "\n========== VIGENÈRE CIPHER PROGRAM ==========\n";
    cout << "1. Mã hóa (Encrypt)\n";
    cout << "2. Giải mã (Decrypt)\n";
    cout << "3. Thoát\n";
    cout << "Chọn tùy chọn (1-3): ";
}

int main() {
    // Đặt chữ tiếng Việt
    system("chcp 65001 > nul");
    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Bỏ qua ký tự newline còn lại
        if (choice == 1) {
            // Chọn mã hóa
            string plaintext, key;
            cout << "\n--- MÃ HÓA ---\n";
            cout << "Nhập khóa: ";
            getline(cin, key);
            cout << "Nhập bản rõ (plaintext): ";
            getline(cin, plaintext);
            string result = encrypt(plaintext, key);
            if (!result.empty()) {
                cout << "Kết quả mã hóa: " << result << "\n";
            }
        } else if (choice == 2) {
            // Chọn giải mã
            string ciphertext, key;
            cout << "\n--- GIẢI MÃ ---\n";
            cout << "Nhập khóa: ";
            getline(cin, key);
            cout << "Nhập bản mã (ciphertext): ";
            getline(cin, ciphertext);
            string result = decrypt(ciphertext, key);
            if (!result.empty()) {cout << "Kết quả giải mã: " << result << "\n";}
        } 
        else if (choice == 3) {
            cout << "Cảm ơn bạn đã sử dụng chương trình!\n";
            break;} 
        else {cout << "Lựa chọn không hợp lệ! Vui lòng chọn lại.\n";}
    } while (true);
    return 0;
}
