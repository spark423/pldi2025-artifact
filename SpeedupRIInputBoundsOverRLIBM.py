import matplotlib
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np

matplotlib.rcParams['pdf.fonttype'] = 42
matplotlib.rcParams['ps.fonttype'] = 42

labels = ["sin", "sinh", "sinpi", "cos", "cosh", "cospi", "log", "log2", "log10", "exp", "exp2", "exp10", "avg."]

ri_input_bounds_time = []
rlibm_time = []

file_name = ["sinf.txt", "sinhf.txt", "sinpif.txt", "cosf.txt", "coshf.txt", "cospif.txt", "logf.txt", "log2f.txt", "log10f.txt", "expf.txt", "exp2f.txt", "exp10f.txt"]

for i in range(0, len(labels)-1) :
    fp = open("overhead/"+file_name[i], "r")
    lines = fp.read().splitlines()
    ri_input_bounds_time.append(float(lines[1]))
    fp.close()
ri_input_bounds_time.append(sum(ri_input_bounds_time))
for i in range(0, len(labels)-1) :
    fp = open("overhead/"+file_name[i], "r")
    lines = fp.read().splitlines()
    rlibm_time.append(float(lines[2]))
    fp.close()
rlibm_time.append(sum(rlibm_time))

for i in range(0, len(labels)) :
    speedup.append(round(((rlibm_time[i] / ri_input_bounds_time[i])-1)*100))

print(speedup)

x = np.arange(len(labels))  # the label locations
width = 0.45  # the width of the bars

fig, ax = plt.subplots()
fig.gca().spines['top'].set_visible(False)
ax.set_ylim(0, 100)
rects = ax.bar(x, speedup2, width, color="tab:green", label="Rounding-invariant Input Bounds", zorder = 100)

for bar in rects1:
   height = bar.get_height()
   ax.annotate(f'{height}', xy=(bar.get_x() + bar.get_width() / 2, height), xytext=(0, 0),
   textcoords="offset points", ha='center', va='bottom')

# Add some text for labels, title and custom x-axis tick labels, etc.
#plt.xticks(rotation=15, ha="right", rotation_mode="anchor")
ax.set_ylabel('Speedup in Percent')
ax.set_title('Speedup of New Prototype over RLIBM Implementations', y=0, pad=-25, verticalalignment="top")
ax.set_xticks(x)
ax.set_xticklabels(labels)
ax.legend(bbox_to_anchor=(-0.1, 0.98, 1.1, 0.2), loc="upper right", ncol=2)

fig.tight_layout()

plt.gcf().set_size_inches(10, 4)
plt.savefig('rounding_invariant_input_bounds_over_rlibm.png', bbox_inches='tight', pad_inches = -0.001)

