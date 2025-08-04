from cs50 import get_string


def main():
    # Get user's card number
    card_number = get_string("Number: ")

    # Handle a valid case
    if invalid_card(card_number):
        print("INVALID")
        return

    # Display card type
    if is_amex(card_number):
        print("AMEX")
    elif is_mastercard(card_number):
        print("MASTERCARD")
    elif is_visa(card_number):
        print("VISA")
    else:
        print("INVALID")


# Check the validity of the card by Luhn algorithm
def invalid_card(card):
    sum = 0

    i = len(card) - 2
    while i >= 0:
        sum += int(card[i]) * 2 % 10 + int(card[i]) * 2 // 10
        i -= 2

    i = len(card) - 1
    while i >= 0:
        sum += int(card[i])
        i -= 2

    return sum % 10 != 0


def is_amex(card):
    return len(card) == 15 and card[0:2] in ["34", "37"]


def is_mastercard(card):
    return len(card) == 16 and card[0:2] in ["51", "52", "53", "54", "55"]


def is_visa(card):
    return len(card) in [13, 16] and card[0] == "4"


if __name__ == "__main__":
    main()
