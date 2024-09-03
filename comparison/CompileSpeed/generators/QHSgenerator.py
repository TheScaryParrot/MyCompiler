PREAMBLE = """
#enterOrderQueue "../qhsLib/lib.qhs" #exitOrderQueue #include 

int mod ( int a , int b )
{
    int localA = a ;
    int localB = b ;

    [ "4" ]
    while ( localA >= localB )
    {
        [ localA ] -= localB ;
    }

    return = localA ;
}

void printDigit ( int n )
{
    [ n ] += "48" ;
    [ n ?! int.size ] print ;

    return ;
}

void printInt ( int n )
{
    mod ( n , "10" ) ;
    int digit = "eax" ;

    [ n ] -= digit ;
    [ n ] /= "10" ;

    [ "4" ]
    if ( n > "0" )
    {
        printInt ( n ) ;
    }

    printDigit ( digit ) ;

    return ;
}
"""

FUNCTIONBODY = """ {
    [ "4" ]
    if ( n <= "1" )
    {
        return ;
    }
    [ "4" ]
    else
    {
        int i = "2" ;

        [ "4" ]
        while ( i * i <= n )
        {
            mod ( n , i ) ;
            [ "4" ]
            if ( "eax" == "0" )
            {
                return ;
            }

            [ i ] += "1" ;
        }

        printInt ( n ) ;
        [ "10" "4" ] print ;
    }
}
"""


def GenFunction(i: int, file):
    file.write('void Func' + str(i) + ' ( int n ) ' + FUNCTIONBODY)


with open('CompileSpeed.qhs', 'w') as file:
    file.write(PREAMBLE)

    for i in range(10000):
        GenFunction(i, file)

    file.write("""
start
{
""")

    for i in range(10000):
        file.write('Func' + str(i) + ' ( "' + str(i) + '" ) ; \n')

    file.write('}\n')
