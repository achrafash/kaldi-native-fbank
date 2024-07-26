#include <napi.h> // ignore

#include <iostream>
#include <cstdint>
#include <sstream>
#include <string>

#include "kaldi-native-fbank/csrc/online-feature.h"
#include "kaldi-native-fbank/csrc/feature-fbank.h"
#include "kaldi-native-fbank/csrc/feature-window.h"
#include "kaldi-native-fbank/csrc/mel-computations.h"


Napi::Value Fbank(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if(info.Length() < 1 || !info[0].IsTypedArray()) {
        Napi::TypeError::New(env, "Float32Array expected").ThrowAsJavaScriptException();
        return env.Null();
    }

    knf::FbankOptions opts;
    opts.frame_opts.dither = 0;
    opts.frame_opts.snip_edges = true;
    opts.frame_opts.frame_shift_ms = 10;
    opts.frame_opts.frame_length_ms = 25;
    opts.frame_opts.window_type = "hamming";
    opts.mel_opts.num_bins = 80;
    opts.mel_opts.debug_mel = false;
    knf::OnlineFbank fbank(opts);
    
    Napi::Float32Array input = info[0].As<Napi::Float32Array>();
    const float *waveform = input.Data();
    size_t num_samples = input.ElementLength();

    fbank.AcceptWaveform(16000, waveform, num_samples);

    int32_t num_frames = fbank.NumFramesReady();
    int32_t num_bins = opts.mel_opts.num_bins;
    
    // Create a vector to store all the features
    std::vector<float> all_features;
    all_features.reserve(num_frames * num_bins);
    for (int32_t k = 0; k < num_frames; ++k) {
        const float* frame = fbank.GetFrame(k);
        all_features.insert(all_features.end(), frame, frame + num_bins);
    }

    // Create a new Float32Array to return to JavaScript
    Napi::Float32Array result = Napi::Float32Array::New(env, all_features.size());
    std::copy(all_features.begin(), all_features.end(), result.Data());

  // Create an array for dimensions
    Napi::Array dims = Napi::Array::New(env, 2);
    dims[uint32_t(0)] = Napi::Number::New(env, num_frames);
    dims[uint32_t(1)] = Napi::Number::New(env, num_bins);

    // Create the return object
    Napi::Object returnObject = Napi::Object::New(env);
    returnObject.Set(Napi::String::New(env, "data"), result);
    returnObject.Set(Napi::String::New(env, "dims"), dims);

    return returnObject;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("fbank", Napi::Function::New(env, Fbank));
    return exports;
}

NODE_API_MODULE(fbank, Init)