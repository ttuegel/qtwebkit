/*
 * Copyright (C) 2011 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#ifndef DFGNodeReferenceBlob_h
#define DFGNodeReferenceBlob_h

#include <wtf/Platform.h>

#if ENABLE(DFG_JIT)

#include "DFGCommon.h"
#include "DFGNodeUse.h"

namespace JSC { namespace DFG {

class NodeReferenceBlob {
public:
    enum Kind {
        Fixed,
        Variable
    };

    NodeReferenceBlob(Kind kind)
#if !ASSERT_DISABLED
        : m_kind(kind)
#endif
    {
        if (kind == Variable) {
            m_words[0].m_encodedWord = UINT_MAX;
            m_words[1].m_encodedWord = UINT_MAX;
        }
    }
    
    NodeReferenceBlob(Kind kind, NodeIndex child1, NodeIndex child2, NodeIndex child3)
#if !ASSERT_DISABLED
        : m_kind(Fixed)
#endif
    {
        ASSERT_UNUSED(kind, kind == Fixed);
        initialize(child1, child2, child3);
    }
    
    NodeReferenceBlob(Kind kind, unsigned firstChild, unsigned numChildren)
#if !ASSERT_DISABLED
        : m_kind(Variable)
#endif
    {
        ASSERT_UNUSED(kind, kind == Variable);
        setFirstChild(firstChild);
        setNumChildren(numChildren);
    }
    
    const NodeUse& child(unsigned i) const
    {
        ASSERT(i < 3);
        ASSERT(m_kind == Fixed);
        return m_words[i];
    }    
    
    NodeUse& child(unsigned i)
    {
        ASSERT(i < 3);
        ASSERT(m_kind == Fixed);
        return m_words[i];
    }
    
    void setChild(unsigned i, NodeUse nodeUse)
    {
        ASSERT(i < 30);
        ASSERT(m_kind == Fixed);
        m_words[i] = nodeUse;
    }
    
    NodeUse child1() const { return child(0); }
    NodeUse child2() const { return child(1); }
    NodeUse child3() const { return child(2); }

    NodeUse& child1() { return child(0); }
    NodeUse& child2() { return child(1); }
    NodeUse& child3() { return child(2); }
    
    void setChild1(NodeUse nodeUse) { setChild(0, nodeUse); }
    void setChild2(NodeUse nodeUse) { setChild(1, nodeUse); }
    void setChild3(NodeUse nodeUse) { setChild(2, nodeUse); }
    
    NodeUse child1Unchecked() const { return m_words[0]; }
    
    void initialize(NodeUse child1, NodeUse child2, NodeUse child3)
    {
        child(0) = child1;
        child(1) = child2;
        child(2) = child3;
    }
    
    void initialize(NodeIndex child1, NodeIndex child2, NodeIndex child3)
    {
        initialize(NodeUse(child1), NodeUse(child2), NodeUse(child3));
    }

    unsigned firstChild() const
    {
        ASSERT(m_kind == Variable);
        return m_words[0].m_encodedWord;
    }
    void setFirstChild(unsigned firstChild)
    {
        ASSERT(m_kind == Variable);
        m_words[0].m_encodedWord = firstChild;
    }
    
    unsigned numChildren() const
    {
        ASSERT(m_kind == Variable);
        return m_words[1].m_encodedWord;
    }
    void setNumChildren(unsigned numChildren)
    {
        ASSERT(m_kind == Variable);
        m_words[1].m_encodedWord = numChildren;
    }
    
private:
    NodeUse m_words[3];
#if !ASSERT_DISABLED
    Kind m_kind;
#endif
};

} } // namespace JSC::DFG

#endif // ENABLE(DFG_JIT)

#endif // DFGNodeReferenceBlob_h
