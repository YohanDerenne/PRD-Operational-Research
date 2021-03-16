// PRD.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Instance.h"

/// <summary>
/// Point d'entrée du programme
/// </summary>
/// <returns></returns>
int main()
{
    std::cout << "Hello World!\n";
    Instance i = Instance();
    try {        
        i.Parse("ne");        
    }
    catch (exception e) {
        std::cout << e.what();
    }
    
}