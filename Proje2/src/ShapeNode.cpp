/** 
* @file ShapeNode.cpp
* @description =Bu dosya ShapeNode sınıfının işlevlerini içerir.
                ShapeNode, bağlı liste yapısında bir düğümü temsil eder 
                ve her düğüm bir Shape nesnesine işaret eder.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#include "ShapeNode.hpp"
#include "Shape.hpp"

ShapeNode::ShapeNode(Shape* s) {
    this->data = s;
    this->next = 0;
}
ShapeNode::~ShapeNode(){ delete data; }