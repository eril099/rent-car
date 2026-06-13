/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package rentcar;
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;

/**
 *
 * @author Eril
 */
public class Pembayaran {
    private Double denda;
    private Double diskon;
    private Double biayaAwal;
    private Double biayaAkhir;

    public Pembayaran(Double diskon, Double biayaAwal) {
        this.denda = 0.0;
        this.diskon = diskon;
        this.biayaAwal = biayaAwal;
        this.biayaAkhir = 0.0;
    }
    
    public void hitungDenda(Pemesanan pesanan, LocalDate tanggalDikembalikanAktual){
        LocalDate tanggalBatas = pesanan.getTanggalKembali();
        
        if(tanggalDikembalikanAktual.isAfter(tanggalBatas)){
            long hariTerlambat = ChronoUnit.DAYS.between(tanggalBatas, tanggalDikembalikanAktual);
            double tarifMobil = pesanan.getMobilDisewa().getTarifPerHari();
            this.denda = 0.5 * tarifMobil * (double) hariTerlambat;
        }
        else{
            this.denda = 0.0;
        }
        
    }
    
 
    public void hitungBiayaAkhir(){
        this.biayaAkhir = (this.biayaAwal + this.denda) - this.diskon;
    }

    public Double getDenda() {
        return denda;
    }

    public Double getDiskon() {
        return diskon;
    }

    public Double getBiayaAwal() {
        return biayaAwal;
    }

    public Double getBiayaAkhir() {
        return biayaAkhir;
    }

    public void setDenda(Double denda) {
        this.denda = denda;
    }

    public void setDiskon(Double diskon) {
        this.diskon = diskon;
    }
    
    
    
}
