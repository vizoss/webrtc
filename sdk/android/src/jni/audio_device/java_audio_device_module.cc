/*
 *  Copyright (c) 2018 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include <jni.h>

#include <memory>
#include <utility>

#include "api/audio/audio_device.h"
#include "api/audio/audio_device_defines.h"
#include "api/environment/environment.h"
#include "sdk/android/generated_java_audio_jni/JavaAudioDeviceModule_jni.h"
#include "sdk/android/native_api/jni/java_types.h"
#include "sdk/android/src/jni/audio_device/audio_common.h"
#include "sdk/android/src/jni/audio_device/audio_device_module.h"
#include "sdk/android/src/jni/audio_device/audio_record_jni.h"
#include "sdk/android/src/jni/audio_device/audio_track_jni.h"
#include "third_party/jni_zero/jni_zero.h"

namespace webrtc {
namespace jni {

static jlong JNI_JavaAudioDeviceModule_CreateAudioDeviceModule(
    JNIEnv* env,
    const jni_zero::JavaParamRef<jobject>& j_context,
    const jni_zero::JavaParamRef<jobject>& j_audio_manager,
    const jni_zero::JavaParamRef<jobject>& j_webrtc_audio_record,
    const jni_zero::JavaParamRef<jobject>& j_webrtc_audio_track,
    jlong webrtcEnvRef,
    int input_sample_rate,
    int output_sample_rate,
    jboolean j_use_stereo_input,
    jboolean j_use_stereo_output) {
  const Environment& webrtc_env = *reinterpret_cast<Environment*>(webrtcEnvRef);
  AudioParameters input_parameters;
  AudioParameters output_parameters;
  GetAudioParameters(env, j_context, j_audio_manager, input_sample_rate,
                     output_sample_rate, j_use_stereo_input,
                     j_use_stereo_output, &input_parameters,
                     &output_parameters);
  auto audio_input = std::make_unique<AudioRecordJni>(
      env, webrtc_env, input_parameters,
      kHighLatencyModeDelayEstimateInMilliseconds, j_webrtc_audio_record);
  auto audio_output = std::make_unique<AudioTrackJni>(
      env, webrtc_env, output_parameters, j_webrtc_audio_track);
  return NativeToJavaPointer(
      CreateAudioDeviceModuleFromInputAndOutput(
          webrtc_env, AudioDeviceModule::kAndroidJavaAudio, j_use_stereo_input,
          j_use_stereo_output, kHighLatencyModeDelayEstimateInMilliseconds,
          std::move(audio_input), std::move(audio_output))
          .release());
}

static jboolean JNI_JavaAudioDeviceModule_SetStereoMode(
    JNIEnv* env,
    jlong native_audio_device_module,
    jboolean enable) {
  return reinterpret_cast<AudioDeviceModule*>(native_audio_device_module)
             ->SetStereoMode(enable) == 0;
}

static jboolean JNI_JavaAudioDeviceModule_IsStereoModeEnabled(
    JNIEnv* env,
    jlong native_audio_device_module) {
  return reinterpret_cast<AudioDeviceModule*>(native_audio_device_module)
      ->StereoModeEnabled();
}

}  // namespace jni
}  // namespace webrtc
