/** 
* @file MainNode.cpp
* @description = Bu dosya MainNode sınıfının yapıcı ve yıkıcı işlevlerini içerir.
                MainNode sınıfı, çift bağlı liste yapısında her düğümün 
                şekiller listesini ve önceki/sonraki düğümlerine işaretçilerini tutar.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#include "MainNode.hpp"

MainNode::MainNode() {
    this->prev = 0;
    this->next = 0;
    // 'shapes' nesnesi (ShapeList) otomatik olarak kendi varsayılan yapıcısıyla oluşturulur.
}
MainNode::~MainNode(){}