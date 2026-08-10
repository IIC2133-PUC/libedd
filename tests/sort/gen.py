import random

START_TEST = 12
START_SIZE = 3
END_SIZE = 12
TEST_COUNT = 15
SLUGS = ["arr", "sll", "dll"]

curr = START_TEST
for slug in SLUGS:
    for i in range(START_SIZE, END_SIZE + 1):
        for j in range(TEST_COUNT):
            arr = list()
            for c in range(i):
                arr.append(random.randint(-200, 200))

            with open(f"input/{curr:03d}_{slug}_mergesort.txt", "w", encoding="utf-8") as file:
                file.write(f"{i + 2}\n")
                file.write(f"{slug}\n")
                for elem in arr:
                    file.write(f"{elem}\n")
                file.write(f"{slug.upper()}_MERGESORT\n")

            curr += 1
