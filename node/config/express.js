//@ts-check
const express = require('express');
const expressLayouts = require('express-ejs-layouts');
const cors = require('cors');

function configExpress(app) {
    app.use(cors());
    app.use(express.json());
    app.use(express.static('public'));
    app.use(expressLayouts);
    app.set('view engine', 'ejs');
}

module.exports = configExpress;