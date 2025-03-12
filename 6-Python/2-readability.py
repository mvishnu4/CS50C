# TODO
from math import ceil
txt = input("Text: ")

l = 0
w = 1
s = 0

for i in range(len(txt)):
    if (txt[i].isalpha()):
        l += 1
    elif (str(txt[i]) == "." or str(txt[i]) == "?" or text[i] == "!"):
        s += 1
    elif (txt[i].isspace()):
        w += 1
print(f"{l} {w} {s}")
L = (l * 100) / w
S = (s * 100) / w

index = int(ceil(0.0588 * L - 0.296 * S - 15.8))

if (index < 1):
    print("Before Grade 1")
elif (index > 16):
    print("Grade 16+")
else:
    print(f"Grade {index}")
