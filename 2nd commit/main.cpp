#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <cstdlib>
#include <QProcess>
using namespace std;
using json = nlohmann::json;

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget pencere;
    pencere.setWindowTitle("GitHub Analiz Aracı v1.0");
    pencere.resize(400,250);

    QVBoxLayout *duzen = new QVBoxLayout(&pencere);

    QLabel *etiket = new QLabel("Analiz edilecek kullanıcının adını giriniz: ");
    QLineEdit *girisKutusu = new QLineEdit;
    girisKutusu->setPlaceholderText("örn: octocat");

    QPushButton *button = new QPushButton("Analizi Başlat");

    duzen->addWidget(etiket);
    duzen->addWidget(girisKutusu);
    duzen->addWidget(button);


    QObject::connect(button, &QPushButton::clicked, [&]() {

        QString kullaniciAdi = girisKutusu->text();

        if (kullaniciAdi.isEmpty()) {
            QMessageBox::warning(&pencere, "Hata", "Lütfen bir kullanıcı adı giriniz!");
        }else {
            QProcess *pythonSureci = new QProcess();

            QString program = "C:/Users/esoyu/AppData/Local/Microsoft/WindowsApps/python.exe";

            QStringList argumanlar;
            argumanlar <<"C:/Users/esoyu/PycharmProjects/githubApi/githubApiRequests.py" << kullaniciAdi;


            QMessageBox::information(&pencere, "Analiz", kullaniciAdi+" için veriler çekiliyor...");

            pythonSureci->start(program,argumanlar);

            if (pythonSureci->waitForFinished(30000)) {
            QMessageBox::information(&pencere, "Başarılı", "Python verileri çekti ve dosyayı güncelledi!");
        } else {
            QMessageBox::critical(&pencere, "Hata", "Python çok uzun sürdü veya çalışmadı!");
        }


        }

        //TODO : PYTHON KODU YAZILACAK


    });



    pencere.show();

    return app.exec();








}