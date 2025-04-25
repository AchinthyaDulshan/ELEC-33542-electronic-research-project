#🦟 Ultrasonic Mosquito Repellent – Final Year Research Project

**University of Kelaniya – Department of Electronics**
**Course Code: ELEC 33542 – Electronic Research Project**

##📘 Project Overview
As part of our final year as undergraduates in the Department of Electronics at the University of Kelaniya, we were tasked with developing innovative electronic solutions to address real-world problems. Our chosen project was focused on creating an **ultrasonic mosquito repellent** using high-frequency sound waves.

##🧠 Project Idea
Mosquitoes are not only annoying but also responsible for spreading diseases such as dengue and malaria. While chemical repellents are widely used, they often have health and environmental concerns. Our goal was to develop a **chemical-free, electronic mosquito repellent** that emits ultrasonic sound waves to deter mosquitoes.

##🛠️ How It Works
-Mosquitoes are known to respond to ultrasonic frequencies in the range of **20kHz to 60kHz**.
-We aimed to generate high-frequency sine waves using a **microcontroller** and emit them using **piezoelectric discs**.
-The microcontroller was used to:
-Generate precise ultrasonic waveforms
-Switch between multiple frequencies during testing

##🧪 Development Process
Throughout the project, we iteratively improved the signal generation mechanism. Initially, we developed custom waveform generation code. However, we faced challenges in precision, frequency range, and waveform stability.

After extensive research and testing, we discovered an **awesome open-source library** on GitHub that perfectly suited our needs:

> [!NOTE]
> 🔗 [esp32-signal-generator](https://github.com/vdeschwb/esp32-signal-generator)
> Developed by: [@vdeschwb](https://github.com/vdeschwb)

This library significantly improved our waveform quality, enabling us to focus on amplifying and testing the signal's effectiveness on mosquitoes.

##⚙️ Tools and Components

-Microcontroller: ESP32 (for signal generation)
-Emitters: Piezoelectric discs to emit ultrasonic waves
-Test Setup: Enclosed containers with live mosquitoes for behavioral observation

##🔍 Results and Observations

-Successfully generated sine waves from 20kHz to 60kHz using ESP32.
-Identified limitations in certain op-amp components when dealing with high-frequency signals.
-Observed changes in mosquito behavior during exposure to specific frequencies (results included in final report).

##📄 Contribution and Learning
This project helped us:
-Understand practical applications of signal processing
-Experiment with hardware limitations and real-world constraints
-Collaborate and adapt open-source tools to academic research

##🤝 Acknowledgements
Special thanks to:
-Our academic supervisors for guidance
-The GitHub open-source community, especially the developer of [esp32-signal-generator](https://github.com/vdeschwb)
-University of Kelaniya – Department of Electronics
