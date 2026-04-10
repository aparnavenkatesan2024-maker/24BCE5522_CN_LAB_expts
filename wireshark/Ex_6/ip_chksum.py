from scapy.all import *
packets=rdpcap("file_capture.pcap")
pktno=1
print("METHOD 3: IPv4 CHECKSUM VALIDATION USING SCAPY\n")
for pkt in packets:
    if pkt.haslayer(IP):
        captured=pkt[IP].chksum
        pkt[IP].chksum=None
        rebuilt=IP(bytes(pkt[IP]))
        calculated=rebuilt[IP].chksum
        print("Packet",pktno,"(IPv4)")
        print("Captured checksum  :",hex(captured))
        print("Calculated checksum:",hex(calculated))
        print("Result:","VALID\n" if captured==calculated 
                else "Result: INVALID\n")
        pktno+=1
