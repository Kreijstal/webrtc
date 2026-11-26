/*
 *  Copyright (c) 2020 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "modules/desktop_capture/win/desktop_capture_utils.h"

#include <string>

#ifdef _MSC_VER
#include "rtc_base/strings/string_builder.h"
#else
#include <cstdio>
#include <cstdlib>
#endif

namespace webrtc {
namespace desktop_capture {
namespace utils {

// Generates a human-readable string from a COM error.
std::string ComErrorToString(const _com_error& error) {
#ifdef _MSC_VER
  webrtc::StringBuilder string_builder;
  // Use _bstr_t to simplify the wchar to char conversion for ErrorMessage().
  _bstr_t error_message(error.ErrorMessage());
  string_builder.AppendFormat("HRESULT: 0x%08X, Message: %s", error.Error(),
                              static_cast<const char*>(error_message));
  return string_builder.Release();
#else
  char buffer[1024];
  int offset = snprintf(buffer, sizeof(buffer),
                        "HRESULT: 0x%08lX, Message: ", error.Error());
#ifdef _UNICODE
  wcstombs(buffer + offset, error.ErrorMessage(), sizeof(buffer) - offset);
#else
  strcpy(buffer + offset, error.ErrorMessage(), sizeof(buffer) - offset);
#endif
  buffer[sizeof(buffer) - 1] = 0;
  return buffer;
#endif
}

}  // namespace utils
}  // namespace desktop_capture
}  // namespace webrtc
