// This is deliberately written in a way that uses as many different features as possible

#include <stdio.h>
#include <stdbool.h>

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

bool isPrime(int n)
{
    bool result;

    if (n <= 1)
    {
        result = false;
        return result;
    }
    else
    {
        for (int i = 2; i * i <= n; i++)
        {
            if (mod(n, i) == 0)
            {
                result = false;
                return result;
            }
        }

        result = true;
        return result;
    }
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

void main(int argc, char *argv[])
{
    int checkUntil = 100000;

    for (int i = 0; i < checkUntil; i++)
    {
        if (isPrime(i))
        {
            printInt(i);
            putchar('\n');
        }
    }
}