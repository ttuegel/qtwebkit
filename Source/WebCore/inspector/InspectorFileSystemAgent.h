/*
 * Copyright (C) 2011, 2012 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
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

#ifndef InspectorFileSystemAgent_h
#define InspectorFileSystemAgent_h

#if ENABLE(INSPECTOR) && ENABLE(FILE_SYSTEM)

#include "InspectorBaseAgent.h"
#include "InspectorFrontend.h"

#include <wtf/PassOwnPtr.h>
#include <wtf/PassRefPtr.h>

namespace WebCore {

class DOMFileSystem;
class InspectorFrontend;
class InspectorPageAgent;
class InspectorState;
class InstrumentingAgents;
class ScriptExecutionContext;
class SecurityOrigin;

class InspectorFileSystemAgent : public InspectorBaseAgent<InspectorFileSystemAgent>, public InspectorBackendDispatcher::FileSystemCommandHandler {
public:
    class FrontendProvider;

    static PassOwnPtr<InspectorFileSystemAgent> create(InstrumentingAgents*, InspectorPageAgent*, InspectorState*);
    virtual ~InspectorFileSystemAgent();

    virtual void enable(ErrorString*) OVERRIDE;
    virtual void disable(ErrorString*) OVERRIDE;

    virtual void requestFileSystemRoot(ErrorString*, const String& origin, const String& type, int* requestId) OVERRIDE;
    virtual void requestDirectoryContent(ErrorString*, const String& url, int* requestId) OVERRIDE;
    virtual void requestMetadata(ErrorString*, const String& url, int* requestId) OVERRIDE;

    virtual void setFrontend(InspectorFrontend*) OVERRIDE;
    virtual void clearFrontend() OVERRIDE;
    virtual void restore() OVERRIDE;

private:
    InspectorFileSystemAgent(InstrumentingAgents*, InspectorPageAgent*, InspectorState*);
    ScriptExecutionContext* scriptExecutionContextForOrigin(SecurityOrigin*);

    InspectorPageAgent* m_pageAgent;
    RefPtr<FrontendProvider> m_frontendProvider;
    bool m_enabled;
    int m_nextRequestId;
};

} // namespace WebCore

#endif // ENABLE(INSPECTOR) && ENABLE(FILE_SYSTEM)
#endif // InspectorFileSystemAgent_h
