from flask import Flask, request
from opcua import Server
import datetime
import socket
import threading

# Setup OPC UA Server
server = Server()
server.set_endpoint("opc.tcp://0.0.0.0:4840")
server.set_server_name("AgusSimulatedOPCUA")

# Namespace dan node
uri = "http://agus.simulation"
idx = server.register_namespace(uri)
objects = server.get_objects_node()
sensor_obj = objects.add_object(idx, "Sensor")

# Buat 8 node tekanan ban
pressure_nodes = []
for i in range(1, 9):
    node = sensor_obj.add_variable(idx, f"Pressure_{i}", 0.0)
    node.set_writable()
    pressure_nodes.append(node)

# Tambahan node suhu jika tetap ingin pakai JSON
temp_node = sensor_obj.add_variable(idx, "Temperature", 0.0)
temp_node.set_writable()

# Start OPC UA server
server.start()
print("✅ OPC UA Server started at opc.tcp://0.0.0.0:4840")

# Setup Flask HTTP receiver (opsional, tetap bisa dipakai)
app = Flask(__name__)

@app.route('/sensor', methods=['POST'])
def receive_data():
    data = request.json
    temperature = data.get('temperature')
    if temperature is not None:
        temp_node.set_value(float(temperature))
        print(f"[{datetime.datetime.now()}] Updated Temperature: {temperature}")
    return "OK", 200

# Fungsi untuk decode frame Modbus RTU
def decode_modbus_frame(data):
    if len(data) != 21 or data[0] != 0x01 or data[1] != 0x03 or data[2] != 0x10:
        print("⚠️ Invalid Modbus frame")
        return None
    pressures = []
    for i in range(8):
        raw = (data[3 + i*2] << 8) | data[4 + i*2]
        pressures.append(raw / 100.0)
    return pressures

# TCP listener untuk ESP32
def tcp_listener():
    sock = socket.socket()
    sock.bind(("0.0.0.0", 5000))
    sock.listen(1)
    print("📡 TCP listener started on port 5000")
    conn, addr = sock.accept()
    print(f"🔌 TCP connected from {addr}")

    while True:
        data = conn.recv(21)
        if not data:
            break
        pressures = decode_modbus_frame(data)
        if pressures:
            for i in range(8):
                pressure_nodes[i].set_value(pressures[i])
            print(f"[{datetime.datetime.now()}] Updated Pressures: {pressures}")

# Jalankan TCP listener di thread terpisah
threading.Thread(target=tcp_listener, daemon=True).start()

# Jalankan Flask HTTP server
app.run(host='0.0.0.0', port=5000)