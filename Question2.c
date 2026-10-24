
#include <stdio.h>

// Returns the sum of all proper divisors of a number
int sumProperDivisors(int num)
{
    int sum = 0;

    for (int i = 1; i <= num / 2; i++)
    {
        if (num % i == 0)
        {
            sum += i;
        }
    }

    return sum;
}

int main()
{
    int n;
    int count = 0;

    printf("Enter a number: ");
    scanf("%d", &n);

    printf("Amicable pairs up to %d:\n", n);

    for (int a = 2; a <= n; a++)
    {
        int b = sumProperDivisors(a);

        // Both numbers must be within the limit
        // The numbers must be different
        // The smaller number must come first
        if (b > a && b <= n)
        {
            if (sumProperDivisors(b) == a)
            {
                printf("(%d, %d)\n", a, b);
                count++;
            }
        }
    }

    if (count == 0)
    {
        printf("No amicable pairs found.\n");
    }

    printf("Total pairs: %d\n", count);

    return 0;
}
