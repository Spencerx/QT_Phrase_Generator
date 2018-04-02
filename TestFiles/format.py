import sys
if len(sys.argv)!=2:
    print("Must call program: PROGRAM_NAME FILENAME")
    exit()
print("Opening " + sys.argv[1] + "...\n")
export = "new-" + sys.argv[1]
f = open(export, "w+")
print("Converting and exporting to " + export + "...\n")
with open(sys.argv[1]) as inputFile:
    del_space = False
    for line in inputFile:
        if line == "\n":
            continue
        for x in line:
            if del_space == True:
                del_space = False
                continue
            f.write(x)
            if x == "." or x == "!":
                f.write("\n")
                del_space = True
    f.close()
inputFile.close()
print("Done!\n")
