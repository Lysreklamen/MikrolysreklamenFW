physical_to_logical = {}
with open("logical_to_physical_bulbs.txt") as f:
	for line in f:
		logical, physical = [int(x) for x in line.strip().split() if line.strip()]
		physical_to_logical[physical] = logical
for physical, logical in sorted(physical_to_logical.items()):
	print(f"{{{200 + logical}, {300 + logical}, {400 + logical}}},")
