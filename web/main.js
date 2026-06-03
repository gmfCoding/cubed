const canvas = document.getElementById("game");
const ctx = canvas.getContext("2d");
const hud = document.getElementById("hud");

let wasm;
let lastTime = 0;

function resize() {
  const dpr = Math.max(1, Math.min(2, window.devicePixelRatio || 1));
  const w = Math.floor(window.innerWidth * dpr);
  const h = Math.floor(window.innerHeight * dpr);
  if (canvas.width !== w || canvas.height !== h) {
    canvas.width = w;
    canvas.height = h;
    if (wasm) wasm.set_viewport(w, h);
  }
}

function drawGrid(w, h) {
  ctx.strokeStyle = "rgba(255,255,255,0.08)";
  ctx.lineWidth = 1;
  const step = 40;
  for (let x = 0; x < w; x += step) {
    ctx.beginPath();
    ctx.moveTo(x, 0);
    ctx.lineTo(x, h);
    ctx.stroke();
  }
  for (let y = 0; y < h; y += step) {
    ctx.beginPath();
    ctx.moveTo(0, y);
    ctx.lineTo(w, y);
    ctx.stroke();
  }
}

function render() {
  const w = canvas.width;
  const h = canvas.height;
  const px = wasm.get_player_x();
  const py = wasm.get_player_y();
  const angle = wasm.get_player_angle();

  const grad = ctx.createLinearGradient(0, 0, 0, h);
  grad.addColorStop(0, "#20324b");
  grad.addColorStop(1, "#111821");
  ctx.fillStyle = grad;
  ctx.fillRect(0, 0, w, h);

  drawGrid(w, h);

  ctx.save();
  ctx.translate(px, py);
  ctx.rotate(angle);

  ctx.fillStyle = "#ffb84a";
  ctx.fillRect(-14, -14, 28, 28);

  ctx.strokeStyle = "#ffd27f";
  ctx.lineWidth = 3;
  ctx.beginPath();
  ctx.moveTo(0, 0);
  ctx.lineTo(24, 0);
  ctx.stroke();
  ctx.restore();

  hud.textContent =
    "cubed wasm prototype\n" +
    "WASD move, arrows rotate\n" +
    `x=${px.toFixed(1)} y=${py.toFixed(1)} a=${angle.toFixed(2)}`;
}

function frame(ts) {
  if (!lastTime) lastTime = ts;
  const dt = Math.min(0.05, (ts - lastTime) / 1000);
  lastTime = ts;

  resize();
  wasm.update_game(dt);
  render();
  requestAnimationFrame(frame);
}

function mapKeyCode(key) {
  if (key === "w" || key === "W") return 87;
  if (key === "a" || key === "A") return 65;
  if (key === "s" || key === "S") return 83;
  if (key === "d" || key === "D") return 68;
  if (key === "ArrowLeft") return 37;
  if (key === "ArrowRight") return 39;
  return 0;
}

window.addEventListener("keydown", (ev) => {
  const code = mapKeyCode(ev.key);
  if (code) {
    ev.preventDefault();
    wasm.key_down(code);
  }
});

window.addEventListener("keyup", (ev) => {
  const code = mapKeyCode(ev.key);
  if (code) {
    ev.preventDefault();
    wasm.key_up(code);
  }
});

window.addEventListener("resize", resize);

(async () => {
  const response = await fetch("cubed.wasm");
  const bytes = await response.arrayBuffer();
  const result = await WebAssembly.instantiate(bytes, {});
  wasm = result.instance.exports;
  resize();
  wasm.init_game(canvas.width, canvas.height);
  hud.textContent = "running";
  requestAnimationFrame(frame);
})();
