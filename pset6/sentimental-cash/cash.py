from cs50 import get_float

# Keep prompting user until we get a non-negative number
while True:
    dollars = get_float("Change: ")
    if dollars >= 0:
        break

# Convert from dollar to cent
cents = int(dollars * 100)

# The minimum coins needed
coins = 0

# Take coins from the largest to the smallest
for value in [25, 10, 5, 1]:
    while cents >= value:
        coins += 1
        cents -= value

# Given the money back
print(coins)
