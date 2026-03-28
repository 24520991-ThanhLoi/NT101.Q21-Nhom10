#include <iostream>
#include <cstdint>
#include <bitset>

// Hàm F đơn giản: XOR với khóa con rồi giữ lại 4 bit (0x0F)
uint8_t F(uint8_t right, uint8_t subkey) {
    return (right ^ subkey) & 0x0F;
}

// Cấu trúc Feistel cho một vòng
// Dùng tham chiếu (&) để cập nhật trực tiếp giá trị của L và R
void feistel_round(uint8_t& L, uint8_t& R, uint8_t subkey) {
    uint8_t L_out = R;
    uint8_t R_out = L ^ F(R, subkey);
    
    L = L_out;
    R = R_out;
}

// Hàm theo dõi hiệu ứng lan truyền
uint8_t track_avalanche(uint8_t msg, uint8_t key) {
    // Tách msg 8-bit thành 2 nửa L và R (mỗi nửa 4 bit)
    uint8_t L = (msg >> 4) & 0x0F;
    uint8_t R = msg & 0x0F;
    
    // Tạo 4 khóa con từ khóa gốc
    uint8_t subkeys[4] = {
        static_cast<uint8_t>(key & 0x0F),               // k0
        static_cast<uint8_t>((key >> 4) & 0x0F),        // k1
        static_cast<uint8_t>((key + 1) & 0x0F),         // k2
        static_cast<uint8_t>((key + 2) & 0x0F)          // k3
    };
    
    // std::bitset<4> giúp in số nguyên thành chuỗi nhị phân 4-bit
    std::cout << "Khoi tao : L=" << std::bitset<4>(L) << ", R=" << std::bitset<4>(R) << std::endl;
    
    for (int i = 0; i < 4; i++) {
        feistel_round(L, R, subkeys[i]);
        std::cout << "Vong  " << i + 1 << ": L=" << std::bitset<4>(L) << ", R=" << std::bitset<4>(R) << std::endl;
    }
    
    return (L << 4) | R;
}

int main() {
    std::cout << "--- Ma hoa M1 (0xAB) ---" << std::endl;
    track_avalanche(0xAB, 0x12);
    
    std::cout << "\n--- Ma hoa M2 (0xAC) ---" << std::endl;
    track_avalanche(0xAC, 0x12);
    
    return 0;
}