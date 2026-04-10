from scapy.all import *
from collections import Counter

pkts = rdpcap("LAB3CN.pcap")
print("Total no. of packets captured = ",len(pkts))

x=len(set(pkt[IP].src for pkt in pkts if IP in pkt))
print("Number of Source IPs = ",x)

y=len(set(pkt[IP].dst for pkt in pkts if IP in pkt))
print("Number of Destination IPs = ",y)

z=len(set(pkt.lastlayer().name for pkt in pkts))
print("Number of protocols used = ",z)

print("Number of packets per protocol =")
print(Counter(pkt.lastlayer().name for pkt in pkts))

