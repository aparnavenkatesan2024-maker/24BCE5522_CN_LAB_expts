from scapy.all import *
packets=rdpcap("file_capture.pcap")
pktno=1

print("METHOD 3: ICMPv6 CHECKSUM VALIDATION USING SCAPY\n")
for pkt in packets:
    if pkt.haslayer(IPv6):
        for layer in pkt.layers():
            if "ICMPv6" in layer.__name__:
                captured=pkt[layer].cksum
                pkt[layer].cksum=None
                rebuilt=IPv6(bytes(pkt[IPv6]))
                calculated=rebuilt[layer].cksum
                print("Packet",pktno,"("+layer.__name__+")")
                print("Captured checksum  :",hex(captured))
                print("Calculated checksum:",hex(calculated))
                print("Result:","VALID\n" if captured==calculated 
                       else "Result: INVALID\n")
                pktno+=1
                break
