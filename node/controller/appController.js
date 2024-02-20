const appController = require('express').Router();

appController.get('/', (req, res) => {
    res.render('index');
});

appController.get('/about', (req, res) => {
    res.render('about');
});

module.exports = appController;