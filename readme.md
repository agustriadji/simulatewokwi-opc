```markdown
# 🚗 Simulasi Tekanan Ban via ESP32 + Modbus RTU + OPC UA

Proyek ini mensimulasikan 8 sensor tekanan ban menggunakan ESP32 (via Wokwi), mengirim data dalam format **Modbus RTU Response**, dan meneruskannya ke **OPC UA Server Python**. Cocok untuk pengujian sistem monitoring tekanan ban sebelum perangkat fisik tersedia.

---

## 📦 Komponen Sistem

1. **ESP32 (Wokwi + PlatformIO)**  
   Mengirim frame Modbus RTU berisi 8 tekanan ban (dalam satu frame 21 byte)

2. **Python OPC UA Server**  
   Menerima frame via TCP, decode, dan expose 8 node tekanan ban via OPC UA

3. **OPC UA Client (opsional)**  
   Untuk monitoring node secara real-time (misalnya: UA Expert, Node-RED, VB.NET)

---

## 🧰 Prasyarat Instalasi

### 1. PlatformIO (untuk ESP32)
- Install [Visual Studio Code](https://code.visualstudio.com/)
- Install ekstensi **PlatformIO IDE**
- Install ekstensi **Wokwi for VS Code** (opsional, untuk simulasi langsung)

### 2. Python 3.8+
- Install [Python](https://www.python.org/downloads/)
- Install pip (biasanya sudah termasuk)

---

## 📁 Struktur Folder

```
project-root/
├── src/
│   ├── main.cpp
│   ├── sensor_utils.cpp
│   ├── modbus_utils.cpp
│   └── network_utils.cpp
├── include/
│   ├── sensor_utils.h
│   ├── modbus_utils.h
│   └── network_utils.h
├── platformio.ini
├── wokwi.toml
├── diagram.json
├── python-opc-server/
│   ├── opc_server.py
│   └── requirements.txt
```

---

## 🚀 Langkah Menjalankan Simulasi

### 🔧 A. Jalankan OPC UA Server (Python)

1. Buka terminal:
   ```bash
   cd python-opc-server
   pip install -r requirements.txt
   python opc_server.py
   ```

2. Output:
   - OPC UA server aktif di `opc.tcp://localhost:4840`
   - TCP listener aktif di port `5000`
   - Menunggu frame Modbus RTU dari ESP32

---

### 🔧 B. Jalankan ESP32 Simulasi (Wokwi + PlatformIO)

1. Buka folder proyek di VS Code
2. Pastikan `platformio.ini` sudah sesuai board ESP32
3. Jalankan:
   ```bash
   pio run --target upload
   pio device monitor
   ```
4. Atau klik ▶️ **Run** di PlatformIO

5. Output:
   - ESP32 akan mengirim frame Modbus RTU setiap 5 detik
   - Format: `01 03 10 ... CRC_L CRC_H`

---

### 🧪 C. Monitoring dengan OPC UA Client

1. Install [UA Expert](https://www.unified-automation.com/products/development-tools/uaexpert.html)
2. Tambahkan server:
   - Endpoint: `opc.tcp://localhost:4840`
3. Browse node:
   - `Objects > Sensor > Pressure_1` sampai `Pressure_8`
4. Lihat nilai tekanan ban berubah setiap 5 detik

---

## ⚙️ Catatan Teknis

- Format tekanan: `uint16_t`, skala `×100` → 235 = 2.35 bar
- Frame Modbus RTU: 21 byte (1 ID + 1 FC + 1 ByteCount + 16 Data + 2 CRC)
- CRC16 dihitung dengan polinomial `0xA001` (standar Modbus)

---

## 📞 Kontak

Proyek ini dikembangkan oleh **Agus Triadji** untuk simulasi sistem tekanan ban berbasis OPC UA.  
Untuk pertanyaan atau kolaborasi, silakan hubungi melalui platform ini.

---
```

---