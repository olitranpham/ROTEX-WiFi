import wifi
import socketpool
import time
import ipaddress

# Wi-Fi connection
SSID = "PicoHotspot"
PWD = "pico1234"

# Laptop IP & port
DEST_IP = "172.20.10.6"
DEST_PORT = 5005

print("Connecting to WiFi:", SSID)

try:
    wifi.radio.connect(SSID, PWD)
except Exception as e:
    print("WiFi connect FAILED:", e)
    raise SystemExit

print("Connected:", wifi.radio.ipv4_address)

# Create socket pool
pool = socketpool.SocketPool(wifi.radio)
sock = pool.socket(pool.AF_INET, pool.SOCK_DGRAM)

dest = (str(ipaddress.ip_address(DEST_IP)), DEST_PORT)

t = 0.0

while True:
    msg = "{}\n".format(t)

    sock.sendto(msg.encode("utf-8"), dest)

    print("sent:", msg.strip())

    t += 0.01
    time.sleep(0.01)
