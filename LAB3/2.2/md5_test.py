import hashlib

# Tính SHA-1 cho shattered-1.pdf
with open('shattered-1.pdf', 'rb') as f:
    hash1 = hashlib.sha1(f.read()).hexdigest()

# Tính SHA-1 cho shattered-2.pdf
with open('shattered-2.pdf', 'rb') as f:
    hash2 = hashlib.sha1(f.read()).hexdigest()

print(f'SHA-1 shattered-1.pdf: {hash1}')
print(f'SHA-1 shattered-2.pdf: {hash2}')
print(f'\nGiong nhau: {hash1 == hash2}')

if hash1 == hash2:
    print('\n✅ SHA-1 COLLISION DETECTED!')
else:
    print('\n❌ No collision')