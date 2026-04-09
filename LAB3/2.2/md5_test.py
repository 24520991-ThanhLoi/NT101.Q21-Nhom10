import hashlib

# Chuỗi hex của Message 1 
msg1_hex = "d131dd02c5e6eec4693d9a0698aff95c2fcab58712467eab4004583eb8fb7f8955ad340609f4b30283e488832571415a085125e8f7cdc99fd91dbdf280373c5bd8823e3156348f5bae6dacd436c919c6dd53e2b487da03fd02396306d248cda0e99f33420f577ee8ce54b67080a80d1ec69821bcb6a8839396f9652b6ff72a70"

# Chuỗi hex của Message 2 
msg2_hex = "d131dd02c5e6eec4693d9a0698aff95c2fcab50712467eab4004583eb8fb7f8955ad340609f4b30283e4888325f1415a085125e8f7cdc99fd91dbd7280373c5bd8823e3156348f5bae6dacd436c919c6dd53e23487da03fd02396306d248cda0e99f33420f577ee8ce54b67080280d1ec69821bcb6a8839396f965ab6ff72a70"

# Chuyển HEX sang dữ liệu byte
msg1_bytes = bytes.fromhex(msg1_hex)
msg2_bytes = bytes.fromhex(msg2_hex)

# Tính và in ra mã băm MD5
print("MD5 Message 1:", hashlib.md5(msg1_bytes).hexdigest())
print("MD5 Message 2:", hashlib.md5(msg2_bytes).hexdigest())