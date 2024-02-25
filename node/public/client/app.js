const socket = io();
const display = document.getElementById('display');
const temperatureContainer = document.getElementById('temperature');
const humidityContainer = document.getElementById('humidity');
const co2Container = document.getElementById('co2');
const noiseContainer = document.getElementById('noise');

/**
 * Variables to store current values of temperature, humidity, CO2 levels, noise level, and analog noise value.
 * @type {string[]}
 */
let [temperature, humidity, co2, noise, analogNoiseVal] = ['', '', '', '', '535']; // analogNoiseVal - The threshold point determining whether KY037 is 0 or 1.

/**
 * Event listener for receiving sensor data and updating variables.
 * @param {string} data - Sensor data from serial-port COM7 when the sensor hub is connected in the format: "23.10 °C, 45.20 %, 5.91 ppm, 49.01 - 53.00 dB, 535"
 */
socket.on('sensorHubData', (data) => {
  [temperature, humidity, co2, noise, analogNoiseVal] = data.split(', ');
  updateDisplay(temperature, humidity, co2, noise);
});

function getNoiseVal() {
  return Number(analogNoiseVal);
}

/**
 * Initializes a Plotly chart with the initial noise value.
 */
Plotly.plot('chart', [
  {
    y: [getNoiseVal()],
    type: 'line'
  }
]);

/**
 * Updates the Plotly chart with the latest noise value at regular intervals.
 */
setInterval(() => {
  Plotly.extendTraces('chart', { y: [[getNoiseVal()]] }, [0]);
}, 30);

/**
 * Updates the display of sensor data in the specified container.
 * @param {HTMLElement} container - The HTML container element to update.
 * @param {string} value - The sensor data value to display.
 */
function updateDisplay(temperature, humidity, co2, noise) {
  temperatureContainer.textContent = 'Температура: '+temperature;
  humidityContainer.textContent = 'Влажност на въздуха: '+humidity;
  co2Container.textContent = 'Ниво на въглероден диоксид във въздуха: '+co2;
  noiseContainer.textContent = 'Ниво на шума: '+noise;
}