#include "CircularHexagonList.hpp"
#include <iostream>

CircularHexagonList::CircularHexagonList()
{
    head = 0;
    hexagonCount = 0;
}

CircularHexagonList::~CircularHexagonList()
{
    if (head == 0) return;
    
    Hexagon* current = head;
    for (int i = 0; i < hexagonCount; i++)
    {
        Hexagon* next = current->getNext();
        delete current;
        current = next;
    }
    
    head = 0;
    hexagonCount = 0;
}

Hexagon* CircularHexagonList::createAndAppendHexagon()
{
    Hexagon* newHex = new Hexagon();

    if (head == 0)
    {
        head = newHex;
        head->setNext(head);
    }
    else
    {
        Hexagon* current = head;
        while (current->getNext() != head)
        {
            current = current->getNext();
        }
        current->setNext(newHex);
        newHex->setNext(head);
    }

    hexagonCount++;
    return newHex;
}

Hexagon* CircularHexagonList::getHead() const { return head; }
int CircularHexagonList::getHexagonCount() const { return hexagonCount; }
Hexagon* CircularHexagonList::getRightNeighbor(Hexagon* current) const { return (current == 0) ? 0 : current->getNext(); }

void CircularHexagonList::processTurn(int turnNumber)
{
    if (head == 0) return;

    int totalHex = hexagonCount;
    int** dataBuffers = new int*[totalHex];
    int* dataCounts = new int[totalHex];

    for(int i=0; i<totalHex; i++) {
        dataBuffers[i] = 0;
        dataCounts[i] = 0;
    }

    Hexagon* current = head;
    bool isOddTurn = (turnNumber % 2 != 0);

    for (int i = 0; i < totalHex; i++)
    {
        BinarySearchTree* removedTree = 0;
        if (isOddTurn) removedTree = current->popNormalTree();
        else           removedTree = current->popPriorityTree();

        if (removedTree != 0)
        {
            int count = removedTree->getNodeCount();
            if (count > 0)
            {
                dataBuffers[i] = new int[count];
                int outCount = 0;
                removedTree->extractAllPostOrder(dataBuffers[i], count, outCount);
                dataCounts[i] = outCount;
            }
            delete removedTree; 
        }
        current = current->getNext();
    }

    current = head;
    for (int i = 0; i < totalHex; i++)
    {
        Hexagon* targetHex = current->getNext();
        if (dataBuffers[i] != 0 && dataCounts[i] > 0)
        {
            targetHex->distributeValues(dataBuffers[i], dataCounts[i]);
            delete[] dataBuffers[i];
        }
        current = current->getNext();
    }

    delete[] dataBuffers;
    delete[] dataCounts;
}

int CircularHexagonList::findGlobalMaxHeightRootValue() const
{
    if (head == 0) return 1;
    int maxHeight = 0;
    int rootValueOfMax = 1;
    Hexagon* current = head;
    for (int i = 0; i < hexagonCount; i++)
    {
        for (int t = 0; t < current->getTreeCount(); t++)
        {
            BinarySearchTree* tree = current->getTreeAt(t);
            if (tree != 0 && !tree->isEmpty())
            {
                int h = tree->getHeight();
                if (h > maxHeight)
                {
                    maxHeight = h;
                    rootValueOfMax = tree->getRootValue();
                }
            }
        }
        current = current->getNext();
    }
    if (maxHeight == 0) return 1;
    return rootValueOfMax;
}

void CircularHexagonList::printWindowAsSnake(Hexagon* windowStart) const
{
    if (windowStart == 0)
    {
        std::cout << "Gosterilecek altigen yok." << std::endl;
        return;
    }

    int windowSize = (hexagonCount < 18) ? hexagonCount : 18;
    int values[18];
    // -1 boşluğu temsil eder
    for (int i = 0; i < 18; i++) values[i] = -1;

    Hexagon* current = windowStart;

    for (int i = 0; i < windowSize; i++)
    {
        if (current->isEmpty()) values[i] = -2; // Özel kod: -2 = Var ama boş (^# basılacak)
        else                    values[i] = current->calculateSpecialDisplayValue();
        
        current = current->getNext();
    }

    std::cout << "Altigen sayisi: " << hexagonCount << std::endl;

    // --- 1. Satır (0..5) ---
    for (int i = 0; i < 6; i++) {
        if (values[i] == -2)      std::cout << "^#\t";
        else if (values[i] != -1) std::cout << values[i] << "\t";
        else                      std::cout << " \t"; // Hiç altıgen yok
    }
    std::cout << std::endl;

    // --- 2. Satır (11..6) TERS ---
    for (int i = 11; i >= 6; i--) {
        if (values[i] == -2)      std::cout << "^#\t";
        else if (values[i] != -1) std::cout << values[i] << "\t";
        else                      std::cout << " \t";
    }
    std::cout << std::endl;

    // --- 3. Satır (12..17) ---
    for (int i = 12; i < 18; i++) {
        if (values[i] == -2)      std::cout << "^#\t";
        else if (values[i] != -1) std::cout << values[i] << "\t";
        else                      std::cout << " \t";
    }
    std::cout << std::endl << std::endl;
}

int CircularHexagonList::findWindowMaxHeightRootValue(Hexagon* windowStart) const
{
    return 1;
}

void CircularHexagonList::printAsSnake(int denominatorRoot) const
{
    if (head == 0 || hexagonCount == 0) return;
    printWindowAsSnake(head);
}