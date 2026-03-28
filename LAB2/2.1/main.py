def F(right, subkey):
    # Hàm F đơn giản: XOR với khóa con và lấy 4 bit cuối
    return (right ^ subkey) & 0x0F

def feistel_round(L_in, R_in, subkey):
    # Triển khai công thức cấu trúc Feistel
    L_out = R_in
    R_out = L_in ^ F(R_in, subkey)
    return L_out, R_out

def track_avalanche(msg, key):
    # Tách bản rõ 8-bit thành nửa trái (L) và nửa phải (R), mỗi nửa 4-bit
    L = (msg >> 4) & 0x0F
    R = msg & 0x0F
    
    # Tạo 4 khóa con từ khóa gốc
    subkeys = [key & 0x0F, (key >> 4) & 0x0F, (key + 1) & 0x0F, (key + 2) & 0x0F]
    
    print(f"Khởi tạo : L={format(L, '04b')}, R={format(R, '04b')}")
    
    # Chạy qua 4 vòng lặp Feistel
    for i in range(4):
        L, R = feistel_round(L, R, subkeys[i])
        print(f"Vòng {i+1}   : L={format(L, '04b')}, R={format(R, '04b')}")
        
    return (L << 4) | R

print("--- Mã hóa M1 (0xAB) ---")
track_avalanche(0xAB, 0x12)

print("\n--- Mã hóa M2 (0xAC) ---")
track_avalanche(0xAC, 0x12)