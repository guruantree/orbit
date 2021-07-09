// Copyright (c) 2021 The Orbit Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "MinorPagefaultTrack.h"

#include <absl/strings/substitute.h>

namespace orbit_gl {

std::string MinorPagefaultTrack::GetTooltip() const {
  return "Shows minor pagefault statistics. A minor pagefault occurs when the requested page "
         "resides in main memory but the process cannot access it.";
}

std::string MinorPagefaultTrack::GetLegendTooltips(size_t legend_index) const {
  switch (static_cast<SeriesIndex>(legend_index)) {
    case SeriesIndex::kProcess:
      return absl::Substitute(
          "<b># of minor pagefaults incurred by the $0 process during the sampling "
          "period.</b><br/><br/>"
          "Derived from the <i>minflt</i> field in file <i>/proc/$1/stat</i>.",
          capture_data_->process_name(), capture_data_->process_id());
    case SeriesIndex::kCGroup:
      return absl::Substitute(
          "<b># of minor pagefaults incurred by the $0 cgroup during the sampling "
          "period.</b><br/><br/>"
          "Derived from <i>pgfault - pgmajfault</i>,"
          "which are two fields in file <i>/sys/fs/cgroup/memory/$0/memory.stat</i>.",
          cgroup_name_);
    case SeriesIndex::kSystem:
      return "<b># of system-wide minor pagefaults occurred during the sampling "
             "period.</b><br/><br/>"
             "Derived from <i>pgfault - pgmajfault</i>, which are two fields in file "
             "<i>/proc/vmstat</i>.";
    default:
      UNREACHABLE();
  }
}

}  // namespace orbit_gl
