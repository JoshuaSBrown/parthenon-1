//========================================================================================
// Athena++ astrophysical MHD code
// Copyright(C) 2014 James M. Stone <jmstone@princeton.edu> and other code contributors
// Licensed under the 3-clause BSD License, see LICENSE file for details
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
#ifndef OUTPUTS_IO_WRAPPER_HPP_
#define OUTPUTS_IO_WRAPPER_HPP_
//! \file io_wrapper.hpp
//  \brief defines a set of small wrapper functions for MPI versus Serial Output.

// C headers

// C++ headers
#include <cstdio>

// Athena++ headers
#include "athena.hpp"

#ifdef MPI_PARALLEL
#include <mpi.h>
#endif

namespace parthenon {
#ifdef MPI_PARALLEL
using IOWrapperFile = MPI_File;
#else
using IOWrapperFile = FILE *;
#endif

using IOWrapperSizeT = std::uint64_t;

class IOWrapper {
  public:
#ifdef MPI_PARALLEL
    IOWrapper() : fh_(nullptr), comm_(MPI_COMM_WORLD) {}
    void SetCommunicator(MPI_Comm scomm) { comm_ = scomm; }
#else
    IOWrapper() { fh_ = nullptr; }
#endif
    ~IOWrapper() {}
    // nested type definition of strongly typed/scoped enum in class definition
    enum class FileMode { read, write };

    // wrapper functions for basic I/O tasks
    int Open(const char *fname, FileMode rw);
    std::size_t Read(void *buf, IOWrapperSizeT size, IOWrapperSizeT count);
    std::size_t Read_all(void *buf, IOWrapperSizeT size, IOWrapperSizeT count);
    std::size_t Read_at_all(void *buf,
                            IOWrapperSizeT size,
                            IOWrapperSizeT count,
                            IOWrapperSizeT offset);
    std::size_t Write(const void *buf, IOWrapperSizeT size, IOWrapperSizeT count);
    std::size_t Write_at_all(const void *buf,
                             IOWrapperSizeT size,
                             IOWrapperSizeT cnt,
                             IOWrapperSizeT offset);
    int Close();
    int Seek(IOWrapperSizeT offset);
    IOWrapperSizeT GetPosition();

  private:
    IOWrapperFile fh_;
#ifdef MPI_PARALLEL
    MPI_Comm comm_;
#endif
};

} // namespace parthenon

#endif // OUTPUTS_IO_WRAPPER_HPP_
