from matplotlib import pyplot as plt
import numpy as np


plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

name = ['纯动态规划', '动态规划+回溯（1条）', '动态规划+回溯（全部）', '纯回溯']
m_1 = [6.38, 5.62, 249.25, 364.50]
m_2 = [10.12, 11.00, 19583.12, np.nan]
m_3 = [34.50, 33.38, np.nan, np.nan]
m_4 = [127.75, 137.88, np.nan, np.nan]
m_5 = [2988.88, 3198.50, np.nan, np.nan]
m_6 = [11831.75, 13221.75, np.nan, np.nan]

plt.figure(figsize=(16, 9), dpi=100)
y_pos = np.arange(len(name))

plt.barh(name, m_1, color='steelblue', height=0.5)
plt.title("数据规模为10", fontsize=18)
plt.xlabel("运行时间 (ms)", fontsize=18)
plt.yticks(y_pos, name, fontsize=16, rotation=45)
# plt.xscale('log')

plt.show()
