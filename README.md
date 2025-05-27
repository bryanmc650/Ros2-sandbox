# Sensor Fusion Sandbox

This is a self-directed engineering project to explore and implement key components of autonomous systems using ROS 2 and C++. It includes working modules for sensor simulation, Kalman filtering, and placeholders for future path planning and control algorithms.

## 🚀 Goals

- Refresh and apply core concepts in:
  - Sensor fusion (Kalman Filter, EKF)
  - State estimation from noisy data
  - Path planning (A*, RRT)
  - Control systems (PID, LQR, MPC)
- Build a clean, modular, and expandable ROS 2 workspace
- Simulate sensor data and implement fusing algorithms in C++
- Lay the groundwork for deploying algorithms on a physical robot or drone

## 📦 Project Structure
src/
├── sensor_sim/ # Simulates IMU and GPS data (with noise)
├── sensor_fusion_core/ # Implements Kalman Filter for position and velocity estimation
├── path_planner/ # (Placeholder) For future A* or sampling-based planners
└── controller_core/ # (Placeholder) For future PID, LQR, or MPC controllers


## ✅ Current Status

- [x] ROS 2 workspace set up and running under WSL
- [x] Simulated IMU and GPS publishers
- [x] Subscribed fusion node logging received messages
- [ ] Kalman Filter implementation in progress
- [ ] Logging and plotting of results
- [ ] Real-time visualization and Gazebo integration

## 🧪 How to Build and Run

```bash
# Source ROS and build the workspace
cd ~/Projects/ros2_ws
source /opt/ros/humble/setup.bash
colcon build
source install/setup.bash

# Run sensor simulation
ros2 run sensor_sim sensor_sim

# In a second terminal
source /opt/ros/humble/setup.bash
source ~/Projects/ros2_ws/install/setup.bash
ros2 run sensor_fusion_core sensor_fusion_core

📈 Roadmap
Implement 1D Kalman Filter with IMU acceleration and GPS position
Output state estimation and compare to ground truth
Add velocity simulation and CSV logging
Extend to 2D fusion (x, y position)
Introduce simple A* path planner
Build PID and LQR controllers
Integrate with a small physical robot or drone
Add Gazebo simulation with sensor plugins

