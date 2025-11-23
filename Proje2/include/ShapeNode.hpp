/** 
* @file ShapeNode.hpp
* @description = 
        Bu dosya, ShapeNode sınıfının tanımını içerir.
        ShapeNode, Shape nesnelerine işaret eden tek yönlü bağlı liste düğümlerini temsil eder.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#ifndef SHAPENODE_HPP
#define SHAPENODE_HPP

class Shape;

class ShapeNode {
    public:
        Shape* data;
        ShapeNode* next;
        ShapeNode(Shape* s);
        ~ShapeNode();
};

#endif