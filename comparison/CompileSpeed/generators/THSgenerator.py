PREAMBLE = """
int mod(int a, int b)
{
    int localA = a;
    int localB = b;

    while (localA >= localB)
    {
        localA -= localB;
    }

    return localA;
}

extern void _print(int length, int value);

void printDigit(int n)
{
    n += 48;
    _print(4, n);
}

void printInt(int n)
{
    int digit = mod(n, 10);
    n = (n - digit) / 10;

    if (n > 0)
    {
        printInt(n);
    }

    printDigit(digit);
}
"""

FUNCTIONBODY = """ {
    if (n <= 1)
    {
        return;
    }
    else
    {
        for (int i = 2; i * i <= n; i += 1;)
        {
            if (mod(n, i) == 0)
            {

                return;
            }
        }

        printInt(n);
        _print(4, 10);
    }
}
"""


def GenFunction(i: int, file):
    file.write('void Func' + str(i) + '(int n)' + FUNCTIONBODY)


with open('CompileSpeed.ths', 'w') as file:
    file.write(PREAMBLE)

    for i in range(10000):
        GenFunction(i, file)

    file.write("""
global _start;
int _start()
{
""")

    for i in range(10000):
        file.write('Func' + str(i) + '(' + str(i) + '); \n')

    file.write('}\n')
