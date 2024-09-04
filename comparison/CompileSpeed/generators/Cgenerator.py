import sys

PREAMBLE = """
# include <stdbool.h>
# include <stdio.h>

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

void printDigit(char n)
{
    n += 48;
    putchar(n);
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
        for (int i = 2; i * i <= n; i++)
        {
            if (mod(n, i) == 0)
            {

                return;
            }
        }

        printInt(n);
        putchar('\\n');
    }
}
"""


def GenFunction(i: int, file):
    file.write('void Func' + str(i) + '(int n)' + FUNCTIONBODY)


with open('tmp/CompileSpeed.c', 'w') as file:
    file.write(PREAMBLE)

    num = int(sys.argv[1])

    for i in range(num):
        GenFunction(i, file)

    file.write("""
int main(int argc, char * argv[])
{
""")

    for i in range(num):
        file.write('Func' + str(i) + '(' + str(i) + '); \n')

    file.write('return 0;\n}\n')
