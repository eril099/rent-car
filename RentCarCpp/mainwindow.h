#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "kendaraan.h"
#include "pelanggan.h"
#include "pemesanan.h"
#include "pembayaran.h"
#include "fleetmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnTambahMobil_clicked();
    void on_btnSewaMobil_clicked();
    void on_btnKembalikanMobil_clicked();

    void on_listRiwayat_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    fleetManager managerPusat;
    QList<Pelanggan*> daftarPelanggan;
    QList<Pemesanan> daftarPemesanan;
    QList<QString> databaseNota;
    void refreshTabelMobil();
};
#endif // MAINWINDOW_H
