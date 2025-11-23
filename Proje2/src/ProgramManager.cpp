/** 
* @file ProgramManager.cpp
* @description = Bu dosya ProgramManager sınıfının işlevlerini içerir.
                ProgramManager, şekillerin oluşturulması, yönetilmesi ve çizilmesi gibi
                ana program akışını kontrol eder.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#include "ProgramManager.hpp"
#include <iostream>
#include <string>
#include "FileManager.hpp"
#include "RandomUtil.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "Star.hpp"
#include "ClampUtil.hpp"

using namespace std;

ProgramManager::ProgramManager() {
    this->running = true;
    this->activeNode = 0;
    this->windowStart = 0;
    this->shapeMode = false;
    this->shapeIndex = 0;
}
// Rastgele bir şekil oluşturur
Shape* ProgramManager::createRandomShape() {
    int type = RandomUtil::range(0, 2);
    int size = RandomUtil::range(4, 10);
    char ch = RandomUtil::pickChar();
    int z = RandomUtil::range(0, 100);

    Shape* newShape;
    if (type == 0) {
        newShape = new Rectangle(0, 0, size, ch, z);
    }
    else if (type == 1) {
        newShape = new Triangle(0, 0, size, ch, z);
    }
    else {
        newShape = new Star(0, 0, size, ch, z);
    }

    int w = newShape->getWidth();
    int h = newShape->getHeight();

    int minX = ClampUtil::SHAPE_MIN_X;
    int maxX = ClampUtil::SHAPE_MAX_X - w + 1;
    int minY = ClampUtil::SHAPE_MIN_Y;
    int maxY = ClampUtil::SHAPE_MAX_Y - h + 1;

    if (maxX < minX) maxX = minX;
    if (maxY < minY) maxY = minY;

    int x = RandomUtil::range(minX, maxX);
    int y = RandomUtil::range(minY, maxY);

    newShape->setX(x);
    newShape->setY(y);

    return newShape;
}

// Ana listeyi rastgele şekillerle doldurur
void ProgramManager::populateRandom() {
    for (int i = 0; i < 20; i++) {
        MainNode* n = new MainNode();
        int count = RandomUtil::range(2, 7);
        for (int j = 0; j < count; j++)
            n->shapes.pushFront(createRandomShape());
        mainList.pushBack(n);
    }
}


// Menü çizimi
void ProgramManager::drawMenu(char menuOutput[ROWS][MENU_WIDTH]) {
    // 1. Önce tüm menü alanını temizle
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < MENU_WIDTH; c++) {
            menuOutput[r][c] = ' ';
        }
    }

    // 2. Menü kutularını çiz
    const int BOX_W = 15;
    int total = mainList.size();
    int end = windowStart + WINDOW_SIZE;
    if (end > total) end = total;

    int row = 0;
    for (int i = windowStart; i < end; i++) {
        MainNode* n = mainList.getAt(i);
        int count = n->shapes.size();

        // --- Üst Çizgi ---
        for (int k = 0; k < BOX_W; k++) menuOutput[row][k] = '*';
        row++;

        // --- Orta Satır (Sayı) ---
        menuOutput[row][0] = '*';
        int digits = (count < 10 ? 1 : (count < 100 ? 2 : 3));
        int space = BOX_W - 2;
        int leftPad = (space - digits) / 2;
        int rightPad = space - leftPad - digits;

        for (int s = 0; s < leftPad; s++) menuOutput[row][1 + s] = ' ';
        
        string num = to_string(count);
        
        for (int k = 0; k < num.size(); k++) menuOutput[row][1 + leftPad + k] = num[k];
        
        for (int s = 0; s < rightPad; s++) menuOutput[row][1 + leftPad + digits + s] = ' ';
        
        menuOutput[row][BOX_W - 1] = '*';
        
        // --- Aktif Düğüm İşareti ---
        if (i == activeNode) {
            // Üst satıra ok ekle (row - 1)
            menuOutput[row - 1][BOX_W] = ' ';
            menuOutput[row - 1][BOX_W + 1] = '<';
            menuOutput[row - 1][BOX_W + 2] = '-';
            menuOutput[row - 1][BOX_W + 3] = '-';
            
            // Orta satıra ok ekle (row)
            menuOutput[row][BOX_W] = ' ';
            menuOutput[row][BOX_W + 1] = '<';
            menuOutput[row][BOX_W + 2] = '-';
            menuOutput[row][BOX_W + 3] = '-';
            
            // Alt satıra ok ekle (row + 1)
            // Not: Alt çizgi henüz çizilmedi ama dizi temizlendiği için yazabiliriz.
            // Alt çizgi döngüsü sadece 0-14 arasını boyadığı için burayı (15-19) ezmez.
            menuOutput[row + 1][BOX_W] = ' ';
            menuOutput[row + 1][BOX_W + 1] = '<';
            menuOutput[row + 1][BOX_W + 2] = '-';
            menuOutput[row + 1][BOX_W + 3] = '-';
            
        }
        row++;

        // --- Alt Çizgi ---
        for (int k = 0; k < BOX_W; k++) menuOutput[row][k] = '*';
        row++;
        
        // --- Boşluk ---
        row++;
    }
}

// Şekilleri ekrana çizer
void ProgramManager::drawShapes(Screen& scr) {
    scr.clear(' ');
    MainNode* node = mainList.getAt(activeNode);
    if (!node) return;

    for (int i = 0; i < node->shapes.size(); ++i) {
        Shape* s = node->shapes.getAt(i);
        if (!s) continue;
        
        // Taşma kontrolü 
        int right = s->getX() + s->getWidth() - 1;
        int bottom = s->getY() + s->getHeight() - 1;
        if (right >= Screen::COLS || bottom >= Screen::ROWS) {
            ClampUtil::clampPosition(s);
        }
    }
    node->shapes.drawAllByZ(scr);
}

// Kullanıcıdan cevap alır ve akışı başlatır
void ProgramManager::init() {
    RandomUtil::init();
    cout << "[1] Rastgele olustur\n"
         << "[2] Dosyadan yukle\nSecim: ";
    int s;
    cin >> s;

    if (s == 2) {
        // Dosya yüklemeyi dene
        if (!FileManager::load(mainList, "data.txt")) {
            // Dosya bulunamazsa kullanıcıya sor
            cout << "Dosya bulunamadi! Rastgele olusturulsun mu? (E/H): ";
            char secim;
            cin >> secim;

            if (secim == 'e' || secim == 'E') {
                cout << "Rastgele olusturuluyor...\n";
                populateRandom();
            } else {
                // KULLANICI HAYIR DEDİĞİNDE ÇIKIŞ YAPILAN KISIM:
                cout << "Program sonlandiriliyor...\n";
                running = false; // <--- BU SATIR EKLENDİ.
                // Bu değişken false olunca run() fonksiyonundaki while döngüsü hiç başlamaz.
            }
        }
    } else {
        populateRandom();
    }
}

// Liste modu için kullanıcı girişleri
void ProgramManager::handleListModeInput(char cmd) {
    if (cmd == 'w' || cmd == 'W') {
        if (activeNode > 0) {
            activeNode--;
            windowStart = (activeNode / WINDOW_SIZE) * WINDOW_SIZE;
        }
    }
    else if (cmd == 's' || cmd == 'S') {
        if (activeNode < mainList.size() - 1) {
            activeNode++;
            windowStart = (activeNode / WINDOW_SIZE) * WINDOW_SIZE;
        }
    }
    else if (cmd == 'c' || cmd == 'C') {
        if (mainList.size() > 0) {
            mainList.removeAt(activeNode);
            if (activeNode >= mainList.size()) activeNode = mainList.size() - 1;
            if (activeNode < 0) activeNode = 0;
            
            if (mainList.size() > 0)
                windowStart = (activeNode / WINDOW_SIZE) * WINDOW_SIZE;
            else
                windowStart = 0;
        }
    }
    else if (cmd == 'f' || cmd == 'F') {
        MainNode* cur = mainList.getAt(activeNode);
        if (cur && cur->shapes.size() > 0) {
            shapeMode = true;
            shapeIndex = 0;
        }
    }
    else if (cmd == 'x' || cmd == 'X') running = false;
}

// Şekil modu için kullanıcı girişleri
void ProgramManager::handleShapeModeInput(char cmd) {
    MainNode* cur = mainList.getAt(activeNode);
    if (!cur || cur->shapes.size() == 0) {
        shapeMode = false;
        return;
    }

    if (shapeIndex >= cur->shapes.size()) {
        shapeIndex = cur->shapes.size() - 1;
    }
    Shape* sh = cur->shapes.getAt(shapeIndex);

    if (cmd == 'w' || cmd == 'W') { sh->moveBy(0, -1); ClampUtil::clampPosition(sh); }
    else if (cmd == 's' || cmd == 'S') { sh->moveBy(0, 1); ClampUtil::clampPosition(sh); }
    else if (cmd == 'a' || cmd == 'A') { sh->moveBy(-1, 0); ClampUtil::clampPosition(sh); }
    else if (cmd == 'd' || cmd == 'D') { sh->moveBy(1, 0); ClampUtil::clampPosition(sh); }
    else if (cmd == 'q' || cmd == 'Q') { if (shapeIndex > 0) shapeIndex--; }
    else if (cmd == 'e' || cmd == 'E') { if (shapeIndex < cur->shapes.size() - 1) shapeIndex++; }
    else if (cmd == 'c' || cmd == 'C') {
        cur->shapes.removeAt(shapeIndex);
        if (cur->shapes.size() == 0) {
            mainList.removeAt(activeNode);
            shapeMode = false;
            if (activeNode >= mainList.size()) {
                activeNode = mainList.size() - 1;
            }
            if (activeNode < 0) {
                activeNode = 0;
            }
            
            if(mainList.size() > 0) {
                windowStart = (activeNode / WINDOW_SIZE) * WINDOW_SIZE;
            }
            
            else {
                windowStart = 0;
            }
        } else {
            if (shapeIndex >= cur->shapes.size()) {
                shapeIndex = cur->shapes.size() - 1;
            }
        }
    }
    else if (cmd == 'g' || cmd == 'G') {
        shapeMode = false;
    }
}

// Ana akış
void ProgramManager::run() {
    // Eğer init() aşamasında kullanıcı "Hayır" dediyse running false olmuştur.
    // Bu durumda döngüye girmeden ve DOSYA KAYDETMEDEN fonksiyondan çık.
    if (!running) return; 

    while (running) {
        system("cls");

        char menu[ROWS][MENU_WIDTH];
        drawMenu(menu);

        Screen scr;
        drawShapes(scr);

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < MENU_WIDTH; c++) {
                cout << menu[r][c];
            }
            scr.renderLine(r, MENU_WIDTH);
        }

        cout << "\n";
        if (!shapeMode)
            cout << "(W/S) Listeler Arasi Hareket | (F) Liste Sec | (C) Listeyi Sil | (X) cikis : ";
        else
            cout << "(W/A/S/D) hareket | (Q) onceki elemani sec | (E) sonraki elemani sec | (C) elemani sil | (G) ana menuye don : ";

        char cmd;
        cin >> cmd;

        if (!shapeMode) handleListModeInput(cmd);
        else handleShapeModeInput(cmd);
    }
    
    // Döngü normal yollarla (X'e basarak) biterse burası çalışır ve kaydeder.
    FileManager::save(mainList, "data.txt");
}