#include <M5Cardputer.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include "M5GFX.h"

const char* ssid = "Brainwave Generator";
const char* password = NULL;  // Open network (no password)

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

String values[3] = {"", "", ""};
String lastValues[3] = {"", "", ""};
int fieldIndex = 0;
bool isPlaying = false;
unsigned long lastInputTime = 0; // For debouncing keyboard input
const unsigned long debounceDelay = 200; // Debounce delay in milliseconds

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    // Handle WebSocket event
}

void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setTextSize(2.0);
    M5Cardputer.Display.fillScreen(BLACK);

    // Initialize display with labels
    M5Cardputer.Display.setCursor(0, 0);
    M5Cardputer.Display.println("F1: " + values[0]);
    M5Cardputer.Display.println("F2: " + values[1]);
    M5Cardputer.Display.println("Pulse: " + values[2]);

    WiFi.softAP(ssid, password);
    server.on("/", HTTP_GET, handleRoot);
    server.begin();
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}

void loop() {
    server.handleClient();
    webSocket.loop();

    M5Cardputer.update();
    bool needsUpdate = false;

    unsigned long currentTime = millis();
    if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed() && (currentTime - lastInputTime > debounceDelay)) {
        lastInputTime = currentTime; // Update last input time for debounce check
        Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

        if (!status.word.empty()) {
            for (char c : status.word) {
                values[fieldIndex] += c;
                needsUpdate = true;
            }
        }
        if (status.del && values[fieldIndex].length() > 0) {
            values[fieldIndex].remove(values[fieldIndex].length() - 1);
            needsUpdate = true;
        }
        if (status.enter) {
            fieldIndex = (fieldIndex + 1) % 3;
            needsUpdate = true;
        }

        for (int i = 0; i < 3; i++) {
            if (values[i] != lastValues[i]) {
                lastValues[i] = values[i];
                needsUpdate = true;
            }
        }
    }

    if (M5Cardputer.BtnA.wasPressed()) {
        isPlaying = !isPlaying;
        String message = isPlaying ? "play," : "stop,";
        message += values[0] + "," + values[1] + "," + values[2];
        webSocket.broadcastTXT(message);
        needsUpdate = true;
    }

    if (needsUpdate) {
        M5Cardputer.Display.fillScreen(BLACK);
        M5Cardputer.Display.setCursor(0, 0);
        M5Cardputer.Display.println("F1: " + values[0]);
        M5Cardputer.Display.println("F2: " + values[1]);
        M5Cardputer.Display.println("Pulse: " + values[2]);
    }
}

