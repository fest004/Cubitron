#import "style.typ": style, serif-text, mono-text, box-text

#show: style

// Title Block
#text(size: 24pt, weight: "bold")[KUBEN]\
#text(size: 18pt, weight: "semibold")[3-Axis Balancing Cube]\
Hardware Revision 1.0 \
#line(length: 100%)

= About The Project
This document outlines the electrical and mechanical architecture for a 15cm³ self-balancing reaction wheel robot. The system utilizes Model Predictive Control (MPC) or Linear Quadratic Regulation (LQR) to handle the coupled dynamics of three orthogonal axes.

#box-text()[
*Specs*
- *Dimensions*: 15cm × 15cm × 15cm
- *Power Source*: 4S LiPo (16.8V Peak)
- *Peak Current*: 12A (4A per motor) 
]

#box-text()[
*Key Components*
- *Compute*: ESP32
- *Motor Driver*: DRV
- *Sensor*: IMU
]

#v(1cm)
#figure(include "figures/rigsketch.typ", caption:[sketch])

#pagebreak()

#{
  set text(font: "Geist", weight: "medium", size: 10pt)
  outline(depth:3, indent: auto)
}

#pagebreak()


= System Architecture
The system is designed around a centralized controller (ESP32-S3) that manages three motor drivers via SPI and PWM. The control loop runs on a dedicated core to ensure real-time performance for the MPC solver.

== High-Level Block Diagram
- *Inputs:* IMU (SPI), Encoders (Quadrature), Battery Voltage (ADC).
- *Processing:* ESP32-S3-WROOM-1 Module.
- *Outputs:* 3x PWM signals (U, V, W) to Gate Drivers.
- *Actuation:* 3x BLDC Motors (Gimbal Type) via DRV8316.

#figure(include "figures/block.typ", caption:[block diagram of the controll circuit])

= Electronics Design
The PCB is a custom 4-layer board designed for high vibration resistance and thermal dissipation.

== Microcontroller Selection
*Component:* **ESP32-S3-WROOM-1-N8R8**
- *Form Factor:* Surface Mount Module (Castellated).
- *Reasoning:* Through-hole headers fail under reaction wheel vibration. The module provides robust mechanical coupling and optimal center of mass.
- *Peripherals Used:* - 3x PCNT (Hardware Encoder Counters)
  - 2x MCPWM (Motor Control PWM)
  - ADC1 (Current Sensing - ADC2 is avoided due to WiFi conflict)

== 3.2. Pin Mapping (ESP32-S3)
*Critical:* Do not route current sensing to ADC2. Do not pull strapping pins (GPIO 0, 45, 46) high during boot.

#figure(
  table(
    columns: (auto, auto, auto, 1fr),
    inset: 5pt,
    align: horizon,
    [*Function*], [*Signal*], [*GPIO*], [*Note*],
    
    table.cell(rowspan: 3)[*Motor X*], "PWM U/V/W", "14, 15, 16", "MCPWM Unit 0",
    "Current Sense", "1", "ADC1_CH0 (Strict requirement)",
    "Encoder A/B", "38, 39", "PCNT Unit 0",

    table.cell(rowspan: 3)[*Motor Y*], "PWM U/V/W", "17, 18, 21", "MCPWM Unit 0",
    "Current Sense", "2", "ADC1_CH1",
    "Encoder A/B", "40, 41", "PCNT Unit 1",

    table.cell(rowspan: 3)[*Motor Z*], "PWM U/V/W", "35, 36, 37", "MCPWM Unit 1",
    "Current Sense", "3", "ADC1_CH2",
    "Encoder A/B", "42, 43", "PCNT Unit 2",

    table.cell(rowspan: 3)[*Shared*], "IMU SPI (SCK/MI/MO)", "12, 13, 11", "LSM6DSO Connection",
    "Driver nSLEEP", "4", "Active High to wake drivers",
    "Battery Sense", "7", "ADC1_CH6 (Voltage Divider)",
  ),
  caption: [Master Pin Assignment Table]
)

