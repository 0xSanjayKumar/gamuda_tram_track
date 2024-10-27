

const esp32IpAddress = "http://192.168.114.245";

function sendCommand(command) {
    fetch(`${esp32IpAddress}/control?command=${command}`)
        .then(response => response.text())
        .then(data => console.log("Response:", data))
        .catch(error => console.error("Error:", error));
}

function submitValue() {
    const value = document.getElementById("valueInput").value;
    fetch(`${esp32IpAddress}/set-value`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ value: parseInt(value) })
    })
        .then(response => response.text())
        .then(data => console.log("Value submitted:", data))
        .catch(error => console.error("Error:", error));
}

function toggleMode() {
    const mode = document.getElementById("modeSwitch").checked ? "automatic" : "manual";
    fetch(`${esp32IpAddress}/toggle-mode?mode=${mode}`)
        .then(response => response.text())
        .then(data => console.log("Mode changed:", data))
        .catch(error => console.error("Error:", error));
}


