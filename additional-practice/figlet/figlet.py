import pyfiglet
import random
import sys

# Create an object to access the entire method, including setting fonts and rendering text
FIGLET = pyfiglet.Figlet()

AVAILABLE_FONTS = pyfiglet.FigletFont.getFonts()


def random_font(text):
    random_font = random.choice(AVAILABLE_FONTS)

    FIGLET.setFont(font=random_font)
    print(FIGLET.renderText(text))


def optional_font(text, optional_font):
    FIGLET.setFont(font=optional_font)
    print(FIGLET.renderText(text))


def main():

    # User choice: render text with a random font
    if len(sys.argv) == 1:

        text = input("Input: ")
        random_font(text)

    # User choice: render text with an optional font
    elif len(sys.argv) == 3:

        # Check if command is incorrect and guide user how to do
        if sys.argv[1] not in ["-f", "--font"]:
            sys.exit("OPTION: -f or --font")
        if sys.argv[2] not in AVAILABLE_FONTS:
            sys.exit("Font is not available")

        text = input("Input: ")
        optional_font(text, sys.argv[2])

    else:
        sys.exit("Usage: python figlet.py [OPTION + FONT]")


if __name__ == "__main__":
    main()