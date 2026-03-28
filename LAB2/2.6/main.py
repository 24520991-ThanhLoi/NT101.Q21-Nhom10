import random

# ==========================================
# 1. CÁC HÀM XỬ LÝ SỐ NGUYÊN TỐ
# ==========================================

# Thuật toán Miller-Rabin để kiểm tra số nguyên tố
def is_prime(n, k=5):
    if n <= 1: return False
    if n <= 3: return True
    if n % 2 == 0: return False
    
    # Phân tích n-1 = 2^r * d
    r, d = 0, n - 1
    while d % 2 == 0:
        r += 1
        d //= 2
        
    # Thử nghiệm k lần
    for _ in range(k):
        a = random.randint(2, n - 2)
        x = mod_exp(a, d, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(r - 1):
            x = mod_exp(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True

# Hàm tạo số nguyên tố ngẫu nhiên có số bit cho trước
def generate_prime(bits):
    while True:
        # Sinh số ngẫu nhiên
        num = random.getrandbits(bits)
        # Ép cho số đó luôn lẻ và có đúng số bit yêu cầu
        num |= (1 << (bits - 1)) | 1 
        if is_prime(num):
            return num

# ==========================================
# 2. TÌM ƯỚC CHUNG LỚN NHẤT (GCD) - EUCLID
# ==========================================
def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

# ==========================================
# 3. LŨY THỪA MODULE (MODULAR EXPONENTIATION)
# ==========================================
# Tính (a^x) mod p cho số siêu lớn mà không bị tràn bộ nhớ
def mod_exp(a, x, p):
    result = 1
    a = a % p
    while x > 0:
        if x % 2 == 1: # Nếu mũ lẻ, nhân a vào kết quả
            result = (result * a) % p
        x = x // 2     # Chia đôi số mũ
        a = (a * a) % p # Bình phương cơ số
    return result

# ==========================================
# CHƯƠNG TRÌNH CHÍNH (TEST CÁC YÊU CẦU)
# ==========================================
if __name__ == "__main__":
    print("--- YÊU CẦU 1: SỐ NGUYÊN TỐ ---")
    print(f"Số nguyên tố 8 bits : {generate_prime(8)}")
    print(f"Số nguyên tố 16 bits: {generate_prime(16)}")
    print(f"Số nguyên tố 64 bits: {generate_prime(64)}")

    print("\n--- 10 số nguyên tố lớn nhất nhỏ hơn Mersenne thứ 10 ---")
    # Số nguyên tố Mersenne thứ 10 là 2^89 - 1
    m10 = (1 << 89) - 1 
    primes_list = []
    num = m10 - 2 # Bắt đầu thử từ số lẻ nhỏ hơn M10
    
    while len(primes_list) < 10:
        if is_prime(num):
            primes_list.append(num)
        num -= 2
        
    for i, p in enumerate(primes_list):
        print(f"Top {i+1}: {p}")

    print("\n--- Kiểm tra 1 số tùy ý nhỏ hơn 2^89 - 1 ---")
    test_num = m10 - 1000 # Chọn đại 1 số
    print(f"Số {test_num} có phải số nguyên tố không? -> {is_prime(test_num)}")

    print("\n--- YÊU CẦU 2: TÌM GCD (ƯỚC CHUNG LỚN NHẤT) ---")
    num1 = generate_prime(64) * 15
    num2 = generate_prime(64) * 25
    print(f"Số thứ 1: {num1}")
    print(f"Số thứ 2: {num2}")
    print(f"Ước chung lớn nhất GCD: {gcd(num1, num2)}")

    print("\n--- YÊU CẦU 3: LŨY THỪA MODULE LỚN ---")
    a, x, p = 7, 40, 19
    print(f"Kết quả của {a}^{x} mod {p} = {mod_exp(a, x, p)}")