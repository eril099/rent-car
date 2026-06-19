#ifndef PEMESANAN_H
#define PEMESANAN_H
#include "kendaraan.h"
#include "pelanggan.h"
#include <QString>

class Pemesanan
{
public:
    Pemesanan (QString ambil, QString kembali, int hari, Kendaraan* mobil, Pelanggan* p);
    Pemesanan();
    QString getTanggalAmbil() const { return tanggalAmbil; }
    QString getTanggalKembali() const { return tanggalKembali; }
    Kendaraan* getMobilYangDisewakan() const { return mobilYangDisewakan; }
    Pelanggan* getPenyewa() const { return penyewa; }
    int getDurasiHari() const { return durasiHari; }

private:
    QString tanggalAmbil;
    QString tanggalKembali;
    Kendaraan* mobilYangDisewakan;
    Pelanggan* penyewa;
    int durasiHari;
};

#endif // PEMESANAN_H
