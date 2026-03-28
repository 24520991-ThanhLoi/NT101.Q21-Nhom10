from Crypto.Cipher import DES

# Hàm tính khoảng cách Hamming (số lượng bit khác nhau giữa 2 chuỗi bytes)
def count_differing_bits(b1, b2):
    # Chuyển bytes sang số nguyên (integer)
    int1 = int.from_bytes(b1, 'big')
    int2 = int.from_bytes(b2, 'big')
    
    # Thực hiện phép XOR: Các bit khác nhau sẽ cho ra kết quả là 1
    xor_result = int1 ^ int2
    
    # Chuyển kết quả sang chuỗi nhị phân và đếm số ký tự '1'
    return bin(xor_result).count('1')

def avalanche_test(key):
    p1 = b'STAYHOME'
    p2 = b'STAYHOMA' # Khác chữ 'E' (0x45) và 'A' (0x41) -> Khác nhau đúng 1 bit
    
    # 1. Khởi tạo đối tượng mã hóa DES (Chế độ ECB)
    cipher = DES.new(key, DES.MODE_ECB)
    
    # 2. Thực hiện mã hóa 2 bản rõ
    c1 = cipher.encrypt(p1)
    c2 = cipher.encrypt(p2)
    
    # 3. Đếm số bit khác nhau (Hamming Distance)
    diff_bits = count_differing_bits(c1, c2)
    total_bits = 64 # Kích thước 1 khối của DES là 64 bits (8 bytes)
    
    # 4. Tính tỷ lệ % bit bị thay đổi
    percent = (diff_bits / total_bits) * 100
    
    # In kết quả
    print(f"Key sử dụng    : {key.decode('utf-8')}")
    print(f"Bản mã 1 (hex) : {c1.hex()}")
    print(f"Bản mã 2 (hex) : {c2.hex()}")
    print(f"Số bit khác biệt: {diff_bits} / {total_bits} bits")
    print(f"Tỷ lệ thay đổi : {percent:.2f}%\n")

print("=== KIỂM TRA HIỆU ỨNG THÁC ĐỔ (AVALANCHE EFFECT) ===")

print("--- 1. Thử nghiệm với Key mặc định ---")
avalanche_test(b'87654321')

print("--- 2. Thử nghiệm với Key là MSSV 1 ---") #Nguyen Thanh Loi
avalanche_test(b'24520991') 

print("--- 3. Thử nghiệm với Key là MSSV 2 (Ví dụ) ---") #Phan Gia Bao
avalanche_test(b'23520135') 