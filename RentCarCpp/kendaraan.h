#ifndef KENDARAAN_H
#define KENDARAAN_H
#include <QString>


class Kendaraan
{
public:
    Kendaraan(QString m, QString t, double tarif);
    Kendaraan();
    QString getMerk() const { return merk; }
    QString getTipe() const{ return tipe; }
    double getTarifPerHari() const { return tarifPerHari; }
    bool getIsTersedia() const { return isTersedia; }

    void setIsTersedia(bool tersedia) { isTersedia = tersedia; }

private:
    QString merk;
    QString tipe;
    double tarifPerHari;
    bool isTersedia;
};

#endif // KENDARAAN_H
