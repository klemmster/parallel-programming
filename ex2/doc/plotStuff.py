from boomslang import Bar, ClusteredBars, Plot
import csv

if __name__ == '__main__':

    data = csv.DictReader(open('benchmark_omp.csv', 'rb'), delimiter=";")
    threadsData = {}
    threadsData['1'] = [[],[]]
    threadsData['2'] = [[],[]]
    threadsData['3'] = [[],[]]
    threadsData['4'] = [[],[]]
    threadsData['8'] = [[],[]]

    try:
        while True:
            row1 = data.next()
            row2 = data.next()
            row3 = data.next()

            x = int(row1[' K'])/20
            y = (float(row1[' PforMSWpS']) + float(row2[' PforMSWpS']) + float(row3[' PforMSWpS'])) / 3.0
            threadsData[row1[' THREADS'].strip()][0].append(x)
            threadsData[row1[' THREADS'].strip()][1].append(y)

    except:
        pass
    bar1 = Bar()
    bar1.xValues = threadsData['1'][0]
    bar1.yValues = threadsData['1'][1]
    bar1.color = "red"
    bar1.label = "1 Thread"

    bar2 = Bar()
    bar2.xValues = threadsData['2'][0]
    bar2.yValues = threadsData['2'][1]
    bar2.color = "blue"
    bar2.label = "2 Threads"

    bar3 = Bar()
    bar3.xValues = threadsData['3'][0]
    bar3.yValues = threadsData['3'][1]
    bar3.color = "green"
    bar3.label = "3 Threads"

    bar4 = Bar()
    bar4.xValues = threadsData['4'][0]
    bar4.yValues = threadsData['4'][1]
    bar4.color = "orange"
    bar4.label = "4 Threads"

    bar8 = Bar()
    bar8.xValues = threadsData['8'][0]
    bar8.yValues = threadsData['8'][1]
    bar8.color = "yellow"
    bar8.label = "8 Threads"

    clusteredBars = ClusteredBars()

    clusteredBars.add(bar1)
    clusteredBars.add(bar2)
    clusteredBars.add(bar3)
    clusteredBars.add(bar4)
    clusteredBars.add(bar8)
    clusteredBars.spacing = 0.1

    clusteredBars.xTickLabels = ["1", "21", "41", "61", "81", "101"]

    plot = Plot()
    plot.add(clusteredBars)
    plot.setXLabel("K")
    plot.setYLabel("WpS")
    plot.hasLegend()

    plot.save("omp_for.png")
