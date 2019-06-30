# Function that checks the card
def check_card(number):
    # Holds the sum of numbers
    soma = 0
    # Holds the number of digits
    count = len(number)
    # Reverse the number so we can work with it
    number = number[::-1]
    # iterates through number string converting digit to integer and working with it
    for index, digit in enumerate(number):
        digit = int(digit)
        if ((index + 1) % 2 == 0):
            digit *= 2
            if digit > 9:
                digit -= 9
        soma += digit
    if soma % 10 == 0:
        return 1
    else:
        return 0
# Main


def main():
    number = input('Number: ')
    length = len(number)
    # Gets 2 first digits and converts to int
    company = int(number[0:2:])
    if (check_card(number) == 1 and length > 13):
        if (company > 50 and company < 56 and length == 16):
            print('MASTERCARD')
        elif (company == 34 or company == 37 and length == 15):
            print('AMEX')
        elif (company / 10 == 4 and length == 13 or length == 16 or length == 19):
            print('VISA')
    else:
        print('INVALID')


if __name__ == "__main__":
    main()