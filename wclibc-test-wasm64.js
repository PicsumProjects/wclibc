async function createModule() {
  let file = (await fetch("./wclibc-test-wasm64.wasm"));
  module = WebAssembly.instantiateStreaming(file);
};

let module = null; 
const canvas = document.querySelector("#canvas");
const ctx = canvas.getContext("2d");
const button = document.querySelector("#button");
const offscreencanv = new OffscreenCanvas(canvas.width, canvas.height);
const octx = offscreencanv.getContext("2d");
const img = document.querySelector("#img");

async function blurWASM(data, radius) {
  if(!module) await createModule();
  let dataPtr = module.instance.exports.doMalloc(data.width * data.height * 4);
  let memData = new Uint8Array(module.instance.exports.memory.buffer, dataPtr, data.width * data.height * 4);
  memData.set(data);
  let resultPtr = module..instance.exports.blurImage(memData, data.width, data.height, radius);
  module.instance.exports.doFree(dataPtr);
  let data = (new Uint8Array(module.instance.exports.memory.buffer, resultPtr, data.width * data.height * 4)).slice(0);
  module.instance.exports.dodoFree(resultPtr);
};

async function blurcanv(radius = 5) {
  octx.drawImage(img, 0, 0);
  let data = await blurWASM(octx.getImageData(0, 0, img.width, img.height), radius);
  ctx.putImageData(data);
};

button.addEventListener("click", blurcanv);
