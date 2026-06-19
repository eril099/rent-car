#ifndef PEMBAYARAN_H
#define PEMBAYARAN_H

class Pembayaran
{
public:
    Pembayaran (double awal, double potong, double charge);
    Pembayaran();
    double getTotalAwal() const { return totalAwal; }
    double getDiskon() const { return diskon; }
    double getDenda() const { return denda; }
    double getTotalAkhir() const { return totalAkhir; }

private:
    double totalAwal;
    double diskon;
    double denda;
    double totalAkhir;
};

#endif // PEMBAYARAN_H
