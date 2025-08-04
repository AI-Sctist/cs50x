from cs50 import get_int

# Keep prompting user's input until we get a height between 1 to 8
while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

# Build a pyramid with the given height
for i in range(0, height):
    # The first half
    print(" " * (height - i - 1), end="")
    print("#" * (i + 1), end="")

    # The middle spaces
    print(" " * 2, end="")

    # The second half
    print("#" * (i + 1), end="\n")
