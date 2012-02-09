/*
 * Copyright (C) 2011 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ShadowRoot_h
#define ShadowRoot_h

#include "DocumentFragment.h"
#include "ExceptionCode.h"
#include "TreeScope.h"

namespace WebCore {

class ContentInclusionSelector;
class Document;
class HTMLContentElement;

class ShadowRoot : public DocumentFragment, public TreeScope {
public:
    static PassRefPtr<ShadowRoot> create(Document*);
    static PassRefPtr<ShadowRoot> create(Element*, ExceptionCode&);

    // FIXME: We will support multiple shadow subtrees, however current implementation does not work well
    // if a shadow root is dynamically created. So we prohibit multiple shadow subtrees
    // in several elements for a while.
    // See https://bugs.webkit.org/show_bug.cgi?id=77503 and related bugs.
    enum ShadowRootCreationPurpose {
        CreatingUserAgentShadowRoot,
        CreatingAuthorShadowRoot,
    };
    static PassRefPtr<ShadowRoot> create(Element*, ShadowRootCreationPurpose, ExceptionCode& = ASSERT_NO_EXCEPTION);

    void recalcShadowTreeStyle(StyleChange);

    void setNeedsReattachHostChildrenAndShadow();
    void clearNeedsReattachHostChildrenAndShadow();
    bool needsReattachHostChildrenAndShadow();

    HTMLContentElement* includerFor(Node*) const;
    void hostChildrenChanged();
    bool isInclusionSelectorActive() const;

    virtual void attach();
    void reattachHostChildrenAndShadow();

    virtual bool applyAuthorSheets() const;
    void setApplyAuthorSheets(bool);

    Element* host() const { return shadowHost(); }

    ContentInclusionSelector* inclusions() const;
    ContentInclusionSelector* ensureInclusions();

private:
    ShadowRoot(Document*);
    virtual ~ShadowRoot();

    virtual String nodeName() const;
    virtual NodeType nodeType() const;
    virtual PassRefPtr<Node> cloneNode(bool deep);
    virtual bool childTypeAllowed(NodeType) const;

    bool hasContentElement() const;

    bool m_applyAuthorSheets : 1;
    bool m_needsRecalculateContent : 1;
    OwnPtr<ContentInclusionSelector> m_inclusions;
};

inline PassRefPtr<ShadowRoot> ShadowRoot::create(Document* document)
{
    return adoptRef(new ShadowRoot(document));
}

inline void ShadowRoot::clearNeedsReattachHostChildrenAndShadow()
{
    m_needsRecalculateContent = false;
}

inline bool ShadowRoot::needsReattachHostChildrenAndShadow()
{
    return m_needsRecalculateContent || hasContentElement();
}

inline ShadowRoot* toShadowRoot(Node* node)
{
    ASSERT(!node || node->nodeType() == Node::SHADOW_ROOT_NODE);
    return static_cast<ShadowRoot*>(node);
}

} // namespace

#endif
