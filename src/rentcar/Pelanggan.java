package rentcar;
import java.util.ArrayList;

public class Pelanggan {
    private String namaPelanggan;
    private String noKtp;
    private String noHp;
    private ArrayList<Pemesanan> riwayatSewa;

    public Pelanggan(String namaPelanggan, String noKtp, String noHp) {
        this.namaPelanggan = namaPelanggan;
        this.noKtp = noKtp;
        this.noHp = noHp;
        this.riwayatSewa = new ArrayList<>();
    }

    public String getNamaPelanggan() {
        return namaPelanggan;
    }

    public void setNamaPelanggan(String namaPelanggan) {
        this.namaPelanggan = namaPelanggan;
    }

    public String getNoKtp() {
        return noKtp;
    }

    public void setNoKtp(String noKtp) {
        this.noKtp = noKtp;
    }

    public String getNoHp() {
        return noHp;
    }

    public void setNoHp(String noHp) {
        this.noHp = noHp;
    }

    public ArrayList<Pemesanan> getRiwayatSewa() {
        return riwayatSewa;
    }

    public void tambahRiwayat(Pemesanan pesananBaru) {
        this.riwayatSewa.add(pesananBaru);
    }
    
    
    
}
