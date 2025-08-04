from cs50 import get_string

text = get_string("Text: ")
text += " "

letter_count = 0
word_count = 0
sentence_count = 0

for i in range(0, len(text)):
    if text[i].isalpha():
        letter_count += 1
    elif text[i] in [".", "?", "!"]:
        sentence_count += 1
    elif text[i] == " ":
        word_count += 1

# Use Coleman Liau index to compute readability
L = letter_count / word_count * 100
S = sentence_count / word_count * 100
index = int(round(0.0588 * L - 0.296 * S - 15.8))

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
