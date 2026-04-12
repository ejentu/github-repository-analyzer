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
#include <QTextEdit>
#include <QComboBox>
using namespace std;
using json = nlohmann::json;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget pencere;
    pencere.setWindowTitle("GitHub Analiz Aracı v1.0");
    pencere.resize(500, 450);

    QVBoxLayout *duzen = new QVBoxLayout(&pencere);

    QLabel *etiket = new QLabel("Analiz edilecek kullanıcının adını giriniz: ");
    QLineEdit *girisKutusu = new QLineEdit;
    girisKutusu->setPlaceholderText("örn: octocat");
    QPushButton *repoButton = new QPushButton("Repoları Getir");

    QComboBox *repoListesi = new QComboBox();
    repoListesi->setPlaceholderText("Önce kullanıcı Ara...");

    QPushButton *analizButton = new QPushButton("Seçili Repoyu Analiz Et");


    QPushButton *temizleButonu = new QPushButton("Geçmişi Sil");

    QTextEdit *sonucAlani = new QTextEdit();
    sonucAlani->setReadOnly(true);
    sonucAlani->setPlaceholderText("Analiz Sonuçları Burada Gözükecek...");


    duzen->addWidget(etiket);
    duzen->addWidget(girisKutusu);
    duzen->addWidget(repoListesi);
    duzen->addWidget(repoButton);
    duzen->addWidget(analizButton);
    duzen->addWidget(new QLabel("Analiz Raporu:"));
    duzen->addWidget(sonucAlani);
    duzen->addWidget(temizleButonu);


    QObject::connect(repoButton, &QPushButton::clicked, [&]() {
        QString kullaniciAdi = girisKutusu->text();

        if (kullaniciAdi.isEmpty()) {
            QMessageBox::warning(&pencere, "Hata", "Lütfen bir kullanıcı adı giriniz!");
        } else {
            sonucAlani->append("<b>> " + kullaniciAdi + "</b> için işlem başlatıldı...");
            QProcess *pythonSureci = new QProcess();

            QString program = "C:/Users/esoyu/AppData/Local/Programs/Python/Python312/python.exe";

            QStringList argumanlar;
            argumanlar << "C:/Users/esoyu/PycharmProjects/githubApi/githubApiRequests.py" << kullaniciAdi;


            QMessageBox::information(&pencere, "Repo", kullaniciAdi + " için repolar çekiliyor...");

            pythonSureci->start(program, argumanlar);
            if (pythonSureci->waitForFinished(30000)) {
                QString hatalar = pythonSureci->readAllStandardError();
                if (!hatalar.isEmpty()) {
                    sonucAlani->append("<font color='red'>Python Hatası: </font>" + hatalar);
                }
                string dosyaYolu = "C:/Users/esoyu/PycharmProjects/githubApi/repo.name.data.json";
                ifstream dosya(dosyaYolu);

                if (dosya.is_open()) {
                    json j;
                    dosya >> j;
                    dosya.close();


                    repoListesi->clear();
                    for (string eleman: j) {
                        repoListesi->addItem(QString::fromStdString(eleman));
                    }

                    //Pulling python datas
                    // string isim = j.value("name", "Bilinmiyor");
                    // int stars = j.value("stars", 0);
                    // int forks = j.value("forks", 0);
                    // string dil = j.value("language", "Bilinmiyor");
                    //
                    // sonucAlani->append("<font color='green'><b>[İŞLEM TAMAMLANDI]</b></font>");
                    // sonucAlani->append("<b>Repo Adı:</b> " + QString::fromStdString(isim));
                    // sonucAlani->append("<b>Yıldız Sayisi:</b> ⭐ " + QString::number(stars));
                    // sonucAlani->append("<b>Fork Sayisi:</b> 🍴 " + QString::number(forks));
                    // sonucAlani->append("<b>Kodların Ana Dili:</b> 💻 " + QString::fromStdString(dil));
                    // sonucAlani->append("---------------------------");
                    //
                    // QMessageBox::information(&pencere, "Başarılı", "Veriler Başarıyla Analiz Edildi!");
                    //
                    // QString pythonHatasi = pythonSureci->readAllStandardError(); // Python'un hata mesajlarını oku
                }
            } else {
                sonucAlani->append("<font color='red'><b>[HATA]</b> JSON dosyası okunamadı!</font>");
                QMessageBox::critical(&pencere, "Hata", "Python çok uzun sürdü veya çalışmadı!");
            }
        }
    });

    QPushButton::connect(analizButton, &QPushButton::clicked, [&]() {
        QString kullaniciAdi = girisKutusu->text();
        QString seciliRepo = repoListesi->currentText();

        if (seciliRepo.isEmpty() || seciliRepo == "Önce kullanıcı Ara...") {
            QMessageBox::warning(&pencere, "Hata!", "Önce kullanıcı arayının ve repo seçin!");
            return;
        }
        QProcess *pythonSureci = new QProcess();
        QString program = "C:/Users/esoyu/AppData/Local/Programs/Python/Python312/python.exe";
        QStringList argumanlar;
        argumanlar << "C:/Users/esoyu/PycharmProjects/githubApi/githubApiRequests.py" << kullaniciAdi << seciliRepo;

        sonucAlani->append("<b>" + seciliRepo + "</b> detayları çekiliyor...");


        QMessageBox::information(&pencere, "Analiz", kullaniciAdi + " için veriler çekiliyor...");

        pythonSureci->start(program, argumanlar);

        if (pythonSureci->waitForFinished(30000)) {
            string dosyaYolu = "C:/Users/esoyu/PycharmProjects/githubApi/repo.data.json";
            ifstream dosya(dosyaYolu);
            if (dosya.is_open()) {
                json j;
                dosya >> j;
                dosya.close();

                //Pulling python datas
                string isim = j.value("name", "Bilinmiyor");
                int stars = j.value("stars", 0);
                int forks = j.value("forks", 0);
                string dil = j.value("language", "Bilinmiyor");

                sonucAlani->append("<font color='green'><b>[İŞLEM TAMAMLANDI]</b></font>");
                sonucAlani->append("<b>Repo Adı:</b> " + QString::fromStdString(isim));
                sonucAlani->append("<b>Yıldız Sayisi:</b> ⭐ " + QString::number(stars));
                sonucAlani->append("<b>Fork Sayisi:</b> 🍴 " + QString::number(forks));
                sonucAlani->append("<b>Kodların Ana Dili:</b> 💻 " + QString::fromStdString(dil));
                sonucAlani->append("---------------------------");
            }
        }
    });

    QPushButton::connect(temizleButonu, &QPushButton::clicked, [&]() {
        sonucAlani->clear();
    });


    pencere.show();

    return app.exec();
}
