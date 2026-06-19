package rentcar;
import java.util.ArrayList;

public class FleetManager {
    private ArrayList<Kendaraan> daftarKendaraan;
    private ArrayList<Pemesanan> daftarPemesanan;
    private int counterIdPemesanan = 1;
    
    public FleetManager(){
        this.daftarKendaraan = new ArrayList<>();
        this.daftarPemesanan = new ArrayList<>();
}
    public void tambahKendaraan(Kendaraan mobilBaru){
        this.daftarKendaraan.add(mobilBaru);
        System.out.println("Log: Berhasil Menambahkan" + mobilBaru.getMerk() + "Ke dalam Armada");
    }
    public void tambahPemesanan(Pemesanan p){
        this.daftarPemesanan.add(p);
    }
    public ArrayList<Pemesanan> getPemesananAktif(){
        ArrayList<Pemesanan> aktif = new ArrayList<>();
        for (Pemesanan p : daftarPemesanan) {
            if (!p.isStatusSelesai()) aktif.add(p);
        }
        return aktif;
    }
    public ArrayList<Pemesanan> getPemesananSelesai(){
        ArrayList<Pemesanan> selesai = new ArrayList<>();
        for (Pemesanan p : daftarPemesanan){
            if(p.isStatusSelesai()){
                selesai.add(p);
            }
        }
        return selesai; 
    }
    public String generateIdPemesanan(){
        return String.valueOf(counterIdPemesanan++);
    }
    public ArrayList<Kendaraan> getDaftarKendaraan(){
        return this.daftarKendaraan;
    }
}
