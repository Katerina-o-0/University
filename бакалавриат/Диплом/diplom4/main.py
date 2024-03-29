import sys

import matplotlib.pyplot as plt
import numpy as np
import math

import os
from PyQt5 import uic
from PyQt5.QtWidgets import QApplication, QMessageBox

# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# Расчетные функции
# Поиск математического ожидания
def find_m_t(list_p):
    list_res = []
    for num in range(len(list_p)):
        summa_mas = sum(list_p[num])
        # Находим мат ожидание
        m = summa_mas / len(list_p[num])
        list_res.append(m)
    return list_res


# Поиск дисперсии
def find_d_t(list_p, list_m):
    list_res = []
    for num in range(len(list_p)):
        summa_mas = 0
        for ch in range(len(list_p[num])):
            summa_mas += (list_p[num][ch] - list_m[num]) ** 2
        # Находим дисперсию
        D = summa_mas / (len(list_p[num]) - 1)
        list_res.append(D)
    return list_res


# Поиск СКО
def find_sigma_t(list_d):
    list_sigma = []
    for num in range(len(list_d)):
        sig = math.sqrt(list_d[num])
        list_sigma.append(sig)
    return list_sigma


# Поиск ОШС
def find_SNR(const, list_for_sig, list_for_all_p, list_m):
    list_SNR = []
    for num in range(len(list_m)):
        sum_mas = 0
        for ch in range(len(list_for_all_p[num])):
            sum_mas += list_for_all_p[num][ch] ** 2
        number1 = (1 + const) ** 2
        number2 = list_for_sig[num] ** 2
        number3 = (sum_mas / len(list_for_all_p[num])) - list_m[num] ** 2
        list_SNR.append(number1 * number2 / number3)
    return list_SNR


# Найдем мат ожидание минус СКО
def find_M_minus_sigma(list_M, list_sigma):
    list_M_min_sig = []
    for num in range(len(list_M)):
        list_M_min_sig.append(list_M[num] - list_sigma[num])
    return list_M_min_sig


# Найдем мат ожидание плюс СКО
def find_M_plus_sigma(list_M, list_sigma):
    list_M_pl_sig = []
    for num in range(len(list_M)):
        list_M_pl_sig.append(list_M[num] + list_sigma[num])
    return list_M_pl_sig


# Найдем мат ожидание по ансамблю
def find_M_ans(list_p):
    list_M_ans = []
    for num in range(len(list_p[0])):
        summa_ans = 0
        for ch in range(len(list_p)):
            summa_ans += list_p[ch][num]
        M_ans = summa_ans / len(list_p)
        list_M_ans.append(M_ans)
    return list_M_ans


# Найдем дисперсию по ансамблю
def find_D_ans(list_p, list_M):
    list_D_ans = []
    for num in range(len(list_p[0])):
        summa_ans = 0
        for ch in range(len(list_p)):
            summa_ans += (list_p[ch][num] - list_M[num]) ** 2
        D_ans = summa_ans / (len(list_p) - 1)
        list_D_ans.append(D_ans)

    return list_D_ans


# Функция для поиска энергии управления
def find_energy_u(list_per):
    list_e = []
    for num in range(len(list_per)):
        sum_u = 0
        for ch in range(len(list_per[num])):
            sum_u += list_per[num][ch] ** 2
        list_e.append(sum_u / len(list_per[num]))
    return list_e

def for_rounnd_zn(list_zn):
    list_r = []
    for i in range(len(list_zn)):
        list_r.append(round((list_zn[i]), 3))
    return list_r

# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# Функции для отрисовки
# Строим графики зависимости x, s, u от Т
def draw_graph_perem_t(list_x, list_s, list_u, list_Y):
    # #Рисуем графики
    list_for_t = []
    for num in range(len(list_x[0])):
        list_for_t.append(num)

    for ch in range(11):
        fig = plt.figure()
        plt.plot(list_for_t, list_x[ch], 'ro')
        plt.title('Зависимость x(t)')
        plt.ylabel('x, усл.ед')
        plt.xlabel('t, усл.ед')
        plt.grid(True)
        plt.legend(['x'], loc=1)
        fig.savefig('Pic_block1_' + str(ch + 1) + '_for_x_t.png')
        plt.close()
        fig_1 = plt.figure()
        plt.plot(list_for_t, list_s[ch], 'ro')
        plt.title('Зависимость s(t)')
        plt.ylabel('s, усл.ед')
        plt.xlabel('t, усл.ед')
        plt.grid(True)
        plt.legend(['s'], loc=1)
        # plt.show()
        fig_1.savefig('Pic_block1_' + str(ch + 1) + '_for_s_t.png')
        plt.close()
        fig_2 = plt.figure()
        plt.plot(list_for_t, list_u[ch], 'ro')
        plt.title('Зависимость u(t)')
        plt.ylabel('u, усл.ед')
        plt.xlabel('t, усл.ед')
        plt.grid(True)
        plt.legend(['u'], loc=1)
        # plt.show()
        fig_2.savefig('Pic_block1_' + str(ch + 1) + '_for_Y_t.png')
        plt.close()
        fig_2 = plt.figure()
        plt.plot(list_for_t, list_Y[ch], 'ro')
        plt.title('Зависимость psi(t)')
        plt.ylabel('psi, усл.ед')
        plt.xlabel('t, усл.ед')
        plt.grid(True)
        plt.legend(['psi'], loc=1)
        # plt.show()
        fig_2.savefig('Pic_block1_' + str(ch + 1) + '_for_psi_t.png')
        plt.close()


# Построим графики зависимости оценок мат ожидания от ОШС
def draw_graph_mark_SNR(list_snr_x, list_m_x, list_snr_s, list_m_s, list_snr_u, list_m_u, list_snr_Y, list_m_Y, list_r_x_snr, list_r_s_snr, list_r_u_snr, list_r_Y_snr ):
    fig_snr_1 = plt.figure()
    plt.plot(list_snr_x, list_m_x, 'r')
    plt.title('Зависимость Mx(ОШС))')
    plt.ylabel('Mx, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Mx'], loc=1)
    fig_snr_1.savefig('Pic_block1_Mx_snr.png')
    plt.close()

    fig_snr_1 = plt.figure()
    plt.plot(list_snr_x, list_m_x, 'r.')
    plt.title('Зависимость Mx(ОШС)')
    plt.ylabel('Mx, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Mx'], loc=1)
    fig_snr_1.savefig('Pic_block1_Mx_snr_2.png')
    plt.close()

    fig_snr_2 = plt.figure()
    plt.plot(list_snr_s, list_m_s, 'r')
    plt.title('Зависимость Ms(ОШС)')
    plt.ylabel('Ms, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Ms'], loc=1)
    fig_snr_2.savefig('Pic_block1_Ms_snr.png')
    plt.close()

    fig_snr_2 = plt.figure()
    plt.plot(list_snr_s, list_m_s, 'r.')
    plt.title('Зависимость Ms(ОШС)')
    plt.ylabel('Ms, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Ms'], loc=1)
    fig_snr_2.savefig('Pic_block1_Ms_snr_2.png')
    plt.close()

    fig_snr_3 = plt.figure()
    plt.plot(list_snr_u, list_m_u, 'r')
    plt.title('Зависимость Mu(ОШС)')
    plt.ylabel('Mu, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Mu'], loc=1)
    fig_snr_3.savefig('Pic_block1_Mu_snr.png')
    plt.close()

    fig_snr_3 = plt.figure()
    plt.plot(list_snr_u, list_m_u, 'r.')
    plt.title('Зависимость Mu(ОШС))')
    plt.ylabel('Mu, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Mu'], loc=1)
    fig_snr_3.savefig('Pic_block1_Mu_snr_2.png')
    plt.close()

    fig_snr_4 = plt.figure()
    plt.plot(list_snr_Y, list_m_Y, 'r')
    plt.title('Зависимость Mpsi(ОШС))')
    plt.ylabel('Mpsi, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Mpsi'], loc=1)
    fig_snr_4.savefig('Pic_block1_MY_snr.png')
    plt.close()

    fig_snr_4 = plt.figure()
    plt.plot(list_snr_Y, list_m_Y, 'r.')
    plt.title('Зависимость Mpsi(ОШС))')
    plt.ylabel('Mpsi, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Mpsi'], loc=1)
    fig_snr_4.savefig('Pic_block1_MY_snr_2.png')
    plt.close()

# Построим график зависимости энергии управления от ОШС
def draw_graph_Eu(list_snr, list_e):
    # Построим график зависимости Энергии управления от ОШС
    fig_snr = plt.figure()
    plt.plot(list_snr,list_e, color="red")
    plt.title('Зависимость Eu(ОШС)')
    plt.ylabel('Eu, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Eu'], loc=1)
    fig_snr.savefig('Pic_block1_E_u_snr.png')
    plt.close()


