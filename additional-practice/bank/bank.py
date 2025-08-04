while True:
    # Get a greeting
    greeting = input("Greeting: ").lower()

    # Remove the leading whitespaces
    for i in range(len(greeting)):
        if not greeting[i].isspace():
            greeting = greeting[i:]
            break

    # Successfully getting a non-empty greeting
    if len(greeting) > 0:
        break

if greeting[0:5] == "hello":
    print("$0")
elif greeting[0] == "h":
    print("$20")
else:
    print("$100")
