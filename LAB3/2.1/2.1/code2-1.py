import math
import base64

def extended_gcd(a, b):
    """Thuật toán Euclid mở rộng để tìm nghịch đảo modulo (d) [cite: 111]"""
    if a == 0:
        return b, 0, 1
    gcd, x1, y1 = extended_gcd(b % a, a)
    x = y1 - (b // a) * x1
    y = x1
    return gcd, x, y

def mod_inverse(e, phi):
    """Tính d sao for (e * d) % phi == 1 """
    gcd, x, y = extended_gcd(e, phi)
    if gcd != 1:
        raise ValueError("Không tồn tại nghịch đảo modulo")
    return x % phi

def generate_keys(p, q, e):
    """Tạo cặp khóa PU(e, n) và PR(d, n) [cite: 104, 108, 112]"""
    n = p * q
    phi = (p - 1) * (q - 1)
    d = mod_inverse(e, phi)
    return (e, n), (d, n)

# --- Câu 1: Xác định khóa cho các bộ thông số [cite: 136, 196, 199] ---

# Bộ 1 (Thập phân)
p1, q1, e1 = 11, 17, 7
pu1, pr1 = generate_keys(p1, q1, e1)
print(f"1.1 Khóa Bộ 1: PU={pu1}, PR={pr1}")

# Bộ 2 (Số lớn)
p2 = 20079993872842322116151219
q2 = 676717145751736242170789
e2 = 17
pu2, pr2 = generate_keys(p2, q2, e2)
print(f"1.2 Khóa Bộ 2:")
print(f"n = {pr2[1]}")
print(f"d = {pr2[0]}")

# Bộ 3 (Hệ thập lục phân - Hex)
p3 = int("F7E75FDC469067FFDC4E847C51F452DF", 16)
q3 = int("E85CED54AF57E53E092113E62F436F4F", 16)
e3 = int("0D88C3", 16)
pu3, pr3 = generate_keys(p3, q3, e3)
print(f"1.3 Khóa Bộ 3:")
print(f"e = {e3}")
print(f"n = {pr3[1]}")
print(f"d = {pr3[0]}")

# --- Câu 2: Mã hóa/Giải mã với M = 5 (Bộ 1) [cite: 202] ---
M = 5
e, n = pu1
d, n = pr1

# Bảo mật (Confidentiality): Dùng PU để mã hóa, PR để giải mã [cite: 114, 117]
C_conf = pow(M, e, n)
M_dec_conf = pow(C_conf, d, n)
print(f"\n2. Bảo mật: Ciphertext={C_conf}, Decrypted={M_dec_conf}")

# Xác thực (Authentication): Dùng PR để mã hóa (ký), PU để giải mã [cite: 115, 117]
C_auth = pow(M, d, n)
M_dec_auth = pow(C_auth, e, n)
print(f"   Xác thực: Ciphertext={C_auth}, Decrypted={M_dec_auth}")

# --- Câu 3: Mã hóa chuỗi văn bản -> Base64 [cite: 204, 205] ---
msg = "The University of Information Technology"

def encrypt_string(text, pu):
    # Chuyển chuỗi sang số (đơn giản hóa bằng cách lấy giá trị byte)
    m_bytes = text.encode('utf-8')
    m_int = int.from_bytes(m_bytes, 'big')
    # Mã hóa: C = M^e mod n
    c_int = pow(m_int, pu[0], pu[1])

    # Chuyển kết quả sang Base64
    c_bytes = c_int.to_bytes((c_int.bit_length() + 7) // 8, 'big')
    return base64.b64encode(c_bytes).decode('utf-8')

# Sử dụng khóa Bộ 3 để mã hóa (vì n đủ lớn để chứa chuỗi)
cipher_base64 = encrypt_string(msg, pu3)
print(f"\n3. Bản mã Base64: {cipher_base64}")