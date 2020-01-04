#include <iostream>

int main(int argc, char **argv)
{
    std::cout << "argument count : " << argc << std::endl;

    for (int index = 0; index < argc; index++)
    {
        std::cout << "argument " << index << " : " << argv[index] << std::endl;
    }

    return 0;
}