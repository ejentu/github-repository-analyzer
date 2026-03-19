#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {

    ifstream dosya("C:/Users/esoyu/PycharmProjects/githubApi/repo.data.json");
    if (!dosya.is_open()) {
        cerr<<"Hata! JSON dosyası bulunamadı"<<endl;
        return 1;
    }

    cout<<"Dosya basariyla acildi, analiz basliyor..."<<endl;

    json j;
    dosya >> j;
    string repoAdi, language;
    int stars;
    int forks;

    try {
        repoAdi = j.value("name","IsimsizRepository");
        stars = j.value("stars",0);
        forks = j.value("forks",0);
        language = j.value("language","BilinmeyenDiller");

        cout<< "Repo Adi: " << repoAdi<< " | Puan: "<< (stars+forks) << endl;






    }catch(json::exception& e) {
        cerr<<"Analiz Hatası " << e.what() << endl;
    }




    cout << "Analiz Raporlari"<<endl;
    int toplamEtkilesim = stars + (forks*2);
    if (stars > 10000) {
        cout<<"Durum: Bu proje dunya capinda populer"<<endl;
    }else if (stars > 1000) {
        cout<<"Durum: Bu proje oldukça başarılı bir proje"<<endl;
    }else if (stars > 100) {
        cout<<"Durum: BU proje gelecek vaadeden bir proje "<<endl;
    }else {
        cout<<"DUrum : yeni ve nispeten kucuk bir proje"<<endl;
    }


    if (language == "C++") {
        cout << "Not: Bu repo performans odakli bir dille yazilmis." << endl;
    } else if (language == "Python") {
        cout << "Not: Bu repo veri bilimi veya hizli prototipleme odakli." << endl;
    }else {
        cout<<language<<endl;
    }


    dosya.close();
    return 0;


}