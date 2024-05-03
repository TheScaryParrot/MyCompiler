class MY_CLASS
{
public:
    int PUBLIC;
    int PUBLIC_FUNC() { return 0; }

protected:
    int PROTECTED;
    int PROTECTED_FUNC() { return 0; }

private:
    int PRIVATE;
    int PRIVATE_FUNC() { return 0; }
};


int INT = 10;
MY_CLASS OBJECT_NONE;
MY_CLASS OBJECT_STACK = MY_CLASS();
MY_CLASS* OBJECT_HEAP = new MY_CLASS();

int main(int argc, char const *argv[])
{
    INT = 15;

    int LOCAL = 20;

    MY_CLASS LOCAL_OBJECT_NONE = OBJECT_NONE;

    LOCAL_OBJECT_NONE.PUBLIC_FUNC();

    int LOCAL_PUBLIC = LOCAL_OBJECT_NONE.PUBLIC;

    MY_CLASS LOCAL_OBJECT_STACK = OBJECT_STACK;
    MY_CLASS* LOCAL_OBJECT_HEAP = OBJECT_HEAP;

    return INT;
}
