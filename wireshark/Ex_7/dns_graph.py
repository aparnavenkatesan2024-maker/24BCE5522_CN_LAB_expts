from scapy.all import rdpcap, DNS
import matplotlib.pyplot as plt
from collections import defaultdict
packets = rdpcap("ex7filecap.pcap")
dns_counts = defaultdict(int)
start_time = packets[0].time
for pkt in packets:
    if DNS in pkt:
        sec = int(pkt.time - start_time)
        dns_counts[sec] += 1

times = sorted(dns_counts.keys())
counts = [dns_counts[t] for t in times]
plt.plot(times, counts)
plt.xlabel("Time (s)")
plt.ylabel("DNS Packets per Second")
plt.title("DNS Traffic (Packets/sec)")
plt.show()
