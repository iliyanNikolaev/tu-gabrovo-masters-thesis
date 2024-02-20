const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');

const port = new SerialPort('/dev/ttyUSB0', { baudRate: 9600 });
const parser = new Readline();

port.pipe(parser);

parser.on('data', (data) => {
  try {
    const sensorData = JSON.parse(data);
    console.log(sensorData);
  } catch (error) {
    console.error(error);
  }
});