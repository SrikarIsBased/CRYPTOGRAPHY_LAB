def main():
    print("===== ARITHMETIC OPERATIONS IN PYTHON =====")
    t = int(input("Enter number of test cases: "))

    for i in range(1, t + 1):
        print(f"\nTest Case {i}")
        a = int(input("Enter first number a: "))
        b = int(input("Enter second number b: "))

        print(f"Addition       : {a} + {b} = {a + b}")
        print(f"Subtraction    : {a} - {b} = {a - b}")
        print(f"Multiplication : {a} * {b} = {a * b}")
        if b == 0:
            print("Division       : Not possible (division by zero)")
            print("Modulus        : Not possible (division by zero)")
        else:
            print(f"Division       : {a} / {b} = {a / b:.4f}")
            r = abs(a) % abs(b)
            if a < 0:
                r = -r
            print(f"Modulus        : {a} % {b} = {r}")


main()
