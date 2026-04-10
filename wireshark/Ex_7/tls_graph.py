from scapy.all import rdpcap, TCP
import matplotlib.pyplot as plt
from collections import defaultdict
packets = rdpcap("ex7filecap.pcap")
tls_bytes = defaultdict(int)
start_time = packets[0].time
for pkt in packets:
    if TCP in pkt:
        if pkt[TCP].sport == 443 or pkt[TCP].dport == 443:
            sec = int(pkt.time - start_time)
            tls_bytes[sec] += len(pkt)
times = sorted(tls_bytes.keys())
values = [tls_bytes[t] for t in times]
plt.plot(times, values)
plt.xlabel("Time (s)")
plt.ylabel("Bytes per Second")
plt.title("TLS (or https Port 443) Traffic")
plt.show()
