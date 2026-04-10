from scapy.all import *
packets=rdpcap("file_capture.pcap")
pktno=1
print("METHOD 3: TCP CHECKSUM VALIDATION USING SCAPY\n")
for pkt in packets:
    if pkt.haslayer(TCP):
        captured=pkt[TCP].chksum
        pkt[TCP].chksum=None
        if pkt.haslayer(IP):
            rebuilt=IP(bytes(pkt[IP]))
        elif pkt.haslayer(IPv6):
            rebuilt=IPv6(bytes(pkt[IPv6]))
        else:
            continue
        calculated=rebuilt[TCP].chksum
        print("Packet",pktno,"(TCP)")
        print("Captured checksum  :",hex(captured))
        print("Calculated checksum:",hex(calculated))
        print("Result:","VALID\n" if captured==calculated
               else "Result: INVALID\n")
        pktno+=1
