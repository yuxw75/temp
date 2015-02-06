/*
 *  Copyright (c) 2012 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "testing/gtest/include/gtest/gtest.h"
#include "webrtc/common_types.h"
#include "webrtc/modules/rtp_rtcp/interface/receive_statistics.h"
#include "webrtc/modules/rtp_rtcp/interface/rtp_header_parser.h"
#include "webrtc/modules/rtp_rtcp/interface/rtp_payload_registry.h"
#include "webrtc/modules/rtp_rtcp/interface/rtp_receiver.h"
#include "webrtc/modules/rtp_rtcp/interface/rtp_rtcp.h"
#include "webrtc/modules/rtp_rtcp/interface/rtp_rtcp_defines.h"
#include "webrtc/system_wrappers/interface/scoped_ptr.h"

namespace webrtc {

// This class sends all its packet straight to the provided RtpRtcp module.
// with optional packet loss.
class LoopBackTransport : public webrtc::Transport {
 public:
  LoopBackTransport()
      : count_(0),
        packet_loss_(0),
        rtp_payload_registry_(NULL),
        rtp_receiver_(NULL),
        rtp_rtcp_module_(NULL) {}
  void SetSendModule(RtpRtcp* rtp_rtcp_module,
                     RTPPayloadRegistry* payload_registry,
                     RtpReceiver* receiver,
                     ReceiveStatistics* receive_statistics);
  void DropEveryNthPacket(int n);
  virtual int SendPacket(int channel, const void* data, size_t len) OVERRIDE;
  virtual int SendRTCPPacket(int channel,
                             const void* data,
                             size_t len) OVERRIDE;

 private:
  int count_;
  int packet_loss_;
  ReceiveStatistics* receive_statistics_;
  RTPPayloadRegistry* rtp_payload_registry_;
  RtpReceiver* rtp_receiver_;
  RtpRtcp* rtp_rtcp_module_;
};

class TestRtpReceiver : public NullRtpData {
 public:
  virtual int32_t OnReceivedPayloadData(
      const uint8_t* payload_data,
      const size_t payload_size,
      const webrtc::WebRtcRTPHeader* rtp_header) OVERRIDE;

  const uint8_t* payload_data() const { return payload_data_; }
  size_t payload_size() const { return payload_size_; }
  webrtc::WebRtcRTPHeader rtp_header() const { return rtp_header_; }

 private:
  uint8_t payload_data_[1500];
  size_t payload_size_;
  webrtc::WebRtcRTPHeader rtp_header_;
};

}  // namespace webrtc
