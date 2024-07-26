Link to original repo: https://github.com/csukuangfj/kaldi-native-fbank

1. install the dependencies
```bash
$ npm install
```

2. compile the addon
```bash
$ npm run build
```

3. install the package in the app
```bash
cd app
npm install ../native/diarization/kaldiFbank
```

4. rebuild for Electron
```bash
npm install electron-rebuild
npx electron-rebuild
```

5. run in the app
```js
const kaldi = require('kaldi-fbank')

feats = kaldi.fbank(waveform)
// { data: Float32Array, dims: [num_frames, num_bins] }
```