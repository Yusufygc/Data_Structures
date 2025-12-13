#ifndef CIRCULARHEXAGONLIST_HPP
#define CIRCULARHEXAGONLIST_HPP

#include "Hexagon.hpp"

class CircularHexagonList
{
private:
    Hexagon* head;
    int hexagonCount;

public:
    CircularHexagonList();
    ~CircularHexagonList();

    Hexagon* createAndAppendHexagon();
    Hexagon* getHead() const;
    int getHexagonCount() const;
    Hexagon* getRightNeighbor(Hexagon* current) const;

    void printAsSnake(int denominatorRoot) const;
    void printWindowAsSnake(Hexagon* windowStart) const;
    
    int findGlobalMaxHeightRootValue() const;
    int findWindowMaxHeightRootValue(Hexagon* windowStart) const;

    // Yeni Eklenen Fonksiyon:
    void processTurn(int turnNumber);
};

#endif