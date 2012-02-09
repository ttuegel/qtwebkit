/*
 * Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#include "config.h"
#include "HTMLSummaryElement.h"

#if ENABLE(DETAILS)

#include "DetailsMarkerControl.h"
#include "HTMLContentElement.h"
#include "HTMLDetailsElement.h"
#include "HTMLNames.h"
#include "MouseEvent.h"
#include "PlatformMouseEvent.h"
#include "RenderSummary.h"

#include "ShadowRoot.h"

namespace WebCore {

using namespace HTMLNames;

class SummaryContentElement : public HTMLContentElement {
public:
    static PassRefPtr<SummaryContentElement> create(Document*);

private:
    SummaryContentElement(Document* document)
        : HTMLContentElement(HTMLNames::divTag, document)
    {
    }
};

PassRefPtr<SummaryContentElement> SummaryContentElement::create(Document* document)
{
    return adoptRef(new SummaryContentElement(document));
}

PassRefPtr<HTMLSummaryElement> HTMLSummaryElement::create(const QualifiedName& tagName, Document* document)
{
    RefPtr<HTMLSummaryElement> result = adoptRef(new HTMLSummaryElement(tagName, document));
    result->createShadowSubtree();
    return result;
}

HTMLSummaryElement::HTMLSummaryElement(const QualifiedName& tagName, Document* document)
    : HTMLElement(tagName, document)
{
    ASSERT(hasTagName(summaryTag));
}

RenderObject* HTMLSummaryElement::createRenderer(RenderArena* arena, RenderStyle*)
{
    return new (arena) RenderSummary(this);
}

void HTMLSummaryElement::createShadowSubtree()
{
    ASSERT(!shadowRoot());
    RefPtr<ShadowRoot> root = ShadowRoot::create(this, ShadowRoot::CreatingUserAgentShadowRoot);
    root->appendChild(DetailsMarkerControl::create(document()), ASSERT_NO_EXCEPTION, true);
    root->appendChild(SummaryContentElement::create(document()), ASSERT_NO_EXCEPTION, true);
}

HTMLDetailsElement* HTMLSummaryElement::detailsElement() const
{
    Node* mayDetails = const_cast<HTMLSummaryElement*>(this)->parentNodeForRenderingAndStyle();
    if (!mayDetails || !mayDetails->hasTagName(detailsTag))
        return 0;
    return static_cast<HTMLDetailsElement*>(mayDetails);
}

bool HTMLSummaryElement::isMainSummary() const
{
    if (HTMLDetailsElement* details = detailsElement())
        return details->findMainSummary() == this;

    return false;
}

static bool isClickableControl(Node* node)
{
    if (!node->isElementNode())
        return false;
    Element* element = toElement(node);
    if (element->isFormControlElement())
        return true;
    Element* host = toElement(element->shadowAncestorNode());
    return host && host->isFormControlElement();
}

void HTMLSummaryElement::defaultEventHandler(Event* event)
{
    HTMLElement::defaultEventHandler(event);
    if (!isMainSummary() || !renderer() || !renderer()->isSummary() || !event->isMouseEvent() || event->type() != eventNames().clickEvent || event->defaultHandled())
        return;
    MouseEvent* mouseEvent = static_cast<MouseEvent*>(event);
    if (mouseEvent->button() != LeftButton)
        return;
    if (isClickableControl(event->target()->toNode()))
        return;

    if (HTMLDetailsElement* details = detailsElement())
        details->toggleOpen();
    event->setDefaultHandled();
}

}

#endif
