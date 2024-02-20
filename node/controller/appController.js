const readSerialPortData = require('../utils/serial');

const appController = require('express').Router();

appController.get('/', (req, res) => {
    res.render('index');
});

appController.get('/about', (req, res) => {
    res.render('about');
});

appController.get('/read-serial', async (req, res) => {
    const data = await readSerialPortData();
    const [temperature, humidity] = data.split(', ');
    res.json({
        temperature,
        humidity
    });
});

module.exports = appController;