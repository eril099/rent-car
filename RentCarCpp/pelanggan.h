#ifndef PELANGGAN_H
#define PELANGGAN_H
#include <QString>

class Pelanggan
{
public:
    Pelanggan (QString n, QString k, QString kontak);
    Pelanggan();
    QString getNama() const { return nama; }
    QString getKtp() const { return ktp; }
    QString getKontak() const { return kontak; }

private:
    QString nama;
    QString ktp;
    QString kontak;

};

#endif // PELANGGAN_H
