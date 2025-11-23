/** 
* @file MainNode.hpp
* @description = Bu sınıf, çift bağlı liste yapısındaki her düğümü temsil eder ve her düğümün ShapeList nesnesi vardır.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#ifndef MAINNODE_HPP
#define MAINNODE_HPP
#include "ShapeList.hpp"

class MainNode {
    public:
        ShapeList shapes; // her ana düğümün şekiller listesi
        MainNode* prev;   // önceki düğüm
        MainNode* next;   // sonraki düğüm

        // constructor ve destructor
        MainNode();
        ~MainNode();
};

#endif