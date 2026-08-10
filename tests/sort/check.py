SLUGS = ["arr", "sll", "dll"]
STARTING_TESTS = [12, 162, 312]
LAST_TESTS = [161, 311, 461]

for i in range(len(SLUGS)):
    for j in range(STARTING_TESTS[i], LAST_TESTS[i] + 1):
        input_lines = []
        output_lines = []
        with open(f"input/{j:03d}_{SLUGS[i]}_mergesort.txt", "r", encoding="utf-8") as file:
            input_lines = file.readlines()
        with open(f"output/{j:03d}_{SLUGS[i]}_mergesort.txt", "r", encoding="utf-8") as file:
            output_lines = file.readlines()

        input_arr = []
        for c in range(2, len(input_lines) - 1):
            input_arr.append(int(input_lines[c].strip()))

        input_arr.sort()

        output_arr = []
        match SLUGS[i]:
            case "arr":
                output_arr = output_lines[-2][10:-2].split(", ")

            case "sll":
                output_arr = output_lines[-2][9:-4].split("]->[")

            case "dll":
                output_arr = output_lines[-3][19:-4].split("]-[")
                reverse_output_arr = output_lines[-2][19:-4].split("]-[")

        for c in range(len(output_arr)):
            output_arr[c] = int(output_arr[c])
            if (SLUGS[i] == "dll"):
                reverse_output_arr[c] = int(reverse_output_arr[c])

        condition = False
        if (SLUGS[i] != "dll"):
            condition = (input_arr == output_arr)
        else:
            condition = (input_arr == output_arr) and (sorted(input_arr, reverse=True) == reverse_output_arr)

        if (condition):
            print(f"\033[1;32mPASSED\033[0m: {j:03d}")
        else:
            print(f"\033[1;31mFAILED\033[0m: {j:03d}")
