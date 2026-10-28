// How often to ask the board for the latest status
const REFRESH_MS = 2000;

async function fetchStatus() {
    const response = await fetch('/status');
    return response.json();
}

function render(status) {
    document.getElementById('status').textContent = status.detected ? 'Home' : 'Away';
    document.getElementById('zone').textContent = status.zone;
    document.getElementById('rssi').textContent = status.detected ? status.rssi : '-';
}

async function update() {
    try {
        render(await fetchStatus());
    } catch {
        document.getElementById('status').textContent = 'Board offline';
    }
}

update();
setInterval(update, REFRESH_MS);