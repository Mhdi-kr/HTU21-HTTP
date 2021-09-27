# HTU21-HTTP

## Description
Measure temperature and humidity using HTU21, post it as a HTTP request to a Node.js server.

## Prerequisites

1. Install arduino IDE
2. Make sure you have `esp8266` boards installed in the `board manager` tab - [see instructions](https://github.com/esp8266/Arduino#installing-with-boards-manager)
3. Clone this repo and install the `HTU21.ino` file on your arduino board

## Wiring

please refer to your manufacturer website

## Why

I wanted to post weather measurments to a Node.js server, hook it up with promethues and use it as data source for my grafana instance on my raspberry pi.

```javascript
const express = require("express");
const client = require("prom-client");

const temperatureGauge = new client.Gauge({
    name: "temperature",
    help: "room temperature",
});
const humidityGauge = new client.Gauge({
    name: "humidity",
    help: "room humidity",
});

const PORT = 9100;
const app = express();

app.use(express.json());

app.get("/metrics", (req, res) => {
    res.status(200).set("Content-Type", "text/plain");
    res.end(client.register.metrics());
});

app.post("/weather", (req, res) => {
    console.log(req.body);
    temperatureGauge.set(req.body.temperature);
    humidityGauge.set(req.body.humidity);
    res.sendStatus(200);
});

app.listen(port, () => {
    console.log(`Example app listening at http://localhost:${port}`);
});

```
This program will spin up an HTTP web server with exposed `POST` and `GET` endpoinst for both arduino to send data and promethues to query statistics from it.