def print_perem (a, b, c, w, x_, Umin, Umax, s, x, u, sigma_const ):
    # ____________________________________________  БЛОК 1 ____________________________________________
    # Целевая макропеременная  в 0 момент времени
    Y = x - x_

    # Создадим списк для списков данных x, s, u, Y, sigma
    list_for_all_x = []
    list_for_all_s = []
    list_for_all_u = []
    list_for_all_Y = []
    list_for_sigma = [x_ * 0.01, x_ * 0.024, x_ * 0.038, x_ * 0.052, x_ * 0.066, x_ * 0.08, x_ * 0.094, x_ * 0.108, x_ * 0.122, x_ * 0.136, x_ * 0.150]

    # list_for_sigma = [1.6, 1.6, 1.6, 1.6, 1.6, 1.6, 1.6, 1.6, 1.6, 1.6, 1.6]
    for n in range(11):
        sigma = list_for_sigma[n]
        # значение шума в 0 момент времени
        e = np.random.normal(0, float(sigma), 1)
        # формируем список значений шума
        list_for_e = [float(e)]
        # формируем список значений кол-ва товаров на складе
        list_for_x = [float(x)]
        # формируем список значений величины спроса
        list_for_s = [float(s)]
        # формируем список значений объема поставок
        list_for_u = [float(u)]
        # формируем список значений макропеременной
        list_for_Y = [float(Y)]
        for t in range(1, 100):
            # получаем значение спроса в момент времени t и добавляем его в список
            s_t = a * list_for_s[t - 1] + b
            list_for_s.append(float(s_t))
            # получаем новое значение шума и добавляем его в список
            e_t = np.random.normal(0, float(sigma), 1)
            list_for_e.append(float(e_t))
            # получаем новое значение кол-ва товаров на складе в момент времени t  и добавляем его в список
            x_t = list_for_x[t - 1] + list_for_u[t - 1] + c * list_for_e[t - 1] + e_t - s_t
            list_for_x.append(float(x_t))
            # получем значение макропеременной и добавляем его в список
            Y_t = x_t - x_
            list_for_Y.append(float(Y_t))
            # получаем момент спроса в t+1
            s_t_plus_1 = a * s_t + b
            # получим значение управления по методу акар
            u_a = (w + c) * (-Y_t) + x_ + c * w * list_for_Y[t - 1] + s_t_plus_1 - x_t

            if u_a < Umin:
                # получаем объём поставок в момент времени t
                u_t = 0
                list_for_u.append(float(u_t))
            elif u_a < Umax:
                u_t = u_a
                list_for_u.append(float(u_t))
            else:
                u_t = Umax
                list_for_u.append(float(u_t))
        # добавляем полученные данные в массив с массивами
        list_for_all_x.append(list_for_x)
        list_for_all_s.append(list_for_s)
        list_for_all_u.append(list_for_u)
        list_for_all_Y.append(list_for_Y)
        # Выводим зачения на экран
        print('x:  ', list_for_x)
        print('s:  ', list_for_s)
        print('u:  ', list_for_u)
        print('Y:  ', list_for_Y)

    # Поиск оценок на временном промежутке
    # формируем список для найденных оценок мат ожиданий
    list_for_M_x = find_m_t(list_for_all_x)
    list_for_M_s = find_m_t(list_for_all_s)
    list_for_M_u = find_m_t(list_for_all_u)
    list_for_M_Y = find_m_t(list_for_all_Y)
    print('M_x', list_for_M_x)
    print('M_s', list_for_M_s)
    print('M_u', list_for_M_u)
    print('M_Y', list_for_M_Y)

    # формируем список для найденных дисперсий
    list_for_D_x = find_d_t(list_for_all_x, list_for_M_x)
    list_for_D_s = find_d_t(list_for_all_s, list_for_M_s)
    list_for_D_u = find_d_t(list_for_all_u, list_for_M_u)
    list_for_D_Y = find_d_t(list_for_all_Y, list_for_M_Y)
    print('D_x', list_for_D_x)
    print('D_s', list_for_D_s)
    print('D_u', list_for_D_u)
    print('D_Y', list_for_D_Y)

    # формируем список для найденных СКО
    list_for_sigma_x = find_sigma_t(list_for_D_x)
    list_for_sigma_s = find_sigma_t(list_for_D_s)
    list_for_sigma_u = find_sigma_t(list_for_D_u)
    list_for_sigma_Y = find_sigma_t(list_for_D_Y)
    print('sigma_x', list_for_sigma_x)
    print('sigma_s', list_for_sigma_s)
    print('sigma_u', list_for_sigma_u)
    print('sigma_Y', list_for_sigma_Y)

    # формируем список для ОШС x
    list_for_SNR_x = find_SNR(c, list_for_sigma, list_for_all_x, list_for_M_x)
    list_for_SNR_s = find_SNR(c, list_for_sigma, list_for_all_s, list_for_M_s)
    list_for_SNR_u = find_SNR(c, list_for_sigma, list_for_all_u, list_for_M_u)
    list_for_SNR_Y = find_SNR(c, list_for_sigma, list_for_all_Y, list_for_M_Y)
    print('SNR_x', list_for_SNR_x)
    print('SNR_s', list_for_SNR_s)
    print('SNR_u', list_for_SNR_u)
    print('SNR_Y', list_for_SNR_Y)

    # округлим значения для графиков
    list_for_SNR_x_r = for_rounnd_zn(list_for_SNR_x)
    list_for_SNR_s_r = for_rounnd_zn(list_for_SNR_s)
    list_for_SNR_u_r = for_rounnd_zn(list_for_SNR_u)
    list_for_SNR_Y_r = for_rounnd_zn(list_for_SNR_Y)

    # формируем список для энергии
    list_for_energy_u = find_energy_u(list_for_all_u)
    print('energy_u', list_for_energy_u)

    # Посчитиаем значения мат ожиданий с учетом СКО для графиков
    list_for_M_x_minus_sigma = find_M_minus_sigma(list_for_M_x, list_for_sigma_x)
    list_for_M_x_plus_sigma = find_M_plus_sigma(list_for_M_x, list_for_sigma_x)
    list_for_M_s_minus_sigma = find_M_minus_sigma(list_for_M_s, list_for_sigma_s)
    list_for_M_s_plus_sigma = find_M_plus_sigma(list_for_M_s, list_for_sigma_s)
    list_for_M_u_minus_sigma = find_M_minus_sigma(list_for_M_u, list_for_sigma_u)
    list_for_M_u_plus_sigma = find_M_plus_sigma(list_for_M_u, list_for_sigma_u)
    list_for_M_Y_minus_sigma = find_M_minus_sigma(list_for_M_Y, list_for_sigma_Y)
    list_for_M_Y_plus_sigma = find_M_plus_sigma(list_for_M_Y, list_for_sigma_Y)

    # Выведем значения на экран
    print('list_for_M_x_plus_sigma', list_for_M_x_plus_sigma)
    print('list_for_M_x_minus_sigma', list_for_M_x_minus_sigma)
    print('list_for_M_s_plus_sigma', list_for_M_s_plus_sigma)
    print('list_for_M_s_minus_sigma', list_for_M_s_minus_sigma)
    print('list_for_M_u_plus_sigma', list_for_M_u_plus_sigma)
    print('list_for_M_u_minus_sigma', list_for_M_u_minus_sigma)
    print('list_for_M_Y_plus_sigma', list_for_M_Y_plus_sigma)
    print('list_for_M_Y_minus_sigma', list_for_M_Y_minus_sigma)

    # Построим графики x, s, u от t
    draw_graph_perem_t(list_for_all_x, list_for_all_s, list_for_all_u, list_for_all_Y)
    # Построим графики зависимости оценок мат ожидания от ОШС
    draw_graph_mark_SNR(list_for_SNR_x, list_for_M_x, list_for_SNR_s, list_for_M_s, list_for_SNR_u, list_for_M_u,
                        list_for_SNR_Y, list_for_M_Y, list_for_SNR_x_r, list_for_SNR_s_r, list_for_SNR_u_r,
                        list_for_SNR_Y_r)
    # Построим график зависимости Энергии управления от ОШС
    draw_graph_Eu(list_for_SNR_u, list_for_energy_u)

    # Построим графики
    fig_snr = plt.figure()
    plt.plot(list_for_SNR_x, list_for_M_x, 'r', list_for_SNR_x, list_for_M_x_plus_sigma, 'g--', list_for_SNR_x,
             list_for_M_x_minus_sigma, 'b--')
    plt.title('Зависимость Mx(ОШС), Mx+СКО(ОШС) и Mx-СКО(ОШС)')
    plt.ylabel('Mx, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Mx', 'Mx+СКО', 'Mx-СКО'], loc=1)
    fig_snr.savefig('Pic_block1_Mx_snr_sigma.png')
    plt.close()

    fig_snr = plt.figure()
    plt.plot(list_for_SNR_s, list_for_M_s, 'r', list_for_SNR_s, list_for_M_s_plus_sigma, 'g--', list_for_SNR_s,
             list_for_M_s_minus_sigma, 'b--')
    plt.title('Зависимость Ms(ОШС), Ms+СКО(ОШС) и Ms-СКО(ОШС)')
    plt.ylabel('Ms, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Ms', 'Ms+СКО', 'Ms-СКО'], loc=1)
    fig_snr.savefig('Pic_block1_Ms_snr_sigma.png')
    plt.close()

    fig_snr = plt.figure()
    plt.plot(list_for_SNR_u, list_for_M_u, 'r', list_for_SNR_u, list_for_M_u_plus_sigma, 'g--', list_for_SNR_u,
             list_for_M_u_minus_sigma, 'b--')
    plt.title('Зависимость Mu(ОШС), Mu+СКО(ОШС) и Mu-СКО(ОШС)')
    plt.ylabel('Mu, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Mu', 'Mu+СКО', 'Mu-СКО'], loc=1)
    fig_snr.savefig('Pic_block1_Mu_snr_sigma.png')
    plt.close()

    fig_snr = plt.figure()
    plt.plot(list_for_SNR_Y, list_for_M_Y, 'r', list_for_SNR_Y, list_for_M_Y_plus_sigma, 'g--', list_for_SNR_Y,
             list_for_M_Y_minus_sigma, 'b--')
    plt.title('Зависимость Mpsi(ОШС), Mpsi+СКО(ОШС) и Mpsi-СКО(ОШС)')
    plt.ylabel('Mpsi, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Mpsi', 'Mpsi+СКО', 'Mpsi-СКО'], loc=1)
    fig_snr.savefig('Pic_block1_MY_snr_sigma.png')
    plt.close()

    # ____________________________________________  БЛОК 2 ____________________________________________
    # ЧАСТЬ БЕЗ ОГРАНИЧЕНИЙ ДЛЯ УПРАВЛЕНИЯ
    # Создадим списк для списков данных x, s, u, Y, sigma
    list_for_all_x_2 = []
    list_for_all_s_2 = []
    list_for_all_u_2 = []
    list_for_all_Y_2 = []
    for n in range(11):
        sigma = list_for_sigma[n]
        # значение шума в 0 момент времени
        e = np.random.normal(0, float(sigma), 1)
        # формируем список значений шума
        list_for_e = [float(e)]
        # формируем список значений кол-ва товаров на складе
        list_for_x = [float(x)]
        # формируем список значений величины спроса
        list_for_s = [float(s)]
        # формируем список значений объема поставок
        list_for_u = [float(u)]
        # формируем список значений макропеременной
        list_for_Y = [float(Y)]
        for t in range(1, 100):
            # получаем значение спроса в момент времени t и добавляем его в список
            s_t = a * list_for_s[t - 1] + b
            list_for_s.append(float(s_t))
            # получаем новое значение шума и добавляем его в список
            e_t = np.random.normal(0, float(sigma), 1)
            list_for_e.append(float(e_t))
            # получаем новое значение кол-ва товаров на складе в момент времени t  и добавляем его в список
            x_t = list_for_x[t - 1] + list_for_u[t - 1] + c * list_for_e[t - 1] + e_t - s_t
            list_for_x.append(float(x_t))
            # получем значение макропеременной и добавляем его в список
            Y_t = x_t - x_
            list_for_Y.append(float(Y_t))
            # получаем момент спроса в t+1
            s_t_plus_1 = a * s_t + b
            # получим значение управления по методу акар
            u_a = (w + c) * (-Y_t) + x_ + c * w * list_for_Y[t - 1] + s_t_plus_1 - x_t
            u_t = u_a
            list_for_u.append(float(u_t))

        # добавляем полученные данные в массив с массивами
        list_for_all_x_2.append(list_for_x)
        list_for_all_s_2.append(list_for_s)
        list_for_all_u_2.append(list_for_u)
        list_for_all_Y_2.append(list_for_Y)
        # print('x_2:  ', list_for_x)
        # print('s_2:  ', list_for_s)
        # print('u_2:  ', list_for_u)
        # print('Y_2:  ', list_for_Y)

    print('list_for_all_x_2', list_for_all_x_2)
    print('list_for_all_s_2', list_for_all_s_2)
    print('list_for_all_u_2', list_for_all_u_2)
    print('list_for_all_Y_2', list_for_all_Y_2)

    # #Рисуем графики
    list_for_t = []
    for num in range(len(list_for_all_x_2[0])):
        list_for_t.append(num)

    for t in range(11):
        fig = plt.figure()
        plt.plot(list_for_t, list_for_all_x[t], 'r.', list_for_t, list_for_all_x_2[t], 'b.')
        plt.title('Зависимость x(t) с ограничением и x2(t) без ограничения')
        plt.ylabel('x, усл.ед')
        plt.xlabel('t, усл.ед')
        plt.grid(True)
        plt.legend(['x', 'x2'], loc=1)
        fig.savefig('Pic_block2_' + str(t + 1) + '_for_x_t_and_x_2_t.png')
        plt.close()
        fig_1 = plt.figure()
        plt.plot(list_for_t, list_for_all_s[t], 'r.', list_for_t, list_for_all_s_2[t], 'b.')
        plt.title('Зависимость s(t) с ограничением и s2(t) без ограничения')
        plt.ylabel('s, усл.ед')
        plt.xlabel('t, усл.ед')
        plt.grid(True)
        plt.legend(['s', 's2'], loc=1)
        # plt.show()
        fig_1.savefig('Pic_block2_' + str(t + 1) + '_for_s_t_and_s_2_t.png')
        plt.close()
        fig_2 = plt.figure()
        plt.plot(list_for_t, list_for_all_u[t], 'r.', list_for_t, list_for_all_u_2[t], 'b.')
        plt.title('Зависимость u(t) с ограничением и u2(t) без ограничения')
        plt.ylabel('u, усл.ед')
        plt.xlabel('t, усл.ед')
        plt.grid(True)
        plt.legend(['u', 'u2'], loc=1)
        # plt.show()
        fig_2.savefig('Pic_block2_' + str(t + 1) + '_for_u_t_and_u_2_t.png')
        plt.close()
        fig_2 = plt.figure()
        plt.plot(list_for_t, list_for_all_Y[t], 'r.', list_for_t, list_for_all_Y_2[t], 'b.')
        plt.title('Зависимость psi(t) с ограничением и psi2(t) без ограничения')
        plt.ylabel('psi, усл.ед')
        plt.xlabel('t, усл.ед')
        plt.grid(True)
        plt.legend(['psi', 'psi2'], loc=1)
        # plt.show()
        fig_2.savefig('Pic_block2_' + str(t + 1) + '_for_Y_t_and_Y_2_t.png')
        plt.close()

    # Посчитаем оценки для модели без ограничений на управление
    # формируем спсисок для найденных оценок мат ожиданий
    list_for_M_x_2 = find_m_t(list_for_all_x_2)
    list_for_M_s_2 = find_m_t(list_for_all_s_2)
    list_for_M_u_2 = find_m_t(list_for_all_u_2)
    list_for_M_Y_2 = find_m_t(list_for_all_Y_2)
    print('M_x_2', list_for_M_x_2)
    print('M_s_2', list_for_M_s_2)
    print('M_u_2', list_for_M_u_2)
    print('M_Y_2', list_for_M_Y_2)

    # формируем список для найденных дисперсий
    list_for_D_x_2 = find_d_t(list_for_all_x_2, list_for_M_x_2)
    list_for_D_s_2 = find_d_t(list_for_all_s_2, list_for_M_s_2)
    list_for_D_u_2 = find_d_t(list_for_all_u_2, list_for_M_u_2)
    list_for_D_Y_2 = find_d_t(list_for_all_Y_2, list_for_M_Y_2)
    print('D_x_2', list_for_D_x_2)
    print('D_s_2', list_for_D_s_2)
    print('D_u_2', list_for_D_u_2)
    print('D_Y_2', list_for_D_Y_2)

    # формируем список для найденных СКО
    list_for_sigma_x_2 = find_sigma_t(list_for_D_x_2)
    list_for_sigma_s_2 = find_sigma_t(list_for_D_s_2)
    list_for_sigma_u_2 = find_sigma_t(list_for_D_u_2)
    list_for_sigma_Y_2 = find_sigma_t(list_for_D_Y_2)
    print('sigma_x_2', list_for_sigma_x_2)
    print('sigma_s_2', list_for_sigma_s_2)
    print('sigma_u_2', list_for_sigma_u_2)
    print('sigma_Y_2', list_for_sigma_Y_2)

    # формируем список для ОШС x
    list_for_SNR_x_2 = find_SNR(c, list_for_sigma, list_for_all_x_2, list_for_M_x_2)
    list_for_SNR_s_2 = find_SNR(c, list_for_sigma, list_for_all_s_2, list_for_M_s_2)
    list_for_SNR_u_2 = find_SNR(c, list_for_sigma, list_for_all_u_2, list_for_M_u_2)
    list_for_SNR_Y_2 = find_SNR(c, list_for_sigma, list_for_all_Y_2, list_for_M_Y_2)
    print('SNR_x_2', list_for_SNR_x_2)
    print('SNR_s_2', list_for_SNR_s_2)
    print('SNR_u_2', list_for_SNR_u_2)
    print('SNR_Y_2', list_for_SNR_Y_2)

    fig_snr = plt.figure()
    plt.plot(list_for_SNR_x_2, list_for_M_x_2, color="red")
    plt.title('Зависимость Mx(ОШС))')
    plt.ylabel('Mx, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Mx'], loc=1)
    fig_snr.savefig('Pic_block2_Mx_snr_2.png')
    plt.close()

    fig_snr = plt.figure()
    plt.plot(list_for_SNR_s_2, list_for_M_s_2, color="red")
    plt.title('Зависимость Ms(ОШС)')
    plt.ylabel('Ms, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Ms'], loc=1)
    fig_snr.savefig('Pic_block2_Ms_snr_2.png')
    plt.close()

    fig_snr = plt.figure()
    plt.plot(list_for_SNR_u_2, list_for_M_u_2, color="red")
    plt.title('Зависимость Mu(ОШС)')
    plt.ylabel('Mu, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Mu'], loc=1)
    fig_snr.savefig('Pic_block2_Mu_snr_2.png')
    plt.close()

    fig_snr = plt.figure()
    plt.plot(list_for_SNR_Y_2, list_for_M_Y_2, color="red")
    plt.title('Зависимость Mpsi(ОШС))')
    plt.ylabel('Mpsi, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Mpsi'], loc=1)
    fig_snr.savefig('Pic_block2_MY_snr_2.png')
    plt.close()

    # формируем список для энергии
    list_for_energy_u_2 = find_energy_u(list_for_all_u_2)
    print('energy_u_2', list_for_energy_u_2)

    # Рисуем график энергии
    fig_snr = plt.figure()
    plt.plot(list_for_SNR_u_2, list_for_energy_u_2, color="red")
    plt.title('Зависимость Eu(ОШС))')
    plt.ylabel('Eu, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Eu(ОШС)'], loc=1)
    fig_snr.savefig('Pic_block2_E_u_snr_2.png')
    plt.close()

    list_for_M_x_minus_sigma_2 = find_M_minus_sigma(list_for_M_x_2, list_for_sigma_x_2)
    list_for_M_x_plus_sigma_2 = find_M_plus_sigma(list_for_M_x_2, list_for_sigma_x_2)
    list_for_M_s_minus_sigma_2 = find_M_minus_sigma(list_for_M_s_2, list_for_sigma_s_2)
    list_for_M_s_plus_sigma_2 = find_M_plus_sigma(list_for_M_s_2, list_for_sigma_s_2)
    list_for_M_u_minus_sigma_2 = find_M_minus_sigma(list_for_M_u_2, list_for_sigma_u_2)
    list_for_M_u_plus_sigma_2 = find_M_plus_sigma(list_for_M_u_2, list_for_sigma_u_2)
    list_for_M_Y_minus_sigma_2 = find_M_minus_sigma(list_for_M_Y_2, list_for_sigma_Y_2)
    list_for_M_Y_plus_sigma_2 = find_M_plus_sigma(list_for_M_Y_2, list_for_sigma_Y_2)

    print('list_for_M_x_plus_sigma_2', list_for_M_x_plus_sigma_2)
    print('list_for_M_x_minus_sigma_2', list_for_M_x_minus_sigma_2)
    print('list_for_M_s_plus_sigma_2', list_for_M_s_plus_sigma_2)
    print('list_for_M_s_minus_sigma_2', list_for_M_s_minus_sigma_2)
    print('list_for_M_u_plus_sigma_2', list_for_M_u_plus_sigma_2)
    print('list_for_M_u_minus_sigma_2', list_for_M_u_minus_sigma_2)
    print('list_for_M_Y_plus_sigma_2', list_for_M_Y_plus_sigma_2)
    print('list_for_M_Y_minus_sigma_2', list_for_M_Y_minus_sigma_2)

    # Построим графики
    fig_snr = plt.figure()
    plt.plot(list_for_SNR_x_2, list_for_M_x_2, 'r', list_for_SNR_x_2, list_for_M_x_plus_sigma_2, 'g--',
             list_for_SNR_x_2, list_for_M_x_minus_sigma_2, 'b--')
    plt.title('Зависимость Mx(ОШС), Mx+СКО(ОШС) и Mx-СКО(ОШС)')
    plt.ylabel('Mx, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Mx', 'Mx+СКО', 'Mx-СКО'], loc=1)
    fig_snr.savefig('Pic_block2_Mx_snr_sigma_2.png')
    plt.close()

    fig_snr = plt.figure()
    plt.plot(list_for_SNR_s_2, list_for_M_s_2, 'r', list_for_SNR_s_2, list_for_M_s_plus_sigma_2, 'g--',
             list_for_SNR_s_2, list_for_M_s_minus_sigma_2, 'b--')
    plt.title('Зависимость Ms(ОШС), Ms+СКО(ОШС) и Ms-СКО(ОШС)')
    plt.ylabel('Ms, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Ms', 'Ms+СКО', 'Ms-СКО'], loc=1)
    fig_snr.savefig('Pic_block2_Ms_snr_sigma_2.png')
    plt.close()

    fig_snr = plt.figure()
    plt.plot(list_for_SNR_u_2, list_for_M_u_2, 'r', list_for_SNR_u_2, list_for_M_u_plus_sigma_2, 'g--',
             list_for_SNR_u_2, list_for_M_u_minus_sigma_2, 'b--')
    plt.title('Зависимость Mu(ОШС), Mu+СКО(ОШС) и Mu-СКО(ОШС)')
    plt.ylabel('Mu, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Mu', 'Mu+СКО', 'Mu-СКО'], loc=1)
    fig_snr.savefig('Pic_block2_Mu_snr_sigma_2.png')
    plt.close()

    fig_snr = plt.figure()
    plt.plot(list_for_SNR_Y_2, list_for_M_Y_2, 'r', list_for_SNR_Y_2, list_for_M_Y_plus_sigma_2, 'g--',
             list_for_SNR_Y_2, list_for_M_Y_minus_sigma_2, 'b--')
    plt.title('Зависимость Mpsi(ОШС), Mpsi+СКО(ОШС) и Mpsi-СКО(ОШС)')
    plt.ylabel('Mpsi, усл.ед')
    plt.xlabel('ОШС, усл.ед')
    plt.grid(True)
    plt.legend(['Mpsi', 'Mpsi+СКО', 'Mpsi-СКО'], loc=1)
    fig_snr.savefig('Pic_block2_MY_snr_sigma_2.png')
    plt.close()

    # ____________________________________________  БЛОК 3 ____________________________________________
    # С одинаковой сигмой
    # Создадим списк для списков данных x, s, u, Y, sigma
    list_for_all_x_sigma_const = []
    list_for_all_s_sigma_const = []
    list_for_all_u_sigma_const = []
    list_for_all_Y_sigma_const = []
    for n in range(50):
        e = np.random.normal(0, float(list_for_sigma[5]), 1)
        # формируем список значений шума
        list_for_e = [float(e)]
        # формируем список значений кол-ва товаров на складе
        list_for_x = [float(x)]
        # формируем список значений величины спроса
        list_for_s = [float(s)]
        # формируем список значений объема поставок
        list_for_u = [float(u)]
        # формируем список значений макропеременной
        list_for_Y = [float(Y)]
        for t in range(1, 100):
            # получаем значение спроса в момент времени t и добавляем его в список
            s_t = a * list_for_s[t - 1] + b
            list_for_s.append(float(s_t))
            # получаем новое значение шума и добавляем его в список
            e_t = np.random.normal(0, float(list_for_sigma[5]), 1)
            list_for_e.append(float(e_t))
            # получаем новое значение кол-ва товаров на складе в момент времени t  и добавляем его в список
            x_t = list_for_x[t - 1] + list_for_u[t - 1] + c * list_for_e[t - 1] + e_t - s_t
            list_for_x.append(float(x_t))
            # получем значение макропеременной и добавляем его в список
            Y_t = x_t - x_
            list_for_Y.append(float(Y_t))
            # получаем момент спроса в t+1
            s_t_plus_1 = a * s_t + b
            # получим значение управления по методу акар
            u_a = (w + c) * (-Y_t) + x_ + c * w * list_for_Y[t - 1] + s_t_plus_1 - x_t

            if u_a < Umin:
                # получаем объём поставок в момент времени t
                u_t = 0
                list_for_u.append(float(u_t))
            elif u_a < Umax:
                u_t = u_a
                list_for_u.append(float(u_t))
            else:
                u_t = Umax
                list_for_u.append(float(u_t))
        # добавляем полученные данные в массив с массивами
        list_for_all_x_sigma_const.append(list_for_x)
        list_for_all_s_sigma_const.append(list_for_s)
        list_for_all_u_sigma_const.append(list_for_u)
        list_for_all_Y_sigma_const.append(list_for_Y)
        print('list_for_x_sigma_const', list_for_x)
        print('list_for_s_sigma_const', list_for_s)
        print('list_for_u_sigma_const', list_for_u)
        print('list_for_Y_sigma_const', list_for_Y)

    # #Рисуем графики
    list_for_t_const = []
    for t in range(100):
        list_for_t_const.append(t)

    for t in range(11):
        fig = plt.figure()
        plt.plot(list_for_t_const, list_for_all_x_sigma_const[t], 'ro')
        plt.title('Зависимость x(t)')
        plt.ylabel('x, усл.ед')
        plt.xlabel('t, усл.ед')
        plt.grid(True)
        plt.legend(['x'], loc=1)
        fig.savefig('Pic_block3_' + str(t + 1) + '_for_x_t_sigma_const.png')
        plt.close()
        fig_1 = plt.figure()
        plt.plot(list_for_t_const, list_for_all_s_sigma_const[t], 'ro')
        plt.title('Зависимость s(t)')
        plt.ylabel('s, усл.ед')
        plt.xlabel('t, усл.ед')
        plt.grid(True)
        plt.legend(['s'], loc=1)
        # plt.show()
        fig_1.savefig('Pic_block3_' + str(t + 1) + '_for_s_t_sigma_const.png')
        plt.close()
        fig_2 = plt.figure()
        plt.plot(list_for_t_const, list_for_all_u_sigma_const[t], 'ro')
        plt.title('Зависимость u(t)')
        plt.ylabel('u, усл.ед')
        plt.xlabel('t, усл.ед')
        plt.grid(True)
        plt.legend(['u'], loc=1)
        # plt.show()
        fig_2.savefig('Pic_block3_' + str(t + 1) + '_for_u_t_sigma_const.png')
        plt.close()
        fig_2 = plt.figure()
        plt.plot(list_for_t_const, list_for_all_Y_sigma_const[t], 'ro')
        plt.title('Зависимость psi(t)')
        plt.ylabel('psi, усл.ед')
        plt.xlabel('t, усл.ед')
        plt.grid(True)
        plt.legend(['psi'], loc=1)
        # plt.show()
        fig_2.savefig('Pic_block3_' + str(t + 1) + '_for_Y_t_sigma_const.png')
        plt.close()

    # Поиск оценок на временном промежутке
    # формируем спсисок для найденных оценок мат ожиданий
    list_for_M_x_sigma_const = find_m_t(list_for_all_x_sigma_const)
    list_for_M_s_sigma_const = find_m_t(list_for_all_s_sigma_const)
    list_for_M_u_sigma_const = find_m_t(list_for_all_u_sigma_const)
    list_for_M_Y_sigma_const = find_m_t(list_for_all_Y_sigma_const)
    print('M_x_sigma_const', list_for_M_x_sigma_const)
    print('M_s_sigma_const', list_for_M_s_sigma_const)
    print('M_u_sigma_const', list_for_M_u_sigma_const)
    print('M_Y_sigma_const', list_for_M_Y_sigma_const)

    # формируем список для найденных дисперсий
    list_for_D_x_sigma_const = find_d_t(list_for_all_x_sigma_const, list_for_M_x_sigma_const)
    list_for_D_s_sigma_const = find_d_t(list_for_all_s_sigma_const, list_for_M_s_sigma_const)
    list_for_D_u_sigma_const = find_d_t(list_for_all_u_sigma_const, list_for_M_u_sigma_const)
    list_for_D_Y_sigma_const = find_d_t(list_for_all_Y_sigma_const, list_for_M_Y_sigma_const)
    print('D_x_sigma_const', list_for_D_x_sigma_const)
    print('D_s_sigma_const', list_for_D_s_sigma_const)
    print('D_u_sigma_const', list_for_D_u_sigma_const)
    print('D_Y_sigma_const', list_for_D_Y_sigma_const)

    # формируем список для найденных СКО
    list_for_sigma_x_sigma_const = find_sigma_t(list_for_D_x_sigma_const)
    list_for_sigma_s_sigma_const = find_sigma_t(list_for_D_s_sigma_const)
    list_for_sigma_u_sigma_const = find_sigma_t(list_for_D_u_sigma_const)
    list_for_sigma_Y_sigma_const = find_sigma_t(list_for_D_Y_sigma_const)
    print('sigma_x_sigma_const', list_for_sigma_x_sigma_const)
    print('sigma_s_sigma_const', list_for_sigma_s_sigma_const)
    print('sigma_u_sigma_const', list_for_sigma_u_sigma_const)
    print('sigma_Y_sigma_const', list_for_sigma_Y_sigma_const)

    list_for_M_x_minus_sigma_const = find_M_minus_sigma(list_for_M_x_sigma_const, list_for_sigma_x_sigma_const)
    list_for_M_x_plus_sigma_const = find_M_plus_sigma(list_for_M_x_sigma_const, list_for_sigma_x_sigma_const)
    list_for_M_s_minus_sigma_const = find_M_minus_sigma(list_for_M_s_sigma_const, list_for_sigma_s_sigma_const)
    list_for_M_s_plus_sigma_const = find_M_plus_sigma(list_for_M_s_sigma_const, list_for_sigma_s_sigma_const)
    list_for_M_u_minus_sigma_const = find_M_minus_sigma(list_for_M_u_sigma_const, list_for_sigma_u_sigma_const)
    list_for_M_u_plus_sigma_const = find_M_plus_sigma(list_for_M_u_sigma_const, list_for_sigma_u_sigma_const)
    list_for_M_Y_minus_sigma_const = find_M_minus_sigma(list_for_M_Y_sigma_const, list_for_sigma_Y_sigma_const)
    list_for_M_Y_plus_sigma_const = find_M_plus_sigma(list_for_M_Y_sigma_const, list_for_sigma_Y_sigma_const)

    print('list_for_M_x_plus_sigma_const', list_for_M_x_plus_sigma_const)
    print('list_for_M_x_minus_sigma_const', list_for_M_x_minus_sigma_const)
    print('list_for_M_s_plus_sigma_const', list_for_M_s_plus_sigma_const)
    print('list_for_M_s_minus_sigma_const', list_for_M_s_minus_sigma_const)
    print('list_for_M_u_plus_sigma_const', list_for_M_u_plus_sigma_const)
    print('list_for_M_u_minus_sigma_const', list_for_M_u_minus_sigma_const)
    print('list_for_M_Y_plus_sigma_const', list_for_M_Y_plus_sigma_const)
    print('list_for_M_Y_minus_sigma_const', list_for_M_Y_minus_sigma_const)

    # Рисуем графики
    list_for_T = []
    for T in range(50):
        list_for_T.append(T)
    fig_snr = plt.figure()

    plt.plot(list_for_T, list_for_M_x_sigma_const, 'r', list_for_T, list_for_M_x_plus_sigma_const, 'g--', list_for_T,
             list_for_M_x_minus_sigma_const, 'b--')
    plt.title('Mx(t),  Mx+СКО(t) и Mx-СКО(t) по выборке')
    plt.ylabel('Mx, усл.ед')
    plt.xlabel('t, усл.ед')
    plt.grid(True)
    plt.legend(['Mx', 'Mx+СКО', 'Mx-СКО'], loc=1)
    fig_snr.savefig('Pic_block3_Mx_t_sigma_sigma_const.png')

    fig_snr = plt.figure()
    plt.plot(list_for_T, list_for_M_s_sigma_const, 'r', list_for_T, list_for_M_s_plus_sigma_const, 'g--', list_for_T,
             list_for_M_s_minus_sigma_const, 'b--')
    plt.title('Ms(t),  Ms+СКО(t) и Ms-СКО(t) по выборке')
    plt.ylabel('Ms, усл.ед')
    plt.xlabel('t, усл.ед')
    plt.grid(True)
    plt.legend(['Ms', 'Ms+СКО', 'Ms-СКО'], loc=1)
    fig_snr.savefig('Pic_block3_Ms_t_sigma_sigma_const.png')

    fig_snr = plt.figure()
    plt.plot(list_for_T, list_for_M_u_sigma_const, 'r', list_for_T, list_for_M_u_plus_sigma_const, 'g--', list_for_T,
             list_for_M_u_minus_sigma_const, 'b--')
    plt.title('Mu(t),  Mu+СКО(t) и Mu-СКО(t) по выборке')
    plt.ylabel('Mu, усл.ед')
    plt.xlabel('t, усл.ед')
    plt.grid(True)
    plt.legend(['Mu', 'Mu+СКО', 'Mu-СКО'], loc=1)
    fig_snr.savefig('Pic_block3_Mu_t_sigma_sigma_const.png')

    fig_snr = plt.figure()
    plt.plot(list_for_T, list_for_M_Y_sigma_const, 'r', list_for_T, list_for_M_Y_plus_sigma_const, 'g--', list_for_T,
             list_for_M_Y_minus_sigma_const, 'b--')
    plt.title('Mpsi(t),  Mpsi+СКО(t) и Mpsi-СКО(t) по выборке')
    plt.ylabel('Mpsi, усл.ед')
    plt.xlabel('t, усл.ед')
    plt.grid(True)
    plt.legend(['Mpsi', 'Mpsi+СКО', 'Mpsi-СКО'], loc=1)
    fig_snr.savefig('Pic_block3_MY_t_sigma_sigma_const.png')

    # Поиск оценок по ансамблю
    # формируем спсисок для найденных оценок мат ожиданий

    list_for_M_x_ans = find_M_ans(list_for_all_x_sigma_const)
    list_for_M_s_ans = find_M_ans(list_for_all_s_sigma_const)
    list_for_M_u_ans = find_M_ans(list_for_all_u_sigma_const)
    list_for_M_Y_ans = find_M_ans(list_for_all_Y_sigma_const)

    print('M_x_ans', list_for_M_x_ans)
    print('M_s_ans', list_for_M_s_ans)
    print('M_u_ans', list_for_M_u_ans)
    print('M_Y_ans', list_for_M_Y_ans)

    # формируем список для найденных дисперсий по ансамблю
    list_for_D_x_ans = find_D_ans(list_for_all_x_sigma_const, list_for_M_x_ans)
    list_for_D_s_ans = find_D_ans(list_for_all_s_sigma_const, list_for_M_s_ans)
    list_for_D_u_ans = find_D_ans(list_for_all_u_sigma_const, list_for_M_u_ans)
    list_for_D_Y_ans = find_D_ans(list_for_all_Y_sigma_const, list_for_M_Y_ans)
    print('D_x_ans', list_for_D_x_ans)
    print('D_s_ans', list_for_D_s_ans)
    print('D_u_ans', list_for_D_u_ans)
    print('D_Y_ans', list_for_D_Y_ans)

    # формируем список для найденных СКО по ансамблю
    list_for_sigma_x_ans = find_sigma_t(list_for_D_x_ans)
    list_for_sigma_s_ans = find_sigma_t(list_for_D_s_ans)
    list_for_sigma_u_ans = find_sigma_t(list_for_D_u_ans)
    list_for_sigma_Y_ans = find_sigma_t(list_for_D_Y_ans)
    print('sigma_x_ans', list_for_sigma_x_ans)
    print('sigma_s_ans', list_for_sigma_s_ans)
    print('sigma_u_ans', list_for_sigma_u_ans)
    print('sigma_Y_ans', list_for_sigma_Y_ans)

    list_for_M_x_minus_sigma_ans = find_M_minus_sigma(list_for_M_x_ans, list_for_sigma_x_ans)
    list_for_M_x_plus_sigma_ans = find_M_plus_sigma(list_for_M_x_ans, list_for_sigma_x_ans)
    list_for_M_s_minus_sigma_ans = find_M_minus_sigma(list_for_M_s_ans, list_for_sigma_s_ans)
    list_for_M_s_plus_sigma_ans = find_M_plus_sigma(list_for_M_s_ans, list_for_sigma_s_ans)
    list_for_M_u_minus_sigma_ans = find_M_minus_sigma(list_for_M_u_ans, list_for_sigma_u_ans)
    list_for_M_u_plus_sigma_ans = find_M_plus_sigma(list_for_M_u_ans, list_for_sigma_u_ans)
    list_for_M_Y_minus_sigma_ans = find_M_minus_sigma(list_for_M_Y_ans, list_for_sigma_Y_ans)
    list_for_M_Y_plus_sigma_ans = find_M_plus_sigma(list_for_M_Y_ans, list_for_sigma_Y_ans)

    print('list_for_M_x_plus_sigma_ans', list_for_M_x_plus_sigma_ans)
    print('list_for_M_x_minus_sigma_ans', list_for_M_x_minus_sigma_ans)
    print('list_for_M_s_plus_sigma_ans', list_for_M_s_plus_sigma_ans)
    print('list_for_M_s_minus_sigma_ans', list_for_M_s_minus_sigma_ans)
    print('list_for_M_u_plus_sigma_ans', list_for_M_u_plus_sigma_ans)
    print('list_for_M_u_minus_sigma_ans', list_for_M_u_minus_sigma_ans)
    print('list_for_M_Y_plus_sigma_ans', list_for_M_Y_plus_sigma_ans)
    print('list_for_M_Y_minus_sigma_ans', list_for_M_Y_minus_sigma_ans)

    # Рисуем графики
    list_for_T_ans = []
    for T in range(100):
        list_for_T_ans.append(T)
    fig_snr = plt.figure()

    plt.plot(list_for_T_ans, list_for_M_x_ans, 'r', list_for_T_ans, list_for_M_x_plus_sigma_ans, 'g--', list_for_T_ans,
             list_for_M_x_minus_sigma_ans, 'b--')
    plt.title('Mx(t),  Mx+СКО(t) и Mx-СКО(t) по ансамблю')
    plt.ylabel('Mx, усл.ед')
    plt.xlabel('t, усл.ед')
    plt.grid(True)
    plt.legend(['Mx', 'Mx+СКО', 'Mx-СКО'], loc=1)
    fig_snr.savefig('Pic_block3_Mx_ans_sigma_sigma_const.png')

    fig_snr = plt.figure()
    plt.plot(list_for_T_ans, list_for_M_s_ans, 'r', list_for_T_ans, list_for_M_s_plus_sigma_ans, 'g--', list_for_T_ans,
             list_for_M_s_minus_sigma_ans, 'b--')
    plt.title('Ms(t),  Ms+СКО(t) и Ms-СКО(t) по ансамблю')
    plt.ylabel('Ms, усл.ед')
    plt.xlabel('t, усл.ед')
    plt.grid(True)
    plt.legend(['Ms', 'Ms+СКО', 'Ms-СКО'], loc=1)
    fig_snr.savefig('Pic_block3_Ms_ans_sigma_sigma_const.png')

    fig_snr = plt.figure()
    plt.plot(list_for_T_ans, list_for_M_u_ans, 'r', list_for_T_ans, list_for_M_u_plus_sigma_ans, 'g--', list_for_T_ans,
             list_for_M_u_minus_sigma_ans, 'b--')
    plt.title('Mu(t),  Mu+СКО(t) и Mu-СКО(t) по ансамблю')
    plt.ylabel('Mu, усл.ед')
    plt.xlabel('t, усл.ед')
    plt.grid(True)
    plt.legend(['Mu', 'Mu+СКО', 'Mu-СКО'], loc=1)
    fig_snr.savefig('Pic_block3_Mu_ans_sigma_sigma_const.png')

    fig_snr = plt.figure()
    plt.plot(list_for_T_ans, list_for_M_Y_ans, 'r', list_for_T_ans, list_for_M_Y_plus_sigma_ans, 'g--', list_for_T_ans,
             list_for_M_Y_minus_sigma_ans, 'b--')
    plt.title('Mpsi(t),  Mpsi+СКО(t) и Mpsi-СКО(t) по ансамблю')
    plt.ylabel('Mpsi, усл.ед')
    plt.xlabel('t, усл.ед')
    plt.grid(True)
    plt.legend(['Mpsi', 'Mpsi+СКО', 'Mpsi-СКО'], loc=1)
    fig_snr.savefig('Pic_block3_MY_ans_sigma_sigma_const.png')

    # формируем список для энергии
    list_for_energy_u_sigma_const = find_energy_u(list_for_all_u_sigma_const)
    print('energy_u_sigma_const', list_for_energy_u_sigma_const)

    # Рисуем график энергии
    fig_snr = plt.figure()
    plt.plot(list_for_T, list_for_energy_u_sigma_const, color="red")
    plt.title('Зависимость Eu(t)')
    plt.ylabel('Eu, усл.ед')
    plt.xlabel('t, усл.ед')
    plt.grid(True)
    plt.legend(['Eu'], loc=1)
    fig_snr.savefig('Pic_block3_E_u_sigma_const.png')
    plt.close()

    # # формируем список для энергии по ансамблю
    # list_for_energy_u_ans_sigma_const = []
    # for i in range (list_for_all_u_sigma_const[0]):
    #     sum_an = 0
    #     for j in range(len(list_for_all_u_sigma_const)):
    #         sum_an += list_for_all_u_sigma_const[j][i]**2
    #     list_for_energy_u_ans_sigma_const.append(sum_an/len(list_for_all_u_sigma_const))
    # print('energy_u_ans_sigma_const', list_for_energy_u_ans_sigma_const)
    #
    # # Рисуем график энергии
    # fig_snr = plt.figure()
    # plt.plot(list_for_T_ans, list_for_energy_u_ans_sigma_const, color="red")
    # plt.title('Зависимость Eu_ans_sigma_const')
    # plt.ylabel('Eu, усл.ед')
    # plt.xlabel('ans, усл.ед')
    # plt.grid(True)
    # plt.legend(['Eu_sigma_const'], loc=1)
    # fig_snr.savefig('Pic_block3_E_u_sigma_const.png')
    # plt.close()

    # Выводим таблицу
    print(
        ' ___________________________________________________________________________________________________________________')
    print(
        '|      sigma      |          psi(11)          |          Mpsi          |          Eu          |          EuA          |')
    print(
        '|___________________________________________________________________________________________________________________|')
    print('|      ', round(list_for_sigma[0], 2), '      |          ', round(list_for_all_Y[0][99], 2),
          '          |       ', round(list_for_M_Y[0], 2), '       |       ', round(list_for_energy_u[0], 2),
          '       |          ', round(list_for_energy_u_2[0], 2))
    print(
        '|___________________________________________________________________________________________________________________|')
    print('|      ', round(list_for_sigma[1], 2), '     |          ', round(list_for_all_Y[1][99], 2),
          '          |       ', round(list_for_M_Y[1], 2), '       |       ', round(list_for_energy_u[1], 2),
          '       |          ', round(list_for_energy_u_2[1], 2))
    print(
        '|___________________________________________________________________________________________________________________|')
    print('|      ', round(list_for_sigma[2], 2), '     |          ', round(list_for_all_Y[2][99], 2),
          '          |       ', round(list_for_M_Y[2], 2), '       |       ', round(list_for_energy_u[2], 2),
          '       |          ', round(list_for_energy_u_2[2], 2))
    print(
        '|___________________________________________________________________________________________________________________|')
    print('|      ', round(list_for_sigma[3], 2), '     |          ', round(list_for_all_Y[3][99], 2),
          '          |       ', round(list_for_M_Y[3], 2), '       |       ', round(list_for_energy_u[3], 2),
          '       |          ', round(list_for_energy_u_2[3], 2))
    print(
        '|___________________________________________________________________________________________________________________|')
    print('|      ', round(list_for_sigma[4], 2), '    |          ', round(list_for_all_Y[4][99], 2),
          '          |       ', round(list_for_M_Y[4], 2), '       |       ', round(list_for_energy_u[4], 2),
          '       |          ', round(list_for_energy_u_2[4], 2))
    print(
        '|___________________________________________________________________________________________________________________|')
    print('|      ', round(list_for_sigma[5], 2), '     |          ', round(list_for_all_Y[5][99], 2),
          '          |       ', round(list_for_M_Y[5], 2), '       |       ', round(list_for_energy_u[5], 2),
          '       |          ', round(list_for_energy_u_2[5], 2))
    print(
        '|___________________________________________________________________________________________________________________|')
    print('|      ', round(list_for_sigma[6], 2), '    |          ', round(list_for_all_Y[6][99], 2),
          '          |       ', round(list_for_M_Y[6], 2), '       |       ', round(list_for_energy_u[6], 2),
          '       |          ', round(list_for_energy_u_2[6], 2))
    print(
        '|___________________________________________________________________________________________________________________|')
    print('|      ', round(list_for_sigma[7], 2), '    |          ', round(list_for_all_Y[7][99], 2),
          '          |       ', round(list_for_M_Y[7], 2), '       |       ', round(list_for_energy_u[7], 2),
          '       |          ', round(list_for_energy_u_2[7], 2))
    print(
        '|___________________________________________________________________________________________________________________|')
    print('|      ', round(list_for_sigma[8], 2), '    |          ', round(list_for_all_Y[8][99], 2),
          '          |       ', round(list_for_M_Y[8], 2), '       |       ', round(list_for_energy_u[8], 2),
          '       |          ', round(list_for_energy_u_2[8], 2))
    print(
        '|___________________________________________________________________________________________________________________|')
    print('|      ', round(list_for_sigma[9], 2), '    |          ', round(list_for_all_Y[9][99], 2),
          '          |       ', round(list_for_M_Y[9], 2), '       |       ', round(list_for_energy_u[9], 2),
          '       |          ', round(list_for_energy_u_2[9], 2))
    print(
        '|___________________________________________________________________________________________________________________|')
    print('|      ', round(list_for_sigma[10], 2), '     |          ', round(list_for_all_Y[10][99], 2),
          '          |       ', round(list_for_M_Y[10], 2), '       |       ', round(list_for_energy_u[10], 2),
          '       |          ', round(list_for_energy_u_2[10], 2))
    print(
        '|___________________________________________________________________________________________________________________|')
    print('len_list_psi', len(list_for_all_Y[0]))
    # Запись данных в файл
    f = open('table.txt', 'w')
    f.write(
        ' ___________________________________________________________________________________________________________________\n')
    f.write(
        '|      sigma      |          psi(11)          |          MY          |          Eu          |          EuA          |\n')
    f.write(
        '|___________________________________________________________________________________________________________________|\n')
    f.write('|      ')
    f.write(str(round(list_for_sigma[0], 2)))
    f.write('      |          ')
    f.write(str(round(list_for_all_Y[0][99], 2)))
    f.write('          |       ')
    f.write(str(round(list_for_M_Y[0], 2)))
    f.write('       |       ')
    f.write(str(round(list_for_energy_u[0], 2)))
    f.write('       |          ')
    f.write(str(round(list_for_energy_u_2[0], 2)))
    f.write(
        '\n|___________________________________________________________________________________________________________________|\n')
    f.write('|      ')
    f.write(str(round(list_for_sigma[1], 2)))
    f.write('     |          ')
    f.write(str(round(list_for_all_Y[1][99], 2)))
    f.write('          |       ')
    f.write(str(round(list_for_M_Y[1], 2)))
    f.write('       |       ')
    f.write(str(round(list_for_energy_u[1], 2)))
    f.write('       |          ')
    f.write(str(round(list_for_energy_u_2[1], 2)))
    f.write(
        '\n|___________________________________________________________________________________________________________________|\n')
    f.write('|      ')
    f.write(str(round(list_for_sigma[2], 2)))
    f.write('     |          ')
    f.write(str(round(list_for_all_Y[2][99], 2)))
    f.write('          |       ')
    f.write(str(round(list_for_M_Y[2], 2)))
    f.write('       |       ')
    f.write(str(round(list_for_energy_u[2], 2)))
    f.write('       |          ')
    f.write(str(round(list_for_energy_u_2[2], 2)))
    f.write(
        '\n|___________________________________________________________________________________________________________________|\n')
    f.write('|      ')
    f.write(str(round(list_for_sigma[3], 2)))
    f.write('     |          ')
    f.write(str(round(list_for_all_Y[3][99], 2)))
    f.write('          |       ')
    f.write(str(round(list_for_M_Y[3], 2)))
    f.write('       |       ')
    f.write(str(round(list_for_energy_u[3], 2)))
    f.write('       |          ')
    f.write(str(round(list_for_energy_u_2[3], 2)))
    f.write(
        '\n|___________________________________________________________________________________________________________________|\n')
    f.write('|      ')
    f.write(str(round(list_for_sigma[4], 2)))
    f.write('    |          ')
    f.write(str(round(list_for_all_Y[4][99], 2)))
    f.write('          |       ')
    f.write(str(round(list_for_M_Y[4], 2)))
    f.write('       |       ')
    f.write(str(round(list_for_energy_u[4], 2)))
    f.write('       |          ')
    f.write(str(round(list_for_energy_u_2[4], 2)))
    f.write(
        '\n|___________________________________________________________________________________________________________________|\n')
    f.write('|      ')
    f.write(str(round(list_for_sigma[5], 2)))
    f.write('     |          ')
    f.write(str(round(list_for_all_Y[5][99], 2)))
    f.write('          |       ')
    f.write(str(round(list_for_M_Y[5], 2)))
    f.write('       |       ')
    f.write(str(round(list_for_energy_u[5], 2)))
    f.write('       |          ')
    f.write(str(round(list_for_energy_u_2[5], 2)))
    f.write(
        '\n|___________________________________________________________________________________________________________________|\n')
    f.write('|      ')
    f.write(str(round(list_for_sigma[6], 2)))
    f.write('    |          ')
    f.write(str(round(list_for_all_Y[6][99], 2)))
    f.write('          |       ')
    f.write(str(round(list_for_M_Y[6], 2)))
    f.write('       |       ')
    f.write(str(round(list_for_energy_u[6], 2)))
    f.write('       |          ')
    f.write(str(round(list_for_energy_u_2[6], 2)))
    f.write(
        '\n|___________________________________________________________________________________________________________________|\n')
    f.write('|      ')
    f.write(str(round(list_for_sigma[7], 2)))
    f.write('    |          ')
    f.write(str(round(list_for_all_Y[7][99], 2)))
    f.write('          |       ')
    f.write(str(round(list_for_M_Y[7], 2)))
    f.write('       |       ')
    f.write(str(round(list_for_energy_u[7], 2)))
    f.write('       |          ')
    f.write(str(round(list_for_energy_u_2[7], 2)))
    f.write(
        '\n|___________________________________________________________________________________________________________________|\n')
    f.write('|      ')
    f.write(str(round(list_for_sigma[8], 2)))
    f.write('    |          ')
    f.write(str(round(list_for_all_Y[8][99], 2)))
    f.write('          |       ')
    f.write(str(round(list_for_M_Y[8], 2)))
    f.write('       |       ')
    f.write(str(round(list_for_energy_u[8], 2)))
    f.write('       |          ')
    f.write(str(round(list_for_energy_u_2[8], 2)))
    f.write(
        '\n|___________________________________________________________________________________________________________________|\n')
    f.write('|      ')
    f.write(str(round(list_for_sigma[9], 2)))
    f.write('    |          ')
    f.write(str(round(list_for_all_Y[9][99], 2)))
    f.write('          |       ')
    f.write(str(round(list_for_M_Y[9], 2)))
    f.write('       |       ')
    f.write(str(round(list_for_energy_u[9], 2)))
    f.write('       |          ')
    f.write(str(round(list_for_energy_u_2[9], 2)))
    f.write(
        '\n|___________________________________________________________________________________________________________________|\n')
    f.write('|      ')
    f.write(str(round(list_for_sigma[10], 2)))
    f.write('     |          ')
    f.write(str(round(list_for_all_Y[10][99], 2)))
    f.write('          |       ')
    f.write(str(round(list_for_M_Y[10], 2)))
    f.write('       |       ')
    f.write(str(round(list_for_energy_u[10], 2)))
    f.write('       |          ')
    f.write(str(round(list_for_energy_u_2[10], 2)))
    f.write(
        '\n|___________________________________________________________________________________________________________________|\n')
    f.close()

    # ____________________________________________  БЛОК 4 ____________________________________________
    # Создадим списк для списков данных x, s, u, Y, sigma
    list_for_all_x_omega = []
    list_for_all_s_omega = []
    list_for_all_u_omega = []
    list_for_all_Y_omega = []

    list_for_omega = [0.01, 0.6, 0.99]
    for n in range(3):
        # значение шума в 0 момент времени
        e = np.random.normal(0, float(list_for_sigma[5]), 1)
        # формируем список значений шума
        list_for_e = [float(e)]
        # формируем список значений кол-ва товаров на складе
        list_for_x = [float(x)]
        # формируем список значений величины спроса
        list_for_s = [float(s)]
        # формируем список значений объема поставок
        list_for_u = [float(u)]
        # формируем список значений макропеременной
        list_for_Y = [float(Y)]
        for t in range(1, 100):
            # получаем значение спроса в момент времени t и добавляем его в список
            s_t = a * list_for_s[t - 1] + b
            list_for_s.append(float(s_t))
            # получаем новое значение шума и добавляем его в список
            e_t = np.random.normal(0, float(list_for_sigma[5]), 1)
            list_for_e.append(float(e_t))
            # получаем новое значение кол-ва товаров на складе в момент времени t  и добавляем его в список
            x_t = list_for_x[t - 1] + list_for_u[t - 1] + c * list_for_e[t - 1] + e_t - s_t
            list_for_x.append(float(x_t))
            # получем значение макропеременной и добавляем его в список
            Y_t = x_t - x_
            list_for_Y.append(float(Y_t))
            # получаем момент спроса в t+1
            s_t_plus_1 = a * s_t + b
            # получим значение управления по методу акар
            u_a = (list_for_omega[n] + c) * (-Y_t) + x_ + c * list_for_omega[n] * list_for_Y[t - 1] + s_t_plus_1 - x_t

            if u_a < Umin:
                # получаем объём поставок в момент времени t
                u_t = 0
                list_for_u.append(float(u_t))
            elif u_a < Umax:
                u_t = u_a
                list_for_u.append(float(u_t))
            else:
                u_t = Umax
                list_for_u.append(float(u_t))
        # добавляем полученные данные в массив с массивами
        list_for_all_x_omega.append(list_for_x)
        list_for_all_s_omega.append(list_for_s)
        list_for_all_u_omega.append(list_for_u)
        list_for_all_Y_omega.append(list_for_Y)
        # # Выводим зачения на экран
        # print('x:  ', list_for_x)
        # print('s:  ', list_for_s)
        # print('u:  ', list_for_u)
        # print('Y:  ', list_for_Y)

        # #Рисуем графики
    list_for_t_omega = []
    for num in range(len(list_for_all_x_omega[0])):
        list_for_t_omega.append(num)

    fig = plt.figure()
    plt.plot(list_for_t_omega, list_for_all_x_omega[0], 'm', list_for_t_omega, list_for_all_x_omega[1], 'k',
             list_for_t_omega, list_for_all_x_omega[2], 'y')
    plt.title('Зависимость x(t) при разном значении omega')
    plt.ylabel('x, усл.ед')
    plt.xlabel('t, усл.ед')
    plt.grid(True)
    plt.legend(['x при omega = 0,01', 'x при omega = 0,6', 'x при omega = 0,99'], loc=1)
    fig.savefig('Pic_block4_for_x_t_omega.png')
    plt.close()
    fig_1 = plt.figure()
    plt.plot(list_for_t_omega, list_for_all_s_omega[0], 'm', list_for_t_omega, list_for_all_s_omega[1], 'k',
             list_for_t_omega, list_for_all_s_omega[2], 'y')
    plt.title('Зависимость s(t) при разном значении omega')
    plt.ylabel('s, усл.ед')
    plt.xlabel('t, усл.ед')
    plt.grid(True)
    plt.legend(['s при omega = 0,01', 's при omega = 0,6', 's при omega = 0,99'], loc=1)
    # plt.show()
    fig_1.savefig('Pic_block4_for_s_t_omega.png')
    plt.close()
    fig_2 = plt.figure()
    plt.plot(list_for_t_omega, list_for_all_u_omega[0], 'm', list_for_t_omega, list_for_all_u_omega[1], 'k',
             list_for_t_omega, list_for_all_u_omega[2], 'y')
    plt.title('Зависимость u(t) при разном значении omega')
    plt.ylabel('u, усл.ед')
    plt.xlabel('t, усл.ед')
    plt.grid(True)
    plt.legend(['u при omega = 0,01', 'u при omega = 0,6', 'u при omega = 0,99'], loc=1)
    # plt.show()
    fig_2.savefig('Pic_block4_for_u_t_omega.png')
    plt.close()
    fig_2 = plt.figure()
    plt.plot(list_for_t_omega, list_for_all_Y_omega[0], 'm', list_for_t_omega, list_for_all_Y_omega[1], 'k',
             list_for_t_omega, list_for_all_Y_omega[2], 'y')
    plt.title('Зависимость psi(t) при разном значении omega')
    plt.ylabel('psi, усл.ед')
    plt.xlabel('t, усл.ед')
    plt.grid(True)
    plt.legend(['psi при omega = 0,01', 'psi при omega = 0,6', 'psi при omega = 0,99'], loc=1)
    # plt.show()
    fig_2.savefig('Pic_block4_for_Y_t_omega.png')
    plt.close()

    # ____________________________________________  БЛОК 5 ____________________________________________
    # Создадим списк для списков данных x, s, u, Y, sigma
    list_for_all_x_nach_zn = []
    list_for_all_s_nach_zn = []
    list_for_all_u_nach_zn = []
    list_for_all_Y_nach_zn = []

    list_for_xo = [100, 160, 250]
    list_for_so = [1, 5, 10]
    # list_for_uo = [0.01, 0.6, 0.99]
    for n in range(3):
        # значение шума в 0 момент времени
        e = np.random.normal(0, float(list_for_sigma[5]), 1)
        # формируем список значений шума
        list_for_e = [float(e)]
        # формируем список значений кол-ва товаров на складе
        list_for_x = [float(list_for_xo[n])]
        # формируем список значений величины спроса
        list_for_s = [float(list_for_so[n])]
        # формируем список значений объема поставок
        list_for_u = [float(u)]
        # формируем список значений макропеременной
        list_for_Y = [float(Y)]
        for t in range(1, 100):
            # получаем значение спроса в момент времени t и добавляем его в список
            s_t = a * list_for_s[t - 1] + b
            list_for_s.append(float(s_t))
            # получаем новое значение шума и добавляем его в список
            e_t = np.random.normal(0, float(list_for_sigma[5]), 1)
            list_for_e.append(float(e_t))
            # получаем новое значение кол-ва товаров на складе в момент времени t  и добавляем его в список
            x_t = list_for_x[t - 1] + list_for_u[t - 1] + c * list_for_e[t - 1] + e_t - s_t
            list_for_x.append(float(x_t))
            # получем значение макропеременной и добавляем его в список
            Y_t = x_t - x_
            list_for_Y.append(float(Y_t))
            # получаем момент спроса в t+1
            s_t_plus_1 = a * s_t + b
            # получим значение управления по методу акар
            u_a = (w + c) * (-Y_t) + x_ + c * w * list_for_Y[t - 1] + s_t_plus_1 - x_t

            if u_a < Umin:
                # получаем объём поставок в момент времени t
                u_t = 0
                list_for_u.append(float(u_t))
            elif u_a < Umax:
                u_t = u_a
                list_for_u.append(float(u_t))
            else:
                u_t = Umax
                list_for_u.append(float(u_t))
        # добавляем полученные данные в массив с массивами
        list_for_all_x_nach_zn.append(list_for_x)
        list_for_all_s_nach_zn.append(list_for_s)
        list_for_all_u_nach_zn.append(list_for_u)
        list_for_all_Y_nach_zn.append(list_for_Y)
        # # Выводим зачения на экран
        # print('x:  ', list_for_x)
        # print('s:  ', list_for_s)
        # print('u:  ', list_for_u)
        # print('Y:  ', list_for_Y)

        # #Рисуем графики
    list_for_t_omega = []
    for num in range(len(list_for_all_x_nach_zn[0])):
        list_for_t_omega.append(num)

    fig = plt.figure()
    plt.plot(list_for_t_omega, list_for_all_x_nach_zn[0], 'm', list_for_t_omega, list_for_all_x_nach_zn[1], 'k',
             list_for_t_omega, list_for_all_x_nach_zn[2], 'y')
    plt.title('Зависимость x(t) при разных начальных значениях')
    plt.ylabel('x')
    plt.xlabel('t')
    plt.grid(True)
    plt.legend(['x при x0=100, s0=1', 'x при x0=160, s0=5', 'x при x0=250, s0=10'], loc=1)
    fig.savefig('Pic_block5_for_x_t_nach_zn.png')
    plt.close()
    fig_1 = plt.figure()
    plt.plot(list_for_t_omega, list_for_all_s_nach_zn[0], 'm', list_for_t_omega, list_for_all_s_nach_zn[1], 'k',
             list_for_t_omega, list_for_all_s_nach_zn[2], 'y')
    plt.title('Зависимость s(t) при разных начальных значениях')
    plt.ylabel('s')
    plt.xlabel('t')
    plt.grid(True)
    plt.legend(['s при x0=100, s0=1', 's при x0=160, s0=5', 's при x0=250, s0=10'], loc=1)
    # plt.show()
    fig_1.savefig('Pic_block5_for_s_t_nach_zn.png')
    plt.close()
    fig_2 = plt.figure()
    plt.plot(list_for_t_omega, list_for_all_u_nach_zn[0], 'm', list_for_t_omega, list_for_all_u_nach_zn[1], 'k',
             list_for_t_omega, list_for_all_u_nach_zn[2], 'y')
    plt.title('Зависимость u(t) при разных начальных значениях')
    plt.ylabel('u')
    plt.xlabel('t')
    plt.grid(True)
    plt.legend(['u при x0=100, s0=1', 'u при x0=160, s0=5', 'u при x0=250, s0=10'], loc=1)
    # plt.show()
    fig_2.savefig('Pic_block5_for_u_t_nach_zn.png')
    plt.close()
    fig_2 = plt.figure()
    plt.plot(list_for_t_omega, list_for_all_Y_nach_zn[0], 'm', list_for_t_omega, list_for_all_Y_nach_zn[1], 'k',
             list_for_t_omega, list_for_all_Y_nach_zn[2], 'y')
    plt.title('Зависимость psi(t) при разных начальных значениях')
    plt.ylabel('psi')
    plt.xlabel('t')
    plt.grid(True)
    plt.legend(['psi при x0=100, s0=1', 'psi при x0=160, s0=5', 'psi при x0=250, s0=10'], loc=1)
    # plt.show()
    fig_2.savefig('Pic_block5_for_Y_t_nach_zn.png')
    plt.close()






#Присваиваем значения введенные пользователем переменным
def on_click():
    a = form.for_a.text()
    b = form.for_b.text()
    c = form.for_c.text()
    w = form.for_w.text()
    x_ = form.for_x_.text()
    Umin = form.for_Umin.text()
    Umax = form.for_Umax.text()
    s = form.for_s0.text()
    x = form.for_x0.text()
    u = form.for_u0.text()
    sigma_const = form.for_sigma.text()
    print_perem(float(a), float(b), float(c), float(w), float(x_), float(Umin), float(Umax), float(s), float(x), float(u), float(sigma_const))
    QMessageBox.information(window, "Вычисления окончены!", "Проверьте папку", QMessageBox.Ok)








if __name__ == '__main__':

    print(os.path.realpath(__file__))
    dirname, filename = os.path.split(os.path.realpath(__file__))
    print(dirname)
    Form, Window = uic.loadUiType(dirname + "\\diplom.ui")

    app = QApplication(sys.argv)
    window = Window()
    form = Form()
    form.setupUi(window)
    window.show()

    form.btn_count.clicked.connect(on_click)



    sys.exit(app.exec_())



