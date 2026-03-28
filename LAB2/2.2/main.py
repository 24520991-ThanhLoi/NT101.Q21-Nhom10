from Crypto.Cipher import AES

# Khởi tạo khóa, IV và dữ liệu (theo đúng đề bài Lab)
key = b'1234567890123456'                        # Khóa 16 bytes
iv = b'abcdefghijklmnop'                         # Vector khởi tạo 16 bytes (dùng cho CBC, CFB, OFB)
plaintext = b"UIT_LAB_UIT_LAB_UIT_LAB_UIT_LAB_"  # 32 bytes (2 khối 16-byte giống hệt nhau)

# Hàm hỗ trợ in chuỗi hex thành từng khối 16-byte (32 ký tự hex) để dễ so sánh
def print_blocks(cipher_text):
    hex_str = cipher_text.hex()
    return f"{hex_str[:32]} | {hex_str[32:]}"

print("Ban ro chia lam 2 khoi: UIT_LAB_UIT_LAB_ | UIT_LAB_UIT_LAB_")
print("-" * 65)

# 1. AES-ECB (Không cần IV)
cipher_ecb = AES.new(key, AES.MODE_ECB)
ct_ecb = cipher_ecb.encrypt(plaintext)
print(f"ECB: {print_blocks(ct_ecb)}")

# 2. AES-CBC (Cần IV)
cipher_cbc = AES.new(key, AES.MODE_CBC, iv)
ct_cbc = cipher_cbc.encrypt(plaintext)
print(f"CBC: {print_blocks(ct_cbc)}")

# 3. AES-CFB (Cần IV, đặt segment_size=128 để xử lý theo khối 16-byte)
cipher_cfb = AES.new(key, AES.MODE_CFB, iv=iv, segment_size=128)
ct_cfb = cipher_cfb.encrypt(plaintext)
print(f"CFB: {print_blocks(ct_cfb)}")

# 4. AES-OFB (Cần IV)
cipher_ofb = AES.new(key, AES.MODE_OFB, iv=iv)
ct_ofb = cipher_ofb.encrypt(plaintext)
print(f"OFB: {print_blocks(ct_ofb)}")

# 5. AES-CTR (Cần Nonce/Counter, pycryptodome tự tạo counter từ nonce)
cipher_ctr = AES.new(key, AES.MODE_CTR, nonce=b'12345678')
ct_ctr = cipher_ctr.encrypt(plaintext)
print(f"CTR: {print_blocks(ct_ctr)}")