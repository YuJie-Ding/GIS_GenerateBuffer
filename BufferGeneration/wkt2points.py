fileName = "nanjing-polygon.wkt"
outFile = "nanjing-polygon-points.txt"
with open(fileName, "r") as f:
    text = f.read()
    points = text.split(",")
    with open(outFile, "w") as of:
        for point in points:
            cods = point.split(" ")
            of.write(cods[0] + "," + cods[1] + "\n")