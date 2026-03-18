#include <iostream>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

/*
 * Chương trình mã hóa và giải mã bằng Affine Cipher
 * Affine cipher sử dụng công thức toán học: E(x) = (ax + b) mod 26
 * Và giải mã: D(y) = a^(-1)(y - b) mod 26
 * Trong đó: a, b là khóa; gcd(a, 26) = 1 (a phải nguyên tố cùng nhau với 26)
 */

// Các giá trị a hợp lệ (nguyên tố cùng nhau với 26): 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25
int validA[] = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};

// Kiểm tra xem a có hợp lệ không (gcd(a, 26) = 1)
bool isValidA(int a) {
    a = a % 26; // Lấy phần dư của a với 26
    for (int valid : validA) {
        if (a == valid) return true;
    }
    return false;
}

// Hàm tính ước số chung lớn nhất (GCD)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Hàm tính nghịch đảo modulo (a^(-1) mod 26)
// Sử dụng thuật toán mở rộng Euclidean
int modInverse(int a, int m) {
    a = a % m; // Lấy phần dư của a với m
    
    // Nếu gcd(a, m) != 1, không có nghịch đảo
    if (gcd(a, m) != 1) {
        return -1; // Không tồn tại nghịch đảo
    }
    
    // Tìm x sao cho (a * x) % m == 1
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    
    return -1;
}

// Hàm mã hóa bằng Affine cipher
string encrypt(string plaintext, int a, int b) {
    // Kiểm tra a có hợp lệ
    if (!isValidA(a)) {
        cout << "Lỗi: Giá trị a phải là: 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25\n";
        return "";
    }
    
    a = a % 26; // Đảm bảo a nằm trong phạm vi 0-25
    b = b % 26; // Đảm bảo b nằm trong phạm vi 0-25
    
    string ciphertext = "";
    
    // Lặp qua từng ký tự
    for (char c : plaintext) {
        if (isalpha(c)) {
            // Lấy vị trí của ký tự (0-25)
            int x;
            if (isupper(c)) {
                x = c - 'A'; // Chữ hoa
                // Áp dụng công thức mã hóa: E(x) = (ax + b) mod 26
                int encrypted = (a * x + b) % 26;
                ciphertext += (char)(encrypted + 'A');
            } else {
                x = c - 'a'; // Chữ thường
                // Áp dụng công thức mã hóa
                int encrypted = (a * x + b) % 26;
                ciphertext += (char)(encrypted + 'a');
            }
        } else {
            // Giữ lại khoảng trắng, dấu câu, số, v.v.
            ciphertext += c;
        }
    }
    return ciphertext;
}

// Hàm giải mã bằng Affine cipher
string decrypt(string ciphertext, int a, int b) {
    // Kiểm tra a có hợp lệ
    if (!isValidA(a)) {
        cout << "Lỗi: Giá trị a phải là: 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25\n";
        return "";
    }
    a = a % 26;
    b = b % 26;
    // Tính a^(-1) mod 26 (nghịch đảo modulo)
    int aInverse = modInverse(a, 26);
    if (aInverse == -1) {
        cout << "Lỗi: Không thể tính nghịch đảo modulo!\n";
        return "";
    }
    string plaintext = "";
    // Lặp qua từng ký tự
    for (char c : ciphertext) {
        if (isalpha(c)) {
            // Lấy vị trí của ký tự (0-25)
            int y;
            if (isupper(c)) {
                y = c - 'A'; // Chữ hoa
                // Áp dụng công thức giải mã: D(y) = a^(-1)(y - b) mod 26
                int decrypted = (aInverse * (y - b + 26)) % 26;
                plaintext += (char)(decrypted + 'A');
            } else {
                y = c - 'a'; // Chữ thường
                // Áp dụng công thức giải mã
                int decrypted = (aInverse * (y - b + 26)) % 26;
                plaintext += (char)(decrypted + 'a');
            }
        } else {
            // Giữ lại khoảng trắng, dấu câu, số, v.v.
            plaintext += c;}
    }
    return plaintext;
}

// Hàm hiển thị menu
void displayMenu() {
    cout << "\n========== AFFINE CIPHER PROGRAM ==========\n";
    cout << "1. Mã hóa (Encrypt)\n";
    cout << "2. Giải mã (Decrypt)\n";
    cout << "3. Hiển thị các giá trị a hợp lệ\n";
    cout << "4. Thoát\n";
    cout << "Chọn tùy chọn (1-4): ";
}

// Hàm hiển thị các giá trị a hợp lệ
void showValidValues() {
    cout << "\nCác giá trị a hợp lệ (nguyên tố cùng nhau với 26):\n";
    for (int valid : validA) {
        cout << valid << " ";
    }
    cout << "\n";
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
            string plaintext;
            int a, b;
            
            cout << "\n--- MÃ HÓA ---\n";
            showValidValues();
            
            cout << "Nhập khóa a (phải là một trong các giá trị trên): ";
            cin >> a;
            
            // Kiểm tra a có hợp lệ
            if (!isValidA(a)) {
                cout << "Lỗi: Giá trị a không hợp lệ!\n";
                cin.ignore();
                continue;
            }
            
            cout << "Nhập khóa b (0-25): ";
            cin >> b;
            
            cin.ignore(); // Bỏ qua ký tự newline
            cout << "Nhập bản rõ (plaintext): ";
            getline(cin, plaintext);
            
            string result = encrypt(plaintext, a, b);
            
            if (!result.empty()) {
                cout << "Kết quả mã hóa: " << result << "\n";
            }
            
        } else if (choice == 2) {
            // Chọn giải mã
            string ciphertext;
            int a, b;
            
            cout << "\n--- GIẢI MÃ ---\n";
            showValidValues();
            
            cout << "Nhập khóa a (phải là một trong các giá trị trên): ";
            cin >> a;
            
            // Kiểm tra a có hợp lệ
            if (!isValidA(a)) {
                cout << "Lỗi: Giá trị a không hợp lệ!\n";
                cin.ignore();
                continue;
            }
            
            cout << "Nhập khóa b (0-25): ";
            cin >> b;
            
            cin.ignore(); // Bỏ qua ký tự newline
            cout << "Nhập bản mã (ciphertext): ";
            getline(cin, ciphertext);
            
            string result = decrypt(ciphertext, a, b);
            
            if (!result.empty()) {
                cout << "Kết quả giải mã: " << result << "\n";
            }
            
        } else if (choice == 3) {
            // Hiển thị các giá trị a hợp lệ
            showValidValues();
            
        } else if (choice == 4) {
            cout << "Cảm ơn bạn đã sử dụng chương trình!\n";
            break;
            
        } else {
            cout << "Lựa chọn không hợp lệ! Vui lòng chọn lại.\n";
        }
        
    } while (true);
    
    return 0;
}
