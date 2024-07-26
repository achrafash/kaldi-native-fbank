{
    "targets": [
        {
            "target_name": "fbank",
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "sources": [
                "addon.cc",
                "kaldi-native-fbank/csrc/feature-functions.cc",
                "kaldi-native-fbank/csrc/mel-computations.cc",
                "kaldi-native-fbank/csrc/whisper-feature.cc",
                "kaldi-native-fbank/csrc/online-feature.cc",
                "kaldi-native-fbank/csrc/feature-window.cc",
                "kaldi-native-fbank/csrc/feature-fbank.cc",
                "kaldi-native-fbank/csrc/feature-mfcc.cc",
                "kaldi-native-fbank/csrc/kaldi-math.cc",
                "kaldi-native-fbank/csrc/fftsg.cc",
                "kaldi-native-fbank/csrc/rfft.cc",
                "kaldi-native-fbank/csrc/log.cc",
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
                ".",
                "kaldi-native-fbank/",
                "kaldi-native-fbank/csrc",
            ],
            "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
            "xcode_settings": {
                "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                "CLANG_CXX_LIBRARY": "libc++",
                "MACOSX_DEPLOYMENT_TARGET": "10.7",
            },
            "msvs_settings": {"VCCLCompilerTool": {"ExceptionHandling": 1}},
            "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"],
        },
    ]
}
