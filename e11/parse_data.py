iArr = []
dArr = []
with open("tr-matmul.ref", "r") as f:
	for line in f:
		if line[-2] == 'I':
			iArr.append(line.split(',')[0][:-3])
		else:
			dArr.append(line.split(',')[0][:-3])

iArr_uniq = list(set(iArr))
dArr_uniq = list(set(dArr))

iArr_output = []
dArr_output = []

for item in iArr_uniq:
	iArr_output.append((item, iArr.count(item)))

for item in dArr_uniq:
	dArr_output.append((item, dArr.count(item)))

from operator import itemgetter

iArr_final = []
dArr_final = []

iArr_final = sorted(iArr_output, reverse=True, key=itemgetter(1))
dArr_final = sorted(dArr_output, reverse=True, key=itemgetter(1))

print "Instructions: "
for item in iArr_final:
	print item
print "\n"
print "Data: "
for item in dArr_final:
	print item
print "\nTotal instructions: ", len(iArr)
print "Total data: ", len(dArr)