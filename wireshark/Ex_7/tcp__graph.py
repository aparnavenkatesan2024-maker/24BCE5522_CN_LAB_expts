from scapy.all import rdpcap, TCP
import matplotlib.pyplot as plt
from collections import defaultdict
packets = rdpcap("ex7filecap.pcap")
tcp_counts = defaultdict(int)
start_time = packets[0].time


for pkt in packets:
    if TCP in pkt:
        sec = int(pkt.time - start_time)
        tcp_counts[sec] += 1
times = sorted(tcp_counts.keys())
counts = [tcp_counts[t] for t in times]
plt.plot(times, counts)
plt.xlabel("Time (s)")
plt.ylabel("TCP Packets per Second")
plt.title("TCP Traffic (Packets/sec)")
plt.show()

