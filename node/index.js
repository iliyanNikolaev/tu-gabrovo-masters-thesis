//@ts-check
const express = require('express');
const configExpress = require('./config/express');
const configRoutes = require('./config/routes');

start();

function start() {
    const app = express();
    configExpress(app);
    configRoutes(app);
    app.listen(3000, () => console.log('Server started on port 3000'));
}