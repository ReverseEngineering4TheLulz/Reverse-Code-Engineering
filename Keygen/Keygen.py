numbers = []

for i in range(0,9):
    if i % 2 == 0:
        numbers.append(i)

print("Valid key values: ", numbers)
input("Press enter to generate the keys")

for i in range(len(numbers)):
    for j in range(len(numbers)):
        for k in range(len(numbers)):
            print(f"{numbers[i]}{numbers[j]}{numbers[k]}")
