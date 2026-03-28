from Crypto.Cipher import AES
from Crypto.Util.Padding import pad

# Hàm hỗ trợ phân tích sự khác biệt giữa bản rõ gốc và bản rõ sau giải mã
def analyze_corruption(original, decrypted, mode_name):
    print(f"\n=== CHẾ ĐỘ {mode_name} ===")
    corrupted_blocks = []
    
    # Chia dữ liệu thành các khối 16 byte để kiểm tra
    for i in range(0, len(original), 16):
        block_orig = original[i:i+16]
        block_dec = decrypted[i:i+16]
        
        if block_orig != block_dec:
            block_num = (i // 16) + 1 # Số thứ tự khối (bắt đầu từ 1)
            
            # Đếm số byte bị hỏng trong khối này
            diff_bytes = sum(1 for a, b in zip(block_orig, block_dec) if a != b)
            
            corrupted_blocks.append(block_num)
            print(f" -> Khối {block_num} (byte {i} đến {i+15}): Hỏng {diff_bytes}/16 bytes.")
            
    if not corrupted_blocks:
        print(" -> Không có khối nào bị hỏng.")

def error_propagation_test():
    key = b'1234567890123456'
    iv = b'abcdefghijklmnop'
    
    # 1. Tạo dữ liệu 1000 byte (Dùng ký tự 'A')
    # Vì ECB và CBC yêu cầu dữ liệu là bội số của 16, ta dùng hàm pad để đệm lên 1008 bytes
    plaintext = b'A' * 1000
    padded_pt = pad(plaintext, AES.block_size)
    
    modes = [
        ('ECB', AES.MODE_ECB),
        ('CBC', AES.MODE_CBC),
        ('CFB', AES.MODE_CFB),
        ('OFB', AES.MODE_OFB)
    ]
    
    for mode_name, mode_val in modes:
        # 2. Mã hóa
        if mode_val == AES.MODE_ECB:
            cipher = AES.new(key, mode_val)
        elif mode_val == AES.MODE_CFB:
            # Set segment_size=128 để CFB hoạt động theo khối 16 byte chuẩn
            cipher = AES.new(key, mode_val, iv, segment_size=128)
        else:
            cipher = AES.new(key, mode_val, iv)
            
        ciphertext = bytearray(cipher.encrypt(padded_pt))
        
        # 3. Làm hỏng bản mã: Đảo 1 bit tại byte thứ 26 (index 25)
        # Khối 1: index 0-15 | Khối 2: index 16-31. Vậy byte 26 nằm ở Khối 2.
        ciphertext[25] ^= 0x01 # Toán tử XOR với 1 để đảo bit
        
        # 4. Giải mã bản mã đã bị lỗi
        if mode_val == AES.MODE_ECB:
            decipher = AES.new(key, mode_val)
        elif mode_val == AES.MODE_CFB:
            decipher = AES.new(key, mode_val, iv, segment_size=128)
        else:
            decipher = AES.new(key, mode_val, iv)
            
        decrypted_pt = decipher.decrypt(bytes(ciphertext))
        
        # Quan sát lỗi lan truyền
        analyze_corruption(padded_pt, decrypted_pt, mode_name)

# Chạy thử nghiệm
error_propagation_test()