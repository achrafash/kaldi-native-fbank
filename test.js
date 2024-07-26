const kaldi = require('./build/Release/fbank')

// Create a sample Float32Array (this should be your audio data)
const sampleRate = 16000 // 16 kHz
const duration = 1 // 1 second
const numSamples = sampleRate * duration
const waveform = new Float32Array(numSamples)

// Fill audioData with a simple sine wave as an example
for (let i = 0; i < numSamples; i++) {
  waveform[i] = Math.sin((2 * Math.PI * 440 * i) / sampleRate)
}

// Compute fbank features
const features = kaldi.fbank(waveform)

console.log(features)
