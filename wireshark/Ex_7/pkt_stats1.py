import csv
from scapy.all import rdpcap, Raw
packets = rdpcap("ex7filecap.pcap")
total_packets = len(packets)
total_bytes = 0
payload_bytes = 0
for pkt in packets:
    total_bytes += len(pkt)
    if pkt.haslayer(Raw):
        payload_bytes += len(pkt[Raw].load)

data_size = payload_bytes
header_size = 0
header_details = {}

with open("exp7filecap.csv", "r") as file:
    reader = csv.reader(file)
    rows = list(reader)

for row in rows[1:]:
    protocol = row[0].strip()
    bytes_value = int(row[4])
    if protocol in ["Ethernet", "Internet Protocol Version 4",
                    "Transmission Control Protocol",
                    "User Datagram Protocol",
                    "Address Resolution Protocol",
                    "Internet Group Management Protocol"]:
        header_details[protocol] = bytes_value
        header_size += bytes_value

print("Total number of packets:", total_packets)
print("Size of data:", data_size, "bytes")

print("\nIndividual Header Sizes (from CSV):")
for protocol, size in header_details.items():
    print(protocol + ":", size, "bytes")

print("\nTotal Size of Headers:", header_size, "bytes")

