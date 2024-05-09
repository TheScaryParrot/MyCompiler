#include <iostream>

int main(int argc, char const *argv[])
{
    bool TRUE = true;

    /*
    cmpb	$0, TRUE
	je	.L2
    */
    if (TRUE)
    {
        std::cout << "TRUE" << "\n";
    }

    /*
    cmpb	$0, TRUE
	je	.L2
    */
    if (TRUE || false)
    {
        std::cout << "TRUE" << "\n";
    }

    int counter = 0;

    while (counter < 10)
    {
        std::cout << counter << "\n";

        if (counter > 5)
        {
            continue;
        }

        counter++;
    }

    int volatile counter2 = 0;

    /*
    evaluate expression in very interesting way

    cmpl	$20, %edx
	sete	%al         ; set 1 if equal
	testb	%al, %al    ; perform AND, sets ZF if result is 0
	je	.L6             ; jump if ZF is set -> therefore if %al is 0 -> therefore if %edx is not 20
    */
    if (counter2 * 5 - (counter2 * 2) == 20)
    {
        std::cout << "IF-counter: " << counter2 << std::endl;
    }


    return 0;
}
