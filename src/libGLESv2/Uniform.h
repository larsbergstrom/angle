//
// Copyright (c) 2010-2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef LIBGLESV2_UNIFORM_H_
#define LIBGLESV2_UNIFORM_H_

#include <string>
#include <vector>

#define GL_APICALL
#include <GLES3/gl3.h>
#include <GLES2/gl2.h>

#include "common/debug.h"
#include "angletypes.h"
#include "compiler/Uniform.h"

namespace gl
{

// Helper struct representing a single shader uniform
struct Uniform
{
    Uniform(GLenum type, GLenum precision, const std::string &name, unsigned int arraySize, const int blockIndex, const sh::BlockMemberInfo &blockInfo);

    ~Uniform();

    bool isArray() const;
    unsigned int elementCount() const;
    bool isReferencedByVertexShader() const;
    bool isReferencedByFragmentShader() const;
    bool isInDefaultBlock() const;

    const GLenum type;
    const GLenum precision;
    const std::string name;
    const unsigned int arraySize;
    const int blockIndex;
    const sh::BlockMemberInfo blockInfo;

    unsigned char *data;
    bool dirty;

    unsigned int psRegisterIndex;
    unsigned int vsRegisterIndex;
    unsigned int registerCount;
};

typedef std::vector<Uniform*> UniformArray;

// Helper struct representing a single shader uniform block
struct UniformBlock
{
    // use GL_INVALID_INDEX for non-array elements
    UniformBlock(const std::string &name, unsigned int elementIndex, unsigned int dataSize);

    bool isArrayElement() const;
    bool isReferencedByVertexShader() const;
    bool isReferencedByFragmentShader() const;

    const std::string name;
    const unsigned int elementIndex;
    const unsigned int dataSize;

    std::vector<unsigned int> memberUniformIndexes;

    unsigned int psRegisterIndex;
    unsigned int vsRegisterIndex;
};

typedef std::vector<UniformBlock*> UniformBlockArray;

}

#endif   // LIBGLESV2_UNIFORM_H_