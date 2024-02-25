const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');
const port = new SerialPort({ path: 'COM7', baudRate: 9600 });
const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));

async function readSerialPortData() {
    return new Promise((res) => {
        parser.on('data', (data) => {
            res(data);
        });
    });
}

module.exports = readSerialPortData;