== 3.3. Motor Drivers (TI DRV8316)
*Variant:* **DRV8316R** (Hardware) or **DRV8316T** (SPI). SPI is preferred for adjustable gain.
- *Current Sensing:* The chip has internal Current Sense Amplifiers (CSA) but *no internal ADC*.
- *Wiring Requirement:* The `SO1`, `SO2`, `SO3` pins must be routed to the ESP32 ADC pins listed above.
- *Mode:* Operate in **Current Sense Mode** (VREF = 3.3V). Do not use the hardware "Current Limiting Mode" or the torque control will fight the MPC solver.

== 3.4. Power Regulation Strategy
Direct 16.8V to 3.3V conversion is thermally impossible for the ESP32 load.
1.  **Stage 1 (Buck):** TPS54302 converts 16.8V $->$ 5.0V.
2.  **Stage 2 (LDO):** AMS1117-3.3 converts 5.0V $->$ 3.3V (Clean logic power).

= 4. Safety & Protection Circuits
Reaction wheels generate massive regenerative currents when braking. Protection is mandatory.

== 4.1. Reverse Polarity Protection
*Component:* P-Channel MOSFET (e.g., AO4407).
- *Circuit:* Gate to GND, Source to Battery+, Drain to System.
- *Why:* Low voltage drop (\<0.1V) compared to diodes, prevents explosion if battery is plugged in backwards.

== 4.2. Regenerative Braking Clamp
*Passive:* 1000µF 35V Electrolytic Capacitor at the main power entry.
- *Active (Optional):* If voltage > 18V, a comparator triggers an N-FET to dump energy into a $10 Omega$, 50W resistor.

== 4.3. Battery Management (BMS)
*Module:* Generic 4S 20A BMS (HX-4S-A01).
- *Function:* Prevents cell under-voltage (\<3.0V) and short circuits.
- *Placement:* Located between the LiPo battery and the Main PCB.

= 5. Control Theory (MPC Implementation)

== 5.1. State Space Model
The robot is modeled as a coupled system. The state vector $x$ contains 9 elements:
$ x = [ theta_x, theta_y, theta_z, dot(theta)_x, dot(theta)_y, dot(theta)_z, omega_(w x), omega_(w y), omega_(w z) ]^T $
Where:
- $theta$: Cube orientation angle (Euler or Quaternion error).
- $dot(theta)$: Angular velocity of the cube (Gyro data).
- $omega_w$: Angular velocity of the reaction wheels (Encoder data).

== 5.2. Control Law
We utilize an LQR approach for the balancing loop:
$ u(t) = -K dot x(t) $
Where $K$ is the optimal gain matrix derived from the system physics (Inertia Tensor) and cost matrices $Q$ and $R$.

== 5.3. Software Sandbox (Safety Limits)
To prevent MPC instability (hallucinations) from destroying hardware:
- *Max Tilt:* If $|theta| > 20 degree$, `Disable_Motors()`.
- *Max Current:* Software clamp at 6A per motor.
- *Slew Rate:* Limit $d("Torque")/dif$ to prevent mechanical jerking.

= 6. Bill of Materials (Key Components)

#table(
  columns: (1fr, 1fr, 2fr),
  inset: 8pt,
  [*Component*], [*Part Number*], [*Notes*],
  "MCU Module", "ESP32-S3-WROOM-1", "N8R8 (8MB Flash/PSRAM) recommended.",
  "Motor Driver", "TI DRV8316", "Qty: 3. Requires bottom thermal pad vias.",
  "IMU", "ST LSM6DSO", "SPI Interface. Mount at PCB center.",
  "Buck Converter", "TPS54302", "Steps 16V down to 5V.",
  "Protection FET", "AO4407", "P-Channel MOSFET for reverse polarity.",
  "Bulk Cap", "1000µF 35V", "Low ESR Electrolytic.",
  "Battery", "4S LiPo 650mAh", "High C-rating (45C+).",
)

= 7. Next Steps
1.  **Simulation:** Model the physics in Python/MATLAB to derive the $K$ matrix.
2.  **Schematic Capture:** Implement the pin map in KiCad/EasyEDA.
3.  **PCB Layout:** Focus on thermal vias for DRV8316 and minimizing loop inductance for the capacitors.
