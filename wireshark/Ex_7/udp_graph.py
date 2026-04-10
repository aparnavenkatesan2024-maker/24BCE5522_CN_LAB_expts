from scapy.all import rdpcap, UDP
import matplotlib.pyplot as plt
from collections import defaultdict
packets = rdpcap("ex7filecap.pcap")
udp_counts = defaultdict(int)
start_time = packets[0].time
for pkt in packets:
    if UDP in pkt:
        sec = int(pkt.time - start_time)
        udp_counts[sec] += 1
times = sorted(udp_counts.keys())
counts = [udp_counts[t] for t in times]
plt.plot(times, counts)
plt.xlabel("Time (s)")
plt.ylabel("UDP Packets per Second")
plt.title("UDP Traffic (Packets/sec)")
plt.show()
