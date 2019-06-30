import sys
# Checks if Key argument is provided else exits
if len(sys.argv) != 2:
    print('Usage: ./caesar.py KEY')
    exit(1)
# Convert argument to int and put it in key variable
key = int(sys.argv[1])
plain = input('Plaintext: ')
# New encoded string so we can append to it
encoded = ''
for letter in plain:
    # Deals with lower case a through z
    if ord(letter) >= ord('a') and ord(letter) <= ord('z'):
        letter = chr(ord(letter) - ord('a') + key)
        if ord(letter) >= 26:
            encoded += chr(ord(letter) % 26 + 97)
        else:
            encoded += chr(ord(letter) + 97)
    # Deals with upper case A through Z
    elif ord(letter) >= ord('A') and ord(letter) <= ord('Z'):
        letter = chr(ord(letter) - ord('A') + key)
        if ord(letter) >= 26:
            encoded += chr(ord(letter) % 26 + 65)
        else:
            encoded += chr(ord(letter) + 65)
    # Deals with other caracters
    else:
        encoded += letter
print('ciphertext: ' + encoded)
exit(0)