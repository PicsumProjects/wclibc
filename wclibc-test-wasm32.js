async function createModule() {
  let file = (await fetch("./wclibc-test-wasm32.wasm"));
  module = WebAssembly.instantiateStreaming(file);
};

let module = null; 

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

