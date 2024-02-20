const appController = require("../controller/appController");

function configRoutes(app) {
    app.use(appController);
}

module.exports = configRoutes;