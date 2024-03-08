# BrainWaveGenerator-M5Cardputer

A project utilizing the M5Cardputer and its built-in keyboard to generate brainwave frequencies. The system allows for the input of two distinct frequencies and a pulse rate to modulate the generated tones, which are then played through a web interface.

## Features

- **Input Two Frequencies and Pulse**: Directly input two different frequencies and a pulse rate using the M5Cardputer's built-in keyboard.
- **WebSocket Communication**: Real-time communication between the M5Cardputer and the web client.
- **Audio Generation**: Browser-based audio generation using the Web Audio API.

## Hardware Requirements

- M5Cardputer
- Any Wi-Fi enabled device with a modern web browser for the client-side

## Software Requirements

- Arduino IDE for compiling and uploading the code to the M5Cardputer.
- Any modern web browser (Chrome, Firefox, etc.) to access the generated web interface.

## Setup and Installation

1. **Prepare the M5Cardputer**: Ensure your M5Cardputer is ready and powered on.
2. **Load the Software**: Open the provided Arduino script in the Arduino IDE and upload it to the M5Cardputer.
3. **Connect to Wi-Fi**: The M5Cardputer will create a Wi-Fi access point named "Brainwave Generator." Connect to this network from your client device.
4. **Open the Web Interface**: Open a browser on the client device and go to the IP address of the M5Cardputer, usually `192.168.4.1`.

## Usage

1. **Enter Frequencies and Pulse Rate**: Use the M5Cardputer's built-in keyboard to input the desired frequencies and pulse rate.
2. **Start the Sound**: Press the button on the M5Cardputer to start the sound generation.

## Science-Based Frequency Combinations

Here are some frequency combinations based on known brainwave states. These are intended for use with binaural or monaural beat generators to encourage the brain to "tune in" to a specific state.

### 1. Deep Relaxation
- **Frequency 1:** 100 Hz
- **Frequency 2:** 104 Hz
- **Pulse:** 4 Hz (Theta range)
- **Explanation:** Aims for Theta range to encourage deep relaxation, meditation, and creativity.

### 2. Focus and Concentration
- **Frequency 1:** 200 Hz
- **Frequency 2:** 215 Hz
- **Pulse:** 15 Hz (Beta range)
- **Explanation:** Utilizes Beta range to enhance focus, alertness, and problem-solving.

### 3. Deep Sleep Induction
- **Frequency 1:** 150 Hz
- **Frequency 2:** 154 Hz
- **Pulse:** 4 Hz (Delta range)
- **Explanation:** Delta range is used to induce deep sleep or restfulness.

### 4. Meditation and Mindfulness
- **Frequency 1:** 200 Hz
- **Frequency 2:** 210 Hz
- **Pulse:** 10 Hz (Alpha range)
- **Explanation:** Alpha range to aid in relaxation, calmness, and meditative states.

### 5. Quick Mental Refresh
- **Frequency 1:** 500 Hz
- **Frequency 2:** 520 Hz
- **Pulse:** 20 Hz (Beta range)
- **Explanation:** Beta range for a quick mental refresh during sustained tasks.

### 6. Creativity Boost
- **Frequency 1:** 300 Hz
- **Frequency 2:** 308 Hz
- **Pulse:** 8 Hz (Alpha/Theta border)
- **Explanation:** Border of Alpha and Theta for a mix of relaxation and alert awareness conducive to creativity.

### Notes on Usage
- **Range Considerations:** Although the actual frequencies input are higher, the pulse (difference) falls within the brainwave frequency range intended for specific mental states.
- **Volume and Duration:** Use a comfortable volume and start with shorter periods, adjusting as needed.
- **Consultation:** If using for therapeutic purposes or if you have health concerns, consulting with a healthcare professional is advised.

These combinations can be used as a tool for enhancing relaxation, focus, creativity, or sleep quality, among other states, but they are not a substitute for medical treatment. Results may vary by individual.

## Troubleshooting

(Include troubleshooting steps specifically adapted for the M5Cardputer setup.)

## Contributing

Contributions to the Brainwave Generator project are welcome. Please fork the repository and submit a pull request with your enhancements or fixes.

## License

This project is licensed under the [MIT License](LICENSE).

## Acknowledgements

- Thanks to the M5Stack community for their support and inspiration.
- This project is inspired by the potential benefits of brainwave entrainment and sound therapy for well-being.
