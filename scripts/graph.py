from matplotlib import pyplot
import matplotlib.pyplot as plt
import numpy
from textwrap import wrap
import matplotlib.ticker as ticker

with open('settings.txt') as file:
    settings=[float(i) for i in file.read().split('\n')]

#считываем показания компаратора и переводим через шаг квантования в вольиты
data=numpy.loadtxt('data2.txt', dtype=int)* settings[1]

#массив времен, создаваемый черед количество измерений и известный шаг по времени
data_time=numpy.array([i/settings[0] for i in range(data.size)])

#параметры фигуры
fig, ax=pyplot.subplots(figsize=(16, 10), dpi=500)
print(data)
print(data_time)

#минимальные и максимальные значения для осей
ax.axis([data_time.min(), data_time.max()+1, data.min(), data.max()+0.2])

#  Устанавливаем интервал основных делений:
ax.xaxis.set_major_locator(ticker.MultipleLocator(1))

#  Устанавливаем интервал вспомогательных делений:
ax.xaxis.set_minor_locator(ticker.MultipleLocator(0.1))

#  Тоже самое проделываем с делениями на оси "y":
ax.yaxis.set_major_locator(ticker.MultipleLocator(0.2))
ax.yaxis.set_minor_locator(ticker.MultipleLocator(0.05))

#название графика с условием для переноса строки и центрированием
ax.set_title("\n".join(wrap('процесс заряда и разряда конденсатора в RC цепи', 50)), loc = 'center')

#сетка основная и второстепенная
ax.grid(which='major', color = 'k')
ax.minorticks_on()
ax.grid(which='minor', color = 'gray', linestyle = ':')

#подпись осей
ax.set_ylabel("напряжение, В", fontsize = 20)
ax.set_xlabel("время, с", fontsize = 20)
ax.text(2.3, 1.3, 'Время заряда', fontsize=20)

#линия с легендой
ax.plot(data_time, data, c='black', linewidth=1, label = 'V(t)')
ax.scatter(data_time[0:data.size:1], data[0:data.size:1], marker = 's', c = 'blue', s=10)

ax.legend(shadow = False, loc = 'right', fontsize = 20)

#сохранение
plt.savefig(
    'graphichek.pdf',
    format='pdf',
    bbox_inches='tight',
    #pad_inches=4
)
