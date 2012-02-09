/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
*/

#include "config.h"
#include "V8TestEventConstructor.h"

#include "OptionsObject.h"
#include "RuntimeEnabledFeatures.h"
#include "V8Binding.h"
#include "V8BindingMacros.h"
#include "V8BindingState.h"
#include "V8DOMWrapper.h"
#include "V8IsolatedContext.h"
#include "V8Proxy.h"
#include <wtf/UnusedParam.h>

namespace WebCore {

WrapperTypeInfo V8TestEventConstructor::info = { V8TestEventConstructor::GetTemplate, V8TestEventConstructor::derefObject, 0, 0 };

namespace TestEventConstructorInternal {

template <typename T> void V8_USE(T) { }

static v8::Handle<v8::Value> attr1AttrGetter(v8::Local<v8::String> name, const v8::AccessorInfo& info)
{
    INC_STATS("DOM.TestEventConstructor.attr1._get");
    TestEventConstructor* imp = V8TestEventConstructor::toNative(info.Holder());
    return v8String(imp->attr1());
}

static v8::Handle<v8::Value> attr2AttrGetter(v8::Local<v8::String> name, const v8::AccessorInfo& info)
{
    INC_STATS("DOM.TestEventConstructor.attr2._get");
    TestEventConstructor* imp = V8TestEventConstructor::toNative(info.Holder());
    return v8String(imp->attr2());
}

} // namespace TestEventConstructorInternal

static const BatchedAttribute TestEventConstructorAttrs[] = {
    // Attribute 'attr1' (Type: 'readonly attribute' ExtAttr: '')
    {"attr1", TestEventConstructorInternal::attr1AttrGetter, 0, 0 /* no data */, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
    // Attribute 'attr2' (Type: 'readonly attribute' ExtAttr: 'InitializedByEventConstructor')
    {"attr2", TestEventConstructorInternal::attr2AttrGetter, 0, 0 /* no data */, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
};

v8::Handle<v8::Value> V8TestEventConstructor::constructorCallback(const v8::Arguments& args)
{
    INC_STATS("DOM.TestEventConstructor.Constructor");

    if (!args.IsConstructCall())
        return throwError("DOM object constructor cannot be called as a function.", V8Proxy::TypeError);

    if (ConstructorMode::current() == ConstructorMode::WrapExistingObject)
        return args.Holder();

    if (args.Length() < 1)
        return throwError("Not enough arguments", V8Proxy::TypeError);

    STRING_TO_V8PARAMETER_EXCEPTION_BLOCK(V8Parameter<>, type, args[0]);
    TestEventConstructorInit eventInit;
    if (args.Length() >= 2) {
        EXCEPTION_BLOCK(OptionsObject, options, args[1]);
        if (!fillTestEventConstructorInit(eventInit, options))
            return v8::Undefined();
    }

    RefPtr<TestEventConstructor> event = TestEventConstructor::create(type, eventInit);

    V8DOMWrapper::setDOMWrapper(args.Holder(), &info, event.get());
    return toV8(event.release(), args.Holder());
}

bool fillTestEventConstructorInit(TestEventConstructorInit& eventInit, const OptionsObject& options)
{
    options.get("attr2", eventInit.attr2);
    return true;
}

static v8::Persistent<v8::FunctionTemplate> ConfigureV8TestEventConstructorTemplate(v8::Persistent<v8::FunctionTemplate> desc)
{
    desc->ReadOnlyPrototype();

    v8::Local<v8::Signature> defaultSignature;
    defaultSignature = configureTemplate(desc, "TestEventConstructor", v8::Persistent<v8::FunctionTemplate>(), V8TestEventConstructor::internalFieldCount,
        TestEventConstructorAttrs, WTF_ARRAY_LENGTH(TestEventConstructorAttrs),
        0, 0);
    UNUSED_PARAM(defaultSignature); // In some cases, it will not be used.
    desc->SetCallHandler(V8TestEventConstructor::constructorCallback);
    

    // Custom toString template
    desc->Set(getToStringName(), getToStringTemplate());
    return desc;
}

v8::Persistent<v8::FunctionTemplate> V8TestEventConstructor::GetRawTemplate()
{
    V8BindingPerIsolateData* data = V8BindingPerIsolateData::current();
    V8BindingPerIsolateData::TemplateMap::iterator result = data->rawTemplateMap().find(&info);
    if (result != data->rawTemplateMap().end())
        return result->second;

    v8::HandleScope handleScope;
    v8::Persistent<v8::FunctionTemplate> templ = createRawTemplate();
    data->rawTemplateMap().add(&info, templ);
    return templ;
}

v8::Persistent<v8::FunctionTemplate> V8TestEventConstructor::GetTemplate()
{
    V8BindingPerIsolateData* data = V8BindingPerIsolateData::current();
    V8BindingPerIsolateData::TemplateMap::iterator result = data->templateMap().find(&info);
    if (result != data->templateMap().end())
        return result->second;

    v8::HandleScope handleScope;
    v8::Persistent<v8::FunctionTemplate> templ =
        ConfigureV8TestEventConstructorTemplate(GetRawTemplate());
    data->templateMap().add(&info, templ);
    return templ;
}

bool V8TestEventConstructor::HasInstance(v8::Handle<v8::Value> value)
{
    return GetRawTemplate()->HasInstance(value);
}


v8::Handle<v8::Object> V8TestEventConstructor::wrapSlow(TestEventConstructor* impl)
{
    v8::Handle<v8::Object> wrapper;
    V8Proxy* proxy = 0;
    wrapper = V8DOMWrapper::instantiateV8Object(proxy, &info, impl);
    if (wrapper.IsEmpty())
        return wrapper;

    impl->ref();
    v8::Persistent<v8::Object> wrapperHandle = v8::Persistent<v8::Object>::New(wrapper);

    if (!hasDependentLifetime)
        wrapperHandle.MarkIndependent();
    getDOMObjectMap().set(impl, wrapperHandle);
    return wrapper;
}

void V8TestEventConstructor::derefObject(void* object)
{
    static_cast<TestEventConstructor*>(object)->deref();
}

} // namespace WebCore
