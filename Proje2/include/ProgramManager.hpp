/** 
* @file ProgramManager.hpp
* @description = Bu sınıf, programın ana yönetim sınıfıdır. MainList'i yönetir, kullanıcı girdilerini işler ve ekran çıktısını oluşturur.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#ifndef PROGRAMMANAGER_HPP
#define PROGRAMMANAGER_HPP

#include "MainList.hpp"
#include "Screen.hpp"
/*
İleri bildirim: 
ProgramManager.hpp içinde Shape tanımına ihtiyaç duymadan 
Shape* işaretçilerini kullanabiliriz.
*/
class Shape; 

class ProgramManager {
private:
    MainList mainList;  // ana liste
    bool running; // program çalışıyor mu ? onun kontrolü için flag
    
    // Program Durumu Değişkenleri
    int activeNode;  // aktif ana düğüm indeksi
    int windowStart; // görüntüleme penceresinin başlangıç indeksi
    bool shapeMode;  // şekil modunda mı (true: şekil mod, false: liste mod)
    int shapeIndex;  // aktif şekil indeksi (şekil modunda)
    
    // Sabitler
    static const int WINDOW_SIZE = 6;
    static const int MENU_WIDTH = 22;
    static const int ROWS = 25;

    // Yardımcı Fonksiyonlar
    Shape* createRandomShape();                // Rastgele şekil oluşturur
    void populateRandom();                     // Ana listeyi rastgele şekillerle doldurur
    void drawMenu(char out[ROWS][MENU_WIDTH]); // Menü çizimi 
    void drawShapes(Screen& screen);           // Şekilleri ekrana çizer
    void printInstructions();                  // Kullanıcı talimatlarını yazdırır
    
    // Girdi İşleme
    void processInput(char cmd);               // Kullanıcı komutunu işler
    void handleListModeInput(char cmd);        // Liste modundaki komutları işler
    void handleShapeModeInput(char cmd);       // Şekil modundaki komutları işler

public:
    ProgramManager();
    void init(); // Açılış (Dosya yüklensin mi yoksa rastgele mi oluşturulsun sorusunu sorar)
    void run();  // Akış başlar 
};

#endif