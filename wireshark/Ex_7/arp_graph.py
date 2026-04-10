from scapy.all import rdpcap, ARP
import matplotlib.pyplot as plt
from collections import defaultdict
packets = rdpcap("ex7filecap.pcap")
arp_bytes = defaultdict(int)
start_time = packets[0].time
for pkt in packets:
    if ARP in pkt:
        sec = int(pkt.time - start_time)
        arp_bytes[sec] += len(pkt)
times = sorted(arp_bytes.keys())
values = [arp_bytes[t] for t in times]
plt.plot(times, values)
plt.xlabel("Time (s)")
plt.ylabel("Bytes per Second")
plt.title("ARP Traffic (Bytes/sec)")
plt.show()
