# find all permutations of all subsets
def generate(letters, current = ""):
    if not letters:
        print(current)
    else:
        print(current)
        for i in range(0, len(letters)):
            nextchar = str(current) + letters[i]
            remaining = letters[0:i] + letters[i + 1:]
            generate(remaining, nextchar)
