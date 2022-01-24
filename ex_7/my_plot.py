def plot(title, file_name):
    print(title)
    with open(file_name) as file:
        for line in file:
            print(line, end='')
