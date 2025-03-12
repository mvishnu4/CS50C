# TODO
Height = int(input("Height:"))
while (Height < 1):
    Height = int(input("Height:"))
while (Height > 8):
    Height = int(input("Height:"))
for i in range(Height):
    print(" " * (Height - i - 1), end = "")
    print("#" * (i + 1), end = "")
    print("  ", end = "")
    print("#" * (i + 1), end = "\n")