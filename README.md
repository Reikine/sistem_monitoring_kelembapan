# 🌱 Sistem Monitoring Kelembapan & Smart Garden

Project ini adalah sistem IoT berbasis ESP32 untuk memantau kelembapan tanah dan suhu udara secara real-time menggunakan aplikasi Blynk.

## 📸 Fitur Utama
* **Monitoring Real-time:** Membaca data sensor setiap detik.
* **Koneksi IoT:** Terhubung ke Blynk Cloud.
* **Notifikasi:** Peringatan otomatis jika tanah terlalu kering.
* **Machine Learning:** Integrasi Edge Impulse untuk klasifikasi kondisi tanaman (jika ada).

## 🛠️ Komponen Hardware
* **Microcontroller:** ESP32 DevKit V1
* **Sensor:** DHT22 (Suhu & Kelembapan Udara)
* **Sensor Tanah:** Capacitive Soil Moisture Sensor (x2)
* **Actuator:** Relay 2 Channel (untuk Pompa Air)

## 💻 Software & Library
* PlatformIO (VS Code)
* Blynk Library
* DHT Sensor Library

## 🚀 Cara Install
1. Clone repository ini.
2. Buka di VS Code dengan ekstensi PlatformIO.
3. Ubah nama file `include/secrets.h.example` menjadi `secrets.h`.
4. Masukkan Token Blynk dan WiFi kamu di `secrets.h`.
5. Upload ke ESP32.

---
*Dibuat oleh Rei*