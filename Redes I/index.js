const express = require("express");
const app = express();
const http = require("http");
const server = http.createServer(app);
const { Server } = require("socket.io");
const io = new Server(server);

// const port = new SerialPort({
//   path: "COM3",
//   baudRate: 9600,
// });

app.get("/", (req, res) => {
  res.sendFile(__dirname + "/index.html");
});

io.on("connection", (socket) => {
  console.log("a user connected");
});

io.on("connection", (socket) => {
  socket.on("chat message", (msg) => {
    io.emit("chat message", msg);
    // port.write(msg, function (err) {
    //   if (err) {
    //     return console.log("Error on write: ", err.message);
    //   }
    // });
  });
});

// port.on("data", function (data) {
//   io.emit("chat message", data);
// });

server.listen(3000, () => {
  console.log("listening on *:3000");
});
