// Copyright (c) 2020 The Orbit Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ORBIT_GL_SCHEDULER_TRACK_H_
#define ORBIT_GL_SCHEDULER_TRACK_H_

#include <string>

#include "CallstackThreadBar.h"
#include "CoreMath.h"
#include "PickingManager.h"
#include "TimerTrack.h"
#include "Track.h"
#include "Viewport.h"
#include "capture_data.pb.h"

class OrbitApp;

class SchedulerTrack final : public TimerTrack {
 public:
  explicit SchedulerTrack(CaptureViewElement* parent, TimeGraph* time_graph,
                          orbit_gl::Viewport* viewport, TimeGraphLayout* layout, OrbitApp* app,
                          const orbit_client_data::CaptureData* capture_data,
                          orbit_client_data::TimerData* timer_data);
  ~SchedulerTrack() override = default;
  void OnTimer(const orbit_client_protos::TimerInfo& timer_info) override;

  [[nodiscard]] std::string GetName() const override { return "Scheduler"; }
  [[nodiscard]] std::string GetLabel() const override {
    return absl::StrFormat("Scheduler (%u cores)", num_cores_);
  }
  [[nodiscard]] Type GetType() const override { return Type::kSchedulerTrack; }
  [[nodiscard]] std::string GetTooltip() const override;

  [[nodiscard]] float GetHeight() const override;
  [[nodiscard]] bool IsCollapsible() const override { return false; }

  [[nodiscard]] float GetDefaultBoxHeight() const override { return layout_->GetTextCoresHeight(); }
  [[nodiscard]] float GetYFromTimer(
      const orbit_client_protos::TimerInfo& timer_info) const override;
  [[nodiscard]] std::vector<const orbit_client_protos::TimerInfo*> GetScopesInRange(
      uint64_t start_ns, uint64_t end_ns) const;

 protected:
  [[nodiscard]] bool IsTimerActive(const orbit_client_protos::TimerInfo& timer_info) const override;
  [[nodiscard]] Color GetTimerColor(const orbit_client_protos::TimerInfo& timer_info,
                                    bool is_selected, bool is_highlighted,
                                    const internal::DrawData& draw_data) const override;
  [[nodiscard]] std::string GetBoxTooltip(const Batcher& batcher, PickingId id) const override;

 private:
  uint32_t num_cores_;
};

#endif  // ORBIT_GL_SCHEDULER_TRACK_H_
