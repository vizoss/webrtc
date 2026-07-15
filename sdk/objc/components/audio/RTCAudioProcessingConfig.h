/*
 * Copyright 2023 LiveKit
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <Foundation/Foundation.h>
#import "RTCMacros.h"

NS_ASSUME_NONNULL_BEGIN

RTC_OBJC_EXPORT
@interface RTC_OBJC_TYPE (RTCAudioProcessingConfig) : NSObject 

@property(nonatomic, assign) BOOL isEchoCancellationEnabled;
@property(nonatomic, assign) BOOL isEchoCancellationMobileMode;

@property(nonatomic, assign) BOOL isNoiseSuppressionEnabled;
@property(nonatomic, assign) BOOL isHighpassFilterEnabled;

@property(nonatomic, assign) BOOL isAutoGainControl1Enabled;
@property(nonatomic, assign) BOOL isAutoGainControl2Enabled;

// Whether APM processes capture/render audio as multi-channel internally
// (rather than downmixing to mono first) -- this gates whether
// capturePostProcessingDelegate/renderPreProcessingDelegate see more than 1
// channel, independent of whether the AudioDeviceModule itself captures/plays
// out in stereo (see RTCAudioDeviceModule.stereoModeEnabled). Both must be
// enabled to get real multi-channel audio all the way through a custom
// processing delegate.
@property(nonatomic, assign) BOOL isMultiChannelCaptureEnabled;
@property(nonatomic, assign) BOOL isMultiChannelRenderEnabled;

@end

NS_ASSUME_NONNULL_END
