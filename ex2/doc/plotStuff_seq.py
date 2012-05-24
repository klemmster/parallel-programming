from boomslang import Bar, ClusteredBars, Plot
import csv

if __name__ == '__main__':

    data = csv.DictReader(open('benchmark_sequentiell.csv', 'rb'), delimiter=";")
    dataY = []
    try:
        row1 = data.next()
        row2 = data.next()
        row3 = data.next()

        print row1

        y = (float(row1[' origMSWpS']) + float(row2[' origMSWpS']) + float(row3[' origMSWpS'])) / 3.0
        dataY.append(y)
        y = (float(row1[' PforMSWpS']) + float(row2[' PforMSWpS']) + float(row3[' PforMSWpS'])) / 3.0
        dataY.append(y)
        y = (float(row1[' TakssWpS']) + float(row2[' TakssWpS']) + float(row3[' TakssWpS'])) / 3.0
        dataY.append(y)
        y = (float(row1[' OptWpS']) + float(row2[' OptWpS']) + float(row3[' OptWpS'])) / 3.0
        dataY.append(y)
        y = (float(row1[' Opt2WpS']) + float(row2[' Opt2WpS']) + float(row3[' Opt2WpS'])) / 3.0
        dataY.append(y)

    except:
        pass


    bars = []
    labels = ['Reference', 'OMP - For', 'OMP - Tasks', 'Comp-Opt', 'Manual-Opt']
    colors = ['yellow', 'red', 'orange', 'blue', 'green']
    index = 0
    for y in dataY:
        bar = Bar()
        bar.xValues = [index]
        bar.yValues = [y]
        bar.color =  colors[index]
        bar.label = labels[index]
        index += 1
        bars.append(bar)

    plot = Plot()
    for bar in bars:
        plot.add(bar)
    plot.setXLabel("Versions")
    plot.setYLabel("WpS")
    plot.hasLegend()

    plot.save("seq.png")
