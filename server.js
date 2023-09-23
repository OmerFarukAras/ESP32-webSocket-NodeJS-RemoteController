import robot from "robotjs";

import { WebSocketServer } from "ws";

const wss = new WebSocketServer({ host: "192.168.1.11", port: 8080 });

let cmd = "";

const basicCommands = [
  {
    ID: "200+",
    name: "CLEAR",
    action: function () {
      cmd = "";
      console.log("Cmd exonerated");
    },
  },
  {
    ID: "100+",
    name: "ENTER",
    action: function () {
      robot.keyTap("enter");
    },
  },
  {
    ID: "CH",
    name: "CH",
    action: function () {
      robot.keyToggle("alt", "down");
      robot.keyTap("tab");
      robot.keyToggle("alt", "up");
    },
  },
  {
    ID: "CH-",
    name: "CH-",
    action: function () {
      robot.keyToggle("command", "down");
      robot.keyTap("D");
      robot.keyToggle("command", "up");
    },
  },
  {
    ID: "CH+",
    name: "CH+",
    action: function () {
      robot.keyToggle("alt", "down");
      robot.keyToggle("shift", "down");
      robot.keyTap("tab");
      robot.keyToggle("shift", "up");
      robot.keyToggle("alt", "up");
    },
  },
  {
    ID: ">>",
    name: "NEXT",
    action: function () {
      robot.keyTap("audio_next");
    },
  },
  {
    ID: "<<",
    name: "PREV",
    action: function () {
      robot.keyTap("audio_prev");
    },
  },
  {
    ID: ">||",
    name: "PAUSE",
    action: function () {
      robot.keyTap("audio_pause");
    },
  },
  {
    ID: "+",
    name: "VOLUME_UP",
    action: function () {
      robot.keyTap("audio_vol_up");
      robot.keyTap("audio_vol_up");
      robot.keyTap("audio_vol_up");
      robot.keyTap("audio_vol_up");
      robot.keyTap("audio_vol_up");
    },
  },
  {
    ID: "-",
    name: "VOLUME_DOWN",
    action: function () {
      robot.keyTap("audio_vol_down");
      robot.keyTap("audio_vol_down");
      robot.keyTap("audio_vol_down");
      robot.keyTap("audio_vol_down");
      robot.keyTap("audio_vol_down");
    },
  },
  {
    ID: "EQ",
    name: "EQ",
    action: function () {
      robot.keyTap("audio_mute");
    },
  },
];

const extendedCommands = [
  {
    ID: "1911",
    name: "ALT+TAB",
    action: function () {
      robot.keyToggle("alt", "down");
      robot.keyTap("tab");
      robot.keyToggle("alt", "up");
    },
  },
];

wss.on("connection", function connection(ws) {
  ws.on("error", console.error);
  ws.on("message", function message(data) {
    console.log(data.toString());
    if (data.toString().startsWith("/")) {
      let command = basicCommands.find(
        (command) => command.ID == data.slice(1)
      );
      if (command) {
        console.log(command.name);
        command.action();
      } else {
        cmd += data.toString().replace("/", "");
        if (cmd.length > 4) cmd = cmd.slice(1);
        console.log(cmd);
        command = extendedCommands.find((command) => command.ID == cmd);
        if (command) {
          console.log(command.name);
          command.action();
          cmd = "";
        }
      }
    }
  });

  ws.on("close", function close() {
    console.log("disconnected");
  });
  console.log("connected");
});
