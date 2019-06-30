from cs50 import get_int
while True:
    num = get_int('Height:')
    if (num >= 0 and num <= 23):
        break
x = 1
while (x <= num):
    print(' ' * (num - x), end='')
    print('#' * x, end='')
    print('  ', end='')
    print('#' * x, end='')
    print()
    x += 1