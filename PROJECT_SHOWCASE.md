# AquaSentinel showcase kit

Use this copy when sharing AquaSentinel outside GitHub. Replace bracketed details with your own information before publishing.

## One-line pitch

AquaSentinel is an IoT and machine-learning system that monitors water quality in real time using ESP32, LoRa, Firebase, and a responsive web dashboard.

## Short portfolio description

AquaSentinel is an end-to-end water-quality monitoring platform built to collect, transmit, analyze, and visualize environmental sensor data. ESP32 nodes transmit readings over LoRa to a Python gateway, where a machine-learning model classifies water conditions and generates treatment and reuse recommendations. Firebase provides real-time synchronization with a responsive dashboard featuring live alerts, multi-location monitoring, sensor trends, mobility detection, and PDF reporting.

**Live demo:** https://watermonitoring-36dcf.web.app

**Source code:** https://github.com/kamalesh-sankaranarayanan/IoT-based-Water-Monitoring

## LinkedIn post

I’m excited to share **AquaSentinel**, an IoT-based smart water-quality monitoring system.

The project connects field sensors to a real-time dashboard through an end-to-end pipeline:

**Sensors → ESP32 → LoRa → Python gateway → Machine Learning → Firebase → Web dashboard**

Key features:

- Real-time pH, turbidity, temperature, TDS, conductivity, gas, distance, and GPS monitoring
- ML-based water-quality classification and treatment recommendations
- Live safety alerts and water-reuse guidance
- Multi-location monitoring and sensor trend charts
- Mobility detection and downloadable PDF reports

Building AquaSentinel helped me combine embedded systems, long-range wireless communication, cloud data, machine learning, and frontend development in one practical solution.

Try it: https://watermonitoring-36dcf.web.app

#IoT #ESP32 #LoRa #MachineLearning #Firebase #WaterQuality #EmbeddedSystems #Python #WebDevelopment #Sustainability

## Devpost or Hackster summary

### Inspiration

Water-quality decisions often depend on manual sampling and delayed laboratory results. AquaSentinel was created to provide continuous, remote visibility into important water parameters and make the readings easier to act on.

### What it does

AquaSentinel collects water-quality and device readings, transmits them over LoRa, analyzes them through a Python gateway and ML model, and publishes the result to Firebase. Operators can view live values, trends, alerts, reuse recommendations, monitoring locations, and system mobility from a responsive dashboard.

### How it was built

- ESP32 boards handle sensing and LoRa transmission.
- A LoRa receiver passes readings to a Python gateway over serial.
- Python applies reuse rules and a trained scikit-learn model.
- Firebase Realtime Database synchronizes the processed readings.
- HTML, CSS, JavaScript, Chart.js, and jsPDF power the dashboard.
- Firebase Hosting serves the production application.

### Challenges

- Maintaining reliable long-range sensor communication
- Normalizing multiple sensor values into one payload
- Combining rule-based thresholds with ML recommendations
- Keeping the dashboard useful across desktop and mobile screens

### What is next

Historical analytics, map-based GPS tracking, authenticated operator roles, offline/PWA support, automated sensor calibration, and broader ML training data.

## Resume bullets

- Developed an end-to-end IoT water-quality monitoring system using ESP32, LoRa, Python, Firebase, and JavaScript.
- Integrated real-time telemetry for 10+ environmental and operational parameters with live alerts and multi-location visualization.
- Applied a scikit-learn model and rule-based analysis to generate water-quality classifications, treatment suggestions, and reuse recommendations.
- Built and deployed a responsive Firebase-hosted dashboard with Chart.js trends and automated PDF reporting.

## Suggested portfolio layout

1. Lead with `screenshots/dashboard-overview.png`.
2. Follow with the problem statement and one-line pitch.
3. Show the architecture from the README.
4. Pair `screenshots/hardware-prototype.jpeg` with a short hardware explanation.
5. Use `screenshots/sensor-analytics.png` to explain ML recommendations.
6. Finish with the live demo, repository link, challenges, and future work.

## GitHub presentation checklist

- Add repository topics: `iot`, `esp32`, `lora`, `water-quality`, `firebase`, `machine-learning`, `python`, `chartjs`, `environmental-monitoring`.
- Set the repository website to `https://watermonitoring-36dcf.web.app`.
- Use `screenshots/dashboard-overview.png` as the repository social preview.
- Pin the repository on your GitHub profile.
- Add a license if you want others to reuse the project.
