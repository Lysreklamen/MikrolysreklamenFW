from intelhex import IntelHex

playlist = []
for line in open('playlist.txt'):
    playlist.append(line.strip('\n'))

print(playlist)

mapping = []
for line in open('logical_to_physical.txt'):
    items = line.split()
    items = [int(x) for x in items]
    mapping.append(items)

#print(mapping)

#path = 'C:/git/'

sequence = []
for pgmfile in playlist:
    i = 0
    for line in open(pgmfile + '.pgm'):
        if(i>3):
            items = line.split()
            items = [int(x) for x in items]
            sequence.append(items)
        i = i + 1

#print(sequence)
compressedsequence = [] #All bytes in a single "line" (list)

for line in sequence:
    templine = [0] * 512
    for map in mapping:
        templine[map[1]] = line[map[0]]
    compressedsequence.extend(templine[0:82])

ih = IntelHex()

i = 0
for byte in compressedsequence:
    ih[i] = byte
    i = i + 1

ih.write_hex_file("mikrolysreklamen17.eep")
