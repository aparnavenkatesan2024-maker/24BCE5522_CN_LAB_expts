import csv
from scapy.all import rdpcap, IP, TCP, UDP, ICMP, ARP
from collections import defaultdict
packets = rdpcap("ex7filecap.pcap")
max_bytes = 0
max_pair = ""
with open("exp7caps.csv", "r") as file:
    reader = csv.reader(file)
    rows = list(reader)
for row in rows[1:]:
    addr_a = row[0].strip()
    addr_b = row[2].strip()
    bytes_transferred = int(row[5])
    pair = addr_a + " <-> " + addr_b
    if bytes_transferred > max_bytes:
        max_bytes = bytes_transferred
        max_pair = pair
print("Address pair communicating maximum bytes:")
print(max_pair, "-", max_bytes, "bytes")

time_diffs = []
for i in range(1, len(packets)):
    diff = packets[i].time - packets[i-1].time
    time_diffs.append(diff)
avg_time = sum(time_diffs) / len(time_diffs)
print("\nAverage inter-packet time difference:",
      round(avg_time, 6), "seconds")
pair_protocol_count = defaultdict(lambda: defaultdict(int))
for pkt in packets:
    if pkt.haslayer(IP):
        src = pkt[IP].src
        dst = pkt[IP].dst
        pair = src + " <-> " + dst
        if pkt.haslayer(TCP):
            protocol_name = "TCP"
        elif pkt.haslayer(UDP):
            protocol_name = "UDP"
        elif pkt.haslayer(ICMP):
            protocol_name = "ICMP"
        else:
            protocol_name = "Other"

        pair_protocol_count[pair][protocol_name] += 1

    elif pkt.haslayer(ARP):
        src = pkt[ARP].psrc
        dst = pkt[ARP].pdst
        pair = src + " <-> " + dst
        pair_protocol_count[pair]["ARP"] += 1

print("\nTotal packets transferred between every pair and every protocol:")
for pair in pair_protocol_count:
    for protocol in pair_protocol_count[pair]:
        print(pair, "-", protocol, ":",
              pair_protocol_count[pair][protocol], "packets")
