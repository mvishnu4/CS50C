# TODO
n = input("Number: ")
i = len(n) - 1
sum = 0
while ( i > -1):
    sum += int(n[i])
    if (int(n[i - 1]) < 5):
        sum += (2* int(n[i - 1]))
    else:
        sum += ((2 * (int(n[i - 1]) - 5)) + 1)
    i -= 2

def m(n):
    if (n < 6):
        return True
    else:
        return False
def a(n):
    if (n == 4):
        return True
    elif (n == 7):
        return True
    else:
        return False

l = len(n)
if ((sum % 10 == 0)):
    if (l == 13):
        if (int(n[0]) == 4):
            print("VISA\n")
        else:
            print("INVALID\n")
    elif (l == 15):
        if (int(n[0]) == 3):
            if (a(int(n[1]))):
                print("AMEX\n")
            else:
                print("INVALID\n")
        else:
            print("INVALID\n")
    elif (l == 16):
        if (int(n[0]) == 5):
            if(m(int(n[i]))):
                print("MASTERCARD\n")
            else:
                print("INVALID\n")
        elif (int(n[0]) == 4):
            print("VISA\n")
        else:
            print("INVALID\n")
    else:
        print("INVALID\n")
else:
    print("INVALID\n")
