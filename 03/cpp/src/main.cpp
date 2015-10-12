#include <iostream>
#include <string>
#include <memory>

#include "stack.h"


/**
*  Testovaci struktura, ketou ulozime 
*  do naseho stacku...
*/
struct user
{
    std::string firstName; 
    std::string lastName;
    unsigned int age;

    user()
    {
        age = 0;
    };

    user(const std::string& fN, 
         const std::string& lN, 
         const unsigned int& age_)
    {
        firstName = fN;
        lastName  = lN;
        age       = age_;
    }

    /**
    *  Kvuli kopirovani dat musime vytvorit pretizeny operaotor =
    */
    void operator=(const user& usr)
    {
        firstName = usr.firstName;
        lastName  = usr.lastName;
        age       = usr.age;
    }
};


/**
*  Testovaci funkce 1
*  Vytvorime si stack pro ukladani integeru
*/
void testStack1()
{
    printf("Test 1\n");
    Stack<int> stack;
        
    stack.push(10);
    stack.push(11);
    stack.push(12);
    stack.push(13);
    
    printf("%d \n", stack.pop());
    printf("%d \n", stack.pop());
    printf("%d \n", stack.pop());
    printf("-------------------\n");
}

/**
*  Tesovaci funkce 2
*  V tomto pripade si vyzkousime co se stane kdyz se budeme 
*  snazit volat pop() vickrat nez je ulozenych dat ve stacku
*/
void testStack2()
{
    try
    {
        std::cout << "Test 2" << std::endl;

        Stack<std::string> stack;

        stack.push("Ahoj");
        stack.push("Nazdar");
        stack.push("Cau");

        std::cout << stack.pop() << std::endl;
        std::cout << stack.pop() << std::endl;
        std::cout << stack.pop() << std::endl;
        std::cout << stack.pop() << std::endl; // here will be dragons

    }
    catch (std::exception const & e)
    {
        std::cout << e.what() << std::endl;
    }
    printf("-------------------\n");
}

/**
*  Tesovaci funkce 3
*  V tomto pripade si ukazeme jak ulozit do Stacku struct
*/
void testStack3()
{
    try
    {
        std::cout << "Test 3" << std::endl;

        Stack<user> stack;

        stack.push(user("Sterling", "Archer", 36));
        stack.push(user("Pam", "Poovey", 32));
        stack.push(user("Cheryl", "Tunt", 28));
        stack.push(user("Lana", "Kane", 33));
        stack.push(user("Malory", "Archer", 58));

        while(stack.size())
        {
            auto usr = stack.pop();
            std::cout << "First name: " << usr.firstName << std::endl;
            std::cout << "Last name : " << usr.lastName << std::endl;
            std::cout << "Age       : " << usr.age << std::endl;
        }

    }
    catch (std::exception const & e)
    {
        std::cout << e.what() << std::endl;
    }

    printf("-------------------\n");
}

/**
*  Tesovaci funkce 4
*  V tomto pripade si ukazeme metodu top(), ktera vraci referenci na prvek
*  ktery je na vrcholu stacku (tj. je posledni, Last in - First out)
*/
void testStack4()
{
    printf("Test 4\n");
    Stack<int> stack;

    stack.push(10);
    stack.push(11);
    stack.push(12);
    stack.push(13);

    auto& tmp = stack.top();
    tmp += 5;

    std::cout << stack.pop() << std::endl;

    printf("-------------------\n");
}

int main(int argc, char *argv[])
{

    testStack1();
    testStack2();
    testStack3();
    testStack4();
    
    return 0;
}