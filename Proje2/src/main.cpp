/** 
* @file main.cpp
* @description = Bu dosya, ProgramManager sınıfını kullanarak programın
                başlatılmasını ve çalıştırılmasını sağlar.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#include "ProgramManager.hpp"

int main() {
    ProgramManager app;
    app.init(); // Kullanıcıya soru sor ve listeyi oluştur
    app.run();  // Program döngüsünü başlat
    return 0;
}