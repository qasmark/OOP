n = int(input('Enter a max count of fns: '))


with open('tests.txt', 'w') as f:
    lst = [f'fn fib{i+2} = fib{i+1} + fib{i}' for i in range(n)]
    for j in range(len(lst)):
        f.write(lst[j] + '\n')

f.close()