void handleRoot() {
    String html = 
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "<title>Brainwave Generator</title>"
    "<style>"
    "  body { text-align: center; font-family: Terminal; margin-top: 50px; background-color: black; color: white; }"
    "  canvas {"
    "    border:1px solid #000;"
    "    margin-top: 10px;"
    "  }"
    "</style>"
    "<script>"
    "var audioCtx = new (window.AudioContext || window.webkitAudioContext)();"
    "var oscillator1, oscillator2, gainNode, lfo;"
    "var analyser = audioCtx.createAnalyser();"
    "var canvas, ctx;"
    "var originalFreq1, originalFreq2, maxVariance = 10, changeInterval = 5000;"
    "var isPlaying = false;"

    "function startSound(frequency1, frequency2, pulseRate) {"
    "  stopSound();"
    "  oscillator1 = audioCtx.createOscillator();"
    "  oscillator2 = audioCtx.createOscillator();"
    "  gainNode = audioCtx.createGain();"
    "  lfo = audioCtx.createOscillator();"
    "  oscillator1.type = 'sine';"
    "  oscillator2.type = 'sine';"
    "  originalFreq1 = frequency1;"
    "  originalFreq2 = frequency2;"
    "  oscillator1.frequency.setValueAtTime(frequency1, audioCtx.currentTime);"
    "  oscillator2.frequency.setValueAtTime(frequency2, audioCtx.currentTime);"
    "  lfo.frequency.setValueAtTime(pulseRate, audioCtx.currentTime);"
    "  lfo.connect(gainNode.gain);"
    "  oscillator1.connect(gainNode);"
    "  oscillator2.connect(gainNode);"
    "  gainNode.connect(analyser);"
    "  analyser.connect(audioCtx.destination);"
    "  oscillator1.start();"
    "  oscillator2.start();"
    "  lfo.start();"
    "  isPlaying = true;"

    // Periodically modify the frequencies slightly
    "  setInterval(function() {"
    "    if(isPlaying) {"
    "      oscillator1.frequency.setValueAtTime("
    "        originalFreq1 + (Math.random() * 2 * maxVariance - maxVariance),"
    "        audioCtx.currentTime"
    "      );"
    "      oscillator2.frequency.setValueAtTime("
    "        originalFreq2 + (Math.random() * 2 * maxVariance - maxVariance),"
    "        audioCtx.currentTime"
    "      );"
    "    }"
    "  }, changeInterval);"

    "  draw();"
    "}"

    "function draw() {"
    "  if(!isPlaying) return;"
    "  requestAnimationFrame(draw);"
    "  var bufferLength = analyser.frequencyBinCount;"
    "  var dataArray = new Uint8Array(bufferLength);"
    "  analyser.getByteTimeDomainData(dataArray);"
    "  ctx.fillStyle = 'rgb(0, 0, 0)';"
    "  ctx.fillRect(0, 0, canvas.width, canvas.height);"
    "  ctx.lineWidth = 2;"
    "  ctx.strokeStyle = 'rgb(255, 255, 255)';"
    "  ctx.beginPath();"
    "  var sliceWidth = canvas.width * 1.0 / bufferLength;"
    "  var x = 0;"
    "  for(var i = 0; i < bufferLength; i++) {"
    "    var v = dataArray[i] / 128.0;"
    "    var y = v * canvas.height/2;"
    "    if(i === 0) {"
    "      ctx.moveTo(x, y);"
    "    } else {"
    "      ctx.lineTo(x, y);"
    "    }"
    "    x += sliceWidth;"
    "  }"
    "  ctx.lineTo(canvas.width, canvas.height/2);"
    "  ctx.stroke();"
    "}"

    "function stopSound() {"
    "  if (oscillator1) {"
    "    oscillator1.stop();"
    "    oscillator1.disconnect();"
    "  }"
    "  if (oscillator2) {"
    "    oscillator2.stop();"
    "    oscillator2.disconnect();"
    "  }"
    "  if (lfo) {"
    "    lfo.stop();"
    "    lfo.disconnect();"
    "  }"
    "  if (gainNode) {"
    "    gainNode.disconnect();"
    "  }"
    "  isPlaying = false;"
    "}"

    "function togglePlay() {"
    "  if(isPlaying) {"
    "    stopSound();"
    "    isPlaying = false;"
    "  } else {"
    "    startSound(parseFloat(values[0]), parseFloat(values[1]), parseFloat(values[2]));"
    "    isPlaying = true;"
    "  }"
    "}"

    "document.addEventListener('DOMContentLoaded', function() {"
    "  canvas = document.getElementById('oscilloscope');"
    "  ctx = canvas.getContext('2d');"
    "  document.getElementById('playButton').click();"
    "});"

    "var ws = new WebSocket('ws://' + window.location.hostname + ':81/');"
    "ws.onmessage = function(event) {"
    "  var parts = event.data.split(',');"
    "  if(parts[0] === 'play') {"
    "    startSound(parseFloat(parts[1]), parseFloat(parts[2]), parseFloat(parts[3]));"
    "  } else if(parts[0] === 'stop') {"
    "    stopSound();"
    "  }"
    "};"
    "</script>"
    "</head>"
    "<body>"
    "<h1>Brainwave Generator</h1>"
    "<p>Adjust the frequencies and pulse on the device.</p>"
    "<button id='playButton' onclick='togglePlay()'>Play</button>"    
    "<br/>" 
    "<canvas id='oscilloscope' width='640' height='480'></canvas>"   
    "</body>"
    "</html>";

    server.send(200, "text/html", html);
}