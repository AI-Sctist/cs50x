from cs50 import get_int

# Keep prompting the user until we get a height between 1 to 8
while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

# Build a pyramid with the given height
for i in range(0, height):
    print(" " * (height - i - 1), end="")
    print("#" * (i + 1))
