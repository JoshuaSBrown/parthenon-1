//========================================================================================
// (C) (or copyright) 2020. Triad National Security, LLC. All rights reserved.
//
// This program was produced under U.S. Government contract 89233218CNA000001 for Los
// Alamos National Laboratory (LANL), which is operated by Triad National Security, LLC
// for the U.S. Department of Energy/National Nuclear Security Administration. All rights
// in the program are reserved by Triad National Security, LLC, and the U.S. Department
// of Energy/National Nuclear Security Administration. The Government is granted for
// itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide
// license in this material to reproduce, prepare derivative works, distribute copies to
// the public, perform publicly and display publicly, and to permit others to do so.
//========================================================================================

// Self Include
#include "Metadata.hpp"

// STL Includes
#include <sstream>
#include <exception>

using parthenon::MetadataFlag;
using parthenon::Metadata;

int Metadata::next_app_flag_ = static_cast<int>(parthenon::internal::MetadataInternal::Max);

MetadataFlag Metadata::AllocateNewFlag() {
    return MetadataFlag(next_app_flag_++);
}