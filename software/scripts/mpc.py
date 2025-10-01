import numpy as np
import scipy.optimize
import matplotlib.pyplot as plt

# --- 1. System Model Definition ---
# A simple double integrator model: x_{k+1} = A*x_k + B*u_k
# State x = [position, velocity]'
# Input u = [acceleration]
dt = 0.1  # Time step
A = np.array([[1, dt], [0, 1]])
B = np.array([[0.5 * dt**2], [dt]])
(nx, nu) = B.shape # Number of states and inputs

# --- 2. MPC Configuration ---
N = 10               # Prediction horizon (how many steps to look ahead)
Q = np.diag([10, 1]) # State cost matrix (penalizes deviation of position and velocity)
R = np.diag([0.1])   # Input cost matrix (penalizes high control actions)

# --- 3. MPC Cost Function ---
def mpc_cost_function(u_sequence, x0, xref):
    """
    Calculates the total cost for a given sequence of control inputs.
    
    Args:
        u_sequence (np.array): Flattened array of control inputs over the horizon (N*nu,).
        x0 (np.array): The initial state of the system.
        xref (np.array): The target state (reference).

    Returns:
        float: The total calculated cost.
    """
    cost = 0.0
    x_predicted = np.copy(x0)
    u_sequence = u_sequence.reshape(N, nu) # Reshape to (N, nu)

    # Simulate the system over the prediction horizon
    for i in range(N):
        u_current = u_sequence[i, :]
        # State cost: (x - xref)^T * Q * (x - xref)
        cost += np.sum((x_predicted - xref).T @ Q @ (x_predicted - xref))
        # Input cost: u^T * R * u
        cost += np.sum(u_current.T @ R @ u_current)
        
        # Predict the next state
        x_predicted = A @ x_predicted + B @ u_current
        
    return cost

# --- 4. Simulation Setup ---
sim_time = 10.0  # Total simulation time
n_steps = int(sim_time / dt)

# Initial and reference states
x0 = np.array([0, 0])      # Initial state [position=0, velocity=0]
xref = np.array([10, 0])   # Target state [position=10, velocity=0]

# Arrays to store simulation history
x_history = np.zeros((n_steps + 1, nx))
u_history = np.zeros((n_steps, nu))
x_history[0, :] = x0

# --- 5. Live Plotting Setup ---
plt.ion() # Turn on interactive mode
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8), sharex=True)
fig.suptitle("MPC Live Simulation")

# Position plot
ax1.set_ylabel("Position")
ax1.grid(True)
pos_line, = ax1.plot(0, x0[0], 'bo-', label="Position")
ax1.axhline(y=xref[0], color='r', linestyle='--', label="Position Setpoint")
ax1.legend()

# Velocity plot
ax2.set_ylabel("Velocity")
ax2.set_xlabel("Time (s)")
ax2.grid(True)
vel_line, = ax2.plot(0, x0[1], 'go-', label="Velocity")
ax2.axhline(y=xref[1], color='r', linestyle='--', label="Velocity Setpoint")
ax2.legend()


# --- 6. Main Simulation Loop ---
current_state = np.copy(x0)

for k in range(n_steps):
    # Optimize to find the best control sequence
    u_guess = np.zeros(N * nu) # Initial guess for the optimizer
    
    # The result object contains the optimal control sequence in res.x
    res = scipy.optimize.minimize(
        fun=mpc_cost_function,
        x0=u_guess,
        args=(current_state, xref),
        method='SLSQP'
    )

    # Get the optimal control sequence
    optimal_u_sequence = res.x.reshape(N, nu)
    
    # **Apply only the FIRST control input to the system**
    control_input = optimal_u_sequence[0, :]
    u_history[k, :] = control_input

    # Simulate the system one step forward
    next_state = A @ current_state + B @ control_input
    current_state = next_state
    x_history[k + 1, :] = current_state

    # --- Update the live plot ---
    time_points = np.arange(k + 2) * dt
    
    # Update position data
    pos_line.set_xdata(time_points)
    pos_line.set_ydata(x_history[:k + 2, 0])
    ax1.relim()
    ax1.autoscale_view()
    
    # Update velocity data
    vel_line.set_xdata(time_points)
    vel_line.set_ydata(x_history[:k + 2, 1])
    ax2.relim()
    ax2.autoscale_view()

    # Redraw the canvas
    fig.canvas.draw()
    fig.canvas.flush_events()
    plt.pause(0.01) # Pause to allow plot to update

# Keep the final plot displayed
plt.ioff()
plt.show()

print("Simulation finished.")
