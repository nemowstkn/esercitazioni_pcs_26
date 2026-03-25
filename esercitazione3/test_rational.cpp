#include <iostream>
#include "rational.hpp"

int main(void) 
{
    int n1, d1, n2, d2;
    char operation;

    std::cout << "Prima frazione (numeratore e denominatore separati da spazio): ";
    std::cin >> n1 >> d1;
    rational<int> r1(n1, d1);

    std::cout << "Operazione (+, -, *, /): ";
    std::cin >> operation;

    std::cout << "Seconda frazione (numeratore e denominatore): ";
    std::cin >> n2 >> d2;
    rational<int> r2(n2, d2);

    rational<int> result;

    bool valid_operation = true;

    switch (operation) {
        case '+':
            result = r1 + r2;
            break;
        case '-':
            result = r1 - r2;
            break;
        case '*':
            result = r1 * r2;
            break;
        case '/':
            result = r1 / r2;
            break;
        default:
            std::cout << "Operatore non riconosciuto.\n";
            valid_operation = false;
            break;
    }
    
    if (valid_operation) {
        std::cout << "Risultato: " << result << "\n";
    }

    return 0;
}