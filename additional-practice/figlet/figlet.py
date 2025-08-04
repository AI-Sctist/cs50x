import pyfiglet
import random
import sys

# Initialize figlet object
figlet = pyfiglet.Figlet()

# Get available fonts
available_font = pyfiglet.FigletFont.getFonts()


def main():
    if len(sys.argv) == 1:
        text = input("Text: ")
        random_choice(text)
    elif error():
        print("Invalid usage")
        sys.exit(1)
    else:
        text = input("Text: ")
        optional_choice(text)


def random_choice(text):
    # Set a random font
    random_font = random.choice(available_font)
    figlet.setFont(font=random_font)

    # Display
    print(figlet.renderText(text))


def error():
    if len(sys.argv) != 3:
        return True

    if sys.argv[1] not in ["-f", "--font"]:
        return True

    try:
        figlet.setFont(font=sys.argv[2])
    except pyfiglet.FontNotFound:
        return True

    return False


def optional_choice(text):
    print(figlet.renderText(text))


if __name__ == "__main__":
    main()
