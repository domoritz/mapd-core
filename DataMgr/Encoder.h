#ifndef ENCODER_H
#define ENCODER_H

#include "ChunkMetadata.h"
#include "../Shared/types.h"
#include "../Shared/sqltypes.h"

#include <glog/logging.h>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <limits>

namespace Data_Namespace {
class AbstractBuffer;
}

// default max input buffer size to 1MB
#define MAX_INPUT_BUF_SIZE 1048576

class Encoder {
 public:
  static Encoder* Create(Data_Namespace::AbstractBuffer* buffer, const SQLTypeInfo sqlType);
  Encoder(Data_Namespace::AbstractBuffer* buffer) : numElems(0), buffer_(buffer) {}
  virtual ChunkMetadata appendData(int8_t*& srcData, const size_t numAppendElems) = 0;
  virtual void getMetadata(ChunkMetadata& chunkMetadata);
  // Only called from the executor for synthesized meta-information.
  virtual ChunkMetadata getMetadata(const SQLTypeInfo& ti);
  virtual void updateStats(const int64_t val, const bool is_null);
  virtual void updateStats(const double val, const bool is_null);
  virtual void copyMetadata(const Encoder* copyFromEncoder) = 0;
  virtual void writeMetadata(FILE* f /*, const size_t offset*/) = 0;
  virtual void readMetadata(FILE* f /*, const size_t offset*/) = 0;
  size_t numElems;
  virtual ~Encoder() {}

 protected:
  Data_Namespace::AbstractBuffer* buffer_;
  // ChunkMetadata metadataTemplate_;
};

#endif  // Encoder_h
