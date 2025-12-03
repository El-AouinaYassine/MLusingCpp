import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# --- Fake dataset ---
np.random.seed(0)
X = np.linspace(0, 10, 50)
y = 3*X + 5 + np.random.randn(50)*3   # true line: y = 3x + 5

# --- Parameters for training ---
w = 0
b = 0
lr = 0.01  # learning rate

# --- Figure ---
fig, ax = plt.subplots()
ax.scatter(X, y, color="blue", label="Data")
line, = ax.plot([], [], color="red", linewidth=2)
ax.set_xlim(0, 10)
ax.set_ylim(min(y)-5, max(y)+5)
ax.set_title("Linear Regression Training Animation (1 FPS)")

# --- Gradient Descent Step ---
def train_step(w, b):
    y_hat = w*X + b
    dw = np.mean((y_hat - y) * X)
    db = np.mean(y_hat - y)
    w -= lr * dw
    b -= lr * db
    return w, b

# --- Animation Function ---
def update(frame):
    global w, b
    w, b = train_step(w, b)

    # Update regression line
    line.set_data(X, w*X + b)
    ax.set_xlabel(f"Iteration: {frame} | w={w:.2f}, b={b:.2f}")
    return line,

# --- Create animation @ 1 FPS ---
ani = FuncAnimation(fig, update, frames=60, interval=1000, repeat=False)

plt.show()
